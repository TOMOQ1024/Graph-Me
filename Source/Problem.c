#include "Problem.h"



// 現在着目しているトークン
Token* token;
// 
INT op_arr[MAX_DATA_SIZE];
INT op_count;



void Push(Stack* stk, double input)
{
	if (stk->size < MAX_DATA_SIZE) {
		stk->arr[stk->size++] = input;
	}
}

double Pop(Stack* stk)
{
	if (0 < stk->size)return stk->arr[--(stk->size)];
	else return 0;
}






WCHAR* GetOpName(INT id)
{
	switch (id)
	{
	case IDOP_X: return L"x";
	case IDOP_A: return L"a";
	case IDOP_B: return L"b";
	case IDOP_C: return L"c";
	case IDOP_D: return L"d";
	case IDOP_PI: return L"PI";
	case IDOP_COS: return L"cos";
	case IDOP_SIN: return L"sin";
	case IDOP_TAN: return L"tan";
	case IDOP_FLOOR: return L"floor";
	case IDOP_ROUND: return L"round";
	case IDOP_CEIL: return L"ceil";
	case IDOP_EXP: return L"exp";
	case IDOP_LOG: return L"log";
	case IDOP_MOD: return L"mod";
	default: return L"?";
	}
}


// 現在のトークンについて調べる関数
BOOL check(WCHAR* op)
{
	if (token->kind != TK_RESERVED || wcsncmp(token->str, op, lstrlen(op)) != 0)
		return FALSE;
	return TRUE;
}

BOOL consume(WCHAR* op)
{
	if (token->kind != TK_RESERVED || wcsncmp(token->str, op, lstrlen(op)) != 0)
		return FALSE;
	token = token->next;
	return TRUE;
}

BOOL consume_var(INT* id)
{
	if (token->kind != TK_RESERVED)return FALSE;
		 if (wcsncmp(token->str, L"x", 1) == 0) *id = IDOP_X;
	else if (wcsncmp(token->str, L"a", 1) == 0) *id = IDOP_A;
	else if (wcsncmp(token->str, L"b", 1) == 0) *id = IDOP_B;
	else if (wcsncmp(token->str, L"c", 1) == 0) *id = IDOP_C;
	else if (wcsncmp(token->str, L"d", 1) == 0) *id = IDOP_D;
	else if (wcsncmp(token->str, L"t", 1) == 0) *id = IDOP_X;
	else if (wcsncmp(token->str, L"h", 1) == 0) *id = IDOP_X;
	else if (wcsncmp(token->str, L"PI", 2) == 0) *id = IDOP_PI;
	else return FALSE;

	for (INT i = 0; i < lstrlen(GetOpName(*id)); i++) token = token->next;
	return TRUE;
}

BOOL consume_fnc(INT* id)
{
	if (token->kind != TK_RESERVED)return FALSE;
		 if (wcsncmp(token->str, L"cos",   3) == 0) *id = IDOP_COS;
	else if (wcsncmp(token->str, L"sin",   3) == 0) *id = IDOP_SIN;
	else if (wcsncmp(token->str, L"tan",   3) == 0) *id = IDOP_TAN;
	else if (wcsncmp(token->str, L"floor", 5) == 0) *id = IDOP_FLOOR;
	else if (wcsncmp(token->str, L"round", 5) == 0) *id = IDOP_ROUND;
	else if (wcsncmp(token->str, L"ceil",  4) == 0) *id = IDOP_CEIL;
	else if (wcsncmp(token->str, L"exp",   3) == 0) *id = IDOP_EXP;
	else if (wcsncmp(token->str, L"log",   3) == 0) *id = IDOP_LOG;
	else if (wcsncmp(token->str, L"mod",   3) == 0) *id = IDOP_MOD;
	else return FALSE;

	for (INT i = 0; i < lstrlen(GetOpName(*id)); i++) token = token->next;
	return TRUE;
}

void expect(WCHAR* op)
{
	token = token->next;
}

INT expect_num(void)
{
	INT val = token->val;
	token = token->next;
	return val;
}

BOOL at_eof(void)
{
	return token->kind == TK_EOF;
}



Token* new_token(TokenKind kind, Token* cur, WCHAR* str)
{
	Token* tok = calloc(1, sizeof(Token));
	if (tok != NULL) {
		tok->kind = kind;
		tok->str = str;
		cur->next = tok;
		return tok;
	}
	return NULL;
}

