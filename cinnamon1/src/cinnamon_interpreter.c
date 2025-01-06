#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 100
#define MAX_PLUGIN_NAME 50
#define MAX_TOKEN_VALUE 256

// トークンタイプの定義
typedef enum {
    TOKEN_INT, TOKEN_IDENTIFIER, TOKEN_NUMBER, TOKEN_PLUS, TOKEN_EOF, TOKEN_UNKNOWN
} TokenType;

typedef struct {
    TokenType type;
    char value[MAX_TOKEN_VALUE];
} Token;

// ASTノードタイプの定義
typedef enum {
    AST_DECLARATION, AST_ASSIGNMENT, AST_ADDITION, AST_NUMBER
} ASTNodeType;

typedef struct ASTNode {
    ASTNodeType type;
    char value[MAX_TOKEN_VALUE];
    struct ASTNode *left, *right;
} ASTNode;

// プラグインの構造体
typedef struct Plugin {
    char name[MAX_PLUGIN_NAME];
    void (*execute)(const char *, const char *);  // 2つの引数を受け取る関数ポインタ
} Plugin;

// 字句解析
Token get_next_token(const char *source, int *pos) {
    Token token = {TOKEN_UNKNOWN, ""};
    while (source[*pos] != '\0' && isspace(source[*pos])) (*pos)++;  // スペースをスキップ

    if (isdigit(source[*pos])) {
        token.type = TOKEN_NUMBER;
        int i = 0;
        while (isdigit(source[*pos])) {
            if (i >= MAX_TOKEN_VALUE - 1) {
                fprintf(stderr, "Token too long\n");
                exit(1);
            }
            token.value[i++] = source[*pos];
            (*pos)++;
        }
        token.value[i] = '\0';
        return token;
    }

    if (source[*pos] == '+') {
        token.type = TOKEN_PLUS;
        token.value[0] = source[*pos];
        token.value[1] = '\0';
        (*pos)++;
        return token;
    }

    if (source[*pos] == '\0') {
        token.type = TOKEN_EOF;
        return token;
    }

    if (isalpha(source[*pos])) {
        token.type = TOKEN_IDENTIFIER;
        int i = 0;
        while (isalnum(source[*pos])) {
            if (i >= MAX_TOKEN_VALUE - 1) {
                fprintf(stderr, "Token too long\n");
                exit(1);
            }
            token.value[i++] = source[*pos];
            (*pos)++;
        }
        token.value[i] = '\0';
        return token;
    }

    token.type = TOKEN_UNKNOWN;
    return token;
}

// ASTノード作成
ASTNode* create_ast_node(ASTNodeType type, char *value) {
    ASTNode *node = malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    node->type = type;
    strcpy(node->value, value);
    node->left = NULL;
    node->right = NULL;
    return node;
}

// 式の解析
ASTNode* parse_expression(Token tokens[], int *pos) {
    ASTNode *node = create_ast_node(AST_NUMBER, tokens[*pos].value);
    (*pos)++;
    if (tokens[*pos].type == TOKEN_PLUS) {
        (*pos)++;
        ASTNode *right = parse_expression(tokens, pos);
        ASTNode *parent = create_ast_node(AST_ADDITION, "+");
        parent->left = node;
        parent->right = right;
        return parent;
    }
    return node;
}

// AST評価
int evaluate(ASTNode *node) {
    if (node->type == AST_NUMBER) {
        return atoi(node->value);
    }

    if (node->type == AST_ADDITION) {
        return evaluate(node->left) + evaluate(node->right);
    }

    return 0;
}

// ファイルの読み込み
char* read_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        exit(1);
    }
    
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char *content = malloc(length + 1);
    if (!content) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    
    size_t read_size = fread(content, 1, length, file);
    if (read_size != length) {
        fprintf(stderr, "Failed to read file contents\n");
        free(content);
        exit(1);
    }
    
    content[length] = '\0';
    
    fclose(file);
    return content;
}

// プラグインの実行
void load_and_execute_plugin(const char *plugin_name, const char *filename) {
    // プラグイン名を確認し、適切な処理を実行
    if (strcmp(plugin_name, "print_plugin") == 0) {
        printf("Plugin: Print\n");
        printf("Executing dogbit code from file: %s\n", filename);
    } else {
        printf("Unknown plugin: %s\n", plugin_name);
    }
}

// 実行関数
void execute_dogbit(const char *filename, Plugin *plugins, int plugin_count) {
    char *source = read_file(filename);
    int pos = 0;
    Token tokens[MAX_TOKENS];
    int token_count = 0;
    
    // 字句解析
    while (1) {
        Token token = get_next_token(source, &pos);
        if (token.type == TOKEN_EOF) break;
        tokens[token_count++] = token;
    }

    // プラグイン処理（ファイル名にプラグイン名が含まれている場合）
    for (int i = 0; i < plugin_count; i++) {
        if (strstr(filename, plugins[i].name)) {  
            plugins[i].execute(plugins[i].name, filename);  // 関数ポインタを使用
            break;
        }
    }

    // 構文解析とAST作成
    int parse_pos = 0;
    ASTNode *ast = parse_expression(tokens, &parse_pos);
    
    // 実行
    int result = evaluate(ast);
    printf("Result: %d\n", result);

    free(source);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <dogbit_file>\n", argv[0]);
        return 1;
    }

    // プラグインの定義
    Plugin plugins[] = {
        {"print_plugin", load_and_execute_plugin}  // 2引数を受け取る関数
    };

    execute_dogbit(argv[1], plugins, sizeof(plugins) / sizeof(Plugin));
    return 0;
}
