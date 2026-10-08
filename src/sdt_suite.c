/**
 * ============================================================================
 * Course: Compiler Design Laboratory (BCSE306L)
 * Experiment 8: Syntax Directed Translation (SDT) Schemes
 * Author: Shrri Dharshan D R (Reg No: 23BPS1090)
 * Slot: L23+L24
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Scheme 1: SDT for Infix to Postfix Translation */
char postfix_buf[256];
int postfix_idx = 0;

void append_postfix(const char *str) {
    strcat(postfix_buf, str);
    strcat(postfix_buf, " ");
}

/* Scheme 2: Type Checking Symbol Table */
typedef enum { TYPE_INT, TYPE_FLOAT, TYPE_UNKNOWN } DataType;

typedef struct {
    char name[32];
    DataType type;
} Symbol;

Symbol sym_table[32];
int sym_count = 0;

void declare_variable(const char *name, DataType type) {
    for (int i = 0; i < sym_count; i++) {
        if (strcmp(sym_table[i].name, name) == 0) {
            sym_table[i].type = type;
            return;
        }
    }
    strncpy(sym_table[sym_count].name, name, 31);
    sym_table[sym_count].type = type;
    sym_count++;
}

DataType lookup_variable(const char *name) {
    for (int i = 0; i < sym_count; i++) {
        if (strcmp(sym_table[i].name, name) == 0) return sym_table[i].type;
    }
    return TYPE_UNKNOWN;
}

const char *type_to_str(DataType t) {
    if (t == TYPE_INT) return "int";
    if (t == TYPE_FLOAT) return "float";
    return "unknown";
}

void check_assignment(const char *lhs, DataType rhs_type) {
    DataType lhs_type = lookup_variable(lhs);
    printf("  Checking Assignment: %s = <expression of type %s>\n", lhs, type_to_str(rhs_type));
    if (lhs_type == TYPE_UNKNOWN) {
        printf("  [ERROR] Variable '%s' undeclared!\n\n", lhs);
    } else if (lhs_type == rhs_type) {
        printf("  [SUCCESS] Type Match! (%s := %s)\n\n", type_to_str(lhs_type), type_to_str(rhs_type));
    } else {
        printf("  [WARNING / TYPE MISMATCH] Type conversion needed: LHS is %s, RHS is %s!\n\n",
               type_to_str(lhs_type), type_to_str(rhs_type));
    }
}

/* Infix to Postfix Converter Algorithm */
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

void infix_to_postfix(const char *infix, char *out) {
    char stack[128];
    int top = -1;
    int out_idx = 0;

    for (int i = 0; infix[i]; i++) {
        char c = infix[i];
        if (isspace((unsigned char)c)) continue;
        if (isalnum((unsigned char)c)) {
            out[out_idx++] = c;
            out[out_idx++] = ' ';
        } else if (c == '(') {
            stack[++top] = c;
        } else if (c == ')') {
            while (top >= 0 && stack[top] != '(') {
                out[out_idx++] = stack[top--];
                out[out_idx++] = ' ';
            }
            if (top >= 0 && stack[top] == '(') top--;
        } else {
            /* Operator */
            while (top >= 0 && precedence(stack[top]) >= precedence(c)) {
                out[out_idx++] = stack[top--];
                out[out_idx++] = ' ';
            }
            stack[++top] = c;
        }
    }
    while (top >= 0) {
        out[out_idx++] = stack[top--];
        out[out_idx++] = ' ';
    }
    out[out_idx] = '\0';
}

int main(void) {
    printf("============================================================\n");
    printf("     EXPERIMENT 8: SYNTAX DIRECTED TRANSLATION (SDT)        \n");
    printf("============================================================\n\n");

    /* Part 1: SDT for Infix to Postfix Translation */
    printf("[SDT SCHEME 1] Infix to Postfix Translation for Stack Machine:\n");
    const char *infix_examples[] = {
        "a + b * c",
        "(a + b) * (c - d)",
        "x + y * z / w"
    };
    for (int i = 0; i < 3; i++) {
        char post[128] = "";
        infix_to_postfix(infix_examples[i], post);
        printf("  Infix   : %s\n", infix_examples[i]);
        printf("  Postfix : %s\n\n", post);
    }

    /* Part 2: SDT for Static Type Checking */
    printf("------------------------------------------------------------\n");
    printf("[SDT SCHEME 2] Semantic Type Checking with Symbol Table:\n");
    declare_variable("a", TYPE_INT);
    declare_variable("b", TYPE_FLOAT);
    declare_variable("c", TYPE_INT);

    printf("Declared Variables in Symbol Table:\n");
    printf("  a : int\n  b : float\n  c : int\n\n");

    check_assignment("a", TYPE_INT);   /* Match */
    check_assignment("b", TYPE_FLOAT); /* Match */
    check_assignment("a", TYPE_FLOAT); /* Type Mismatch */
    check_assignment("d", TYPE_INT);   /* Undeclared */

    return 0;
}
