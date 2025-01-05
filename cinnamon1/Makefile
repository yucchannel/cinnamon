# コンパイルオプション
CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c99

# ソースファイルとターゲット名
SRC_DIR = cinnamon1/src
BIN_DIR = bin
SRC_FILES = $(SRC_DIR)/cinnamon_interpreter.c $(SRC_DIR)/plugin.c
TARGET = $(BIN_DIR)/cinnamon

# 出力ディレクトリ
OBJ_FILES = $(SRC_FILES:.c=.o)

# ビルドターゲット
all: $(TARGET)

# 実行ファイルを作成
$(TARGET): $(OBJ_FILES) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ_FILES)

# オブジェクトファイルを作成
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# プラグインのディレクトリ作成（必要に応じて）
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# クリーンアップ
clean:
	rm -rf $(OBJ_FILES) $(TARGET)

# インストール
install: all
	cp $(TARGET) /usr/local/bin/

.PHONY: all clean install
