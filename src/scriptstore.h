#ifndef NUMAI_SCRIPTSTORE_H
#define NUMAI_SCRIPTSTORE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct {
    uint8_t *records;
    size_t capacity;
} ScriptStore;

typedef struct {
    const char *name;
    const char *source;
    size_t size;
} ScriptRecord;

// An empty store represents an unsupported firmware or invalid record table.
ScriptStore calculator_script_store(void);
bool script_record_next(ScriptStore store, size_t *position, ScriptRecord *record);
bool script_record_save(ScriptStore store, const char *name, const char *owner,
                        const char *source, size_t size);

#endif
