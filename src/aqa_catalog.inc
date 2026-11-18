/* Original revision summaries keyed to the AQA separate-science specifications.
 * H marks both whole Higher-only subsections and the Higher-only parts split
 * out of mixed-tier subsections. Foundation material stays in the S cards. */
#define S(id, heading, notes) { .title = heading, .course = id "\n\nKey ideas\n- " notes, .example = SCIENCE_MORE }
#define H(id, title, notes) S(id, title " (higher only)", notes)

#undef SCIENCE_MORE
#define SCIENCE_MORE "\n\nUnderstand the mechanism\n- Explain structure and function together. A large surface area gives more membrane through which material can move; a short diffusion path reduces the distance travelled. Mitochondria supply energy through aerobic respiration, while ribosomes assemble proteins.\n\nApply your understanding\n- Microscope images show a two-dimensional section of a three-dimensional cell. Use the scale bar rather than the size of the printed image, keep image and actual size in matching units, and distinguish magnification from resolving detail."
static const Topic bio_cells[] = {
    S("4.1.1.1", "Eukaryotes and prokaryotes", "Animal and plant cells contain DNA inside a nucleus. Bacteria are smaller, lack a nucleus and have a circular chromosome in the cytoplasm. They may also have plasmids."
      "\n\n- " "Compare where DNA is held, rather than saying bacteria lack DNA. Both cell types have a membrane, cytoplasm and ribosomes. Some bacteria also have a cell wall."),
    S("4.1.1.2", "Animal and plant cells", "Nucleus: genetic control. Cytoplasm: reaction site. Membrane: controls movement. Mitochondria: aerobic respiration. Ribosomes: protein synthesis. Plants also have a cellulose wall, a permanent vacuole and, in photosynthetic cells, chloroplasts."
      "\n\n- " "A cheek cell lacks a cell wall; a palisade cell has many chloroplasts. An onion bulb epidermal cell is a plant cell even without visible chloroplasts."),
    S("4.1.1.3", "Cell specialisation", "A sperm has a tail and many mitochondria. Neurones conduct impulses over long distances. Muscle cells contract. Root hair cells absorb water and ions; xylem and phloem move materials through plants."
      "\n\n- " "Link each feature to function: a long axon conducts impulses farther, and the root hair's projection enlarges the area available for uptake."),
    S("4.1.1.4", "Cell differentiation", "Differentiation gives cells different structures and roles. Most animal cells specialise early. Many plant cells can differentiate throughout life. Cell division in mature animals mainly replaces or repairs cells."
      "\n\n- " "Differentiated cells usually contain the same genetic information, but express different genes. A palisade cell and a root hair cell therefore make different proteins."),
    S("4.1.1.5", "Microscopy", "Magnification = image size / real size. Convert both sizes to the same units. Electron microscopes resolve much finer detail than light microscopes because their resolution is higher."
      "\n\n- " "If an image is 30 mm long and the cell is 60 micrometres, convert 30 mm to 30000 micrometres first. Magnification is 30000/60 = x500. Resolution means distinguishing two close points."),
    S("4.1.1.6", "Microorganisms and cultures", "Bacteria reproduce by binary fission. Every generation doubles the population if conditions stay favourable. A lawn on agar can show clear inhibition zones. Aseptic practice limits contamination; school cultures have restricted incubation conditions."
      "\n\n- " "A generation doubles the count, not the diameter of a colony. Starting with 20 cells, four ideal generations give 20*2^4=320; a real culture eventually runs short of resources."),
    H("4.1.1.6", "Culture area: standard form", "Use area = pi*r^2 for a circular clear zone. A radius of 5 mm gives 78.5 mm^2, or 7.85*10^1 mm^2. Keep track of squared units."
      "\n\n- " "If the clear diameter is 18 mm, radius is 9 mm and area is about 254 mm^2, or 2.54*10^2 mm^2. A doubled diameter means four times the area."),
    S("4.1.2.1", "Chromosomes", "Chromosomes are long DNA molecules carrying genes. Body cells usually have their chromosomes in pairs, with one chromosome of each pair from each parent."
      "\n\n- " "A human body cell normally has 46 chromosomes in 23 pairs. A gene is a section of DNA, whereas a chromosome is a long package of DNA containing many genes."),
    S("4.1.2.2", "Mitosis and the cell cycle", "The cell grows and copies its DNA. During mitosis chromosome copies separate into two nuclei. The cytoplasm and membrane then divide, giving two genetically identical cells for growth and repair."
      "\n\n- " "After DNA replication, sister copies separate; chromosome number per daughter cell stays the same. A human skin cell produces two cells with 46 chromosomes apiece."),
    S("4.1.2.3", "Stem cells", "Embryonic stem cells can form many cell types. Adult bone marrow stem cells form blood cells. Plant meristems can form many plant tissues. Compare possible cell-replacement benefits with rejection, infection and ethical concerns."
      "\n\n- " "A patient's own cells may reduce rejection. Compare a broad differentiation potential with the risks of uncontrolled growth and ethical objections to particular cell sources."),
    S("4.1.3.1", "Diffusion", "Particles spread from higher to lower concentration. A larger gradient, warmer conditions and larger surface area can increase rate. Exchange surfaces also have a short diffusion path and often a good blood supply or ventilation."
      "\n\n- " "Diffusion gives net movement down the gradient even though individual particles move randomly in both directions. Oxygen moves from alveoli into blood with lower oxygen concentration."),
    S("4.1.3.2", "Osmosis", "Water moves across a partially permeable membrane towards a more concentrated solution. Plant cells gain mass in dilute solutions and lose mass in more concentrated ones. No net mass change suggests matching concentrations."
      "\n\n- " "In dilute solution the vacuole swells and presses against the wall, making the cell turgid. Water loss makes it flaccid; severe loss can pull the cell membrane away from the wall."),
    S("4.1.3.3", "Active transport", "Active transport moves substances against a concentration gradient and requires energy from respiration. Roots take up dilute mineral ions; the small intestine can absorb glucose against its gradient."
      "\n\n- " "If mineral concentration is already larger inside the root hair, diffusion cannot explain net uptake from soil. Respiration supplies energy to carrier proteins that move ions inward.")
};

#undef SCIENCE_MORE
#define SCIENCE_MORE "\n\nUnderstand the mechanism\n- Follow substances through an organ system. Digested small molecules enter the blood and are delivered to cells; oxygen is absorbed at exchange surfaces and carried by haemoglobin. Cells use the supplied materials, while waste products must be removed.\n\nApply your understanding\n- Enzymes are specific because substrates fit their active sites. Temperature affects particle movement and collisions; very high temperatures change the active site's shape. Explain a change in rate using this mechanism and distinguish digestion from respiration."
static const Topic bio_org[] = {
    S("4.2.1", "Levels of organisation", "Cells form tissues. Several tissues work together in an organ. Organs work together in systems. A leaf, for example, contains tissues for photosynthesis, support, transport and gas exchange."
      "\n\n- " "A tissue is a group of cells carrying out a function. Stomach muscle contracts, gland tissue secretes substances and epithelium lines the stomach; together they make an organ."),
    S("4.2.2.1", "Digestion and enzymes", "Carbohydrases break carbohydrate into simple sugars, proteases act on proteins and lipases release fatty acids and glycerol. Enzyme active sites fit their substrates. Heat or extreme pH can change that shape. Bile neutralises acid and emulsifies fats."
      "\n\n- " "Amylase acts on starch; pepsin works in acid. Heating past an optimum can denature an enzyme. Bile is not an enzyme: it disperses fat droplets and changes conditions in the small intestine."),
    S("4.2.2.2", "Heart, lungs and vessels", "The right heart pumps to lungs; the left pumps to the body. Learn the vena cava, pulmonary artery, pulmonary vein and aorta. Valves prevent backflow. Arteries have thick walls, veins have valves and capillaries have thin walls. Alveoli exchange gases."
      "\n\n- " "Follow a red cell: vena cava -> right heart -> pulmonary artery -> lungs -> pulmonary vein -> left heart -> aorta. The left ventricle is thicker because it supplies the whole body."),
    S("4.2.2.3", "Blood", "Plasma carries dissolved materials and cells. Red blood cells use haemoglobin to carry oxygen. White blood cells defend the body and platelets help form clots."
      "\n\n- " "Red blood cells have a biconcave shape and no nucleus to make room for haemoglobin. Capillary walls are one cell thick, reducing the diffusion distance."),
    S("4.2.2.4", "Coronary heart disease", "Fatty deposits can narrow coronary arteries and reduce oxygen delivery to heart muscle. Stents hold arteries open; statins reduce cholesterol. Compare valve replacements, transplants and artificial hearts by benefit and risk."
      "\n\n- " "A stent quickly restores flow but has surgical and clotting risks. Statins act over time and may have side effects. Compare timescale and risk for the method in the question."),
    S("4.2.2.5", "Health and disease", "Health includes physical and mental wellbeing. Infectious and non-infectious diseases can interact: viral infection can contribute to some cancers, and immune defects make infections more likely."
      "\n\n- " "One disease can predispose people to another. For instance, long-term physical illness can affect mental wellbeing; an immune deficiency can increase susceptibility to infection."),
    S("4.2.2.6", "Lifestyle and risk factors", "Smoking raises the risk of lung disease and heart disease. Alcohol can damage the liver and brain. Obesity is linked to type 2 diabetes. Radiation can raise cancer risk. A correlation needs further evidence before it is treated as causal."
      "\n\n- " "When comparing groups, age and other habits can confound the relationship. Show a plausible biological mechanism and use controls before drawing a causal conclusion."),
    S("4.2.2.7", "Cancer", "Changes in cells can cause uncontrolled division. Benign tumours stay in one place. Malignant cells can spread in the blood and form secondary tumours. Some risks are inherited; others are environmental."
      "\n\n- " "A benign tumour can still cause harm by pressing on an organ. Malignant cells can invade surrounding tissue and be carried to other sites, where they form secondary tumours."),
    S("4.2.3.1", "Plant tissues", "Epidermis protects leaves; palisade cells capture light. Spongy mesophyll has air spaces. Guard cells control stomata. Xylem transports water and minerals; phloem carries dissolved sugars. Meristems produce new cells."
      "\n\n- " "The waxy cuticle reduces evaporation. Palisade cells are near the lit surface; air spaces and stomata shorten the path for carbon dioxide to reach photosynthetic cells."),
    S("4.2.3.2", "Plant transport systems", "Root hairs increase uptake area. Water moves up lignified xylem in the transpiration stream. Light, warmth and air movement often raise transpiration; humid air reduces it. Phloem translocates sugars from sources to sinks."
      "\n\n- " "Xylem carries mostly upward flow in dead hollow vessels. Phloem uses living sieve tubes and can move dissolved sugars in either direction according to source and sink.")
};

#undef SCIENCE_MORE
#define SCIENCE_MORE "\n\nUnderstand the mechanism\n- Separate the pathogen, route of transmission, symptoms and control measure. A control works by breaking part of the transmission route, reducing exposure or helping the immune system recognise an antigen.\n\nApply your understanding\n- Antibodies are specific to antigens. Memory cells help produce a faster response after a later exposure. Antibiotic resistance arises when resistant variants survive treatment and reproduce; individual bacteria do not choose to become resistant."
static const Topic bio_infection[] = {
    S("4.3.1.1", "Communicable diseases", "Pathogens include bacteria, viruses, fungi and protists. They spread by contact, water, air or vectors. Hygiene, isolation, vaccination and controlling vectors reduce transmission."
      "\n\n- " "A vector carries a pathogen between hosts; it is not the pathogen itself. Match prevention to the route, for example clean water for waterborne transmission and hygiene for contact."),
    S("4.3.1.2", "Viral diseases", "Measles spreads in droplets and vaccination limits it. HIV attacks immune cells and can lead to AIDS if untreated. Tobacco mosaic virus causes mottling and reduces photosynthesis."
      "\n\n- " "Measles can cause fever and a rash. Untreated HIV weakens immune defences over time. TMV reduces the green surface able to absorb light, so less carbohydrate is made."),
    S("4.3.1.3", "Bacterial diseases", "Salmonella can spread in food and cause fever and diarrhoea. Gonorrhoea is sexually transmitted. Food hygiene, flock vaccination, barrier contraception and appropriate treatment help limit these infections."
      "\n\n- " "Salmonella symptoms can result from toxins made by bacteria. Gonorrhoea may cause painful urination and discharge. Resistance reduces which antibiotic treatments still work."),
    S("4.3.1.4", "Fungal diseases", "Rose black spot spreads by water or wind. Leaf spots and yellowing reduce photosynthesis. Removing affected material and using fungicides can control the disease."
      "\n\n- " "Damaged leaves may fall early; less green leaf area means less glucose for growth. The dispersal of fungal spores explains why plant spacing and moisture can affect spread."),
    S("4.3.1.5", "Protist diseases", "Malaria is caused by a protist carried by mosquitoes. Nets reduce bites and reducing mosquito breeding can reduce spread."
      "\n\n- " "The mosquito transmits the protist in a bite. Explain that nets reduce contact between vector and humans rather than directly killing the parasite in infected people."),
    S("4.3.1.6", "Human defence systems", "Skin and clots block entry. Nasal hairs, mucus and cilia trap and remove particles; stomach acid kills many pathogens. White blood cells can engulf pathogens or produce specific antibodies and antitoxins."
      "\n\n- " "Distinguish phagocytosis, which takes a pathogen into a cell, from antibodies, which bind a particular antigen. Antitoxins neutralise toxins rather than preventing all infection."),
    S("4.3.1.7", "Vaccination", "Vaccine antigens trigger an immune response and memory. Later exposure produces a faster antibody response. High population coverage reduces the opportunities for a disease to spread."
      "\n\n- " "On a secondary response graph, antibodies rise more rapidly and often to a higher concentration. Explain this with immune memory rather than antibiotics or an immediate cure."),
    S("4.3.1.8", "Antibiotics and painkillers", "Antibiotics target susceptible bacteria. Viruses reproduce inside cells and are unaffected by antibiotics. Painkillers relieve symptoms. Careful antibiotic use reduces selection for resistance."
      "\n\n- " "Pain relief can improve symptoms while infection persists. A resistant bacterium may survive antibiotic treatment and divide, increasing the resistant proportion."),
    S("4.3.1.9", "Discovering and testing drugs", "Examples of drug origins include plants, microbes and synthesis. Preclinical tests investigate toxicity and activity. Clinical trials check safety, dose and efficacy, using placebo, randomisation and blinding where appropriate."
      "\n\n- " "Compare a blinded treatment group with placebo or standard treatment. A double-blind design reduces expectation bias in both participants and assessors; large samples make rare effects easier to detect."),
    H("4.3.2.1", "Monoclonal antibody making", "A hybridoma combines antibody production with the ability to divide. A clone of one selected hybridoma produces identical antibodies recognising one antigen."
      "\n\n- " "The antibody-producing cell gives specificity while the tumour-derived cell allows continuous division. A cloned cell line produces one antibody type, recognising one antigen."),
    H("4.3.2.2", "Monoclonal antibody uses", "A pregnancy test uses antibodies that detect hCG. Tagged antibodies can locate molecules in research or diagnosis. They can deliver treatments to selected cells, though side effects can limit use."
      "\n\n- " "In a lateral-flow test a control line shows liquid moved and the test operated. A missing control line means the result cannot be interpreted reliably."),
    S("4.3.3.1", "Plant pathogens and deficiencies", "Recall tobacco mosaic virus, fungal black spot and aphids. Nitrate deficiency limits protein production and growth. Magnesium deficiency limits chlorophyll and causes yellowing."
      "\n\n- " "Nitrate supplies nitrogen for amino acids. Magnesium shortage can reduce photosynthesis through lower chlorophyll. Similar yellowing can have more than one cause, so look at the full pattern."),
    H("4.3.3.1", "Identifying plant disease", "Look for stunting, spots, rot, abnormal growth, discolouration and pests. Use reference images, laboratory identification or antigen-specific test kits to distinguish possible causes."
      "\n\n- " "Unusual marks are evidence of poor health, not a diagnosis by themselves. Compare affected and healthy plants, check for pests and use an appropriate identification method."),
    S("4.3.3.2", "Plant defences", "Cellulose walls, waxy cuticles and bark are physical barriers. Plants make antibacterial chemicals and poisons. Thorns, hairs and leaf movements discourage herbivores."
      "\n\n- " "Some barriers prevent entry while others discourage feeding. A thistle's spines deter a herbivore; chemicals provide a different, chemical defence.")
};

#undef SCIENCE_MORE
#define SCIENCE_MORE "\n\nUnderstand the mechanism\n- Photosynthesis transfers energy from light into chemical stores. Respiration transfers energy for cellular processes. Plants respire continuously, and photosynthesis occurs only when suitable light is available; gas exchange depends on the relative rates of both processes.\n\nApply your understanding\n- For a limiting factor, explain why raising another factor cannot keep increasing the rate. Use the shape and axes of a graph, compare gradients or plateaus, and support a statement about rate with values from the graph."
static const Topic bio_energy[] = {
    S("4.4.1.1", "Photosynthesis reaction", "Carbon dioxide + water -> glucose + oxygen using light energy absorbed by chlorophyll. Photosynthesis transfers energy into chemical stores and takes place in chloroplasts."
      "\n\n- " "Photosynthesis is endothermic. Write 6CO2 + 6H2O -> C6H12O6 + 6O2. Light is the energy source and chlorophyll absorbs it; neither is consumed as a reactant."),
    S("4.4.1.2", "Photosynthesis rate", "Low light, low carbon dioxide, low chlorophyll or unsuitable temperature can restrict photosynthesis. Raising a limiting factor increases rate until a different factor limits it."
      "\n\n- " "Use oxygen volume per minute as a rate measure in pondweed. At low light adding light helps; a plateau means another factor is limiting under those conditions."),
    H("4.4.1.2", "Limiting-factor graphs", "Compare where rate plateaus at different temperatures or carbon dioxide levels. Light intensity from a point source is proportional to 1/distance^2. In greenhouses, weigh the benefit of faster growth against heating, lighting and carbon dioxide costs."
      "\n\n- " "Moving a lamp from 10 to 20 cm gives about one quarter of the original intensity. At a plateau, compare curves with differing CO2 or temperature to identify the limiting factor."),
    S("4.4.1.3", "Uses of glucose in plants", "Plants use glucose in respiration, make starch and lipids for storage, and build cellulose. They combine sugars with mineral nutrients such as nitrates to make amino acids."
      "\n\n- " "Starch is an insoluble store and cellulose supports cell walls. Nitrate ions provide nitrogen to make amino acids from products of photosynthesis."),
    S("4.4.2.1", "Aerobic and anaerobic respiration", "Aerobic respiration releases energy from glucose with oxygen, producing carbon dioxide and water. Anaerobic respiration releases less energy: muscles make lactic acid, while yeast fermentation produces ethanol and carbon dioxide."
      "\n\n- " "Aerobic respiration transfers energy for contraction, active transport and building molecules. Yeast fermentation produces gas for bread and ethanol in brewing; inhaled oxygen enables complete oxidation."),
    S("4.4.2.2", "Response to exercise", "Heart and breathing rates rise to deliver more oxygen and glucose. If oxygen delivery is insufficient, muscles respire anaerobically, build up lactic acid and fatigue. Recovery involves an oxygen debt."
      "\n\n- " "Muscles need ATP faster as exercise intensifies. Increased circulation and ventilation help, but at high demand oxygen delivery may still fail to match demand."),
    H("4.4.2.2", "Lactic acid and oxygen debt", "Blood transports lactic acid to the liver, where it can be converted to glucose. Oxygen debt is the extra oxygen required after activity to remove accumulated lactic acid."
      "\n\n- " "Raised breathing and heart rate can continue after exercise to repay oxygen debt. Link lactate removal to the liver and explain why fatigue does not disappear instantly."),
    S("4.4.2.3", "Metabolism", "Metabolism is the sum of cell reactions, including respiration and synthesis of carbohydrates, lipids and proteins. Excess amino acids are broken down and urea is formed for excretion."
      "\n\n- " "Examples include converting glucose to glycogen, using glucose to make cellulose, and joining amino acids into proteins. Distinguish building reactions from breakdown.")
};

