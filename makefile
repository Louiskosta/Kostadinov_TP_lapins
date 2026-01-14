# ============================================================================
# Makefile - Simulation de Population de Lapins
# ============================================================================

# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra -std=c17 -Isrc/core -Isrc/external/mt19937ar-cok
LDFLAGS = -lm -lgmp -lmpfr

# Répertoires
SRC_CORE = src/core
SRC_PROGRAMS = src/programs
SRC_EXTERNAL = src/external/mt19937ar-cok
BUILD_DIR = build
BIN_DIR = bin
DATA_DIR = data

# Exécutables
TARGET = $(BIN_DIR)/exe
EXPERIMENTS = $(BIN_DIR)/experiments
GRAPHIQUES = $(BIN_DIR)/graphiques
FIBO = $(BIN_DIR)/fibo

# Fichiers objets (dans build/)
CORE_OBJS = $(BUILD_DIR)/simulation.o $(BUILD_DIR)/config.o $(BUILD_DIR)/population.o \
            $(BUILD_DIR)/aging.o $(BUILD_DIR)/reproduction.o
MT_OBJ = $(BUILD_DIR)/mt19937ar-cok.o

MAIN_OBJS = $(BUILD_DIR)/main.o $(CORE_OBJS) $(MT_OBJ)
EXP_OBJS = $(BUILD_DIR)/experiments.o $(CORE_OBJS) $(MT_OBJ)
GRAPH_OBJS = $(BUILD_DIR)/graphiques.o $(CORE_OBJS) $(MT_OBJ)
FIBO_OBJS = $(BUILD_DIR)/fibo.o $(MT_OBJ)

# ============================================================================
# Règles principales
# ============================================================================

all: dirs $(TARGET) $(EXPERIMENTS) $(GRAPHIQUES) $(FIBO)

dirs:
	@mkdir -p $(BUILD_DIR) $(BIN_DIR) $(DATA_DIR)

$(TARGET): $(MAIN_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(EXPERIMENTS): $(EXP_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(GRAPHIQUES): $(GRAPH_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(FIBO): $(FIBO_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# ============================================================================
# Règles de compilation des objets
# ============================================================================

# Programmes principaux
$(BUILD_DIR)/main.o: $(SRC_PROGRAMS)/main.c $(SRC_CORE)/simulation.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/experiments.o: $(SRC_PROGRAMS)/experiments.c $(SRC_CORE)/*.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/graphiques.o: $(SRC_PROGRAMS)/graphiques.c $(SRC_CORE)/*.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/fibo.o: $(SRC_PROGRAMS)/fibo.c $(SRC_EXTERNAL)/mt19937ar-cok.h
	$(CC) $(CFLAGS) -c $< -o $@

# Modules core
$(BUILD_DIR)/simulation.o: $(SRC_CORE)/simulation.c $(SRC_CORE)/simulation.h \
                            $(SRC_CORE)/population.h $(SRC_CORE)/reproduction.h $(SRC_CORE)/aging.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/config.o: $(SRC_CORE)/config.c $(SRC_CORE)/config.h $(SRC_CORE)/simulation.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/population.o: $(SRC_CORE)/population.c $(SRC_CORE)/population.h \
                            $(SRC_CORE)/simulation.h $(SRC_CORE)/reproduction.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/aging.o: $(SRC_CORE)/aging.c $(SRC_CORE)/aging.h \
                      $(SRC_CORE)/simulation.h $(SRC_CORE)/config.h $(SRC_CORE)/reproduction.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/reproduction.o: $(SRC_CORE)/reproduction.c $(SRC_CORE)/reproduction.h \
                              $(SRC_CORE)/simulation.h
	$(CC) $(CFLAGS) -c $< -o $@

# Bibliothèque externe
$(BUILD_DIR)/mt19937ar-cok.o: $(SRC_EXTERNAL)/mt19937ar-cok.c $(SRC_EXTERNAL)/mt19937ar-cok.h
	$(CC) $(CFLAGS) -c $< -o $@

# ============================================================================
# Règles utilitaires
# ============================================================================

clean:
	rm -rf $(BUILD_DIR)/* $(BIN_DIR)/*

clean-all: clean
	rm -rf $(DATA_DIR)/*.dat $(DATA_DIR)/*.gp $(DATA_DIR)/*.png

run-exe: $(TARGET)
	$(TARGET)

run-fibo: $(FIBO)
	$(FIBO) 15

run-experiments: $(EXPERIMENTS)
	$(EXPERIMENTS)

run-graphiques: $(GRAPHIQUES)
	cd $(DATA_DIR) && ../$(GRAPHIQUES)

doc:
	doxygen Doxyfile

help:
	@echo "Makefile - Simulation de Population de Lapins"
	@echo ""
	@echo "Cibles disponibles:"
	@echo "  all              - Compile tous les programmes (défaut)"
	@echo "  clean            - Supprime les fichiers objets et exécutables"
	@echo "  clean-all        - Supprime aussi les données générées"
	@echo "  run-exe          - Compile et exécute la simulation simple"
	@echo "  run-fibo         - Compile et exécute Fibonacci"
	@echo "  run-experiments  - Compile et exécute les expériences"
	@echo "  run-graphiques   - Compile et génère les graphiques"
	@echo "  doc              - Génère la documentation Doxygen"
	@echo "  help             - Affiche cette aide"

.PHONY: all dirs clean clean-all run-exe run-fibo run-experiments run-graphiques doc help
