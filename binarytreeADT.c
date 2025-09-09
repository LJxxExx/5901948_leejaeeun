#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char data;
    struct Node* parent;
    struct Node** children;
    int child_count;
} Node;

Node* createNode(char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(1);
    }
    newNode->data = data;
    newNode->parent = NULL;
    newNode->children = NULL;
    newNode->child_count = 0;
    return newNode;
}

Node* buildTree(const char* s, int* index, Node* parent) {
    if (s[*index] == '\0' || s[*index] == ')') {
        return NULL;
    }

    Node* current = createNode(s[*index]);
    current->parent = parent;
    (*index)++;

    if (s[*index] == ' ') {
        (*index)++;
    }
  
    if (s[*index] == '(') {
        (*index)++; // '(' 건너뛰기
 
        Node** temp_children = (Node**)malloc(sizeof(Node*));
        if (temp_children == NULL) {
            fprintf(stderr, "메모리 할당 실패\n");
            exit(1);
        }
        int temp_count = 0;
        
       
        while (s[*index] != ')') {
            Node* child = buildTree(s, index, current);
            if (child != NULL) {
                temp_count++;
              
                temp_children = (Node**)realloc(temp_children, sizeof(Node*) * temp_count);
                if (temp_children == NULL) {
                    fprintf(stderr, "메모리 재할당 실패\n");
                    exit(1);
                }
                temp_children[temp_count - 1] = child;
            }
           
            if (s[*index] == ' ') {
                (*index)++;
            }
        }
    
        current->children = temp_children;
        current->child_count = temp_count;

        (*index)++;
    }
    
    return current;
}

int calculateHeight(Node* root) {
    if (root == NULL || root->child_count == 0) {
        return 0;
    }
    
    int max_height = 0;
    for (int i = 0; i < root->child_count; i++) {
        int child_height = calculateHeight(root->children[i]);
        if (child_height + 1 > max_height) {
            max_height = child_height + 1;
        }
    }
    return max_height;
}

int countNodes(Node* root) {
    if (root == NULL) {
        return 0;
    }
    
    int count = 1;
    for (int i = 0; i < root->child_count; i++) {
        count += countNodes(root->children[i]);
    }
    return count;
}

int countLeafNodes(Node* root) {
    if (root == NULL) {
        return 0;
    }
    
    if (root->child_count == 0) {
        return 1;
    }
    
    int count = 0;
    for (int i = 0; i < root->child_count; i++) {
        count += countLeafNodes(root->children[i]);
    }
    return count;
}

int main()
{
    const char* input = "(A (B (C D) E (G H (I J (K (L) M (N))))))";
    int index = 0;
 
    int root_start = 0;
    while (input[root_start] == '(' || input[root_start] == ' ') {
        root_start++;
    }
    
    Node* root = createNode(input[root_start]);
    index = root_start + 1;
   
    if (input[index] == ' ') {
        index++;
    }

    if (input[index] == '(') {
        index++;
        Node** temp_children = (Node**)malloc(sizeof(Node*));
        if (temp_children == NULL) {
            fprintf(stderr, "메모리 할당 실패\n");
            exit(1);
        }
        int temp_count = 0;
        
        while (input[index] != ')') {
            Node* child = buildTree(input, &index, root);
            if (child != NULL) {
                temp_count++;
                temp_children = (Node**)realloc(temp_children, sizeof(Node*) * temp_count);
                if (temp_children == NULL) {
                    fprintf(stderr, "ERROR: 메모리 재할당 실패\n");
                    exit(1);
                }
                temp_children[temp_count - 1] = child;
            }
            if (input[index] == ' ') {
                index++;
            }
        }
        
        root->children = temp_children;
        root->child_count = temp_count;
    }

    int height = calculateHeight(root);
    int node_count = countNodes(root);
    int leaf_count = countLeafNodes(root);
    
    printf("%d, %d, %d\n", height, node_count, leaf_count);
    
    return 0;
}
