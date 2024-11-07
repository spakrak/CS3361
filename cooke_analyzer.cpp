#include <stdio.h>
#include <ctype.h>
#include <string.h> // For strcmp()
#include "front.h"

/* Global Variable */
int nextToken;

/* Local Variables */
static int charClass;
static char lexeme[100];
static char nextChar;
static int lexLen;
static FILE *file;

/* Function Declarations */
static void addChar();
static void getChar();
char peekChar();
static void getNonBlank();
static int lookup(char ch);

/* Main Driver */
int main(int argc, char* argv[]) {
    /* Check for a command-line argument */
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    /* Open the input data file specified by the command-line argument */
    if ((file = fopen(argv[1], "r")) == NULL) {
        printf("ERROR - cannot open file: %s\n", argv[1]);
        return 1;
    } else {
        printf("Cooke Analyzer :: R11843588\n");
        getChar(); // Initialize first character

        do {
            lex();
        } while (nextToken != -1); // Continue until EOF
    } 
    return 0;
}

/* addChar - Adds nextChar to lexeme and null-terminates it */
static void addChar() {
    if (lexLen <= 98) {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = 0; // Null-terminate the string
    } else {
        printf("Error - lexeme is too long\n");
    }
}

/* getChar - Gets the next character and determines its character class */
static void getChar() {
    if ((nextChar = getc(file)) != EOF) {
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else
            charClass = UNKNOWN;
    } else {
        charClass = EOF;
    }
}

/* peekChar - Peeks at the next character without consuming it */
char peekChar() {
    char c = getc(file);
    if (c != EOF) {
        ungetc(c, file); // Push the character back to input stream
    }
    return c;
}

/* getNonBlank - Skips whitespace characters */
static void getNonBlank() {
    while (isspace(nextChar)) {
        getChar();
    }
}

/* lookup - Identifies operators and special characters */
static int lookup(char ch) {
    char ahead = peekChar(); // Peek at the next character
    switch (ch) {
        case '(':
            addChar();
            nextToken = OPEN_PAREN;
            break;
        case ')':
            addChar();
            nextToken = CLOSE_PAREN;
            break;
        case '+':
            addChar();
            nextToken = ADD_OP;
            break;
        case '-':
            addChar();
            nextToken = SUB_OP;
            break;
        case '*':
            addChar();
            nextToken = MULT_OP;
            break;
        case '/':
            addChar();
            nextToken = DIV_OP;
            break;
        case '%':
            addChar();
            nextToken = MOD_OP;
            break;
        case ';':
            addChar();
            nextToken = SEMICOLON;
            break;
        case '{':
            addChar();
            nextToken = OPEN_CURL;
            break;
        case '}':
            addChar();
            nextToken = CLOSE_CURL;
            break;
        case '<':
            addChar();
            if (ahead == '=') {
                getChar();
                addChar();
                nextToken = LEQUAL_OP;
            } else {
                nextToken = LESSER_OP;
            }
            break;
        case '>':
            addChar();
            if (ahead == '=') {
                getChar();
                addChar();
                nextToken = GEQUAL_OP;
            } else {
                nextToken = GREATER_OP;
            }
            break;
        case '=':
            addChar();
            if (ahead == '=') {
                getChar();
                addChar();
                nextToken = EQUAL_OP;
            } else {
                nextToken = ASSIGN_OP;
            }
            break;
        case '!':
            addChar();
            if (ahead == '=') {
                getChar();
                addChar();
                nextToken = NEQUAL_OP;
            } else {
                nextToken = BOOL_NOT;
            }
            break;
        case '&':
            addChar();
            if (ahead == '&') {
                getChar();
                addChar();
                nextToken = BOOL_AND;
            } else {
                nextToken = UNKNOWN;
            }
            break;
        case '|':
            addChar();
            if (ahead == '|') {
                getChar();
                addChar();
                nextToken = BOOL_OR;
            } else {
                nextToken = UNKNOWN;
            }
            break;
        default:
            addChar();
            nextToken = UNKNOWN;
            break;
    }
    return nextToken;
}

/* getTokenName - Returns the string representation of a token */
const char* getTokenName(int token) {
    switch (token) {
        case INT_LIT: return "INT_LIT";
        case IDENT: return "IDENT";
        case ASSIGN_OP: return "ASSIGN_OP";
        case ADD_OP: return "ADD_OP";
        case SUB_OP: return "SUB_OP";
        case MULT_OP: return "MULT_OP";
        case DIV_OP: return "DIV_OP";
        case MOD_OP: return "MOD_OP";
        case OPEN_PAREN: return "OPEN_PAREN";
        case CLOSE_PAREN: return "CLOSE_PAREN";
        case LESSER_OP: return "LESSER_OP";
        case GREATER_OP: return "GREATER_OP";
        case EQUAL_OP: return "EQUAL_OP";
        case NEQUAL_OP: return "NEQUAL_OP";
        case LEQUAL_OP: return "LEQUAL_OP";
        case GEQUAL_OP: return "GEQUAL_OP";
        case BOOL_AND: return "BOOL_AND";
        case BOOL_OR: return "BOOL_OR";
        case BOOL_NOT: return "BOOL_NOT";
        case OPEN_CURL: return "OPEN_CURL";
        case CLOSE_CURL: return "CLOSE_CURL";
        case SEMICOLON: return "SEMICOLON";
        case KEY_IF: return "KEY_IF";
        case KEY_ELSE: return "KEY_ELSE";
        case KEY_IN: return "KEY_IN";
        case KEY_OUT: return "KEY_OUT";
        case EOF: return "EOF";  // Add this line
        default: return "UNKNOWN";
    }
}

/* lex - Main lexical analyzer function */
int lex() {
    lexLen = 0;
    getNonBlank(); // Skip whitespace
    switch (charClass) {
        case LETTER: // Parse identifiers and keywords
            addChar();
            getChar();
            while (charClass == LETTER || charClass == DIGIT) {
                addChar();
                getChar();
            }
            if (strcmp(lexeme, "if") == 0) {
                nextToken = KEY_IF;
            } else if (strcmp(lexeme, "else") == 0) {
                nextToken = KEY_ELSE;
            } else if (strcmp(lexeme, "input") == 0) {
                nextToken = KEY_IN;
            } else if (strcmp(lexeme, "output") == 0) {
                nextToken = KEY_OUT;
            } else {
                nextToken = IDENT;
            }
            break;
        case DIGIT: // Parse integer literals
            addChar();
            getChar();
            while (charClass == DIGIT) {
                addChar();
                getChar();
            }
            nextToken = INT_LIT;
            break;
        case UNKNOWN: // Handle unknown characters
            lookup(nextChar);
            getChar();
            break;
        case EOF: // End of file handling
            nextToken = EOF;
            strcpy(lexeme, "EOF");
            return nextToken; // Return immediately on EOF
    }
    // Print lexeme and token if not EOF
    printf("%s \t %s\n", lexeme, getTokenName(nextToken));
    return nextToken;
}