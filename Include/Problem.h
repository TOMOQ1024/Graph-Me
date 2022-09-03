#pragma once

#include "Main.h"



// 構文木ノードの分類
typedef enum {
	ND_ADD,
	ND_SUB,
	ND_MUL,
	ND_DIV,
	ND_POW,
	ND_NUM,
	ND_VAR,
	ND_FNC,
} NodeKind;

// 構文木ノード構造体
typedef struct tagNode Node;
struct tagNode {
	NodeKind kind;
	Node* lhs;
	Node* rhs;
	INT val;
};

// トークンの分類
typedef enum {
	TK_RESERVED,
	TK_NUM,
	TK_EOF,
} TokenKind;

// トークン構造体
typedef struct tagToken Token;
struct tagToken {
	TokenKind kind;
	Token* next;
	INT val;
	WCHAR* str;
};

// スタック
typedef struct tagStack {
	double arr[MAX_DATA_SIZE];
	INT size;
} Stack;
void Push(Stack* stk, double input);
double Pop(Stack* stk);



WCHAR* GetOpName(INT id);

// 現在のトークンについて調べる関数
BOOL check(WCHAR* op);
BOOL consume(WCHAR* op);
BOOL consume_var(INT* id);
BOOL consume_fnc(INT* id);
void expect(WCHAR* op);
INT expect_num(void);
BOOL at_eof(void);

Token* new_token(TokenKind kind, Token* cur, WCHAR* str);
Token* tokenize(WCHAR* p);

// 構文木ノードの生成
Node* new_node(NodeKind kind, Node* lhs, Node* rhs);
Node* new_node_num(INT val);
Node* new_node_var(INT id);
Node* new_node_fnc(INT id, Node* lhs, Node* rhs);

// 構文木の生成
Node* expr(void);
Node* mult(void);
Node* powr(void);
Node* prim(void);
Node* func(INT id);



// 命令配列 op_arr の生成
void gen(Node* node);
void SetVars(double a, double b, double c, double d);