#undef SCIENCE_MORE
#define SCIENCE_MORE "\n\nUnderstand the mechanism\n- A control system includes receptors, a coordination centre and effectors. Receptors detect changes; a response reduces the original deviation in negative feedback. Explain the direction of each change rather than merely naming the hormone or organ.\n\nApply your understanding\n- Nervous responses use electrical impulses along neurones and chemical transmission across synapses. Hormones travel in blood to target organs. Relate the route, duration and specificity of the response to the particular example."
static const Topic bio_control[] = {
    S("4.5.1", "Homeostasis", "Internal conditions such as body temperature, water level and blood glucose are kept within suitable ranges. Receptors detect changes, coordination centres process information and effectors respond."
      "\n\n- " "Think stimulus -> receptor -> coordination centre -> effector -> response. Internal conditions are regulated around a range so enzymes and cells can function well."),
    S("4.5.2.1", "Neurones, synapses and reflexes", "A receptor detects a stimulus. Sensory, relay and motor neurones carry impulses towards an effector. Chemicals cross synapses. Reflexes are rapid automatic responses; a reaction-time test measures time from stimulus to response."
      "\n\n- " "A withdrawal reflex can use the spinal cord before conscious awareness. Map sensory neurone into the CNS, relay neurone within it and motor neurone out to muscle."),
    S("4.5.2.2", "The brain", "The cerebral cortex supports consciousness, intelligence and memory. The cerebellum coordinates movement and balance. The medulla controls vital automatic processes such as breathing and heart rate."
      "\n\n- " "The cerebellum refines movement, while the medulla controls automatic functions. Damage in one area gives evidence about that area's role but may affect other connected areas."),
    H("4.5.2.2", "Investigating the brain", "Evidence comes from brain damage, stimulation and imaging such as MRI. Brain areas interact and tissue is delicate, so both assigning a function and treating damage can be difficult."
      "\n\n- " "Brain imaging shows associations between activity and tasks. Electrical stimulation can supply causal evidence, but invasive interventions carry risks and the functions of regions may overlap."),
    S("4.5.2.3", "The eye", "The iris controls light through the pupil. The cornea and lens focus light on the retina. For near objects ciliary muscles contract, ligaments slacken and the lens thickens. Short sight is corrected by a concave lens; long sight by a convex lens."
      "\n\n- " "For a distant object the ciliary muscles relax, ligaments tighten and the lens becomes thinner. In dim light radial iris muscles contract to enlarge the pupil."),
    S("4.5.2.4", "Temperature control", "The brain monitors blood and receives signals from skin receptors. When hot, sweating and vasodilation occur. When cold, sweating stops, surface vessels constrict and muscles shiver."
      "\n\n- " "The same disturbance initiates several responses. The skin and brain detect changing temperature, while vessels, sweat glands and skeletal muscles act as effectors."),
    H("4.5.2.4", "Explaining heat transfer", "Sweat evaporates and takes energy from skin. Wider surface vessels increase heat loss; constriction reduces it. Shivering raises energy transfer from respiration in muscle."
      "\n\n- " "Evaporation requires energy, so sweat that drips off cools less than sweat that evaporates. More blood near the surface increases the rate of transfer to cooler surroundings."),
    S("4.5.3.1", "The endocrine system", "Endocrine glands put hormones into the blood. The pituitary regulates other glands. Locate the thyroid, adrenals, pancreas, ovaries and testes. Hormonal signals are often slower and longer-lasting than nervous signals."
      "\n\n- " "Blood distributes a hormone widely but only cells with appropriate receptors respond. The pituitary controls other glands and also releases hormones with direct targets."),
    S("4.5.3.2", "Insulin and diabetes", "Insulin promotes glucose uptake and storage as glycogen when glucose rises. In type 1, little insulin is made; insulin therapy is used. Type 2 involves reduced responsiveness and can be managed with diet, activity and treatments."
      "\n\n- " "After a meal glucose rises; insulin causes greater uptake and glycogen storage, so it falls. In insulin resistance, cells respond less to a given insulin concentration."),
    H("4.5.3.2", "Glucagon and feedback", "Low blood glucose stimulates glucagon release by the pancreas. The liver breaks glycogen down and releases glucose. Together insulin and glucagon correct deviations in opposite directions."
      "\n\n- " "If blood glucose falls between meals, glucagon increases glucose release from stored glycogen. As concentration rises toward the normal range, the stimulus for more glucagon weakens."),
    S("4.5.3.3", "Kidneys and water balance", "Kidneys filter blood and selectively reabsorb glucose, ions and water. Excess water, salts and urea leave in urine. Compare dialysis, which cleans blood by exchange across a membrane, with kidney transplantation."
      "\n\n- " "Useful substances are reclaimed after filtration. In dialysis a suitable fluid allows urea to diffuse out across a membrane while normal concentrations of useful solutes are maintained."),
    H("4.5.3.3", "Deamination and ADH", "The liver removes amino groups from excess amino acids and converts toxic ammonia into urea. When blood is too concentrated the pituitary releases more ADH, increasing water reabsorption as tubules become more permeable."
      "\n\n- " "Dehydration raises blood concentration, so more ADH produces a smaller volume of more concentrated urine. Rehydration reverses the change through negative feedback."),
    S("4.5.3.4", "Reproductive hormones", "Oestrogen and testosterone drive changes at puberty. In the menstrual cycle FSH helps a follicle mature, LH triggers ovulation, oestrogen rebuilds the uterine lining and progesterone maintains it."
      "\n\n- " "The monthly sequence connects maturation of an egg, ovulation and preparation of the uterine lining. A fall in progesterone allows the lining to break down."),
    H("4.5.3.4", "Menstrual hormone feedback", "FSH stimulates follicle growth and oestrogen. Rising oestrogen suppresses FSH and high oestrogen triggers an LH surge. Progesterone suppresses FSH and LH. Read peaks and timing from hormone graphs."
      "\n\n- " "Follow the LH peak on a graph to identify likely ovulation. Progesterone rises after ovulation and falls if pregnancy does not occur, permitting the next cycle."),
    S("4.5.3.5", "Contraception", "Methods include hormonal pills, injections, implants or patches; barriers; intrauterine devices; spermicides; fertility awareness and sterilisation. Compare effectiveness, permanence, side effects and STI protection."
      "\n\n- " "Barrier methods can reduce transmission of some STIs as well as prevent pregnancy. Compare typical-use effectiveness and whether the method needs consistent action each time."),
    H("4.5.3.6", "Treating infertility", "FSH and LH can promote egg maturation and ovulation. In IVF fertilisation takes place outside the body, then an embryo is transferred to the uterus. Consider success rates, physical and emotional effects and multiple pregnancies."
      "\n\n- " "Selecting single-embryo transfer can reduce the risks associated with multiple births, but IVF outcomes vary. Compare the benefit with cost, uncertainty and health risks."),
    H("4.5.3.7", "Hormonal negative feedback", "Adrenaline prepares the body for action by increasing heart rate and glucose supply. Thyroxine helps control metabolic rate and development. Rising thyroxine reduces stimulation of the thyroid through negative feedback."
      "\n\n- " "In a thyroxine feedback loop, low thyroxine increases the signal to the thyroid; high thyroxine reduces it. Adrenaline is rapid preparation for increased activity."),
    S("4.5.4.1", "Plant tropisms and auxin", "Shoots grow towards light and against gravity; roots usually grow towards gravity. Unequal auxin distribution causes unequal growth. In shoots, auxin promotes elongation on the shaded side."
      "\n\n- " "In a shoot lit from one side, cells on the shaded side become longer, bending the shoot towards the light. In roots, a high auxin level can restrict elongation."),
    H("4.5.4.1", "Gibberellins and ethene", "Gibberellins help initiate germination. Ethene regulates fruit ripening and affects cell division. Know their effects without needing the detailed mechanisms."
      "\n\n- " "Seed germination needs the embryo to access stored food. Gibberellins help start this process. Ripening driven by ethene can coordinate the quality of fruit reaching shops."),
    H("4.5.4.2", "Using plant hormones", "Auxins are used in rooting powders, tissue culture and selective weedkillers. Gibberellins can end dormancy or change fruit growth and flowering. Ethene helps control when stored fruit ripens."
      "\n\n- " "A rooting treatment helps cuttings establish roots. A selective weedkiller interferes with growth in susceptible plants while leaving the crop relatively unaffected.")
};

#undef SCIENCE_MORE
#define SCIENCE_MORE "\n\nUnderstand the mechanism\n- Use gene, allele and chromosome precisely. An allele is a variant of a gene. Genotype describes the alleles present; phenotype is the expressed characteristic, which can also be affected by environmental conditions.\n\nApply your understanding\n- A genetic probability describes each independent offspring and does not guarantee a fixed ratio in a small family. State parent genotypes, show the gametes, combine alleles systematically and translate the possible genotypes into phenotypes."
static const Topic bio_genetics[] = {
    S("4.6.1.1", "Sexual and asexual reproduction", "Sexual reproduction combines gametes and produces genetic variation. Asexual reproduction uses one parent and mitosis, producing genetically identical offspring except for mutations."
      "\n\n- " "Identical asexual offspring are clones apart from new mutations. Gametes from two parents combine alleles into new genotypes during sexual reproduction."),
    S("4.6.1.2", "Meiosis", "DNA copies once and the cell divides twice. Four genetically different gametes form, each with half the usual chromosome number. Fertilisation restores paired chromosomes."
      "\n\n- " "A diploid human cell starts with 46 chromosomes; gametes receive 23 each. Fertilisation combines two haploid sets to restore 46."),
    S("4.6.1.3", "Advantages of reproductive modes", "Sexual reproduction gives variation to cope with change. Asexual reproduction is rapid and does not need a mate. Some species use both, depending on conditions or stage of the life cycle."
      "\n\n- " "When conditions are stable rapid cloning can spread a successful genotype. When conditions vary, genetic diversity increases the chance that some offspring have favourable traits."),
    S("4.6.1.4", "DNA and the genome", "DNA is a double-helix polymer. A gene is a region of DNA carrying information for a protein. A genome is the organism's complete genetic material. Genome data can help study disease and ancestry."
      "\n\n- " "DNA information is stored in the order of bases. Studying genomes can reveal inherited risk and relationships, but a genetic variant does not guarantee a phenotype."),
    S("4.6.1.5", "DNA structure", "DNA has a sugar-phosphate backbone with bases A, C, G and T. Nucleotides repeat along the chain. A sequence of three bases represents an amino acid."
      "\n\n- " "A nucleotide consists of a sugar, phosphate and base. The sequence, rather than the repeating sugar-phosphate backbone, supplies the coding information."),
    H("4.6.1.5", "Gene expression and protein", "A pairs with T and C with G. Ribosomes assemble amino acids in the sequence specified by the template. A coding change can alter protein shape or activity. A non-coding change can alter when a gene is expressed."
      "\n\n- " "A changed amino acid can alter how a protein folds and whether its active site fits. Noncoding variants can instead affect the amount or timing of protein production."),
    S("4.6.1.6", "Genetic inheritance", "Alleles are versions of a gene. Genotype is the allele combination; phenotype is the expressed characteristic. Use dominant and recessive, homozygous and heterozygous. Read or complete a simple Punnett square and interpret pedigrees."
      "\n\n- " "Heterozygous Aa can express the dominant phenotype while still passing a. A carrier of a recessive disorder can therefore be unaffected."),
    H("4.6.1.6", "Constructing genetic cross", "Choose allele symbols and derive each parent's gametes. Fill a Punnett square and turn the outcomes into probabilities. For Aa x Aa, AA:Aa:aa is 1:2:1, so a recessive phenotype has probability 1/4."
      "\n\n- " "For Aa x aa the gametes are A or a from one parent and only a from the other. The offspring ratio is 1 Aa : 1 aa and recessive probability is 1/2."),
    S("4.6.1.7", "Inherited disorders", "A dominant allele can cause polydactyly. Cystic fibrosis is recessive, so carriers may be unaffected. Evaluate what embryo screening can reveal and the decisions and ethical questions it raises."
      "\n\n- " "Two unaffected cystic-fibrosis carriers have a 1/4 affected probability in each pregnancy under a simple recessive model. Earlier children do not change that probability."),
    S("4.6.1.8", "Sex determination", "Most human females are XX and males XY. Eggs carry X; sperm can carry X or Y. A cross of XX and XY predicts about equal probabilities of XX and XY offspring."
      "\n\n- " "Each egg contributes an X. X sperm gives XX and Y sperm gives XY in the simplified GCSE cross. Each fertilisation is an independent event."),
    S("4.6.2.1", "Variation and mutations", "Phenotypes depend on genes, environment or both. Mutations generate new genetic variants. Most have little effect; a few affect phenotype or survival."
      "\n\n- " "Diet can affect mass without changing alleles. A different allele can change a trait even in identical surroundings. Many phenotypes depend on both factors."),
    S("4.6.2.2", "Evolution by natural selection", "Variation is already present. Individuals with advantageous inherited traits leave more offspring. Over many generations their alleles become more common. Evolution is a change in inherited characteristics over time."
      "\n\n- " "Natural selection filters existing variation across generations. A population evolves as allele frequencies change; an individual does not acquire the needed allele by trying."),
    S("4.6.2.3", "Selective breeding", "Select parents with desired characteristics, breed them and repeat with selected offspring. This can increase yield or disease resistance, but inbreeding can reduce genetic diversity and increase inherited disorders."
      "\n\n- " "Select high-yield parents and repeat across generations. Using too few parents raises the chance that harmful recessive alleles meet in offspring."),
    S("4.6.2.4", "Genetic engineering", "Genetic engineering changes DNA to introduce a desired trait. Examples include producing human insulin with modified microorganisms and changing crop characteristics. Evaluate yield, ecological effects and uncertainties."
      "\n\n- " "Selective breeding chooses existing variations by reproduction; genetic engineering can introduce a specified gene. Compare predicted benefit and ecological uncertainty."),
    H("4.6.2.4", "Role of genes and vectors", "In a textbook model, an isolated gene is carried into recipient cells by a vector so the cells can express the new characteristic. Identify the roles of the gene, vector, recipient and resulting protein in an exam diagram."
      "\n\n- " "In an exam diagram keep the roles separate: the gene encodes the trait, the vector carries it, and the recipient expresses the introduced information."),
    S("4.6.2.5", "Cloning", "Plant cuttings and tissue culture produce genetically identical plants. Animal examples include embryo splitting and adult-cell nuclear transfer. Discuss uses, low diversity and ethical concerns."
      "\n\n- " "Distinguish plant cuttings, splitting an early embryo, and adult-cell nuclear transfer. A clone can still develop a different phenotype in a different environment."),
    S("4.6.3.1", "Darwin, Wallace and Lamarck", "Darwin and Wallace explained evolution through natural selection. Darwin's ideas were controversial because inheritance was poorly understood. Lamarck proposed inheritance of acquired traits; evidence did not generally support that proposal."
      "\n\n- " "Natural selection explains why advantageous inherited traits become common. An acquired change, such as stronger muscles from exercise, is not automatically inherited."),
    S("4.6.3.2", "Speciation", "Isolated populations face different selection pressures. Allele frequencies diverge. When populations can no longer interbreed to produce fertile offspring, they are separate species."
      "\n\n- " "A physical barrier can stop gene flow. Different environments then favour different variants, and accumulated differences can prevent successful interbreeding."),
    S("4.6.3.3", "Mendel and genetics", "Mendel's pea crosses showed inherited factors can be passed on without blending. Chromosomes and genes were subsequently identified, providing a physical explanation for his patterns."
      "\n\n- " "A recessive trait can disappear from one generation and reappear in the next. This supports discrete inherited factors rather than permanent blending."),
    S("4.6.3.4", "Evidence for evolution", "Fossils record changes in organisms over time. Resistance evolving in bacteria demonstrates selection in living populations. Genetic comparisons can provide further evidence of relatedness."
      "\n\n- " "Several independent lines of evidence strengthen the explanation. Fossil sequences show historical change while resistant strains show allele selection observable today."),
    S("4.6.3.5", "Fossils", "Remains can persist when decay is prevented, be replaced by minerals, or leave traces such as footprints. Soft material decays readily and many rocks have been destroyed, so the fossil record is incomplete."
      "\n\n- " "Hard parts preserve more often than soft tissues. Use this bias to explain gaps rather than assuming a group was absent wherever no fossils were found."),
    S("4.6.3.6", "Extinction", "A species becomes extinct when no individuals remain. Rapid environmental change, new predators or diseases, competition and catastrophic events can prevent survival and reproduction."
      "\n\n- " "A rapid environmental shift can exceed the time available for adaptation. Small isolated populations are vulnerable because they often have less genetic variation."),
    S("4.6.3.7", "Antibiotic resistance", "Resistant mutants may survive antibiotic exposure and reproduce. Their descendants spread resistance. Avoid unnecessary prescriptions, follow prescribed courses and restrict inappropriate agricultural use."
      "\n\n- " "Antibiotics select among variants; they do not give the bacteria the trait because the bacteria need it. Surviving resistant bacteria can multiply and spread."),
    S("4.6.4", "Classification", "Linnaean groups run kingdom, phylum, class, order, family, genus, species. Binomial names use genus and species. Woese's domains are Bacteria, Archaea and Eukaryota. Evolutionary trees show inferred relationships."
      "\n\n- " "In a binomial name the genus comes first. Organisms sharing a recent node on an evolutionary tree are inferred to be more closely related.")
};

