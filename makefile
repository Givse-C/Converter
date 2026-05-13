# --- CONFIGURAZIONE ---
CXX      := g++
CXXFLAGS := -I./include -std=c++20 -Wall -Wextra
TARGET   := converter

# --- DIRECTORY ---
SRC_DIR  := src
OBJ_DIR  := build

# --- TROVA I SORGENTI E DEFINISCE GLI OGGETTI ---
# Trova tutti i .cpp in src/
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
# Trasforma i nomi da src/file.cpp a build/file.o
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# --- REGOLE PRINCIPALI ---

# Regola di default: compila l'eseguibile
all: $(OBJ_DIR) $(TARGET)

# Crea l'eseguibile unendo i file oggetto
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)
	@echo "[SYSTEM] Build complete: $(TARGET) is ready for launch."

# Compila i singoli file .cpp in file .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Crea la cartella build se non esiste
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# --- UTILITY ---

# Pulisce i file della compilazione
clean:
	rm -rf $(OBJ_DIR) $(TARGET)
	@echo "[SYSTEM] Cleanup complete. Station reset."

# Impedisce conflitti se esistono file chiamati 'all' o 'clean'
.PHONY: all clean