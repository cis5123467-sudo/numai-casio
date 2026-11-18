#include "scriptstore.h"

#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

static bool flush_store(ScriptStore store);

static unsigned read_size(const uint8_t *p) {
    return p[0] | (unsigned)p[1] << 8;
}

bool script_record_next(ScriptStore store, size_t *position, ScriptRecord *record) {
    if (!store.records || *position > store.capacity || store.capacity - *position < 2) return false;
    const uint8_t *start = store.records + *position;
    unsigned length = read_size(start);
    if (length < 4 || length > store.capacity - *position - 2) return false;
    const char *name = (const char *)start + 2;
    const char *name_end = memchr(name, 0, length - 2);
    if (!name_end || name == name_end) return false;
    size_t size = length - (size_t)(name_end + 1 - (const char *)start);
    *position += length;
    *record = (ScriptRecord){name, size >= 2 ? name_end + 2 : NULL, size >= 2 ? size - 1 : 0};
    return true;
}

static bool valid_store(ScriptStore store) {
    size_t position = 0;
    ScriptRecord record;
    while (script_record_next(store, &position, &record)) {}
    return store.records && store.capacity - position >= 2 && !read_size(store.records + position);
}

bool script_record_save(ScriptStore store, const char *name, const char *owner,
                        const char *source, size_t size) {
    if (!valid_store(store) || size < 2 || source[size - 1] != '\0') return false;
    size_t position = 0;
    ScriptRecord record;
    while (script_record_next(store, &position, &record)) {
        if (strcmp(record.name, name)) continue;
        size_t owner_length = strlen(owner);
        if (record.size != size || size <= owner_length || strncmp(record.source, owner, owner_length))
            return false;
        // Same-size replacement leaves firmware record pointers and names intact.
        memcpy((char *)record.source, source, size);
        return flush_store(store);
    }
    size_t name_size = strlen(name) + 1, needed = 3 + name_size + size;
    if (needed > UINT16_MAX || needed + 2 > store.capacity - position) return false;
    uint8_t *start = store.records + position;
    memcpy(start + 2, name, name_size);
    start[2 + name_size] = 0; // Do not auto-import this script in the Python shell.
    memcpy(start + 3 + name_size, source, size);
    start[needed] = start[needed + 1] = 0;
    // Publish the new record after its payload and end marker are in place.
    __asm__ volatile("" ::: "memory");
    start[1] = (uint8_t)(needed >> 8);
    start[0] = (uint8_t)needed;
    return flush_store(store);
}

enum { StoreSize = 42 * 1024 };
static uint8_t storage[StoreSize];

static bool write_file(const char *name, const uint8_t *data, size_t size) {
    int fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd < 0) return false;
    bool ok = true;
    while (size) {
        ssize_t written = write(fd, data, size);
        if (written <= 0) { ok = false; break; }
        data += written;
        size -= (size_t)written;
    }
    if (close(fd) < 0) ok = false;
    return ok;
}

static bool flush_store(ScriptStore store) {
    size_t position = 0;
    ScriptRecord record;
    while (script_record_next(store, &position, &record)) {}
    if (!write_file("/numai.tmp", store.records, position + 2)) return false;
    // The completed temporary file also provides recovery if a rename fails.
    unlink("/numai.bak");
    bool previous = rename("/numai.sav", "/numai.bak") == 0;
    if (rename("/numai.tmp", "/numai.sav") == 0) return true;
    if (previous) rename("/numai.bak", "/numai.sav");
    return false;
}

static bool load_store(const char *path) {
    int fd = open(path, O_RDONLY);
    if (fd < 0) return false;
    size_t count = 0;
    while (count < sizeof(storage)) {
        ssize_t amount = read(fd, storage + count, sizeof(storage) - count);
        if (amount < 0) { close(fd); return false; }
        if (!amount) break;
        count += (size_t)amount;
    }
    close(fd);
    if (count < 2) return false;
    return valid_store((ScriptStore){storage, count});
}

ScriptStore calculator_script_store(void) {
    if (!load_store("/numai.sav") && !load_store("/numai.tmp") && !load_store("/numai.bak"))
        memset(storage, 0, sizeof(storage));
    return (ScriptStore){storage, sizeof(storage)};
}