#undef SCIENCE_MORE
#define SCIENCE_MORE "\n\nUnderstand the mechanism\n- A change to one population can affect others through food supply, predation or competition. Trace a specific link in the food web and consider both biotic and abiotic factors before predicting the direction of a population change.\n\nApply your understanding\n- Sampling estimates populations. Place quadrats randomly when comparing abundance, or use a transect to investigate a gradient. Repeat samples and calculate a mean, use consistent area units, and explain how the sample represents the whole habitat."
static const Topic bio_ecology[] = {
    S("4.7.1.1", "Communities and competition", "Individuals of one species form populations; interacting populations form communities. Plants compete for light, space, water and minerals. Animals compete for territory, mates and food. In stable communities populations are broadly balanced."
      "\n\n- " "Interdependence means a change in one population can affect others. Removing a key food species can reduce predator numbers even if habitat stays suitable."),
    S("4.7.1.2", "Abiotic factors", "Non-living factors include temperature, light, moisture, soil pH and minerals, wind, carbon dioxide and oxygen. Explain distributions by linking the factor to a process or survival."
      "\n\n- " "Choose a specific mechanism: less light can reduce photosynthesis, whereas low oxygen can restrict aerobic respiration in water."),
    S("4.7.1.3", "Biotic factors", "Living influences include food availability, predators, pathogens and competitors. A new predator can lower prey numbers and affect other members of the food web."
      "\n\n- " "Competition can limit population size when resources are scarce. A newly introduced superior competitor may displace a native species using the same resources."),
    S("4.7.1.4", "Adaptations", "Structural, behavioural and functional adaptations improve survival in particular conditions. Extremophiles survive unusually hot, salty or high-pressure environments."
      "\n\n- " "Thick fur is structural, migration is behavioural and concentrated urine is functional. Link the feature to survival or reproduction in the habitat."),
    S("4.7.2.1", "Ecosystems and food chains", "An ecosystem includes a community and its physical environment. Producers make biomass, which is passed to consumers. Predators and prey can show linked population cycles. Sample abundance with quadrats and distribution with transects."
      "\n\n- " "Arrows in a food chain show transfer from food to consumer. A predator peak can lag behind the prey peak because predator reproduction responds after food increases."),
    S("4.7.2.2", "Carbon and water cycles", "Photosynthesis takes carbon dioxide into biomass. Respiration, decay and combustion return it. Water evaporates or transpires, condenses, falls as precipitation and returns by runoff or drainage."
      "\n\n- " "Carbon enters organisms by photosynthesis and moves through feeding; decomposers return it through respiration. Water evaporates and condenses in a different cycle."),
    S("4.7.2.3", "Decomposition", "Warm, moist and oxygenated conditions generally increase aerobic decay. Decomposers release minerals back into ecosystems. Composting uses decay to recycle nutrients; anaerobic breakdown can yield methane-rich biogas."
      "\n\n- " "Microorganisms break down material faster near a suitable temperature but slow in cold or very hot conditions. Explain oxygen availability before discussing aerobic or anaerobic decay."),
    H("4.7.2.4", "Environmental change", "Changes in temperature, water and atmospheric gases can shift species distributions. Distinguish seasonal, geographic and human-caused changes. Explain outcomes using evidence and an organism's tolerance."
      "\n\n- " "Reduced rainfall can shrink the range of a moisture-dependent species. Consider whether the pattern could also be seasonal or caused by other environmental changes."),
    S("4.7.3.1", "Biodiversity", "Biodiversity describes the variety of life in an area or on Earth. High diversity can stabilise ecosystems because other species may provide similar food or habitat roles."
      "\n\n- " "Compare richness as number of species and relative abundances if data are available. Habitat fragmentation can leave small populations cut off from each other."),
    S("4.7.3.2", "Waste and pollution", "Pollution can affect air, water and soil. Sewage and fertiliser can pollute water, smoke and gases can pollute air, and landfill or toxic chemicals can contaminate land."
      "\n\n- " "Excess nutrient input can lead to algal growth, reduced light and oxygen depletion as organic material decays. Explain a chain of consequences rather than just naming pollution."),
    S("4.7.3.3", "Land use and peat", "Building, farming, mining and waste disposal replace habitats. Draining or burning peat destroys habitat and releases stored carbon. Peat-free alternatives help reduce demand."
      "\n\n- " "Peat developed where waterlogged conditions slowed decay. Draining it allows greater aerobic decomposition and carbon loss as well as habitat damage."),
    S("4.7.3.4", "Deforestation", "Forest is cleared for grazing, crop production and resources. Fewer trees remove less carbon dioxide, while decay and burning release it. Habitat loss reduces biodiversity."
      "\n\n- " "Deforestation changes both sides of the carbon balance: less uptake by trees and more release through burning or decay. It can also fragment habitats."),
    S("4.7.3.5", "Global warming", "Increasing greenhouse gases strengthens the greenhouse effect. Warming can shift habitats, alter rainfall, melt land ice and raise sea level. Evaluate trends and avoid treating one event as a long-term trend."
      "\n\n- " "A trend over decades is more informative than one cold or hot year. Explain effects on habitat suitability and the possibility of shifts towards cooler areas."),
    S("4.7.3.6", "Conserving biodiversity", "Use breeding programmes, habitat restoration, protection, hedgerows and recycling. Weigh conservation outcomes against costs, food demand and local livelihoods."
      "\n\n- " "Connecting habitats allows dispersal and gene flow. Captive breeding alone does not guarantee recovery if habitat loss persists, so pair intervention with restoration."),
    S("4.7.4.1", "Trophic levels", "Producers are level 1; primary consumers eat producers, secondary consumers eat primary consumers, and so on. Decomposers break down dead material from all levels."
      "\n\n- " "An omnivore can occupy different levels depending on what it eats. Identify the chain shown before assigning its trophic level."),
    S("4.7.4.2", "Pyramids of biomass", "Draw a bar for the biomass at each trophic level, with widths proportional to biomass. Producers form the base. Biomass usually decreases up the chain."
      "\n\n- " "Use dry mass per area if given. A large count of small organisms may still give little mass, so do not confuse number pyramids with biomass pyramids."),
    S("4.7.4.3", "Transfer of biomass", "Percentage transfer = biomass at next level / biomass at previous level * 100. Material may be uneaten or egested. Respiration transfers energy and produces wastes, so only some intake becomes new biomass."
      "\n\n- " "If producers have 800 g and herbivores 96 g, transfer is 96/800*100=12%. The remainder is not all heat: some material is uneaten or leaves as waste."),
    S("4.7.5.1", "Food security", "Food security means reliable access to enough food. Population growth, diet changes, pests, disease, water shortages, expensive inputs and conflict can threaten supply."
      "\n\n- " "Food supply includes availability and access. Crop diseases reduce production, while conflict can disrupt transport even when food is produced elsewhere."),
    S("4.7.5.2", "Efficient farming", "Restricting movement or heat loss can divert more feed into biomass. High-energy or high-protein feeds can increase growth. Evaluate welfare, cost and resource use."
      "\n\n- " "Explain trade-offs: less movement can improve conversion to biomass, yet housing and feed have costs and animal-welfare consequences."),
    S("4.7.5.3", "Sustainable fisheries", "Catch quotas reduce total removals and larger mesh can allow young fish to escape and reproduce. Compare short-term catches with long-term population recovery."
      "\n\n- " "Protecting mature breeding fish or allowing juveniles to escape helps replace the stock. Evaluate whether the catch limits are enforceable and based on recent population data."),
    S("4.7.5.4", "Biotechnology and food", "Fungal mycoprotein is produced by fermentation. Genetic modification can improve nutrient content or other crop traits. Compare potential food security benefits with risks and costs."
      "\n\n- " "A controlled production system can supply protein with limited land use, but still requires resources and energy. Compare it with farming in the context of available evidence.")
};

#undef SCIENCE_MORE
#define SCIENCE_MORE "\n\nUnderstand the mechanism\n- Link explanations across levels of organisation, from molecules and cells to organs and populations. A change in a cell process can affect an organism's function, which can then affect interactions with other organisms.\n\nApply your understanding\n- Use evidence to distinguish a description from an explanation. A description states the observed change; an explanation links that change to a biological process such as diffusion, enzyme action, reproduction or natural selection."
static const Topic bio_key[] = {
    S("4.8", "Biology key ideas", "Relate structure to function, processes to energy transfer, and response to changing conditions. DNA controls inherited characteristics; selection changes populations. Organisms interact with their environment and cycle materials."
      "\n\n- " "Use a cause-and-effect chain in explanations: structure or change, process affected, then outcome. Link molecular, cellular and whole-organism levels as appropriate.")
};

#undef SCIENCE_MORE
#define SCIENCE_MORE "\n\nUnderstand the mechanism\n- State the independent variable, the dependent variable and how each control variable is maintained. Give apparatus and measurements clearly enough for another student to repeat the method, including a suitable range and intervals.\n\nApply your understanding\n- Record repeats with units, identify anomalies using evidence and calculate a mean where appropriate. For biological samples, variation between organisms can be substantial, so use enough specimens and standardise their size, age or starting condition."
static const Topic bio_practicals[] = {
    S("RP1", "Microscopy", "Prepare a clear thin specimen. Identify and label structures in a biological drawing. Report magnification and calculate actual size using matching units."
      "\n\n- " "Use a sharp pencil, plain outlines and straight labels touching structures. A scale bar remains meaningful if the diagram is subsequently enlarged or reduced."),
    S("RP2", "Antimicrobials and growth", "Compare the clear zones in a supervised antimicrobial investigation. Include a control and compare areas, not just diameters. Explain why asepsis and school-lab incubation limits matter."
      "\n\n- " "Use comparable starting samples and include an appropriate control. A larger clear area indicates greater inhibition under those conditions, but diffusion can also influence the measured area."),
    S("RP3", "Osmosis in plant tissue", "Compare equal-sized plant tissue pieces in solutions of different concentrations. Control time and temperature, blot consistently and calculate percentage mass change. Estimate the zero-change concentration."
      "\n\n- " "Percentage change=100*(final-initial)/initial. For 2.0 g to 2.2 g the change is +10%. Use repeats and interpolate where the graph crosses zero."),
    S("RP4", "Food tests", "Iodine gives blue-black with starch; Benedict's with heating gives green through brick-red with reducing sugar; Biuret goes lilac with protein; Sudan III gives a stained lipid layer. Include a negative control."
      "\n\n- " "Use a fresh sample for each test and record both the starting and final appearance. An equal volume of water can serve as a negative control."),
    S("RP5", "Amylase and pH", "Use buffers to vary pH and use iodine to track when starch is gone. Control temperature and enzyme and starch volumes. Compare relative rates using 1/time."
      "\n\n- " "Take samples at uniform intervals and use the first iodine spot remaining orange-brown as the endpoint. A shorter time means a greater starch breakdown rate."),
    S("RP6", "Photosynthesis and light", "Compare pondweed oxygen output at different lamp distances. Keep temperature and carbon dioxide availability consistent. Collecting gas volume is preferable to counting unequal bubbles."
      "\n\n- " "Water temperature can rise when the lamp moves nearer. Control it independently and record oxygen volume over a fixed time, then calculate volume per minute."),
    S("RP7", "Human reaction time", "Measure a participant's response with a ruler drop or timer. Vary one factor, control the procedure, repeat and compare averages. Consider practice effects and participant differences."
      "\n\n- " "Use the same participant across paired conditions where appropriate, alternate the order and average repeats. A shorter ruler drop represents a faster response."),
    S("RP8", "Seedlings and tropisms", "Compare seedling growth direction under different light directions or orientations relative to gravity. Keep moisture, age and temperature matched and include a control."
      "\n\n- " "Measure curvature or growth direction against the control. A dark control or an all-direction light control separates the effect of light direction from normal growth."),
    S("RP9", "Quadrats and transects", "Use random quadrats for unbiased estimates of abundance. For a gradient, take systematic quadrats along a transect. Increase sample size, record the area, and calculate mean density or percentage cover."
      "\n\n- " "If 12 plants occur in six 0.25 m^2 quadrats, mean density is 12/1.5=8 per m^2. Along a transect record position as well as counts."),
    S("RP10", "Decay in milk", "In the school model, compare how temperature affects the time for milk pH to fall as fatty acids are released. Standardise starting conditions and use the same endpoint for comparisons."
      "\n\n- " "Use a fixed endpoint rather than judging colour at different times. A shorter time to reach the endpoint means a faster change and can be compared using 1/time.")
};

#undef SCIENCE_MORE
#define SCIENCE_MORE "\n\nUnderstand the mechanism\n- Identify the system and its energy stores before and after the change. Transfers occur mechanically, electrically, by heating or by radiation. Energy remains conserved even when some is dissipated into less useful thermal stores in the surroundings.\n\nApply your understanding\n- Choose an equation that relates the known values to the required quantity. Convert units first, write the substituted expression and attach units to the answer. For efficiency, compare useful output with total input for the same process."
static const Topic phys_energy[] = {
    S("4.1.1.1", "Energy stores and systems", "Describe the object or group in the system. Energy stores include kinetic, gravitational, elastic, thermal, chemical, magnetic, electrostatic and nuclear. Transfers can occur by heating, waves, or mechanical or electrical work."
      "\n\n- " "Always name a store and a pathway separately. For a falling object, gravitational store decreases while kinetic store increases, mostly by mechanical transfer."),
    S("4.1.1.2", "Kinetic, elastic and GPE", "Kinetic energy = 0.5*m*v^2. Gravitational energy change = m*g*h. Elastic energy = 0.5*k*e^2 when spring behaviour is linear. Use kg, m/s, N/kg, m and N/m; results are in joules."
      "\n\n- " "For a 2 kg object at 4 m/s, Ek=16 J. Lifting it 1 m increases its gravitational store by 19.6 J if g=9.8 N/kg."),
    S("4.1.1.3", "Specific heat capacity", "Thermal energy change = mass * specific heat capacity * temperature change. Compare materials by the energy needed to warm 1 kg by 1 C. Keep energy in J and mass in kg."
      "\n\n- " "For 0.5 kg of water with c=4200 J/(kg C), warming by 10 C requires 21000 J. Equal energy inputs can cause different temperature rises."),
    S("4.1.1.4", "Power", "Power is energy transferred per second or work done per second: P=E/t and P=W/t. One watt is one joule per second. For the same work a shorter time means higher power."
      "\n\n- " "A 600 W motor transferring energy for 5 s transfers 3000 J. Power describes rate rather than the total quantity transferred."),
    S("4.1.2.1", "Conservation and dissipation", "A closed system's total energy stays constant. Friction and resistance often transfer energy to surrounding thermal stores. Lubrication reduces friction; thicker walls or lower thermal conductivity reduce heat transfer."
      "\n\n- " "In conduction, energy spreads through collisions and, in metals, mobile electrons. Loft insulation traps air and reduces the rate of energy transfer to colder surroundings."),
    S("4.1.2.2", "Efficiency", "Efficiency = useful energy out / total energy in, or useful power out / total power in. Multiply by 100 for a percentage. Compare like units."
      "\n\n- " "If 120 J enters and 90 J is useful, efficiency is 0.75=75%; 30 J goes to other stores. The useful transfer depends on the device's intended job."),
    H("4.1.2.2", "Improving efficiency", "Identify how energy is wasted in the device, then reduce that pathway. Examples include insulating a hot vessel, lubricating moving parts, and reducing resistive losses in power transmission."
      "\n\n- " "To suggest an improvement, state which unwanted pathway is reduced. For example, better insulation reduces transfer through the walls of a heater."),
    S("4.1.3", "Energy resources", "Fossil fuels and nuclear fuels are finite. Wind, solar, hydroelectric, tidal, wave, geothermal and biofuel resources can renew. Compare reliability, cost, environmental effects and uses for transport, heating and electricity."
      "\n\n- " "Compare demand and reliability over time. Solar output depends on light, whereas stored water behind a dam can be released when electricity is needed.")
};

#undef SCIENCE_MORE
#define SCIENCE_MORE "\n\nUnderstand the mechanism\n- Current is the rate of charge flow, whereas potential difference is energy transferred per unit charge. Resistance relates potential difference to current. Use the values for the same component and account for changes caused by heating.\n\nApply your understanding\n- In series, the current is the same around the loop and potential differences add. In parallel, branches share the same potential difference and currents add at junctions. Use these rules before applying a component equation."
static const Topic phys_electric[] = {
    S("4.2.1.1", "Circuit symbols", "Recognise cell, battery, switch, lamp, resistor, variable resistor, fuse, diode, LED, thermistor, LDR, ammeter and voltmeter. Put an ammeter in series and a voltmeter across the component."
      "\n\n- " "Use standard symbols and clear junctions. A voltmeter measures the difference between two points; an ammeter must carry the branch current it measures."),
    S("4.2.1.2", "Charge and current", "Current is the rate charge flows. Q=I*t, where Q is in coulombs, I in amperes and t in seconds. A complete circuit and a potential difference enable a continuous current."
      "\n\n- " "One ampere means one coulomb per second. A 0.20 A current flowing for 30 s transfers 6.0 C of charge."),
    S("4.2.1.3", "Potential difference and resistance", "V=I*R for measurements across a component. Potential difference is energy transferred per coulomb. Larger resistance gives smaller current at the same potential difference."
      "\n\n- " "Resistance can be found as V/I from a specified operating point. At 6 V and 0.30 A the resistance is 20 ohms."),
    S("4.2.1.4", "Resistors and I-V characteristics", "A fixed resistor at constant temperature gives a straight I-V line through zero. A filament gets hotter and its resistance increases. A diode conducts mostly one way. NTC thermistor resistance falls when heated; LDR resistance falls in brighter light."
      "\n\n- " "For a graph of I against V, the straight-line gradient equals 1/R. A heated filament's current increases less rapidly as its temperature and resistance rise."),
    S("4.2.2", "Series and parallel circuits", "Series: same current everywhere; supply voltage is shared; resistances add. Parallel: same voltage across branches; currents add; adding branches reduces equivalent resistance."
      "\n\n- " "Two 6 ohm resistors give 12 ohms in series or 3 ohms in parallel. Total parallel current is the sum of currents in the branches."),
    S("4.2.3.1", "AC and DC", "A direct supply keeps the same polarity; an alternating supply reverses. UK mains is about 230 V at 50 Hz. Cells provide DC."
      "\n\n- " "A 50 Hz AC period is 0.020 s. On a graph, DC voltage is steady in sign, while an alternating voltage repeatedly crosses zero."),
    S("4.2.3.2", "Mains plugs and safety", "Live is brown, neutral blue and earth green/yellow. The live wire can be dangerous even when a device is switched off. Earth provides a fault path; a fuse or breaker disconnects a high fault current."
      "\n\n- " "If live touches the earthed metal case, a large current can make the fuse or breaker disconnect the supply. Explain both the low-resistance path and the interruption."),
    S("4.2.4.1", "Electrical power", "Power = V*I and also I^2*R for a resistive component. Power is in W, voltage in V, current in A and resistance in ohms."
      "\n\n- " "At 12 V and 2 A a device transfers 24 J each second. In a fixed resistor, doubling current makes I^2R losses four times larger."),
    S("4.2.4.2", "Electrical energy transfers", "E=P*t and E=Q*V. Explain the intended energy store changes in appliances, such as a heater warming water or a motor transferring energy mechanically."
      "\n\n- " "A 2 kW heater running 0.5 h uses 1 kWh, equal to 3.6 million J. Label the unit for the time and power pair used."),
    S("4.2.4.3", "The National Grid", "Step-up transformers increase voltage for transmission. At the same power, higher voltage means lower current and smaller heating losses. Step-down transformers give a suitable supply for users."
      "\n\n- " "For fixed transmitted power, doubling the transmission voltage halves current. Resistive heating proportional to I^2 then falls to one quarter for the same cable."),
    S("4.2.5.1", "Static charge", "Friction can transfer electrons. The object gaining electrons becomes negative and the donor positive. Like charges repel; unlike charges attract. A large potential difference can cause a discharge."
      "\n\n- " "Electrons move between materials and total charge is conserved. A neutral conductor can still be attracted because its charges separate slightly."),
    S("4.2.5.2", "Electric fields", "An electric field is a region where a charge experiences force. Field arrows indicate the force on a positive test charge. A stronger field near a charge can lead to sparks when air becomes conductive."
      "\n\n- " "Field lines closer together represent greater field strength. Around a negative point charge, arrows point inward because a positive test charge is attracted.")
};

