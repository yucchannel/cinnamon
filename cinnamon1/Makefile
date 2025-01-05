CC = gcc
CFLAGS = -Wall
SRC = cinnamon1/src/cinnamon_interpreter.c
OBJ = cinnamon_interpreter.o
EXEC = cinnamon

# リモートバージョンのURL
REMOTE_VERSION_URL = "https://raw.githubusercontent.com/Yuto_DEVELOP/cinnamon/main/version.txt"
VERSION_FILE = "current_version.txt"

all: $(EXEC) check_updates

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)

# クリーンアップ
clean:
	rm -f $(OBJ) $(EXEC)

# 更新チェック
check_updates:
	@echo "Checking for updates..."
	@gcc -o update_checker update_checker.c
	@./update_checker

# 更新処理
update:
	@git pull origin main
	@echo "Updating version to 1.0.0"
	@echo "1.0.0" > $(VERSION_FILE)

# バージョンチェックのためのスクリプトを実行
check_version:
	@echo "Checking version..."
	@./update_checker

