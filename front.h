#ifndef FRONT_H
#define FRONT_H

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

/* Token codes */
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define MOD_OP 25
#define OPEN_PAREN 26
#define CLOSE_PAREN 27
#define LESSER_OP 28
#define GREATER_OP 29
#define EQUAL_OP 30
#define NEQUAL_OP 31
#define LEQUAL_OP 32
#define GEQUAL_OP 33
#define BOOL_AND 34
#define BOOL_OR 35
#define BOOL_NOT 36
#define OPEN_CURL 37
#define CLOSE_CURL 38
#define SEMICOLON 39
#define KEY_IF 40
#define KEY_ELSE 41
#define KEY_IN 42
#define KEY_OUT 43

int lex();

#endif
