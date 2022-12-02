#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char *data;
    int top;
    int size;
} Stack;

Stack* initStack(int size) {
    Stack *s = (Stack*)malloc(sizeof(Stack));
    s->data = (char*)malloc(sizeof(char) * size);
    s->top = -1;
    s->size = size;
    return s;
}

void push(Stack *s, char c) {
    if (s->top == s->size - 1) {
        printf("Stack is full!\n");
        return;
    }

    s->data[++s->top] = c;
}

char pop(Stack *s) {
    if (s->top == -1) {
        printf("Stack is empty!\n");
        return -1;
    }

    return s->data[s->top--];
}

char peek(Stack *s) {
    if (s->top == -1) {
        printf("Stack is empty!\n");
        return -1;
    }

    return s->data[s->top];
}

int isOperator(char c) {
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
        return 1;
    }

    return 0;
}

int precedence(char c) {
    if (c == '+' || c == '-') {
        return 1;
    } else if (c == '*' || c == '/') {
        return 2;
    } else if (c == '^') {
        return 3;
    }

    return -1;
}

char* infixToPostfix(char *infix) {
    int i, j;
    int len = strlen(infix);
    char *prefix = (char*)malloc(sizeof(char) * (len + 1));
    Stack *s = initStack(len);

    for (i = 0, j = 0; i < len; i++) {
        if (infix[i] == '(') {
            infix[i] = ')';
        } else if (infix[i] == ')') {
            infix[i] = '(';
        }
    }

    for (i = 0; i < len; i++) {
        if (infix[i] == '(') {
            push(s, infix[i]);
        } else if (isalpha(infix[i]) || isdigit(infix[i])) {
            prefix[j++] = infix[i];
        } else if (isOperator(infix[i])) {
            while (s->top != -1 && peek(s) != '(' && precedence(infix[i]) <= precedence(peek(s))) {
                prefix[j++] = pop(s);
            }
            push(s, infix[i]);
        } else if (infix[i] == ')') {
            while (s->top != -1 && peek(s) != '(') {
                prefix[j++] = pop(s);
            }
            pop(s);
        }
    }

    while (s->top != -1) {
        prefix[j++] = pop(s);
    }

    prefix[j] = '\0';

    return prefix;
}

int main(int argc, char** argv)
{
    char* infix = "5+6*7";
    char* postfix = infixToPostfix(infix);

    printf("Infix:  %s\n", infix);
    printf("Postfix: %s\n", postfix);

    if (strcmp(prefix, "76*5+") == 0) printf("TEST PASS\n");
    else printf("TEST FAIL\n");

    return 0;
}