Token* tokenize(WCHAR* p)
{
	Token head;
	head.next = NULL;
	Token* cur = &head;

	while (*p) {
		if (iswspace(*p)) {
			p++;
			continue;
		}
		if (iswdigit(*p)) {
			cur = new_token(TK_NUM, cur, p);
			cur->val = wcstol(p, &p, 10);
			continue;
		}

		cur = new_token(TK_RESERVED, cur, p++);
		continue;
	}

	new_token(TK_EOF, cur, p);
	return head.next;
}

// 構文木ノードの生成
Node* new_node(NodeKind kind, Node* lhs, Node* rhs)
{
	Node* node = calloc(1, sizeof(Node));
	if (node != NULL) {
		node->kind = kind;
		node->lhs = lhs;
		node->rhs = rhs;
		return node;
	}
	return NULL;
}

Node* new_node_num(INT val)
{
	Node* node = calloc(1, sizeof(Node));
	if (node != NULL) {
		node->kind = ND_NUM;
		node->val = val;
		return node;
	}
	return NULL;
}

Node* new_node_var(INT id)
{
	Node* node = calloc(1, sizeof(Node));
	if (node != NULL) {
		node->kind = ND_VAR;
		node->val = id;
		return node;
	}
	return NULL;
}

Node* new_node_fnc(INT id, Node* lhs, Node* rhs)
{
	Node* node = calloc(1, sizeof(Node));
	if (node != NULL) {
		node->kind = ND_FNC;
		node->lhs = lhs;
		node->rhs = rhs;
		node->val = id;
		return node;
	}
	return NULL;
}

// 構文木の生成
Node* expr(void)
{
	Node* node;

	// 先頭が0だった場合の処理
	if (consume(L"-"))node = new_node(ND_SUB, mult(), new_node_num(0));
	else {
		consume(L"+");
		node = mult();
	}

	for (;;) {
		if (consume(L"+"))node = new_node(ND_ADD, mult(), node);
		else if (consume(L"-"))node = new_node(ND_SUB, mult(), node);
		else return node;
	}
}
Node* mult(void)
{
	Node* node = powr();

	for (;;) {
		if (consume(L"*"))node = new_node(ND_MUL, powr(), node);
		else if (consume(L"/"))node = new_node(ND_DIV, powr(), node);
		else if (!check(L"+") && !check(L"-") && !check(L",") && !check(L")") && !at_eof())
			node = new_node(ND_MUL, powr(), node);
		else return node;
	}
}
Node* powr(void)
{
	Node* node = prim();

	if (consume(L"^"))return new_node(ND_POW, node, powr());
	return node;
}
Node* prim(void)
{
	Node* node;
	INT id;

	if (consume(L"(")) {
		node = expr();
		expect(L")");
		return node;
	}
	if (consume_fnc(&id)) return func(id);
	if (consume_var(&id)) return new_node_var(id);
	return new_node_num(expect_num());
}
Node* func(INT id)
{
	Node* node;

	if (consume(L"(")) {
		node = expr();
		while (consume(L",")) node = new_node_fnc(id, node, expr());
		expect(L")");
		return node->kind == ND_FNC ? node : new_node_fnc(id, node, NULL);
	}
	return new_node_fnc(id, mult(), NULL);
}



// 命令配列 op_arr の生成
void gen(Node* node)
{
	if (node == NULL) return;
	INT v = node->val;

	if (node->kind == ND_NUM) {
		op_arr[op_count++] = v;
		return;
	}
	if (node->kind == ND_VAR) {
		op_arr[op_count++] = v;
		return;
	}

	gen(node->lhs);
	gen(node->rhs);

	switch (node->kind) {
	case ND_ADD: op_arr[op_count++] = IDOP_ADD; break;
	case ND_SUB: op_arr[op_count++] = IDOP_SUB; break;
	case ND_MUL: op_arr[op_count++] = IDOP_MUL; break;
	case ND_DIV: op_arr[op_count++] = IDOP_DIV; break;
	case ND_POW: op_arr[op_count++] = IDOP_POW; break;
	case ND_FNC: op_arr[op_count++] = v;        break;
	default    : op_arr[op_count++] = IDOP_ERR; break;
	}
}