#undef SCIENCE_MORE
#define SCIENCE_MORE "\n\nUnderstand the mechanism\n- Distinguish the behaviour of particles from the behaviour of a bulk substance. Heating may increase average particle kinetic energy or change particle arrangement during a change of state. Particles themselves do not expand.\n\nApply your understanding\n- During melting or boiling at a constant pressure, energy can increase the potential part of internal energy while temperature remains constant. Mass is conserved in a closed system even if volume and density change."
static const Topic phys_particles[] = {
    S("4.3.1.1", "Density", "Density = mass/volume. Regular solids use geometric volume; irregular solids use water displacement. For liquids, subtract the empty container mass. Use kg/m^3 or consistent g/cm^3."
      "\n\n- " "Water displacement is final minus initial volume. An 81 g object displacing 30 cm^3 has density 2.7 g/cm^3, equal to 2700 kg/m^3."),
    S("4.3.1.2", "Particle states and changes", "Solids have particles in fixed positions, liquids can flow, and gas particles are far apart. Melting, freezing, boiling, condensing and subliming are physical changes; mass is conserved in a closed system."
      "\n\n- " "Evaporation occurs at the surface below the boiling point; boiling occurs throughout the liquid at its boiling point for that pressure."),
    S("4.3.2.1", "Internal energy", "Internal energy is the total kinetic and potential energy of particles. Heating transfers energy into these stores, raising temperature or changing state."
      "\n\n- " "Internal energy includes particle interactions. During melting, potential energy increases even though the temperature and average kinetic energy stay roughly constant."),
    S("4.3.2.2", "Heating and specific heat", "Use E=m*c*change in temperature when no state change occurs. For the same mass and input energy, a material with greater specific heat capacity has a smaller temperature rise."
      "\n\n- " "Use a temperature difference, not the final temperature. A drop from 34 C to 26 C corresponds to a change of -8 C with the warming-positive convention."),
    S("4.3.2.3", "Specific latent heat", "During a state change temperature stays constant as energy changes particle separation. E=m*L. Use the latent heat of fusion for melting or freezing, and vaporisation for liquid-gas change."
      "\n\n- " "A plateau on a heating graph occurs during a change of state. A 0.1 kg sample at L=334000 J/kg needs 33400 J to melt."),
    S("4.3.3.1", "Gas motion and temperature", "Gas particles move randomly. Higher temperature means greater average kinetic energy. Collisions against container walls exert forces and create pressure."
      "\n\n- " "Warmer gas particles strike walls more frequently and with larger momentum changes if volume is fixed. Both help explain the pressure increase."),
    S("4.3.3.2", "Gas pressure and volume", "For a fixed mass of gas at constant temperature, p*V is constant. A smaller volume means more frequent particle collisions with the walls and a larger pressure."
      "\n\n- " "For a fixed mass at fixed temperature, p1V1=p2V2. Cutting the volume to one third triples absolute pressure."),
    H("4.3.3.3", "Work done on a gas", "Compressing a gas transfers energy mechanically. If energy cannot escape quickly, internal energy and temperature rise. This can be felt when a bike pump warms up."
      "\n\n- " "In a rapid compression, little energy escapes by heating during the compression. Work input raises internal energy and can temporarily raise the gas temperature.")
};

#undef SCIENCE_MORE
#define SCIENCE_MORE "\n\nUnderstand the mechanism\n- Proton number identifies an element. Isotopes have the same number of protons and different numbers of neutrons. Radioactive decay is random for an individual nucleus, while a large population shows a predictable statistical pattern.\n\nApply your understanding\n- Distinguish irradiation from contamination. Irradiation exposes an object to radiation, while contamination puts radioactive material on or inside it. Explain a precaution using penetration, exposure time, distance or shielding."
static const Topic phys_atoms[] = {
    S("4.4.1.1", "Atoms and energy levels", "A tiny positive nucleus contains protons and neutrons; electrons occupy energy levels. Absorbing radiation can raise an electron to a higher level; a downward transition emits radiation."
      "\n\n- " "Only particular energy differences are allowed. Absorbed radiation must provide the correct energy difference; emission occurs when an electron drops to a lower level."),
    S("4.4.1.2", "Isotopes and atomic numbers", "Proton number identifies the element. Mass number counts protons plus neutrons. Isotopes have the same proton number and different neutron numbers. An ion has gained or lost electrons."
      "\n\n- " "For chlorine-37 with atomic number 17, there are 17 protons and 20 neutrons. A chloride ion has 18 electrons after gaining one."),
    S("4.4.1.3", "Atomic model evidence", "Most alpha particles passed through foil; a few scattered by large angles, supporting a small dense positive nucleus rather than the plum pudding model. Bohr added electron levels; Chadwick provided evidence for neutrons."
      "\n\n- " "The rare large deflections mattered because a diffuse positive charge would not explain them. Most undeflected paths support an atom mostly empty by volume."),
    S("4.4.2.1", "Alpha, beta, gamma and neutrons", "Unstable nuclei decay randomly. Alpha is a helium nucleus, beta is an electron emitted in decay, gamma is electromagnetic radiation, and neutrons can also be emitted. Compare ionisation, penetration and range. Activity uses Bq."
      "\n\n- " "Alpha is strongly ionising but readily stopped by paper; gamma is less ionising per path length and penetrates farther. Beta lies between for typical GCSE comparisons."),
    S("4.4.2.2", "Nuclear equations", "Conserve mass number and charge number. Alpha reduces them by 4 and 2 respectively. Beta-minus increases proton number by one with mass number unchanged. Gamma does not change either number."
      "\n\n- " "For a beta-minus equation show A unchanged and Z increasing by one in the daughter nucleus; the emitted electron carries charge number -1."),
    S("4.4.2.3", "Half-life", "Half-life is the time for activity or the number of undecayed nuclei to halve. Individual decays are random, but large samples have a predictable trend. Subtract background when analysing a decay graph."
      "\n\n- " "If measured rate falls from 100 to 60 with background 20 counts/min, corrected rates are 80 and 40. This interval represents one half-life."),
    H("4.4.2.3", "Half-life ratios", "Each elapsed half-life multiplies activity by 1/2. After three half-lives 1/8 remains, so the remaining to original ratio is 1:8 and 7/8 has decayed."
      "\n\n- " "For 160 Bq after three half-lives: 160 -> 80 -> 40 -> 20. The activity remaining is 12.5% of its initial value."),
    S("4.4.2.4", "Contamination and irradiation", "Contamination means radioactive material has reached an object. Irradiation is exposure to radiation from a source. Irradiating an object does not normally make it radioactive. Risk depends on radiation, dose and whether material enters the body."
      "\n\n- " "Removing the source stops irradiation from it. Contamination can continue to irradiate while radioactive material remains, especially if taken inside the body."),
    S("4.4.3.1", "Background radiation", "Natural sources include rocks and cosmic radiation. Human sources include medical uses and nuclear industry. Exposure varies with location and occupation; dose is measured in sieverts."
      "\n\n- " "Natural background can differ between regions due to geology or altitude. Measure background separately before interpreting a source's count rate."),
    S("4.4.3.2", "Short and long half-lives", "A short half-life produces rapid decay and can mean high initial activity for the same number of atoms. Long-lived sources persist. Match activity and persistence to risk and use."
      "\n\n- " "An isotope with very long half-life can remain hazardous long after use. Choose a tracer that remains active long enough for the measurement and decays afterwards."),
    S("4.4.3.3", "Uses and hazards of radiation", "A medical tracer should be detectable outside the body and short-lived enough to limit dose. Radiotherapy aims to damage tumour cells while limiting healthy tissue damage. Compare shielding and exposure time."
      "\n\n- " "For a detector outside the patient, emissions must escape the body. For a local treatment, judge how strongly the radiation deposits its energy in the intended region."),
    S("4.4.4.1", "Nuclear fission", "A heavy nucleus can absorb a neutron and split, releasing energy and more neutrons. Further splits can form a chain reaction. A reactor controls the chain reaction."
      "\n\n- " "In a reactor, control rods absorb some neutrons. The reaction releases energy that can heat a coolant and ultimately produce electricity."),
    S("4.4.4.2", "Nuclear fusion", "Light nuclei can join to form a heavier nucleus, releasing energy as some mass is converted to energy. Fusion powers stars; high temperature is needed for nuclei to get close enough."
      "\n\n- " "Fusion releases energy in stars, but keeping very hot fuel confined is difficult on Earth. The high temperature helps nuclei overcome electrostatic repulsion.")
};

#undef SCIENCE_MORE
#define SCIENCE_MORE "\n\nUnderstand the mechanism\n- Draw a force diagram for the chosen object, with arrows showing direction and relative size. Combine forces in the same direction and subtract opposing forces to find the resultant. Balanced forces can accompany constant velocity.\n\nApply your understanding\n- Scalars have magnitude, while vectors also have direction. State sign conventions when calculating displacement, velocity or acceleration, and distinguish the gradient of a graph from the area beneath it."
static const Topic phys_forces[] = {
    S("4.5.1.1", "Scalars and vectors", "Scalars have magnitude only, such as speed or mass. Vectors have magnitude and direction, such as force or velocity. Arrow length represents magnitude and the arrowhead direction."
      "\n\n- " "A displacement needs a direction, e.g. 4 m east. A speed such as 5 m/s has no direction, whereas 5 m/s east is a velocity."),
    S("4.5.1.2", "Contact and non-contact forces", "Friction, drag, tension and normal contact forces act through contact. Gravity, magnetic and electrostatic forces act without contact. A force is a push or pull from an interaction."
      "\n\n- " "A normal reaction is perpendicular to the surface. Friction is parallel to it and opposes relative motion or its tendency."),
    S("4.5.1.3", "Mass, weight and gravity", "Mass is in kg. Weight is a force in N: W=m*g. On Earth g is about 9.8 N/kg. Weight acts as if concentrated at the centre of mass."
      "\n\n- " "A mass of 2.5 kg at g=9.8 N/kg has weight 24.5 N. Moving to the Moon changes weight because g changes; mass stays constant."),
    S("4.5.1.4", "Resultant force", "A single resultant represents the combined forces. Along one line choose a positive direction and add signed values. Opposite forces of equal size give zero resultant."
      "\n\n- " "If 8 N acts right and 5 N left, choose right positive and get +3 N. Zero resultant can mean rest or constant velocity."),
    H("4.5.1.4", "Resolving forces", "Draw a free-body diagram. Resolve a force into two perpendicular components, or use a scale vector diagram to combine non-collinear forces. For equilibrium the components sum to zero in each direction."
      "\n\n- " "On a diagram of two perpendicular force components, find resultant magnitude with Pythagoras and direction with trigonometry. Keep vector signs when resolving."),
    S("4.5.2", "Work and energy transfer", "Work done = force * distance moved along the force. One newton metre of work equals one joule. Friction transfers energy to thermal stores when moving objects."
      "\n\n- " "Moving 3 m along a 15 N force transfers 45 J. A perpendicular force does no work on displacement in that direction."),
    S("4.5.3", "Elasticity and springs", "F=k*e up to the limit of proportionality, with extension in m. Elastic deformation reverses on unloading. Inelastic deformation remains. The elastic store increases by 0.5*k*e^2 on the linear section."
      "\n\n- " "If 5 N produces 0.020 m extension in the linear region, k=250 N/m. Unloading beyond the elastic limit may leave a permanent extension."),
    S("4.5.4", "Moments, levers and gears", "Moment = force * perpendicular distance from pivot. Equilibrium requires equal clockwise and anticlockwise moments. Levers and gears can trade force or turning effect against distance or speed."
      "\n\n- " "A 40 N force 0.30 m from the pivot at right angles gives 12 N m. The force needed falls as the perpendicular lever arm increases."),
    S("4.5.5.1.1", "Pressure in fluids", "Pressure = force normal to area / area, in pascals. A fluid exerts pressure on surfaces. The force acts perpendicular to each surface."
      "\n\n- " "A 400 N load over 0.02 m^2 produces 20000 Pa. Reducing contact area with the same force increases pressure."),
    H("4.5.5.1.2", "Pressure at depth", "Liquid pressure due to depth is p=h*rho*g. The deeper surface of an object experiences greater pressure, giving upthrust. Compare upthrust and weight to explain floating or sinking."
      "\n\n- " "At h=3 m in water with rho=1000 kg/m^3 and g=9.8 N/kg, liquid pressure is 29400 Pa. Add atmospheric pressure only for absolute pressure."),
    S("4.5.5.2", "Atmospheric pressure", "Air molecules collide with surfaces to exert pressure. Air density and atmospheric pressure decrease with increasing height because there is less air above."
      "\n\n- " "At higher altitude less air lies above a surface. Lower atmospheric pressure can make a sealed flexible bag expand compared with its original surroundings."),
    S("4.5.6.1.1", "Distance and displacement", "Distance is total path length and is scalar. Displacement specifies the straight-line change of position with direction. A round trip can have nonzero distance and zero displacement."
      "\n\n- " "Walking 3 m east then 4 m west gives 7 m distance but 1 m west displacement. State direction for displacement."),
    S("4.5.6.1.2", "Speed", "Average speed = distance/time. Convert units before calculating. Recall approximate walking, running, cycling and sound speeds to check the size of answers."
      "\n\n- " "A 90 km journey in 1.5 h gives 60 km/h, about 16.7 m/s. Average speed is total distance over total elapsed time."),
    S("4.5.6.1.3", "Velocity", "Velocity is speed in a given direction. It can change when speed changes or when the direction of motion changes."
      "\n\n- " "A runner continuing at 5 m/s east keeps constant velocity; turning south at the same speed changes velocity."),
    H("4.5.6.1.3", "Velocity in a circle", "The velocity vector is tangent to the circle. Its direction changes continually, so velocity changes even at constant speed."
      "\n\n- " "For uniform circular motion the velocity changes direction each moment, even at constant speed. The net force points towards the centre."),
    S("4.5.6.1.4", "Distance-time graphs", "The gradient gives speed. A flat line means stationary and a steeper line means greater speed. Calculate change in distance divided by change in time."
      "\n\n- " "For uniform circular motion velocity changes direction each moment, even at constant speed. The net force points towards the centre."),
    H("4.5.6.1.4", "Instantaneous speed", "Draw a tangent at the required point on a curved distance-time graph. Take two points well apart on that tangent and divide rise by run."
      "\n\n- " "A distance-time graph rising 30 m in 6 s has gradient 5 m/s. A horizontal piece represents no change in distance."),
    S("4.5.6.1.5", "Acceleration", "a=(v-u)/t. The gradient of a velocity-time graph gives acceleration. At constant acceleration use v^2-u^2=2*a*s. Falling objects may reach terminal speed when drag balances weight."
      "\n\n- " "For a tangent passing through (2 s, 5 m) and (6 s, 17 m), gradient is 3 m/s. Use points on the tangent, not arbitrary points on the curve."),
    H("4.5.6.1.5", "Velocity-time graph areas", "Signed area under a velocity-time graph gives displacement. Add the magnitudes of areas for distance. Use shapes or count grid squares for a curved graph."
      "\n\n- " "From 4 to 10 m/s in 3 s, average acceleration is 2 m/s^2. A negative acceleration is in the negative direction, which is braking only when motion is positive."),
    S("4.5.6.2.1", "Newton's first law", "When resultant force is zero a stationary object stays at rest and a moving object keeps constant velocity. At steady speed in a straight line, driving force balances resistive forces."
      "\n\n- " "A velocity-time triangle from 0 to 8 m/s over 3 s contributes 12 m displacement. An area below the axis contributes negatively to displacement."),
    H("4.5.6.2.1", "Inertia", "Inertia is the tendency to stay at rest or continue in uniform motion. A passenger moves forward relative to a suddenly braking vehicle until a restraint changes their velocity."
      "\n\n- " "If driving force and drag are equal, velocity does not change. A force is required to change motion rather than to maintain velocity."),
    S("4.5.6.2.2", "Newton's second law", "Resultant force = mass * acceleration. For the same mass, doubling resultant force doubles acceleration. At the same force, doubling mass halves acceleration."
      "\n\n- " "When a bus pulls away, a standing passenger's body initially tends to keep its previous velocity. Their feet accelerate through contact with the floor."),
    H("4.5.6.2.2", "Inertial mass", "Inertial mass measures resistance to a change in velocity. It is the ratio of resultant force to acceleration, m=F/a."
      "\n\n- " "A net 12 N on a 3 kg cart produces 4 m/s^2. Use net force, after subtracting resistance, rather than the driving force alone."),
    S("4.5.6.2.3", "Newton's third law", "An interaction gives equal and opposite forces of the same type on different objects. For example, a hand pushes a wall and the wall pushes the hand."
      "\n\n- " "Earth pulls a falling object down while the object pulls Earth up with equal force. Their accelerations differ because their masses differ."),
    S("4.5.6.3.1", "Stopping distance", "Stopping distance is thinking distance plus braking distance. Thinking distance is travelled before braking starts; braking distance is travelled from applying brakes to rest."
      "\n\n- " "At constant initial speed, thinking distance equals speed times reaction time. Braking distance starts only when the brakes act."),
    S("4.5.6.3.2", "Reaction time", "Tiredness, distraction, alcohol and other drugs can increase reaction time. Compare repeated ruler-drop or computer-based measurements and allow for practice effects."
      "\n\n- " "Record repeated times or ruler distances against an identical release procedure. Removing anticipation and switching condition order helps control practice effects."),
    S("4.5.6.3.3", "Factors in braking distance", "Higher initial speed, wet or icy roads, worn tyres and poor brakes can increase braking distance. Explain these using kinetic energy and the maximum friction available."
      "\n\n- " "Higher speed raises initial kinetic energy with v^2. A wet surface can reduce the maximum braking force available, increasing the stopping distance."),
    S("4.5.6.3.4", "Energy during braking", "Friction transfers kinetic energy to thermal stores, including brakes and surroundings. Larger braking forces give larger deceleration. Very large deceleration can overheat brakes or cause loss of control."
      "\n\n- " "Braking transfers energy mostly to the brakes and surroundings. Repeated hard braking can warm the brakes enough to reduce effective performance."),
    H("4.5.6.3.4", "Estimating braking forces", "Find acceleration from a change of velocity over time, or from stopping distance for uniform braking, then apply F=m*a. Report the magnitude and show that force opposes motion."
      "\n\n- " "A 1200 kg car slowing from 20 m/s to rest in 5 s has a=-4 m/s^2 and mean net force -4800 N, opposing motion."),
    H("4.5.7.1", "Momentum", "Momentum = mass * velocity, in kg m/s. It is a vector, so choose a direction convention before using signs."
      "\n\n- " "If a 3 kg trolley moves left at 2 m/s and right is positive, p=-6 kg m/s. The sign is part of the answer."),
    H("4.5.7.2", "Momentum conservation", "Total momentum is constant in an isolated system. Add signed momenta before and after impact. For objects that stick together, use their combined mass after impact."
      "\n\n- " "A 1 kg cart at 6 m/s sticks to a stationary 2 kg cart. Total initial momentum is 6 kg m/s, so shared velocity is 2 m/s."),
    H("4.5.7.3", "Force and momentum change", "F = change in momentum / time. A longer stopping time reduces force for the same momentum change. Apply this to seat belts, airbags, crumple zones and soft landing surfaces."
      "\n\n- " "A change of 24 kg m/s in 0.2 s needs average force 120 N. Over 0.4 s the mean force falls to 60 N for the same change.")
};

