#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

void remove_spaces(char* str) {
    int i = 0, j = 0;
    while (str[i]) {
        if (str[i] != ' ' && str[i] != '\n') {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';
}

bool is_valid_parentheses(const char* s) {
    int balance = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '(') {
            balance++;
        }
        else if (s[i] == ')') {
            balance--;
        }
        if (balance < 0) {
            return false;
        }
    }
    return balance == 0;
}

bool is_binary_tree_recursive(const char* s, int* pos) {
    if (*pos >= strlen(s) || s[*pos] != '(') {
        return false;
    }
    (*pos)++;
    
    if (*pos < strlen(s) && s[*pos] == ')') {
        (*pos)++;
        return true;
    }

    if (*pos >= strlen(s) || !(s[*pos] >= 'A' && s[*pos] <= 'Z')) {
        return false;
    }
    (*pos)++;

    int child_count = 0;
    while (*pos < strlen(s) && s[*pos] == '(') {
        child_count++;
        if (child_count > 2) {
            return false;
        }
        if (!is_binary_tree_recursive(s, pos)) {
            return false;
        }
    }

    if (*pos >= strlen(s) || s[*pos] != ')') {
        return false;
    }
    (*pos)++;

    return true;
}

int main() {
    char input[256];
    printf("트리를 입력하세요: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("ERROR\n");
        return 1;
    }

    remove_spaces(input);

    if (strlen(input) < 3 || input[0] != '(' || input[strlen(input) - 1] != ')') {
        printf("ERROR\n");
        return 0;
    }

    if (!is_valid_parentheses(input)) {
        printf("ERROR\n");
        return 0;
    }

    int pos = 0;
    bool is_binary = is_binary_tree_recursive(input, &pos);

    if (is_binary && pos == strlen(input)) {
        printf("TRUE\n");
    }
    else {
        printf("FALSE\n");
    }

    return 0;
}