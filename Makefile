TARGET_EXEC := main
BUILD_DIR   := ./build
SRC_DIR     := ./src

$(BUILD_DIR)/$(TARGET_EXEC): $(SRC_DIR)/main.c $(SRC_DIR)/token.c $(SRC_DIR)/token.h $(SRC_DIR)/lexico.c $(SRC_DIR)/lexico.h
	mkdir -p $(BUILD_DIR)
	cc $(SRC_DIR)/main.c -o $(BUILD_DIR)/$(TARGET_EXEC)

clean:
	rm -rf $(BUILD_DIR)