#undef SCIENCE_MORE
#define SCIENCE_MORE "\n\nUnderstand the mechanism\n- A wave transfers energy without a net transfer of matter. Wavelength is a spatial separation between corresponding points, while period is the time for one cycle. Frequency counts complete cycles per second.\n\nApply your understanding\n- At a boundary the source fixes frequency. A change in wave speed changes wavelength, and refraction can change direction. On diagrams, measure angles to the normal and label the incident, reflected or refracted ray."
static const Topic phys_waves[] = {
    S("4.6.1.1", "Transverse and longitudinal waves", "Waves transfer energy without net transfer of matter. Transverse vibrations are perpendicular to travel; longitudinal vibrations are parallel. Sound has compressions and rarefactions."
      "\n\n- " "For a longitudinal wave, compressions are close-particle regions and rarefactions are widely spaced regions. Particles oscillate about their positions while the disturbance travels."),
    S("4.6.1.2", "Wave properties", "Amplitude is maximum displacement, wavelength is spacing between equivalent points, and frequency is cycles per second. Period=1/f and wave speed=f*wavelength."
      "\n\n- " "If frequency is 40 Hz, period is 0.025 s. A wavelength of 0.10 m gives speed 4.0 m/s."),
    S("4.6.1.3", "Reflection of waves", "Angle of incidence equals angle of reflection, measured from the normal. At a boundary waves may be reflected, transmitted or absorbed. Rough surfaces scatter light in many directions."
      "\n\n- " "Measure both angles from the normal. An incident ray at 30 degrees to the mirror surface is 60 degrees from the normal and reflects at 60 degrees to it."),
    H("4.6.1.4", "Sound waves and hearing", "Vibrations in solids or sound waves can cause the eardrum to vibrate. Sound changes speed at boundaries and can refract. Human hearing is roughly 20 Hz to 20 kHz."
      "\n\n- " "A loudspeaker drives pressure variations in air. The eardrum vibrates in response, converting an airborne disturbance to mechanical vibrations in the ear."),
    H("4.6.1.5", "Ultrasound and seismic", "Echoes locate boundaries; distance = speed * round-trip time / 2. Ultrasound partly reflects at tissue boundaries. P waves travel through solids and liquids; S waves only through solids, giving evidence about Earth's interior."
      "\n\n- " "An echo after 0.004 s in water at 1500 m/s travelled 6 m there and back, so the reflecting object is 3 m away."),
    S("4.6.2.1", "Electromagnetic spectrum", "In order of increasing frequency: radio, microwave, infrared, visible, ultraviolet, X-ray, gamma. All are transverse and have the same speed in a vacuum. Frequency rises as wavelength falls."
      "\n\n- " "Visible runs from long-wavelength red to shorter-wavelength violet. Gamma has the highest frequency of the listed groups. All travel at c in vacuum."),
    S("4.6.2.2", "Waves at boundaries", "Construct a ray diagram showing how a ray refracts into another medium. Draw the normal and identify the incident and refracted rays and their angles."
      "\n\n- " "Extend the normal through the boundary. The incident angle and refracted angle are both measured relative to that perpendicular line."),
    H("4.6.2.2", "EM wavefronts and media", "Materials absorb, transmit, refract and reflect different wavelengths differently. An angled wavefront turns if one side changes speed first; frequency is unchanged across the boundary."
      "\n\n- " "Entering a slower medium obliquely causes a wave to bend towards the normal. Frequency stays fixed by the source, so shorter speed means shorter wavelength."),
    S("4.6.2.3", "Origin and hazards of EM waves", "Changes in atoms or nuclei can emit or absorb EM waves; gamma originates in the nucleus. UV, X-rays and gamma can harm tissue. Dose in sieverts represents risk."
      "\n\n- " "Ionising radiation can damage cells and DNA. Compare hazards with exposure and dose rather than assuming every use gives the same risk."),
    H("4.6.2.3", "Radio wave generation", "Oscillations in a circuit can emit radio waves. A wave received by a conductor can induce alternating current with the same frequency."
      "\n\n- " "An aerial can transmit a changing electric signal as waves. A receiving aerial develops a signal of the same frequency when the waves induce a current."),
    S("4.6.2.4", "Uses of electromagnetic waves", "Learn examples across the spectrum: radio communication, microwave satellites and cooking, IR heaters or imaging, visible fibre optics, UV lamps, X-ray imaging and gamma treatment or sterilisation."
      "\n\n- " "Match application and band: infrared for thermal imaging, visible light for fibre-optic signals, and X-rays to distinguish tissues in an image."),
    H("4.6.2.4", "Explaining uses of EM waves", "Link a property to the application. X-rays pass through softer tissue more easily than bone. Microwaves pass through the atmosphere for satellite links. Optical fibres guide light."
      "\n\n- " "TV or radio transmission uses waves that can travel long distances. For an imaging application, explain a difference in absorption or transmission between materials."),
    S("4.6.2.5", "Lenses and ray diagrams", "Converging lenses focus parallel rays; diverging lenses spread them as if from a focus. Use principal rays to locate real or virtual images. Magnification=image height/object height."
      "\n\n- " "A converging lens gives a virtual upright magnified image when the object is inside its focal length. An image projected onto a screen is real."),
    S("4.6.2.6", "Visible light, colour and filters", "An opaque object's colour depends on the light it reflects. A filter transmits selected wavelengths. Transparent materials transmit light; translucent materials scatter it as it passes through."
      "\n\n- " "A red object reflects red and absorbs most other colours. Under blue illumination alone it appears dark if it reflects very little blue light."),
    S("4.6.3.1", "Infrared and black bodies", "All objects emit and absorb infrared. A hotter object emits more radiation. An ideal black body absorbs all incident radiation and is the best possible emitter at its temperature."
      "\n\n- " "A matt dark surface is a good absorber and emitter compared with a shiny matched surface at the same temperature."),
    S("4.6.3.2", "Black-body radiation", "Increasing temperature increases the total radiation emitted and shifts the peak to shorter wavelengths. Cooler objects emit mainly infrared; very hot objects can visibly glow."
      "\n\n- " "As a filament heats, more radiation is emitted and the fraction at shorter wavelengths grows. This can change its visible colour as well as brightness."),
    H("4.6.3.2", "Thermal radiation balance", "Constant temperature means energy absorbed equals energy emitted per second. If absorbed power exceeds emitted power the system warms. Incoming sunlight, reflection and outgoing infrared affect Earth's balance."
      "\n\n- " "If the absorbed power stays greater than the emitted power, temperature rises until their rates balance or conditions change. Reflective surfaces affect the energy input.")
};

#undef SCIENCE_MORE
#define SCIENCE_MORE "\n\nUnderstand the mechanism\n- Field lines show the direction of the force on a north pole. Closely spaced lines indicate a stronger field. Around a current-carrying wire, the field direction changes if the current reverses.\n\nApply your understanding\n- Separate the motor effect from electromagnetic induction. A current in a magnetic field can experience a force; changing magnetic flux through a circuit can induce a potential difference. Identify what changes and where the energy comes from."
static const Topic phys_magnets[] = {
    S("4.7.1.1", "Permanent and induced magnets", "Like poles repel and unlike poles attract. A permanent magnet produces its own field. Induced magnetism occurs in suitable materials in an external field and gives an attractive force."
      "\n\n- " "A permanent magnet can attract unmagnetised iron through induction. When a temporary induced magnet is removed from the field, most of its magnetism may disappear."),
    S("4.7.1.2", "Magnetic fields and compasses", "Field lines outside a magnet point north to south and are closest where the field is strongest. A compass needle aligns with the local field. Earth's field gives a navigation reference."
      "\n\n- " "The north end of a compass points in the direction of the local field. Use several compass positions to construct a field pattern."),
    S("4.7.2.1", "Electromagnets", "A current produces a magnetic field around a wire. More current increases field strength. A solenoid gives a stronger, nearly uniform core field; an iron core strengthens it further."
      "\n\n- " "Reversing the current reverses the magnetic field. Adding turns to a comparable solenoid or increasing current can make its field stronger."),
    H("4.7.2.2", "Fleming's left-hand rule", "First finger: field. Second finger: conventional current. Thumb: motor force. For perpendicular field and wire, F=B*I*l. Reverse current or field to reverse force."
      "\n\n- " "For B=0.4 T, I=5 A and length 0.2 m at right angles, F=0.4 N. Reverse both B and I and the force direction stays the same."),
    H("4.7.2.3", "Electric motors", "Opposite sides of a coil experience opposite magnetic forces, giving a turning effect. A split-ring commutator reverses current each half-turn to maintain the turning direction."
      "\n\n- " "The two opposite forces on a coil form a couple. The split-ring commutator swaps coil connections every half turn so rotation continues in one direction."),
    H("4.7.2.4", "Loudspeakers", "Alternating input current makes the coil experience a changing force in a permanent field. The cone vibrates with the signal and sets up pressure waves in air."
      "\n\n- " "Changing the signal frequency changes cone vibration frequency and hence pitch. Increasing the amplitude generally increases the size of the sound pressure variations."),
    H("4.7.3.1", "Induced potential", "A changing magnetic field through a coil, or motion of a wire across field lines, induces a potential difference. A closed circuit carries current. Faster change gives a larger effect; the induced effect opposes the change."
      "\n\n- " "Moving the same magnet into a coil faster produces a larger peak voltage. Reversing the motion reverses the polarity of the induced voltage."),
    H("4.7.3.2", "Generators and alternators", "A rotating coil or magnet changes the magnetic field linked to the coil. Alternators generate AC; a dynamo uses a commutator to give a DC output."
      "\n\n- " "Turning at higher speed can raise both output frequency and peak voltage. Slip rings keep coil connections fixed, whereas a split ring switches them."),
    H("4.7.3.3", "Microphones", "Sound moves a diaphragm linked to a coil in a magnetic field. The changing position induces a varying voltage that represents the sound wave."
      "\n\n- " "The diaphragm follows changes in air pressure, moving the coil and changing the linked magnetic field. The induced signal varies with the original vibrations."),
    H("4.7.3.4", "Transformers", "A changing field links primary and secondary coils. Vp/Vs=Np/Ns. In an ideal transformer Vp*Ip=Vs*Is. More secondary turns step voltage up and reduce current at equal power."
      "\n\n- " "A transformer with twice as many secondary turns gives twice the secondary voltage and about half the current if ideal. A steady DC input cannot sustain induction after switching.")
};

#undef SCIENCE_MORE
#define SCIENCE_MORE "\n\nUnderstand the mechanism\n- Gravity supplies the centripetal force for an orbit. Velocity changes continuously because its direction changes even when speed is constant. Explain an orbital change using gravity, radius and speed where the syllabus requires it.\n\nApply your understanding\n- Observations support models through evidence. A redshift indicates a longer observed wavelength, and large-scale galactic redshifts support an expanding universe. Distinguish observed evidence from an explanation inferred from it."
static const Topic phys_space[] = {
    S("4.8.1.1", "Solar system", "Earth and other planets orbit the Sun. Moons are natural satellites; artificial satellites serve communications, navigation and observation. Our solar system lies in the Milky Way."
      "\n\n- " "The Sun contains most of the solar system's mass. Planets orbit the Sun; moons generally orbit planets, while a space probe can be put into artificial orbit."),
    S("4.8.1.2", "Life cycles of stars", "Gravity gathers gas and dust into a protostar. Fusion supports a main-sequence star. Sun-like stars become red giants, then white dwarfs. Massive stars become red supergiants, then supernovae leaving neutron stars or black holes; heavy elements are dispersed."
      "\n\n- " "A low-mass star leaves a white dwarf after shedding outer layers. A massive star's core may leave a neutron star or black hole after a supernova."),
    S("4.8.1.3", "Orbits and satellites", "Gravity provides the inward force keeping moons, planets and artificial satellites in orbit. Compare the object orbited, the scale of the orbit and whether the satellite is natural or artificial."
      "\n\n- " "An orbiting satellite is continually falling towards the central body while moving sideways. Natural and artificial satellites obey the same gravitational principles."),
    H("4.8.1.3", "Orbital speed and radius", "Gravity changes the direction of velocity in a circular orbit while speed stays constant. A stable circular orbit at a larger radius requires a lower speed around the same central body."
      "\n\n- " "If a circular orbital speed changes suddenly, the original radius does not remain a stable circular path. A larger stable circular radius around the same body has lower speed."),
    S("4.8.2", "Red-shift and the universe", "Spectral lines from most galaxies shift to longer wavelengths; larger shifts usually occur farther away. This supports expansion and a hot dense beginning. Cosmic microwave background and accelerated expansion inform current models."
      "\n\n- " "Compare observed absorption lines with their laboratory positions. Stretch to longer wavelengths supports expansion; the microwave background is independent evidence for a hot early universe.")
};

#undef SCIENCE_MORE
#define SCIENCE_MORE "\n\nUnderstand the mechanism\n- Use physical quantities and units consistently. A proportional relationship is supported by a straight line through the origin; a straight line with an intercept represents a different relationship. Inspect axes and scales before drawing a conclusion.\n\nApply your understanding\n- Check whether a result is plausible using a rough estimate, its sign and units. State assumptions such as negligible resistance, constant acceleration or an isolated system when these determine which model can be applied."
static const Topic phys_key[] = {
    S("4.9", "Physics key ideas", "Use models to explain matter and fields, energy transfers, motion and waves. Apply conservation rules, distinguish interactions from their effects, and check the dimensions of every equation."
      "\n\n- " "For a calculation, state the model, convert values to the equation's units, show substitution and include the result's unit and direction where appropriate.")
};

#undef SCIENCE_MORE
#define SCIENCE_MORE "\n\nUnderstand the mechanism\n- Identify the quantity measured directly and any quantity calculated from it. Select instruments with an appropriate range and resolution, check zero readings, and control variables that could change the measured relationship.\n\nApply your understanding\n- Repeat measurements, plot suitable graphs and use a large triangle for a gradient. An anomalous point needs investigation. Averaging helps reduce random variation, while a systematic offset requires identifying and correcting its cause."
static const Topic phys_practicals[] = {
    S("RP1", "Specific heat capacity", "Heat a known mass with an electrical heater. Measure temperature rise and input energy using power*time or V*I*t. Use c=E/(m*temperature rise). Insulate and account for energy losses."
      "\n\n- " "Plot temperature rise against input energy. For a known mass, gradient of temperature change versus energy is 1/(m*c). Heat lost to the room can bias the estimate."),
    S("RP2", "Thermal insulation", "Compare cooling curves for matched containers with different insulation. Control start temperature, volume, material thickness or layers as appropriate. Use the fall over a fixed time."
      "\n\n- " "Use identical starting water temperatures and the same monitoring interval. Compare rates from the initial gradients or the temperature drops after a fixed time."),
    S("RP3", "Resistance of wires and circuits", "Vary wire length with the same material and cross-section. Measure V and I and calculate V/I. Compare series and parallel resistors and minimise changes from heating."
      "\n\n- " "Keep current low enough to limit heating. A graph of resistance against length should be close to linear for a uniform wire held at similar temperature."),
    S("RP4", "I-V characteristics", "Vary the supply and record paired current and potential difference values for a resistor, lamp and diode. Include both polarities where appropriate. Compare the shapes and gradients."
      "\n\n- " "Repeat current-voltage pairs at different settings, then reverse polarity if required. Use limits to avoid heating a fixed resistor or damaging a diode."),
    S("RP5", "Density of solids and liquids", "Measure mass with a balance and volume geometrically or by displacement. For a liquid use a measured volume and subtract the container mass. Convert units before dividing."
      "\n\n- " "A measuring cylinder reading is taken at the liquid meniscus. Small displaced volumes have larger percentage uncertainty, so suitable apparatus matters."),
    S("RP6", "Force and spring extension", "Calculate load as weight, and extension from the unloaded length. Plot force against extension and identify the proportional region and spring constant. Do not confuse length with extension."
      "\n\n- " "Plot force vertically against extension horizontally. The gradient is k, and a departure from the straight region indicates that proportionality no longer holds."),
    S("RP7", "Force, mass and acceleration", "Use a trolley and light gates or a motion sensor. Vary force at fixed total mass, then vary mass with force fixed. Compare acceleration graphs; discuss friction and repeatability."
      "\n\n- " "When changing the pulling mass, transfer masses between trolley and hanger to keep total mass fixed. Compare repeated measurements and account for track friction."),
    S("RP8", "Measuring wave speed", "Use a ripple tank for water waves and a suitable vibration method for waves in a solid. Measure wavelength across several cycles and frequency or period; use v=f*wavelength."
      "\n\n- " "Measure a run of several wavelengths and divide by their number. Time many oscillations for a better period estimate, then use v=lambda/T."),
    S("RP9", "Reflection and refraction", "Trace rays around a mirror or transparent block. Draw the normal at each boundary and measure angles to it. Compare several angles and note beam width and reading uncertainty."
      "\n\n- " "Trace incident and emergent directions with well-separated points. Measure angles from the normal, not from the block surface, to check patterns."),
    S("RP10", "Infrared and surfaces", "Compare emission or absorption by surfaces under controlled geometry and temperatures. Keep source distance or detector position fixed and compare matched surfaces such as matt black and shiny metal."
      "\n\n- " "For emission compare surfaces at the same temperature and detector distance. For absorption use the same input source, distance and exposure time.")
};

