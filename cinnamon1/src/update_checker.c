#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERSION_FILE_URL "https://raw.githubusercontent.com/Yuto_DEVELOP/cinnamon/main/version.txt"
#define LOCAL_VERSION_FILE "current_version.txt"

// 関数: バージョン情報をリモートから取得
void get_remote_version(char *version) {
    FILE *fp = popen("curl -s " VERSION_FILE_URL, "r");
    fgets(version, 256, fp);
    fclose(fp);
}

// 関数: ローカルのバージョン情報を取得
void get_local_version(char *version) {
    FILE *fp = fopen(LOCAL_VERSION_FILE, "r");
    fgets(version, 256, fp);
    fclose(fp);
}

// 関数: アップデートの確認
int check_for_updates() {
    char remote_version[256], local_version[256];
    get_remote_version(remote_version);
    get_local_version(local_version);
    
    // 改行を取り除く
    remote_version[strcspn(remote_version, "\n")] = '\0';
    local_version[strcspn(local_version, "\n")] = '\0';
    
    if (strcmp(remote_version, local_version) != 0) {
        return 1; // アップデートが必要
    }
    return 0; // アップデートは不要
}

// 関数: アップデートを実行
void update() {
    printf("New version available! Updating...\n");
    system("git pull origin main");
    FILE *fp = fopen(LOCAL_VERSION_FILE, "w");
    fputs("1.0.0", fp); // 新しいバージョンを書き込む
    fclose(fp);
    printf("Update complete!\n");
}

int main() {
    if (check_for_updates()) {
        update();
    } else {
        printf("You are already using the latest version.\n");
    }
    return 0;
}