double Calc(double x, double a, double b, double c, double d)
{
	Stack stst;
	Stack* st = &stst;
	st->size = 0;

	for (INT i = 0; i < op_count; i++) {
		switch (op_arr[i]) {
		case IDOP_X: Push(st, x); break;
		case IDOP_A: Push(st, a); break;
		case IDOP_B: Push(st, b); break;
		case IDOP_C: Push(st, c); break;
		case IDOP_D: Push(st, d); break;
		case IDOP_PI: Push(st, M_PI); break;
		case IDOP_ADD: Push(st, Pop(st) + Pop(st)); break;
		case IDOP_SUB: Push(st, Pop(st) - Pop(st)); break;
		case IDOP_MUL: Push(st, Pop(st) * Pop(st)); break;
		case IDOP_DIV: Push(st, Pop(st) / Pop(st)); break;
		case IDOP_POW: Push(st, pow(Pop(st), Pop(st))); break;
		case IDOP_COS: Push(st, cos(Pop(st))); break;
		case IDOP_SIN: Push(st, sin(Pop(st))); break;
		case IDOP_TAN: Push(st, tan(Pop(st))); break;
		case IDOP_FLOOR: Push(st, floor(Pop(st))); break;
		case IDOP_ROUND: Push(st, round(Pop(st))); break;
		case IDOP_CEIL: Push(st, ceil(Pop(st))); break;
		case IDOP_EXP: Push(st, exp(Pop(st))); break;
		case IDOP_LOG: Push(st, log(Pop(st))); break;
		case IDOP_MOD: Push(st, fmod(Pop(st), Pop(st))); break;
		default: Push(st, op_arr[i]); break;
		}
	}

	return st->arr[0];
}





void LoadProblemData(void)
{
	//HMODULE handle = GetModuleHandle(NULL);
	HRSRC rc = FindResource(NULL, MAKEINTRESOURCE(IDR_PROBLEMTEXT), MAKEINTRESOURCE(TEXTFILE));
	HGLOBAL hGlobal = LoadResource(NULL, rc);
	//char* problem_data = (char*)LockResource(hGlobal);
	char problem_data[16384];
	strcpy_s(problem_data, sizeof(problem_data), (char*)LockResource(hGlobal));

	PROBLEM* p;
	char* state;

	WCHAR pd[128] = { 0 };
	WCHAR* pd_ = NULL;
	WCHAR p_type[10];
	for (INT i = 0; i < sizeof(problems) / sizeof(problems[0]); i++) problems[i].type = PTY_NULL;
	for (
		char* tok = strtok_s(problem_data, "#", &state);
		tok != NULL;
		tok = strtok_s(NULL, "#", &state)
	) {
		if (!isdigit(tok[0]))continue;
		p = &problems[strtol(tok, &tok, 12)];
		if (tok[0] == ':')tok += 2;
		mbstowcs_s(NULL, pd, sizeof(pd) / sizeof(pd[0]), tok, _TRUNCATE);
		swscanf_s(
			pd, L"%s %d %lf %lf %lf %s",
			&p_type, (unsigned)(sizeof(p_type)/sizeof(p_type[0])), &p->vcount,
			&p->x0, &p->y0, &p->gscale,
			&p->fstr, (unsigned)(sizeof(p->fstr) / sizeof(p->fstr[0]))
		);
		if (lstrcmp(p_type, L"explicit") == 0)p->type = PTY_EXPLICIT;
		for (INT i = 0; i < lstrlen(pd); i++) {
			if (pd[i] == L'$') {
				pd_ = pd + i + 1;
				break;
			}
		}
		if (pd_ == NULL)continue;
		for (INT i = 0; i < p->vcount; i++) {
			// min value max vscale answer
			swscanf_s(
				pd_, L"%d %lf %d %d %lf",
				&(p->min[i]), &(p->value[i]), &(p->max[i]), &(p->vscale[i]), &(p->answer[i])
			);
			for (INT j = 0; j < lstrlen(pd_); j++) {
				if (pd_[j] == L'\n') {
					pd_ = pd_ + j + 1;
					break;
				}
			}
		}
	}
}

void LoadProblem(PROBLEM* p)
{
	WCHAR str[30] = { 0 };
	lstrcpy(str, p->fstr);
	token = tokenize(str);
	op_count = 0;
	gen(expr());
}