#undef SCIENCE_MORE
#define SCIENCE_MORE "\n\nUnderstand the mechanism\n- Proton number defines the element; electron arrangement helps explain chemical behaviour. Isotopes differ in neutron number. In an ordinary chemical reaction, atoms are rearranged and the nuclei retain their identity.\n\nApply your understanding\n- Distinguish an element, a compound and a mixture. Compounds have elements chemically combined in fixed proportions. Mixtures can contain variable proportions and can be separated using differences in physical properties."
static const Topic chem_atoms[] = {
    S("4.1.1.1", "Atoms, elements and compounds", "An element contains one type of atom. Compounds contain elements chemically joined in fixed proportions and can be separated by reactions. Use element symbols, formulae, word and balanced symbol equations. Change coefficients when balancing."
      "\n\n- " "Element symbols start with a capital and may include a lowercase second letter. In 2H2O, the coefficient applies to both atoms in the formula: four H and two O atoms total."),
    H("4.1.1.1", "Ionic and half equations", "In a net ionic equation remove unchanged spectator ions. Balance charge and atoms in half equations using electrons. For example, Ag+ + Cl- -> AgCl(s)."
      "\n\n- " "For Fe^2+ -> Fe^3+, add an electron to the products to balance charge: Fe^2+ -> Fe^3+ + e-. Keep the atom count unchanged."),
    S("4.1.1.2", "Mixtures and separation", "Mixtures are physically combined and have variable composition. Use filtration for insoluble solids, crystallisation for dissolved solids, simple or fractional distillation for liquids, and chromatography to separate dissolved substances."
      "\n\n- " "Filtration leaves an insoluble residue and lets the solution pass. To recover its dissolved solid, use crystallisation; distillation instead collects a condensed liquid."),
    S("4.1.1.3", "Development of atomic models", "The model moved from solid spheres to Thomson's plum pudding model. Alpha scattering supported a small positive nucleus. Bohr used electron shells; Chadwick identified the neutron."
      "\n\n- " "A scattering result that the earlier model could not explain prompted a new model. Distinguish the observation itself from the inference about the nucleus."),
    S("4.1.1.4", "Subatomic charges", "Protons have relative charge +1; electrons -1; neutrons 0. A neutral atom has equal numbers of protons and electrons. Proton number identifies the element."
      "\n\n- " "An atom with 12 protons has 12 electrons when neutral. If it loses two electrons the ion is 2+, while the proton number stays 12."),
    S("4.1.1.5", "Atomic size, mass and isotopes", "An atom's radius is about 10^-10 m; the nucleus is far smaller and holds nearly all the mass. Mass number is protons plus neutrons. Isotopes have the same proton number and different neutron numbers."
      "\n\n- " "For an isotope with A=24 and Z=12, neutrons=24-12=12. Isotopes of an element have similar chemistry because their electron arrangements agree when neutral."),
    S("4.1.1.6", "Relative atomic mass", "Relative atomic mass is an isotope-abundance weighted mean on the carbon-12 scale. Multiply each relative isotope mass by its fractional abundance and add."
      "\n\n- " "If 75% is isotope mass 35 and 25% is mass 37, Ar=35*0.75+37*0.25=35.5. The mean is closer to the more abundant isotope."),
    S("4.1.1.7", "Electron arrangements", "Fill shells from the inside out. GCSE arrangements for the first 20 elements use 2 in the first shell and up to 8 in each of the next two before the fourth begins. Chlorine is 2,8,7."
      "\n\n- " "Calcium has 20 electrons, arranged 2,8,8,2 in this model. Its period is 4 and two outer electrons place it in group 2."),
    S("4.1.2.1", "Periodic table structure", "Elements are ordered by atomic number. A period corresponds to shells occupied and, for main-group elements, group reflects outer-shell arrangement. Similar outer-shell structures give similar chemistry."
      "\n\n- " "Moving across a period increases atomic number by one each element. Descending a group adds an occupied shell, which helps explain trends."),
    S("4.1.2.2", "Development of the periodic table", "Early tables used atomic weights. Mendeleev left gaps and sometimes changed weight order to group similar elements. Later discoveries matched his predictions and isotopes explained anomalous mass order."
      "\n\n- " "Mendeleev's gaps made predictions that could be checked, including an unknown element resembling silicon. Comparing predictions with discoveries supported the arrangement."),
    S("4.1.2.3", "Metals and non-metals", "Metals are mainly on the left and centre and often lose electrons to form positive ions. Non-metals are mainly on the right and may gain electrons or share them in covalent bonds."
      "\n\n- " "A metal atom does not become a different element when it forms an ion, because its proton number is unchanged. The charge comes from the electron imbalance."),
    S("4.1.2.4", "Group 0 noble gases", "Full outer electron shells make the noble gases unreactive and monatomic. Boiling point generally rises down the group as atoms become larger and attractions stronger."
      "\n\n- " "Helium is stable with two electrons in its only shell; other GCSE noble-gas examples have eight outer electrons. Their boiling points are low because atoms attract weakly."),
    S("4.1.2.5", "Group 1 alkali metals", "Group 1 atoms form +1 ions. They react with water to form an alkaline metal hydroxide and hydrogen. Reactivity increases down the group because the outer electron is further away and more shielded."
      "\n\n- " "Sodium reacts with water to give sodium hydroxide and hydrogen. Down the group the extra shells outweigh increased nuclear charge, so the outer electron is lost more easily."),
    S("4.1.2.6", "Group 7 halogens", "Halogens are diatomic and form -1 ions. Their melting and boiling points increase down the group, while reactivity decreases. A more reactive halogen displaces a less reactive halide."
      "\n\n- " "Chlorine displaces bromine from potassium bromide. The products are potassium chloride and bromine. Reactivity falls as an incoming electron is farther from the nucleus and more shielded."),
    S("4.1.3.1", "Transition metals versus group 1", "Typical transition metals are denser, stronger, harder and have higher melting points than alkali metals. They generally react less vigorously with water or oxygen."
      "\n\n- " "The trends are typical, with exceptions. Compare iron and sodium for strength and reaction vigour rather than assuming every metal behaves the same way."),
    S("4.1.3.2", "Transition-metal properties", "Many transition metals form ions with different charges and coloured compounds, and their elements or compounds can act as catalysts. Examples include iron, copper, manganese, chromium, cobalt and nickel."
      "\n\n- " "Iron can act as a catalyst in the Haber process and copper(II) compounds are often coloured. The same metal can form different ions, such as Fe^2+ and Fe^3+.")
};

#undef SCIENCE_MORE
#define SCIENCE_MORE "\n\nUnderstand the mechanism\n- Explain a property through structure, bonding and the particles that move. In metals, delocalised electrons carry charge. Ionic solids conduct when ions become free to move in a melt or solution.\n\nApply your understanding\n- Melting a simple molecular substance overcomes forces between molecules. It usually leaves covalent bonds within molecules intact. Giant structures need a different explanation because strong bonds extend through the structure."
static const Topic chem_bonds[] = {
    S("4.2.1.1", "Ionic, covalent and metallic bonds", "Ionic bonding is attraction between oppositely charged ions. Covalent bonding shares electron pairs. Metallic bonding attracts positive metal ions to delocalised electrons."
      "\n\n- " "Identify the particles before describing the force. Ionic attractions involve ions; a metallic lattice includes delocalised electrons; covalent bonds involve shared pairs."),
    S("4.2.1.2", "Ion formation", "Metals lose electrons and non-metals gain them. Use outer-shell dot-and-cross diagrams and brackets with charges. Group 1 forms +1, group 2 +2, group 6 -2 and group 7 -1."
      "\n\n- " "Mg loses two electrons while each Cl gains one, explaining the MgCl2 ratio. Show final outer shells and charges with brackets in a dot-and-cross diagram."),
    S("4.2.1.3", "Ionic lattices and formulae", "Ionic compounds contain repeating 3D lattices with attractions in all directions. Use ion charges to find the simplest neutral ratio, such as MgCl2. Compare dot-and-cross and lattice model limitations."
      "\n\n- " "A formula such as NaCl describes the ratio of ions in the lattice rather than one discrete molecule. Each ion has oppositely charged neighbours."),
    S("4.2.1.4", "Covalent structures", "A shared electron pair makes a covalent bond. Molecules may contain single, double or triple bonds; some covalent substances form giant networks or long polymer chains. Translate between displayed and dot-and-cross diagrams."
      "\n\n- " "In methane carbon shares four pairs, one with each hydrogen. A displayed line shows a bond but omits unshared pairs and may not show real 3D angles."),
    S("4.2.1.5", "Metallic bonding", "Outer electrons become delocalised through a regular lattice of positive ions. Attraction between ions and these electrons holds the metal together."
      "\n\n- " "When drawing the lattice, show positive ions surrounded by a shared pool of delocalised electrons rather than paired to particular ions."),
    S("4.2.2.1", "Solids, liquids and gases", "Use melting and boiling points to predict state. Changing state requires transferring energy to or from particles. Stronger attractions generally mean more energy is needed to separate particles."
      "\n\n- " "A material with melting point 30 C and boiling point 120 C is liquid at 60 C under the stated pressure. Distinguish boiling from surface evaporation."),
    H("4.2.2.1", "Particle model limitations", "A drawing of solid spheres can show arrangement and spacing but does not represent the forces, internal structure or deformability of real particles. It cannot explain changes of state on its own."
      "\n\n- " "A solid-sphere diagram is a simplification: particle size and gaps may not be to scale. Forces and energy transfers require more than the arrangement alone."),
    S("4.2.2.2", "State symbols", "Use (s) solid, (l) liquid, (g) gas and (aq) dissolved in water. For example, NaCl(s) differs from NaCl(aq). Aqueous is a solution state."
      "\n\n- " "State labels are added after formulae, e.g. an insoluble precipitate formed in water is (s), even though the original ions were (aq)."),
    S("4.2.2.3", "Ionic compound properties", "Strong ionic attractions require much energy to overcome, giving high melting points. Solid ions are fixed. Molten or dissolved ions can move and carry electric charge."
      "\n\n- " "Molten sodium chloride can carry current through ions moving in opposite directions. The solid lattice contains charges but they are fixed in position."),
    S("4.2.2.4", "Small molecules", "Strong covalent bonds hold a molecule together, but comparatively weak intermolecular forces give many small molecules low melting and boiling points. Simple molecules generally lack mobile charges."
      "\n\n- " "On boiling iodine, molecules separate from one another; the covalent I-I bonds within the molecules are not the bonds being overcome in that state change."),
    S("4.2.2.5", "Polymer properties", "Polymers contain very large molecules with strong covalent bonds along each chain. Intermolecular attractions can be strong because of the large chains, making most polymers solids at room temperature."
      "\n\n- " "A repeat unit describes the pattern in the polymer. It is not a separate molecule, and individual chains can have different lengths."),
    S("4.2.2.6", "Giant covalent structures", "Continuous covalent networks require many strong bonds to be broken to melt them. Examples include diamond, graphite and silicon dioxide. Mobile charge carriers determine conductivity."
      "\n\n- " "Silicon dioxide has a continuous network with many strong bonds. Most such structures do not conduct; graphite is an exception because it has mobile electrons."),
    S("4.2.2.7", "Metals and alloys", "Layers of atoms can slide in a pure metal. Different-sized atoms distort those layers in an alloy, hindering sliding and often making the material harder."
      "\n\n- " "Pure metal layers slide relatively easily. Different atom sizes in an alloy interrupt the regular layers, improving hardness for uses such as tools or structural parts."),
    S("4.2.2.8", "Metal conductivity", "Delocalised electrons move through metal to carry electric charge and help transfer thermal energy. This explains why metals conduct even when solid."
      "\n\n- " "Heating one end of a metal transfers energy partly through mobile electrons and lattice vibrations. Current is a net flow of charge through the solid lattice."),
    S("4.2.3.1", "Diamond", "Each carbon makes four covalent bonds in a rigid giant network. Diamond is very hard and has a very high melting point. It has no delocalised electrons to carry current."
      "\n\n- " "Diamond's rigid network makes it useful for cutting. Strong covalent bonds must be broken to melt it, but none of its outer electrons is freely mobile."),
    S("4.2.3.2", "Graphite", "Each carbon bonds to three others in hexagonal sheets. The layers slide because the forces between layers are weak. A delocalised electron per carbon enables conductivity."
      "\n\n- " "Graphite conducts along sheets. The sheets can slide because the attractions between them are much weaker than the bonds within each sheet."),
    S("4.2.3.3", "Graphene and fullerenes", "Graphene is a conducting sheet of carbon one atom thick. Fullerenes are hollow carbon structures such as C60 and nanotubes. Applications include composite reinforcement, electronics and molecular delivery."
      "\n\n- " "Nanotubes have high tensile strength and can conduct electricity. Fullerene structures have cavities and high surface areas, useful when evaluating applications."),
    S("4.2.4.1", "Nanoparticles and surface area", "Nanoparticles are around 1 to 100 nm. Large surface area per unit volume can change reactivity or the amount needed. For a cube, area/volume = 6/side length."
      "\n\n- " "Compare cubes with side lengths 1 and 2 units: area-to-volume ratio is 6 and 3 per unit respectively. Smaller particles have more exposed area per unit volume."),
    S("4.2.4.2", "Uses and risks of nanoparticles", "Examples include catalysis, electronics, sunscreens, materials and medicine. Consider performance, ease of dispersion, possible effects on living organisms and incomplete evidence of long-term risks."
      "\n\n- " "In a catalyst, high surface area can provide more active sites for a given mass. Before deciding on use, compare performance with exposure and disposal evidence.")
};

#undef SCIENCE_MORE
#define SCIENCE_MORE "\n\nUnderstand the mechanism\n- Track the substance and unit at every stage. Relative formula mass sums relative atomic masses with the correct atom counts. Moles measure amount of substance and connect mass, concentration and reaction ratios.\n\nApply your understanding\n- A balanced equation gives mole ratios. Convert the known quantity to moles, apply the coefficient ratio, then convert to the required mass, concentration or volume. Check that a percentage has been divided or multiplied by 100 at the appropriate step."
static const Topic chem_amount[] = {
    S("4.3.1.1", "Mass conservation and balancing", "No atoms are created or destroyed in a chemical reaction. Balance each element using whole-number coefficients without changing formulae. Total mass is conserved in a closed system."
      "\n\n- " "For Al + O2 -> Al2O3, use 4Al + 3O2 -> 2Al2O3. Changing a subscript would change the substance rather than balance it."),
    S("4.3.1.2", "Relative formula mass", "Mr is the sum of the relative atomic masses for all atoms in a formula. For a balanced equation the sum of relative masses including coefficients is the same on both sides."
      "\n\n- " "Mr of CaCO3 = 40 + 12 + 3*16 = 100. Use the coefficient outside a formula only when comparing quantities in a balanced equation."),
    S("4.3.1.3", "Mass changes involving gases", "An open vessel can lose mass as a gas escapes or gain mass when a gas reacts with its contents. Include all matter crossing the boundary when applying conservation."
      "\n\n- " "A heated metal can appear to gain mass because it combines with oxygen from air. In a sealed setup that oxygen's mass was already part of the system."),
    S("4.3.1.4", "Chemical measurement uncertainty", "Repeat measurements and recognise variation. A rough estimate of uncertainty is half the range of repeated results. Report appropriate significant figures and identify anomalies."
      "\n\n- " "For repeated readings 12.0, 12.1 and 12.4 g, half the range is 0.2 g. Quote a mean with reasonable precision and discuss unusually different readings."),
    H("4.3.2.1", "Moles", "One mole contains about 6.02*10^23 specified particles. Amount in mol = mass in g / molar mass in g/mol. Molar mass is numerically equal to Ar or Mr."
      "\n\n- " "9 g of water with Mr=18 is 0.50 mol, containing about 3.01*10^23 molecules. Specify which kind of particle is counted."),
    H("4.3.2.2", "Amounts in equations", "Balanced equation coefficients give mole ratios. Convert known mass to moles, apply the ratio, then convert the desired species back to mass if needed."
      "\n\n- " "CaCO3 -> CaO + CO2 has a 1:1 ratio. 10 g CaCO3 is 0.10 mol and can yield 0.10 mol CO2, equal to 4.4 g."),
    H("4.3.2.3", "Balancing using moles", "Convert measured masses to moles and divide by the smallest amount. Multiply ratios to whole numbers where necessary to infer formula ratios or reaction coefficients."
      "\n\n- " "24 g Mg and 16 g oxygen atoms correspond to 1 mol of each, giving formula MgO. If counting oxygen molecules in a reaction, use O2 with Mr=32."),
    H("4.3.2.4", "Limiting reactants", "Divide the amount of each reactant by its coefficient to compare how many reaction batches are possible. The smallest fixes maximum product; other reactants may be in excess."
      "\n\n- " "For 2H2+O2 -> 2H2O, 3 mol H2 and 1 mol O2 give 1.5 and 1 reaction batches respectively. Oxygen limits water production to 2 mol."),
    S("4.3.2.5", "Concentration in g/dm^3", "For concentration in g/dm^3, find solute mass by multiplying concentration by solution volume in dm^3. Divide cm^3 by 1000 to convert to dm^3."
      "\n\n- " "A solution of 12 g/dm^3 in 250 cm^3 contains 12*0.250=3.0 g of dissolved solute. Use the final total solution volume."),
    H("4.3.2.5", "Solute mass and volume", "Concentration is mass of solute divided by total solution volume. At fixed solute mass, doubling volume halves concentration. At fixed volume, doubling dissolved mass doubles it."
      "\n\n- " "Diluting 4 g in 0.20 dm^3 to 0.50 dm^3 gives concentration 8 g/dm^3. The solute mass is unchanged by adding water."),
    S("4.3.3.1", "Percentage yield", "Percentage yield = actual mass / theoretical maximum mass * 100. Losses during separation, incomplete reaction or competing products can reduce yield."
      "\n\n- " "A practical gives 8.4 g from a theoretical 12 g. Percentage yield = 8.4/12*100=70%. A value over 100% suggests impurities or measurement problems."),
    H("4.3.3.1", "Theoretical product mass", "Find moles of limiting reactant from mass and Mr. Use the balanced mole ratio to get theoretical moles of product, then multiply by product Mr."
      "\n\n- " "For CaCO3 -> CaO + CO2, 25 g of CaCO3 is 0.25 mol. Theoretical CaO mass is 0.25*56=14 g."),
    S("4.3.3.2", "Atom economy", "Atom economy = relative mass of desired product, including its coefficient, divided by total relative mass of reactants in the balanced equation, times 100. It measures theoretical resource use."
      "\n\n- " "CaCO3 -> CaO + CO2, desired product CaO. Atom economy=56/100*100=56%. Atom economy uses the balanced equation, not the measured yield."),
    H("4.3.3.2", "Choosing reaction pathways", "Compare atom economy, actual yield, rate, position of equilibrium, feedstock cost and usefulness of by-products. High atom economy alone does not guarantee an economical process."
      "\n\n- " "A route with a valuable by-product may be preferable despite lower atom economy for one product. Compare material costs and how much is produced in practice."),
    H("4.3.4", "Concentration in mol/dm^3", "Use n=c*V with V in dm^3. A titration gives one amount of substance; use the balanced mole ratio to find the other. Multiply mol/dm^3 by molar mass for g/dm^3."
      "\n\n- " "0.20 mol/dm^3 in 25.0 cm^3 gives 0.20*0.0250=0.00500 mol. In a 1:2 equation calculate the second amount using that ratio."),
    H("4.3.5", "Molar gas volume", "At room temperature and pressure one mole of gas occupies about 24 dm^3. Use V=24*n in dm^3. Gas volumes at the same temperature and pressure follow the balanced mole ratios."
      "\n\n- " "At RTP, 0.35 mol gas occupies 0.35*24=8.4 dm^3. Use equal-temperature and equal-pressure volumes in mole-ratio comparisons.")
};

