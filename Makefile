SRC_DIR := ./src
INCLUDE_DIR := ./include
BUILD_DIR := ./build
BIN_DIR := ./bin

CC := gcc
CFLAGS := -Wall -I$(INCLUDE_DIR)

TARGET_EXEC := $(BIN_DIR)/main
OBJECTS := $(addprefix $(BUILD_DIR)/, main.o token.o) #lexico.o sintactico.o)

.PHONY: clean all

all: $(TARGET_EXEC)

$(TARGET_EXEC): $(OBJECTS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(^) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
