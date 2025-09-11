#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

char* input_string;
int pos;

void skip_whitespace() {
    while (isspace(input_string[pos])) {
        pos++;
    }
}

bool is_binary_tree_recursive();

bool is_child_list() {
    skip_whitespace();
    int child_count = 0;

    while (input_string[pos] != ')' && input_string[pos] != '\0') {
        if (child_count >= 2) {
            return false;
        }

        if (!is_binary_tree_recursive()) {
            return false;
        }
        child_count++;
        skip_whitespace();
    }

    if (input_string[pos] != ')') {
        return false;
    }
    pos++;
    return true;
}

bool is_binary_tree_recursive() {
    skip_whitespace();

    if (input_string[pos] == '\0') {
        return true;
    }

    if (input_string[pos] == '(') {
        pos++; // 괄호 안으로 이동
        skip_whitespace();

        if (input_string[pos] == ')') {
            return false;
        }

        if (!is_binary_tree_recursive()) {
            return false;
        }

        skip_whitespace();
        if (input_string[pos] == ')') {
            pos++;
            return true;
        }
        else {
            return false;
        }
    }

    if (!isalpha(input_string[pos])) {
        return false;
    }
    pos++;

    skip_whitespace();
    if (input_string[pos] == '(') {
        pos++;
        if (!is_child_list()) {
            return false;
        }
    }

    return true;
}

int main() {
    char buffer[256];
    fgets(buffer, sizeof(buffer), stdin);
    input_string = buffer;

    skip_whitespace();
    if (input_string[pos] != '(') {
        printf("FALSE\n");
        return 0;
    }
    pos++;

    bool is_valid = is_binary_tree_recursive();

    skip_whitespace();
    if (input_string[pos] != '\0') {
        is_valid = false;
    }

    if (is_valid) {
        printf("TRUE\n");
    }
    else {
        printf("FALSE\n");
    }

    return 0;
}