#include "Problem.h"
#include <errno.h>

// 現在着目しているトークン
Token* token;
// 
double op_var[4];
INT op_arr_tang[MAX_DATA_SIZE];
INT op_arr_goal[MAX_DATA_SIZE];
INT op_arr_main[MAX_DATA_SIZE];
INT op_count_tang;
INT op_count_goal;
INT op_count_main;


void Push(Stack* stk, double input)
{
	if (stk->size < MAX_DATA_SIZE) {
		stk->arr[stk->size++] = input;
	}
	else {
		PostQuitMessage(0);
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
	case IDOP_E: return L"e";
	case IDOP_PI: return L"PI";
	case IDOP_SQRT: return L"sqrt";
	case IDOP_ABS: return L"abs";
	case IDOP_COS: return L"cos";
	case IDOP_SIN: return L"sin";
	case IDOP_TAN: return L"tan";
	case IDOP_MOD: return L"mod";
	case IDOP_FLOOR: return L"floor";
	case IDOP_ROUND: return L"round";
	case IDOP_CEIL: return L"ceil";
	case IDOP_EXP: return L"exp";
	case IDOP_LOG: return L"log";
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
	else if (wcsncmp(token->str, L"e", 1) == 0) *id = IDOP_E;
	else if (wcsncmp(token->str, L"PI", 2) == 0) *id = IDOP_PI;
	else return FALSE;

	for (INT i = 0; i < lstrlen(GetOpName(*id)); i++) token = token->next;
	return TRUE;
}

BOOL consume_fnc(INT* id)
{
	if (token->kind != TK_RESERVED)return FALSE;
		 if (wcsncmp(token->str, L"sqrt",  4) == 0) *id = IDOP_SQRT;
	else if (wcsncmp(token->str, L"abs",   3) == 0) *id = IDOP_ABS;
	else if (wcsncmp(token->str, L"cos",   3) == 0) *id = IDOP_COS;
	else if (wcsncmp(token->str, L"sin",   3) == 0) *id = IDOP_SIN;
	else if (wcsncmp(token->str, L"tan",   3) == 0) *id = IDOP_TAN;
	else if (wcsncmp(token->str, L"mod",   3) == 0) *id = IDOP_MOD;
	else if (wcsncmp(token->str, L"floor", 5) == 0) *id = IDOP_FLOOR;
	else if (wcsncmp(token->str, L"round", 5) == 0) *id = IDOP_ROUND;
	else if (wcsncmp(token->str, L"ceil",  4) == 0) *id = IDOP_CEIL;
	else if (wcsncmp(token->str, L"exp",   3) == 0) *id = IDOP_EXP;
	else if (wcsncmp(token->str, L"log",   3) == 0) *id = IDOP_LOG;
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


void FreeTokens(Token* head)
{
	if (head->next != NULL)FreeTokens(head->next);
	free(head);
}

void FreeNodes(Node* head)
{
	if (head->lhs != NULL)FreeNodes(head->lhs);
	if (head->rhs != NULL)FreeNodes(head->rhs);
	free(head);
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
		return node->kind == ND_FNC && node->val == id ? node : new_node_fnc(id, node, NULL);
	}
	return new_node_fnc(id, mult(), NULL);
}



// a, b, c, dとして使用する数値の設定
void SetVars(double a, double b, double c, double d)
{
	op_var[0] = a;
	op_var[1] = b;
	op_var[2] = c;
	op_var[3] = d;
}


// 命令配列 op_arr の生成
void gen(INT op_arr[], INT* op_count, Node* node)
{
	if (node == NULL) return;
	INT v = node->val;

	if (node->kind == ND_NUM) {
		op_arr[(*op_count)++] = v;
		return;
	}
	if (node->kind == ND_VAR) {
		op_arr[(*op_count)++] = v;
		return;
	}

	gen(op_arr, op_count, node->lhs);
	gen(op_arr, op_count, node->rhs);

	switch (node->kind) {
	case ND_ADD: op_arr[(*op_count)++] = IDOP_ADD; break;
	case ND_SUB: op_arr[(*op_count)++] = IDOP_SUB; break;
	case ND_MUL: op_arr[(*op_count)++] = IDOP_MUL; break;
	case ND_DIV: op_arr[(*op_count)++] = IDOP_DIV; break;
	case ND_POW: op_arr[(*op_count)++] = IDOP_POW; break;
	case ND_FNC: op_arr[(*op_count)++] = v;        break;
	default    : op_arr[(*op_count)++] = IDOP_ERR; break;
	}
}





double Calc0(INT op_arr[], INT op_count, double x, double y)
{
	static Stack stst;
	static Stack* st = &stst;
	double tmp;
	st->size = 0;

	for (INT i = 0; i < op_count; i++) {
		switch (op_arr[i]) {
		case IDOP_X: Push(st, x); break;
		case IDOP_Y: Push(st, y); break;
		case IDOP_A: Push(st, op_var[0]); break;
		case IDOP_B: Push(st, op_var[1]); break;
		case IDOP_C: Push(st, op_var[2]); break;
		case IDOP_D: Push(st, op_var[3]); break;
		case IDOP_E: Push(st, M_E); break;
		case IDOP_PI: Push(st, M_PI); break;
		case IDOP_ADD: Push(st, Pop(st) + Pop(st)); break;
		case IDOP_SUB: Push(st, Pop(st) - Pop(st)); break;
		case IDOP_MUL: Push(st, Pop(st) * Pop(st)); break;
		case IDOP_DIV: Push(st, Pop(st) / Pop(st)); break;
		case IDOP_POW: Push(st, pow(Pop(st), Pop(st))); break;
		case IDOP_SQRT: Push(st, sqrt(Pop(st))); break;
		case IDOP_ABS: Push(st, fabs(Pop(st))); break;
		case IDOP_COS: Push(st, cos(Pop(st))); break;
		case IDOP_SIN: Push(st, sin(Pop(st))); break;
		case IDOP_TAN: Push(st, tan(Pop(st))); break;
		case IDOP_MOD: Push(st, fmod(Pop(st), Pop(st))); break;
		case IDOP_FLOOR: Push(st, floor(Pop(st))); break;
		case IDOP_ROUND: Push(st, round(Pop(st))); break;
		case IDOP_CEIL: Push(st, ceil(Pop(st))); break;
		case IDOP_EXP: Push(st, exp(Pop(st))); break;
		case IDOP_LOG:
			//errno = 0;
			tmp = Pop(st);
			tmp = tmp < 1e-99 ? log(1e-99) : log(tmp);
			if (FALSE/*errno != 0*/) {
				Push(st, -1e+99);
			}
			else {
				Push(st, tmp);
			}
			break;
		default: Push(st, op_arr[i]); break;
		}
	}

	return st->arr[0];
}

double CalcMain(INT id, double x, double y)
{
	SetVars(sliders[0].value, sliders[1].value, sliders[2].value, sliders[3].value);
	return Calc0(op_arr_main, op_count_main, x, y);
}

double CalcGoal(INT id, double x, double y)
{
	PROBLEM p = problems[problem_crnt];
	SetVars(p.answer[0], p.answer[1], p.answer[2], p.answer[3]);
	return Calc0(op_arr_goal, op_count_goal, x, y);
}

double CalcTang(INT id, double x, double y)
{
	PROBLEM p = problems[problem_crnt];
	double e, a, b, c;
	e = 0.00001;
	b = p.tangent[id];
	a = (CalcGoal(id, b + e, 0) - CalcGoal(id, b - e, 0)) / 2 / e;
	c = CalcGoal(id, b, 0);
	SetVars(a, b, c, 0);
	return Calc0(op_arr_tang, op_count_tang, x, y);
}




void LoadProblemData(void)
{
	//HMODULE handle = GetModuleHandle(NULL);
	HRSRC rc = FindResource(NULL, MAKEINTRESOURCE(IDR_PROBLEMTEXT), MAKEINTRESOURCE(TEXTFILE));
	HGLOBAL hGlobal = LoadResource(NULL, rc);
	//char* problem_data = (char*)LockResource(hGlobal);
	static char problem_data[16384];
	strcpy_s(problem_data, sizeof(problem_data), (char*)LockResource(hGlobal));

	PROBLEM* p;
	char* state = NULL;

	static WCHAR pd[128] = { 0 };
	WCHAR* pd_ = NULL;
	WCHAR p_type[10];
	WCHAR fstr[30] = { 0 };
	INT id;
	for (INT i = 0; i < sizeof(problems) / sizeof(problems[0]); i++) problems[i].type = PTY_NULL;
	for (
		char* tok = strtok_s(problem_data, "#", &state);
		tok != NULL;
		tok = strtok_s(NULL, "#", &state)
	) {
		if (!isdigit(tok[0]))continue;
		id = strtol(tok, &tok, 12);
		problem_latest = max(id, problem_latest);
		p = &problems[id];
		mbstowcs_s(NULL, pd, sizeof(pd) / sizeof(pd[0]), tok, _TRUNCATE);
		swscanf_s(
			pd, L"%s %d %lf %lf %lf %s",
			&p_type, (unsigned)(sizeof(p_type)/sizeof(p_type[0])), &p->vcount,
			&p->x0, &p->y0, &p->gscale,
			&fstr, (unsigned)(sizeof(fstr) / sizeof(fstr[0]))
		);
		if (lstrcmp(p_type, L"explicit") == 0)p->type = PTY_EXPLICIT;
		if (fstr[0] == L'\\') {
			p->hide = TRUE;
			wcscpy_s(p->fstr, sizeof(p->fstr) / sizeof(p->fstr[0]), fstr + 1);
		}
		else {
			p->hide = FALSE;
			wcscpy_s(p->fstr, sizeof(p->fstr) / sizeof(p->fstr[0]), fstr);
		}
		for (INT i = 0; i < lstrlen(pd); i++) {
			switch (pd[i]) {
			case L'T':
			{
				pd_ = pd + i + 1;
				for (INT j = 0; !iswdigit(pd_[0]); j++) pd_ += 1;
				swscanf_s(pd_, L"%d", &(p->tcount));
				for (INT j = 0; iswdigit(pd_[0]); j++) pd_ += 1;
				for (INT j = 0; j < p->tcount; j++) {
					swscanf_s(
						pd_, L"%lf",
						&(p->tangent[j])
					);
					for (INT k = 1; k < lstrlen(pd_); k++) {
						if (pd_[k] == L' ' || pd_[k] == L'\n') {
							pd_ = pd_ + k + 1;
							break;
						}
						if (pd_[k] == L'P' && pd_[k + 1] == L'I') {
							p->points[j] *= M_PI;
							k++;
						}
					}
				}
				break;
			}
			case L'P':
			{
				pd_ = pd + i + 1;
				for (INT j = 0; !iswdigit(pd_[0]); j++) pd_ += 1;
				swscanf_s(pd_, L"%d", &p->pcount);
				for (INT j = 0; iswdigit(pd_[0]); j++) pd_ += 1;
				for (INT j = 0; j < p->pcount; j++) {
					swscanf_s(
						pd_, L"%lf",
						&(p->points[j])
					);
					for (INT k = 1; k < lstrlen(pd_); k++) {
						if (pd_[k] == L' ' || pd_[k] == L'\n') {
							pd_ = pd_ + k + 1;
							break;
						}
						if (pd_[k] == L'P' && pd_[k + 1] == L'I') {
							p->points[j] *= M_PI;
							k++;
						}
					}
				}
				break;
			}
			case L'S':
			{
				pd_ = pd + i + 1;
				for (INT j = 0; j < p->vcount; j++) {
					// min max vscale answer
					swscanf_s(
						pd_, L"%d %d %lf %lf",
						&(p->min[j]), &(p->max[j]), &(p->vscale[j]), &(p->answer[j])
					);
					p->value[j] = (p->min[j] + p->max[j]) / 2.0;
					for (INT k = 0; k < lstrlen(pd_); k++) {
						if (pd_[k] == L'\n') {
							pd_ = pd_ + k + 1;
							break;
						}
					}
				}
				break;
			}
			}
		}
	}
}

void SetCalcs(void)
{
	PROBLEM p = problems[problem_crnt];
	WCHAR str[30] = { 0 };
	Node* head;
	Token* headToken;

	// main
	lstrcpy(str, p.fstr);
	headToken = token = tokenize(str);
	op_count_main = 0;
	head = expr();
	gen(op_arr_main, &op_count_main, head);
	FreeTokens(headToken);
	FreeNodes(head);

	// goal
	lstrcpy(str, p.fstr);
	headToken = token = tokenize(str);
	op_count_goal = 0;
	head = expr();
	gen(op_arr_goal, &op_count_goal, head);
	FreeTokens(headToken);
	FreeNodes(head);

	// tang
	wsprintf(str, L"a(x-b)+c");// 接線の式: y = f'(t)(x-t) + f(t)
	headToken = token = tokenize(str);
	op_count_tang = 0;
	head = expr();
	gen(op_arr_tang, &op_count_tang, head);
	FreeTokens(headToken);
	FreeNodes(head);
}






BOOL IsCorrectAnswer(void)
{
	PROBLEM* p = &problems[problem_crnt];
	BOOL b = TRUE;
	for (INT i = 0; i < p->vcount; i++) {
		if (
			(sliders[i].max - sliders[i].min) / 30
			< fabs(sliders[i].value - p->answer[i])
		) {
			b = FALSE;
		}
	}
	return b;
}