#undef SCIENCE_MORE
#define SCIENCE_MORE "\n\nUnderstand the mechanism\n- Predict products from the reacting species and then balance atoms. For ionic equations, spectator ions are omitted. Where electrons are involved, oxidation is electron loss and reduction is electron gain.\n\nApply your understanding\n- For salt preparation, choose a method suitable for whether the salt is soluble and whether the starting reagent is soluble. In electrolysis, identify the ions present and distinguish a molten electrolyte from an aqueous solution."
static const Topic chem_changes[] = {
    S("4.4.1.1", "Metal oxides and oxygen", "Metals can react with oxygen to produce oxides. Oxidation can mean gaining oxygen and reduction losing oxygen. For example, heating copper in air forms copper oxide."
      "\n\n- " "In 2Mg + O2 -> 2MgO, magnesium gains oxygen and is oxidised. In the reverse type of change, removing oxygen from an oxide is reduction."),
    S("4.4.1.2", "Reactivity and displacement", "More reactive metals form ions more easily. Learn positions of potassium, sodium, lithium, calcium, magnesium, aluminium, carbon, zinc, iron, hydrogen and copper. More reactive metals displace less reactive metals from compounds."
      "\n\n- " "Zinc displaces copper ions: zinc is more reactive and enters solution while copper metal forms. Copper would not displace zinc from the reverse mixture."),
    S("4.4.1.3", "Metal extraction", "Unreactive metals may occur native. Metals below carbon in the reactivity series can often be obtained by reduction with carbon. More reactive metals commonly need electrolysis."
      "\n\n- " "Carbon can remove oxygen from suitable oxides such as iron oxide. Aluminium is above carbon, so its extraction requires a different method."),
    H("4.4.1.4", "Electron transfer and redox", "Oxidation is electron loss; reduction is electron gain. In a displacement, the more reactive metal forms ions as the less reactive metal ions gain electrons."
      "\n\n- " "In Zn + Cu^2+ -> Zn^2+ + Cu, zinc loses two electrons and copper ions gain them. The linked oxidation and reduction occur together."),
    S("4.4.2.1", "Acids with metals", "Reactive metals such as magnesium, zinc and iron form a salt and hydrogen with suitable dilute acids. Hydrochloric acid gives chlorides and sulfuric acid gives sulfates."
      "\n\n- " "Magnesium and dilute hydrochloric acid give magnesium chloride and hydrogen. A gas test distinguishes hydrogen from carbon dioxide produced by a carbonate."),
    H("4.4.2.1", "Acid-metal redox", "The metal loses electrons and is oxidised. Hydrogen ions gain electrons and form hydrogen gas, so they are reduced. The acid's remaining anion is a spectator in the net ionic reaction."
      "\n\n- " "Write Zn -> Zn^2+ + 2e- and 2H+ + 2e- -> H2. Adding them cancels electrons and shows why this reaction is redox."),
    S("4.4.2.2", "Neutralisation and salts", "Acid + base gives salt and water. With a carbonate, carbon dioxide also forms. The acid supplies the anion and the metal or base supplies the cation. Nitric acid forms nitrates."
      "\n\n- " "Sulfuric acid plus copper oxide gives copper sulfate and water. An acid reacting with a carbonate also releases carbon dioxide."),
    S("4.4.2.3", "Preparing soluble salts", "An acid can react with excess insoluble oxide or carbonate. Filter off unreacted solid and concentrate the clear solution. Cool it so crystals form and then separate and dry them."
      "\n\n- " "Add the insoluble solid until some remains so the acid is used up. Remove the excess solid before concentrating and cooling the filtrate."),
    S("4.4.2.4", "pH and neutralisation", "Acids release H+ in water; alkalis provide OH-. pH 7 is neutral, lower is acidic and higher alkaline. Use universal indicator or a pH probe. H+ + OH- -> H2O."
      "\n\n- " "At pH 7 a solution is neutral at ordinary temperatures. Acidic and alkaline tests use indicator colours, while a meter gives a numeric reading."),
    S("4.4.2.5", "Titration technique", "Use a pipette for a fixed aliquot, a burette for the measured addition and a suitable indicator for the endpoint. Obtain concordant titres and use their mean."
      "\n\n- " "Read the burette at eye level and subtract initial from final. Use only concordant titres for a mean, leaving the rough attempt out."),
    H("4.4.2.5", "Titration calculations", "Use concentration * volume in dm^3 to find moles of the known solution. Apply the equation's coefficients and divide by the unknown solution volume to find mol/dm^3."
      "\n\n- " "20.0 cm^3 of 0.10 M acid reacting 1:1 with 25.0 cm^3 alkali gives 0.0020 mol alkali. Its concentration is 0.080 mol/dm^3."),
    H("4.4.2.6", "Strong and weak acids", "Strong acids ionise essentially completely in water; weak acids ionise partly. Strength and concentration describe different things. A pH decrease of one means ten times the H+ concentration."
      "\n\n- " "A dilute strong acid can have a higher pH than a more concentrated strong acid. Distinguish the fraction ionised from the original amount dissolved per volume."),
    S("4.4.3.1", "Electrolysis principles", "An electrolyte contains mobile ions. Cations move to the negative cathode and anions to the positive anode. A direct supply drives a reaction that does not happen by itself."
      "\n\n- " "A molten or aqueous electrolyte conducts through ions; the external wires conduct through electrons. Electrode products follow the ions and conditions present."),
    S("4.4.3.2", "Electrolysis of molten salts", "A molten binary ionic compound can yield a metal at the cathode and a non-metal at the anode. Ions must be able to move, so the solid salt does not work."
      "\n\n- " "Molten lead bromide can give lead at the cathode and bromine at the anode. Without mobile ions the solid cannot sustain electrolysis."),
    S("4.4.3.3", "Aluminium extraction", "Aluminium oxide dissolved in molten cryolite is electrolysed. Cryolite lowers operating temperature. Aluminium forms at the cathode and oxygen reacts with carbon anodes, which need replacement."
      "\n\n- " "In aluminium extraction oxygen formed at the anode reacts with carbon to form carbon dioxide. Replacing the anodes adds operating cost and emissions."),
    S("4.4.3.4", "Electrolysis in water", "At an inert cathode, hydrogen usually forms unless the metal is less reactive than hydrogen. At an inert anode, halide ions can form halogen; otherwise oxygen commonly forms from hydroxide."
      "\n\n- " "Aqueous copper chloride commonly gives copper and chlorine with inert electrodes. In a sulfate solution oxygen can form at the anode instead."),
    H("4.4.3.5", "Electrolysis half equations", "Cathode reduction gains electrons, e.g. Cu^2+ + 2e- -> Cu. Anode oxidation releases electrons, e.g. 2Cl- -> Cl2 + 2e-. Balance both atoms and total charge."
      "\n\n- " "For oxygen from OH-, 4OH- -> O2 + 2H2O + 4e-. Count H, O and total charge before accepting the half equation.")
};

#undef SCIENCE_MORE
#define SCIENCE_MORE "\n\nUnderstand the mechanism\n- Exothermic reactions transfer energy to the surroundings; endothermic reactions take energy from them. Reaction profiles compare reactant and product energies and show the activation energy barrier.\n\nApply your understanding\n- Breaking bonds requires energy, and forming bonds releases energy. An estimated overall energy change is energy needed to break bonds minus energy released on forming bonds. A catalyst changes the pathway and activation energy."
static const Topic chem_energy[] = {
    S("4.5.1.1", "Exothermic and endothermic", "Exothermic reactions warm the surroundings, as in combustion and many neutralisations. Endothermic reactions take energy from the surroundings, as in some dissolving processes. Applications include hot and cold packs."
      "\n\n- " "A thermometer measures the surroundings' temperature change. Apparatus also absorbs energy, so identical insulation and volumes matter for comparisons."),
    S("4.5.1.2", "Reaction energy profiles", "The height from reactants to the peak represents activation energy. Products below reactants indicate an exothermic change; products above them indicate an endothermic change."
      "\n\n- " "An exothermic forward reaction has a smaller forward activation barrier than the reverse when drawn on one common profile. Measure each from its own starting level."),
    H("4.5.1.3", "Bond energy calculations", "Bond breaking requires energy; bond formation releases energy. Overall energy change = sum of bond energies broken minus sum formed. A negative result is exothermic."
      "\n\n- " "For H2+Cl2 -> 2HCl using 436, 243 and 432 kJ/mol respectively, change=436+243-2*432=-185 kJ/mol of reaction."),
    S("4.5.2.1", "Chemical cells and batteries", "A cell generates potential difference from chemical reactions. Electrode materials and electrolytes affect voltage. Primary cells have finite reactants; a rechargeable cell uses electrical energy to reverse its reactions."
      "\n\n- " "Cells connected in series combine their potential differences if oriented in the same direction. Electrode materials and the electrolyte affect what voltage can be produced."),
    S("4.5.2.2", "Hydrogen fuel cells", "Supplying hydrogen and oxygen to a fuel cell produces electricity and water continuously. Compare refuelling, fuel production and storage, water at point of use, efficiency and infrastructure with rechargeable batteries."
      "\n\n- " "The point-of-use reaction forms water, but environmental impact also depends on how hydrogen is produced and transported. State this when comparing with batteries."),
    H("4.5.2.2", "Fuel cell half equations", "For an acidic fuel cell, anode: 2H2 -> 4H+ + 4e-. Cathode: O2 + 4H+ + 4e- -> 2H2O. Add the halves and cancel electrons and hydrogen ions."
      "\n\n- " "For acidic cells, combine 2H2 -> 4H+ + 4e- with O2 + 4H+ + 4e- -> 2H2O. Electrons cancel to give 2H2+O2 -> 2H2O.")
};

#undef SCIENCE_MORE
#define SCIENCE_MORE "\n\nUnderstand the mechanism\n- Rate depends on successful collisions between reacting particles. Concentration and pressure can change collision frequency; temperature also changes the fraction of particles with sufficient energy to react.\n\nApply your understanding\n- Use a tangent for an instantaneous rate and change divided by time for a mean rate. At dynamic equilibrium, forward and reverse reactions continue at equal rates, so concentrations remain constant in a closed system."
static const Topic chem_rates[] = {
    S("4.6.1.1", "Reaction rates and graphs", "Mean rate = quantity used or produced divided by time. Typical units are g/s or cm^3/s. On an amount-time graph a steeper tangent means a faster rate; a plateau means the amount stops changing."
      "\n\n- " "If gas volume rises by 30 cm^3 over the first 15 s, mean rate is 2 cm^3/s. A plateau indicates no further measured product under those conditions."),
    H("4.6.1.1", "Instantaneous rate in mol/s", "Draw a tangent at the required time and calculate rise/run from two points on it. If the quantity is in moles the rate is mol/s. Use a positive rate for the magnitude of reactant consumption."
      "\n\n- " "A tangent that rises by 0.012 mol over 8 s has gradient 0.0015 mol/s. Choose two distant points on the tangent to reduce reading uncertainty."),
    S("4.6.1.2", "Factors affecting reaction rate", "Higher concentration or gas pressure, greater exposed surface area and higher temperature can speed reactions. A catalyst can also increase the rate."
      "\n\n- " "Compare powdered and lumped solid with the same mass. Powder exposes more surface, so there can be more collisions per second."),
    S("4.6.1.3", "Collision theory", "Reactants must collide with enough energy. Higher concentration, pressure or area increases collision frequency. Higher temperature also increases the fraction of collisions with energy above activation energy."
      "\n\n- " "At higher temperature more collisions have enough energy to react, as well as occurring more frequently. Concentration raises collision frequency without supplying extra energy per particle."),
    S("4.6.1.4", "Catalysts", "A catalyst offers a reaction route with lower activation energy and is not used up overall. A catalysed reaction profile has a lower peak while reactant and product energies stay the same."
      "\n\n- " "A catalyst changes the activation energy, not the overall energy difference between products and reactants. It is regenerated in the reaction pathway."),
    S("4.6.2.1", "Reversible reactions", "Some products react back to form the original reactants. Use reversible arrows. Heating hydrated copper sulfate can remove water; adding water can restore its hydrated form."
      "\n\n- " "In a reversible reaction, the conditions can affect how much of each substance is present. The two arrows indicate both directions are possible."),
    S("4.6.2.2", "Energy in reversible reactions", "If the forward direction is exothermic, the reverse is endothermic by the same energy per stated amount of reaction. Reversing the equation reverses the sign."
      "\n\n- " "A forward energy change of -60 kJ/mol becomes +60 kJ/mol for the reverse of the same balanced equation."),
    S("4.6.2.3", "Dynamic equilibrium", "In a closed system a reversible reaction can reach a state where forward and reverse rates match. Reactant and product amounts stay constant while both reactions continue."
      "\n\n- " "A sealed system can reach a stable mixture that still reacts microscopically. Equal rates do not require equal amounts of reactants and products."),
    H("4.6.2.4", "Le Chatelier's principle", "Changing a condition of a system at equilibrium can shift the balance in the direction that counteracts the change. A catalyst speeds both directions and does not shift the final equilibrium position."
      "\n\n- " "After a disturbance the forward and reverse rates can temporarily differ. At the new equilibrium they are equal again, at changed concentrations."),
    H("4.6.2.5", "Concentration effects", "Adding a reactant usually favours the direction consuming it. Removing a product favours making more of it. Compare equilibrium position separately from the rate of reaching it."
      "\n\n- " "Removing a product drives net formation of more product until a new equilibrium forms. It does not necessarily restore its original concentration."),
    H("4.6.2.6", "Temperature at equilibrium", "Increasing temperature favours the endothermic direction; cooling favours the exothermic direction. Use the sign of the stated forward reaction to decide which side is favoured."
      "\n\n- " "For exothermic forward reaction, heating shifts equilibrium towards reactants. Heating may still increase the rates in both directions and shorten the time to reach equilibrium."),
    H("4.6.2.7", "Gas pressure at equilibrium", "Increasing pressure favours the side with fewer gas molecules according to equation coefficients. If the two sides have equal gas mole totals, pressure does not move the equilibrium position."
      "\n\n- " "For N2+3H2 <-> 2NH3, count four gas moles on the left and two on the right. Higher pressure favours ammonia at equilibrium.")
};

#undef SCIENCE_MORE
#define SCIENCE_MORE "\n\nUnderstand the mechanism\n- Connect a displayed or structural formula with its functional group and reaction. A homologous series shares a functional group, general formula and similar chemistry, with a trend in physical properties.\n\nApply your understanding\n- Write reactants and products clearly and conserve every atom. Distinguish complete combustion from incomplete combustion, and addition reactions from substitution or polymerisation. Include conditions when they are part of the required reaction."
static const Topic chem_organic[] = {
    S("4.7.1.1", "Crude oil and alkanes", "Crude oil is a finite mixture of hydrocarbons. Most are alkanes, saturated chains with general formula CnH(2n+2). Learn methane, ethane, propane and butane and recognise their displayed formulae."
      "\n\n- " "A hydrocarbon contains hydrogen and carbon only. The alkane series has the same general formula and broadly similar reactions, with trends as the chain grows."),
    S("4.7.1.2", "Fractional distillation", "Heating vaporises much of crude oil. A tower is hotter at the bottom and cooler at the top; fractions condense over different boiling ranges. Fractions provide fuels and petrochemical feedstocks."
      "\n\n- " "Shorter chains are more volatile and tend to condense higher up, where it is cooler. A fraction contains compounds with similar boiling ranges rather than one pure substance."),
    S("4.7.1.3", "Hydrocarbon trends and burning", "Longer chains generally have higher boiling points, greater viscosity and lower flammability. Complete combustion gives carbon dioxide and water. Limited oxygen can produce carbon monoxide and soot."
      "\n\n- " "Complete combustion of propane: C3H8+5O2 -> 3CO2+4H2O. Insufficient oxygen can instead form carbon monoxide or soot."),
    S("4.7.1.4", "Cracking and alkenes", "Cracking converts long-chain hydrocarbons into shorter alkanes and useful alkenes by catalytic or steam cracking. Alkenes have a C=C bond and decolourise bromine water."
      "\n\n- " "One possible cracking balance is C10H22 -> C8H18 + C2H4. Count both atoms to check it. Ethene is a useful feedstock for polymerising."),
    S("4.7.2.1", "Alkene structures", "An alkene with one C=C and an open chain has general formula CnH2n. Recognise ethene, propene, butene and pentene. The C=C is the functional group."
      "\n\n- " "Ethene is C2H4 and contains one double bond. Alkenes are unsaturated, so they can take part in addition reactions at that bond."),
    S("4.7.2.2", "Alkene reactions", "The double bond allows addition: hydrogen makes an alkane, steam can form an alcohol, and a halogen gives a dihalo product. Alkene flames can be smoky when combustion is incomplete."
      "\n\n- " "Adding bromine across ethene's double bond forms C2H4Br2. The loss of bromine water's orange colour gives a test for a C=C bond in this context."),
    S("4.7.2.3", "Alcohols", "Alcohols contain the -OH group. Know methanol through butanol. They can burn, react with sodium, and be oxidised to carboxylic acids. Ethanol can be made by yeast fermentation of sugar."
      "\n\n- " "Methanol through butanol share the alcohol group. Sodium can produce hydrogen and an alkoxide; oxidation of a suitable alcohol can form a carboxylic acid."),
    S("4.7.2.4", "Carboxylic acids and esters", "Carboxylic acids contain -COOH. The first four run methanoic to butanoic. They react with carbonates, and with alcohols can form esters. Ethanol plus ethanoic acid can produce ethyl ethanoate."
      "\n\n- " "Ethanoic acid plus a carbonate gives a salt, carbon dioxide and water. The ester from ethanol and ethanoic acid has the ethyl group from the alcohol."),
    H("4.7.2.4", "Carboxylic acid ionisation", "Carboxylic acids are weak: only a fraction of the dissolved molecules donate H+ to water. At equal concentration this gives a higher pH than a strong acid."
      "\n\n- " "Weak describes degree of ionisation, not safety or concentration. At equal molar concentration a weak monoprotic acid gives less H+ than a strong one."),
    S("4.7.3.1", "Addition polymers", "Alkene double bonds open so monomers link into long chains. Draw a repeat unit in brackets with bonds through the sides and subscript n. The process has no small-molecule by-product."
      "\n\n- " "Ethene produces poly(ethene), with repeating -CH2-CH2-. Keep the side groups in their original positions when converting a substituted alkene to its repeat unit."),
    H("4.7.3.2", "Condensation polymers", "Monomers with two functional groups can join and release a small molecule such as water. A diol and dicarboxylic acid can form a polyester with ester links."
      "\n\n- " "An ester linkage is -COO-. Each new ester link in the diol/dicarboxylic-acid model forms alongside a molecule of water."),
    H("4.7.3.3", "Amino acids and peptides", "Amino acids have amine and carboxylic acid groups. They can form peptide links by condensation. A polypeptide has an ordered sequence of amino-acid residues."
      "\n\n- " "An amino acid can join another through an amide (peptide) link and loss of water. Changing the sequence changes the polypeptide made."),
    S("4.7.3.4", "DNA and natural polymers", "DNA comprises two polymer strands of four types of nucleotide in a double helix. Proteins are polymers of amino acids; starch and cellulose are examples of sugar-based polymers."
      "\n\n- " "The nucleotide sequence stores information; a protein's sequence is a different kind of polymer. Starch and cellulose can have different properties despite being made from glucose units.")
};

#undef SCIENCE_MORE
#define SCIENCE_MORE "\n\nUnderstand the mechanism\n- Report the observation separately from the chemical conclusion. A colour change, precipitate or gas test gives evidence for a particular substance only when the reagent and conditions are appropriate.\n\nApply your understanding\n- Use separate samples for tests that would interfere with each other. In chromatography, compare spots under the same conditions, measure to the solvent front from the baseline, and account for more than one substance in a mixture."
static const Topic chem_analysis[] = {
    S("4.8.1.1", "Chemical purity", "A pure substance consists of a single element or compound and has characteristic melting and boiling points. Impurities can change these values or broaden the melting range."
      "\n\n- " "A mixture often melts over a range. Compare a measured melting point with a reference value as one piece of evidence for identity and purity."),
    S("4.8.1.2", "Formulations", "A formulation is a designed mixture with carefully measured amounts to achieve particular properties. Examples include paints, fuels, cleaners, foods, medicines and fertilisers."
      "\n\n- " "A formulation is adjusted to a purpose: paint may need pigment for colour, binder for adhesion and solvent to make it spreadable."),
    S("4.8.1.3", "Chromatography and Rf", "A mobile phase carries substances past a stationary phase. Components move different distances because of differences in attraction and solubility. Rf=distance of spot/distance of solvent front, both measured from baseline."
      "\n\n- " "A spot moving 3.2 cm with solvent front at 8.0 cm gives Rf=0.40. Compare with references only under the same solvent and paper conditions."),
    S("4.8.2.1", "Hydrogen test", "A lit splint gives a squeaky pop with hydrogen."
      "\n\n- " "Distinguish a lit splint for hydrogen from a glowing splint for oxygen. The characteristic sound is brief when hydrogen burns near the flame."),
    S("4.8.2.2", "Oxygen test", "A glowing splint relights in oxygen."
      "\n\n- " "A glowing splint relighting indicates enough oxygen to support combustion. An ordinary flame test on a metal ion answers a different question."),
    S("4.8.2.3", "Carbon dioxide test", "Carbon dioxide turns limewater cloudy because a calcium carbonate precipitate forms."
      "\n\n- " "The cloudiness is a precipitate, not gas bubbles. A carbonate with acid gives carbon dioxide that can be passed into limewater."),
    S("4.8.2.4", "Chlorine test", "Chlorine bleaches damp litmus paper. It may turn the litmus red briefly before bleaching it."
      "\n\n- " "Report bleaching of damp litmus as the positive result. Dry paper is less suitable because water is involved in the reaction causing bleaching."),
    S("4.8.3.1", "Flame tests", "Lithium: crimson. Sodium: yellow. Potassium: lilac. Calcium: orange-red. Copper: green-blue. Contamination or several metals can mask colours."
      "\n\n- " "Use a clean wire and avoid cross-contamination. Sodium's strong yellow emission can mask more subtle colours from other ions."),
    S("4.8.3.2", "Metal hydroxide tests", "With sodium hydroxide, Al, Ca and Mg ions give white precipitates; aluminium hydroxide dissolves in excess. Cu(II) is blue, Fe(II) green, and Fe(III) brown."
      "\n\n- " "Aluminium hydroxide dissolves in excess sodium hydroxide, unlike the other white precipitates here. Use fresh portions for separate tests."),
    S("4.8.3.3", "Carbonate ion test", "Adding dilute acid to carbonate releases carbon dioxide. Confirm the gas with limewater."
      "\n\n- " "Use the acid reaction and limewater together. Effervescence alone does not identify the gas as carbon dioxide."),
    S("4.8.3.4", "Halide ion tests", "Acidify a sample with dilute nitric acid. Silver nitrate produces silver chloride white, silver bromide cream, or silver iodide yellow."
      "\n\n- " "Use nitric acid rather than hydrochloric acid for the halide test because hydrochloric acid supplies chloride and can cause a false precipitate."),
    S("4.8.3.5", "Sulfate ion test", "With dilute hydrochloric acid followed by barium chloride, sulfate produces a white barium sulfate precipitate."
      "\n\n- " "Acidifying removes carbonate interference before testing for sulfate. Use a separate portion from the halide test to avoid mixing reagents."),
    S("4.8.3.6", "Instrumental analysis", "Instrumental methods can be fast, sensitive and accurate, and distinguish mixtures. Compare equipment cost, preparation and operator requirements with simple chemical tests."
      "\n\n- " "Use a reference or calibration where relevant. Instrumental methods may detect smaller quantities than a visual comparison."),
    S("4.8.3.7", "Flame emission spectroscopy", "An excited ion emits a characteristic set of wavelengths. Compare line positions with references to identify ions. Calibrated intensities can give concentrations."
      "\n\n- " "Compare wavelength positions for identification and intensities against known concentrations for quantification. Mixtures can show several sets of lines.")
};

