# Compilador
CXX = g++

# Flags
CXXFLAGS = -Wall -std=c++11 -Iinclude

# Diretórios
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Fontes
SRCS = $(SRC_DIR)/main.cpp \
       $(SRC_DIR)/Dicionario.cpp \
       $(SRC_DIR)/Grafo.cpp \
       $(SRC_DIR)/Tema.cpp \
       $(SRC_DIR)/Usuario.cpp \
       $(SRC_DIR)/No.cpp
# Objetos
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Executável obrigatório
TARGET = $(BIN_DIR)/tp1.out

# Regra principal
all: $(TARGET)

# Linkagem
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilação
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza
clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)

# Recompilar
rebuild: clean all