#undef SCIENCE_MORE
#define SCIENCE_MORE "\n\nUnderstand the mechanism\n- Separate a source of a gas from its effect. Combustion can release carbon dioxide and other pollutants, while different pollutants have different impacts on health, materials and ecosystems.\n\nApply your understanding\n- Greenhouse gases absorb outgoing infrared radiation. This differs from ozone depletion. Explain a claim about climate using the evidence, its uncertainty and the distinction between a short-term fluctuation and a longer-term trend."
static const Topic chem_atmosphere[] = {
    S("4.9.1.1", "The atmosphere today", "Dry air is about 78% nitrogen, 21% oxygen and about 1% other gases, mainly argon with a small carbon dioxide fraction. Water vapour varies."
      "\n\n- " "The percentages are approximate proportions in dry air. Water vapour varies with location and conditions, making wet air composition a little different."),
    S("4.9.1.2", "Early atmosphere", "Volcanic emissions probably supplied carbon dioxide, water vapour and nitrogen, with very little oxygen at first. As Earth cooled, water condensed and oceans formed. Evidence about the early atmosphere is incomplete."
      "\n\n- " "Evidence about the early atmosphere is indirect. Volcanic gas composition and models support an atmosphere unlike today's, with little or no free oxygen early on."),
    S("4.9.1.3", "Oxygen in the atmosphere", "Early algae and later plants released oxygen by photosynthesis. Rising oxygen eventually supported aerobic organisms and changed the atmosphere."
      "\n\n- " "The increase was gradual: early photosynthetic organisms released oxygen, and some of it reacted with materials before much accumulated in the atmosphere."),
    S("4.9.1.4", "Removal of carbon dioxide", "Carbon dioxide dissolved in oceans and became incorporated in carbonates. Photosynthesis moved carbon into organisms; burial produced deposits including carbonate rocks and fossil fuels."
      "\n\n- " "Dissolved carbon can enter shells and sediments. Burial preserves some carbon long-term, while respiration of living or decaying biomass returns some quickly."),
    S("4.9.2.1", "Greenhouse gases", "Water vapour, carbon dioxide and methane absorb outgoing infrared and re-emit it. Incoming solar radiation warms the surface, and the greenhouse effect keeps Earth warmer than it would otherwise be."
      "\n\n- " "Separate incoming short-wavelength radiation from outgoing infrared. Greenhouse gases absorb some outgoing infrared and emit it again, including back towards the surface."),
    S("4.9.2.2", "Human sources of greenhouse gases", "Burning fossil fuels and deforestation raise carbon dioxide. Livestock, rice cultivation, landfill and fossil fuel production can emit methane. Distinguish direct releases from changes in carbon uptake."
      "\n\n- " "Distinguish gas sources by activity. Fossil burning releases stored carbon as CO2; cattle, landfill and some fossil fuel extraction can release methane."),
    S("4.9.2.3", "Global climate change", "Evidence includes temperature trends and changes in ice, rainfall and sea level. Models include uncertainty and are evaluated against observations. Potential impacts include flooding, drought and shifts in habitats."
      "\n\n- " "Evaluate model predictions against measurements and consider uncertainty. Changes to extreme weather risk can occur even though individual events have multiple causes."),
    S("4.9.2.4", "Carbon footprint", "A footprint estimates greenhouse gases attributable to a product, activity or organisation across its life cycle. Ways to cut emissions include efficiency, lower-carbon energy, reduced demand and carbon capture."
      "\n\n- " "A life-cycle comparison includes manufacture as well as use. For an electric device, the electricity source affects use-phase emissions."),
    S("4.9.3.1", "Pollutants from fuels", "Combustion can release carbon dioxide, carbon monoxide, particulates, sulfur dioxide and nitrogen oxides. Incomplete combustion favours carbon monoxide and soot; high temperatures allow nitrogen and oxygen to react."
      "\n\n- " "Incomplete fuel combustion leads to CO when oxygen is limited. Nitrogen oxides can arise from nitrogen and oxygen in hot engines rather than from nitrogen in the fuel itself."),
    S("4.9.3.2", "Effects of pollutants", "Carbon monoxide reduces blood oxygen transport. Sulfur dioxide and nitrogen oxides can cause respiratory problems and acid rain. Particulates harm lungs and can contribute to global dimming."
      "\n\n- " "CO binds to haemoglobin and reduces oxygen transport. Sulfur and nitrogen oxides can contribute to acid deposition; fine particulates can enter the lungs.")
};

#undef SCIENCE_MORE
#define SCIENCE_MORE "\n\nUnderstand the mechanism\n- Compare a process using its feedstocks, energy use, useful output and waste. A renewable resource is replenished on a suitable timescale, while a finite resource is depleted as it is used.\n\nApply your understanding\n- Life-cycle assessments include raw materials, manufacture, use and disposal. State the boundary and data used before comparing alternatives. Recycling can reduce extraction and waste but also requires collection, sorting and processing."
static const Topic chem_resources[] = {
    S("4.10.1.1", "Resources and sustainability", "Natural resources supply food, water, energy and materials. Renewable resources can replace themselves on useful timescales; finite resources cannot. Sustainable decisions consider current needs and future access."
      "\n\n- " "Compare resource extraction with replenishment. Using a renewable resource faster than it regenerates can still be unsustainable."),
    S("4.10.1.2", "Potable water", "Potable water has safe levels of dissolved substances and microbes. Freshwater treatment uses filtration and sterilisation. Desalination by distillation or reverse osmosis needs energy."
      "\n\n- " "Potable does not mean chemically pure. Distillation removes dissolved salts, while water treatment also addresses microorganisms and suspended particles."),
    S("4.10.1.3", "Waste water treatment", "Screen and settle sewage to remove solids, treat sludge with anaerobic digestion and the liquid effluent aerobically. Industrial wastewater may need extra treatment for specific contaminants."
      "\n\n- " "Settling separates solids as sludge. Anaerobic digestion treats sludge without oxygen, while aerobic organisms help break down organic material in the liquid."),
    H("4.10.1.4", "Bioleaching and phytomining", "Bioleaching releases copper compounds into solution through microbial action. In phytomining plants take up metals and the harvested material yields metal compounds. Compare these low-grade ore methods with traditional extraction."
      "\n\n- " "These approaches can use low-grade material but are often slower. Copper in the resulting solution still needs recovering, for example by displacement or electrolysis as appropriate."),
    S("4.10.2.1", "Life cycle assessment", "Track extraction, manufacture, transport, use and disposal. Compare energy, water, resources and pollution. Weightings can be subjective and missing data can change conclusions."
      "\n\n- " "Specify what functional unit is compared, such as one product use. A reusable item can have a higher production impact but spread it over many uses."),
    S("4.10.2.2", "Reduce, reuse and recycle", "Reduce demand first where possible. Reuse extends product life. Recycling reduces raw material extraction but needs collection, separation and processing. Glass and metals illustrate different reuse and recycling routes."
      "\n\n- " "Recycling aluminium can save extraction energy but still needs separation and processing. Reuse can be preferable when transport and cleaning do not erase the savings."),
    S("4.10.3.1", "Corrosion and prevention", "Rusting needs oxygen and water. A coating gives a barrier. Galvanising protects iron with zinc, which also corrodes preferentially if the coating is scratched. More reactive metals can provide sacrificial protection."
      "\n\n- " "Scratched paint exposes iron, whereas surrounding zinc can still sacrificially oxidise. Both methods can limit contact with water and oxygen while intact."),
    S("4.10.3.2", "Useful alloys", "Bronze contains copper and tin, brass copper and zinc. Steels contain iron with variable carbon or other elements. Aluminium alloys are light; jewellery alloys harden gold. Match properties to use."
      "\n\n- " "Low-carbon steel and high-carbon steel can have different hardness. Stainless steel contains other elements to improve corrosion resistance."),
    S("4.10.3.3", "Ceramics, polymers and composites", "Glass and clay ceramics are usually hard and brittle. Thermosoftening polymers can reshape on warming; cross-linked thermosets cannot. Composites combine a matrix with reinforcement, such as glass fibres in a polymer."
      "\n\n- " "In a composite the matrix holds the reinforcement in place, and the reinforcement supplies properties such as stiffness. Match each component to the application."),
    S("4.10.4.1", "The Haber process", "Nitrogen from air reacts reversibly with hydrogen, commonly from natural gas, to make ammonia. Typical conditions are about 450 C, 200 atmospheres and an iron catalyst. Cool to remove ammonia and recycle unreacted gases."
      "\n\n- " "The balanced reaction is N2+3H2 <-> 2NH3. Cooling and removing ammonia allow unreacted feed gases to be recirculated."),
    H("4.10.4.1", "Optimising Haber conditions", "Higher pressure favours fewer gas moles and raises rate but costs more. Lower temperature favours exothermic ammonia production but slows rate. Industrial conditions balance rate, yield, safety and cost."
      "\n\n- " "A catalyst speeds attainment of equilibrium without shifting it. High pressure improves yield at additional plant and energy cost; temperature is a rate-yield compromise."),
    S("4.10.4.2", "NPK fertilisers", "N, P and K are essential plant nutrients. Ammonia is used to make ammonium compounds. Potassium salts can come from mined deposits. Phosphate rock is treated to make useful soluble phosphates. Formulate ratios for different crops."
      "\n\n- " "Ammonium salts supply nitrogen and soluble phosphates supply phosphorus. Compare how readily nutrients are available to plants and the risk of nutrient runoff.")
};

#undef SCIENCE_MORE
#define SCIENCE_MORE "\n\nUnderstand the mechanism\n- Explain changes using particles, atoms and electrons. Chemical reactions rearrange atoms, and balanced equations express conservation of atoms. A coefficient changes the number of formula units; a subscript changes the formula itself.\n\nApply your understanding\n- Relate an observation to a model and give the intermediate reasoning. For example, explain a change in conductivity by identifying the charge carriers and whether they can move, rather than stating only that bonding has changed."
static const Topic chem_key[] = {
    S("4.11", "Chemistry key ideas", "Explain patterns using particles, bonding, energetics and electron structure. Equations represent changes with conserved atoms. Rates depend on collisions, and reactions can reach equilibrium."
      "\n\n- " "For an explanation, connect the observed property or change to the particles involved and the relevant bonding, energy or collision model.")
};

#undef SCIENCE_MORE
#define SCIENCE_MORE "\n\nUnderstand the mechanism\n- Give a repeatable sequence with measured quantities, suitable apparatus and a clear endpoint. State how a hazard is controlled and why the control reduces the relevant risk.\n\nApply your understanding\n- Select measurements that test the intended relationship. Rinse equipment appropriately, record values with units and repeat measurements. Discuss losses, contamination and heat exchange when they affect the quantity being calculated."
static const Topic chem_practicals[] = {
    S("RP1", "Making a pure soluble salt", "Prepare a soluble salt from excess insoluble oxide or carbonate and dilute acid. Explain excess, filtration, partial evaporation, crystallisation and drying."
      "\n\n- " "Warm the acid as directed in a supervised experiment, use excess insoluble base and filter before concentrating. Prevent spitting and avoid evaporating the solution to dryness."),
    S("RP2", "Acid-alkali titration", "Compare measured reacting volumes using a pipette, burette and indicator. Carry out a rough determination then repeat for concordant results and calculate a mean."
      "\n\n- " "The titre is the final burette reading minus the initial one. Repeat slowly near the colour change and use concordant results."),
    H("RP2", "Concentration by titration", "Calculate moles in the known solution using its concentration and titre or aliquot. Use the reaction ratio, then divide by the other volume in dm^3 and convert to g/dm^3 if asked."
      "\n\n- " "Use volume in dm^3 before multiplying by concentration. Divide by the known volume of the unknown solution after applying the balanced ratio."),
    S("RP3", "Aqueous electrolysis", "Use inert electrodes in a school investigation to compare products from different aqueous electrolytes. Identify which product forms at which electrode and explain it using the ions present."
      "\n\n- " "Use labelled electrodes and account for dissolved ions and water. Compare positive tests against expected products using a supervised school procedure."),
    S("RP4", "Temperature changes in reactions", "Measure the peak or minimum temperature after mixing. Control initial temperature, amounts and insulation. Plot the temperature change against the chosen independent variable."
      "\n\n- " "Use the same total volume and initial temperature if appropriate. An insulated cup with a lid reduces energy loss and improves comparison."),
    S("RP5", "Concentration and rate", "Compare rates at different concentrations by gas volume over time or time to an agreed visible change. Keep other variables constant and use repeated readings or initial slopes."
      "\n\n- " "A gas syringe gives a volume-time graph; use the initial gradient for initial rate. Define a clear endpoint if using a visible change instead."),
    S("RP6", "Paper chromatography", "Make a pencil baseline above the solvent. Apply small samples, mark the solvent front when the paper is removed, and compare spot positions or Rf values under identical conditions."
      "\n\n- " "Keep solvent below sample spots to stop them washing into the solvent pool. Mark the front immediately because solvent can evaporate."),
    S("RP7", "Identifying ions", "Use separate aliquots for flame, hydroxide, carbonate, sulfate and halide tests as appropriate. Compare colours, precipitates or gas tests with known ions; distinguish a positive observation from an inference."
      "\n\n- " "Keep samples and reagents labelled and use separate portions. Several positive tests can identify both the cation and anion of a salt."),
    S("RP8", "Water analysis and purification", "Compare water samples by pH and dissolved solids. Evaporating a measured sample can reveal residue; distillation can separate water from dissolved solids. Compare the original sample with the distillate."
      "\n\n- " "Measure the original water volume before evaporating and compare residues per equal volume. A distillate can have less dissolved material without proving it is safe to drink.")
};

#undef SCIENCE_MORE
#define SCIENCE_MORE "\n\nUnderstand the mechanism\n- A testable explanation makes predictions that can be compared with observations. Identify the variable changed, the outcome measured and other influences controlled. Describe the evidence needed to support the conclusion.\n\nApply your understanding\n- Quote values from the data, with units, when comparing results. Distinguish random variation from systematic error. A large sample improves an estimate, but repeated measurements alone cannot remove an incorrectly calibrated instrument's bias."
static const Topic science_skills[] = {
    S("3.1", "Developing scientific explanations", "A hypothesis gives a testable prediction. Models represent important features and have limits. New evidence can support or overturn an explanation. Evaluate risks, ethical implications, peer review and whether findings apply to the wider population."
      "\n\n- " "A good conclusion separates observation and interpretation. Evaluate an explanation using quality, quantity, independence and consistency of evidence."),
    S("3.2", "Designing an investigation", "Change the independent variable, measure the dependent variable and control other influences. Choose suitable apparatus, range, intervals and sample size. A control gives a baseline; repeat readings and other groups' results help assess reliability."
      "\n\n- " "Choose a range broad enough to show a pattern, with intervals small enough to detect changes. Control variables that could independently affect the result."),
    S("3.3", "Analysing data and evidence", "Use tables with units and suitable graphs. Interpret anomalies, gradients, patterns and uncertainty. Repeatability uses the same method and conditions; reproducibility can involve different people or equipment. Give a conclusion limited by the evidence."
      "\n\n- " "An anomalous point should be investigated, not automatically discarded. Show how excluding it affects a mean or conclusion if relevant."),
    S("3.4", "Terminology and measurements", "Accuracy is closeness to the true value; precision concerns the spread of readings. Resolution is the smallest detectable change. Random variation is reduced by averaging; systematic error needs correction. Use appropriate SI units and significant figures."
      "\n\n- " "Check instrument zero, read scales at eye level where appropriate and distinguish uncertainty from mistakes. High precision can coexist with systematic bias."),
    S("7", "Mathematical skills", "Use ratios, rates, percentages, areas, volumes and scientific notation. Convert units before substituting and rearrange equations consistently. Read scales, calculate a mean and gradient, and interpret graphs and proportional relationships."
      "\n\n- " "For a graph gradient choose two sufficiently separated points on the line and calculate rise/run. Include units from both axes and avoid rounding intermediate values.")
};

static const Chapter aqa_physics[] = {
    CH("Energy", phys_energy), CH("Electricity", phys_electric), CH("Particle model of matter", phys_particles),
    CH("Atomic structure", phys_atoms), CH("Forces", phys_forces), CH("Waves", phys_waves),
    CH("Magnetism and electromagnetism", phys_magnets), CH("Space physics", phys_space), CH("Key ideas", phys_key),
    CH("Required practicals", phys_practicals), CH("Working scientifically and maths", science_skills)
};

static const Chapter aqa_biology[] = {
    CH("Cell biology", bio_cells), CH("Organisation", bio_org), CH("Infection and response", bio_infection),
    CH("Bioenergetics", bio_energy), CH("Homeostasis and response", bio_control),
    CH("Inheritance, variation and evolution", bio_genetics), CH("Ecology", bio_ecology), CH("Key ideas", bio_key),
    CH("Required practicals", bio_practicals), CH("Working scientifically and maths", science_skills)
};

static const Chapter aqa_chemistry[] = {
    CH("Atomic structure and periodic table", chem_atoms), CH("Bonding and properties of matter", chem_bonds),
    CH("Quantitative chemistry", chem_amount), CH("Chemical changes", chem_changes), CH("Energy changes", chem_energy),
    CH("Rate and extent of chemical change", chem_rates), CH("Organic chemistry", chem_organic),
    CH("Chemical analysis", chem_analysis), CH("Chemistry of the atmosphere", chem_atmosphere),
    CH("Using resources", chem_resources), CH("Key ideas", chem_key), CH("Required practicals", chem_practicals),
    CH("Working scientifically and maths", science_skills)
};

#undef H
#undef S
