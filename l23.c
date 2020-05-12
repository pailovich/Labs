#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
struct Node{
    int num;
    char val;
    Node** nodes;
    Node* parent;
};

typedef struct Tree Tree;
struct Tree{
    Node *root;
};

Node* addNode(Node* parent, char v);
Node* addRoot(Tree* parent, char v);
void printTree(Tree tree);
void printNode(Node* node, int p);
Node* dellNode(Node* node);
int func(Node* node);
int menu(Node* node);

Node* current;



int main() {
    Tree tree;
    printf("Welcome!\nEner a char\n");
    char ch;
    //ch = getchar();
    scanf("%c", &ch);
    current = addRoot(&tree, ch);
    int m = menu(current);
    while (m != 0) {
        switch (m) {
            case 1:
                getchar();
                printf("Ener a char\n");
                //ch = getchar();
                scanf("%c", &ch);
                current = addNode(current, ch);
                break;
            
            case 2:
                printTree(tree);
                break;
            
            case 3:
                current = dellNode(current);
                break;
            
            case 4:
                printf("%s", func(tree.root) == 1 ? "Yes\n" : "NO\n");
                break;
                
            case 5:
                printf("enter 0 to go to the parent node, or enter child number\n");
                scanf("%d", &m);
                if (m == 0)
                    current = current->parent;
                else
                    current = current->nodes[m - 1];
                break;
            
            default:
                break;
        }
        m = menu(current);
    }
    return 0;
}



Node* addNode(Node* parent, char v){
    ++parent->num;
    parent->nodes = (Node**) realloc(parent->nodes, sizeof(Node*) * parent->num);
    parent->nodes[parent->num - 1] = malloc(sizeof(Node));
    parent->nodes[parent->num - 1]->val = v;
    parent->nodes[parent->num - 1]->num = 0;
    parent->nodes[parent->num - 1]->nodes = NULL;
    parent->nodes[parent->num - 1]->parent = parent;
    return parent->nodes[parent->num - 1];
}

Node* addRoot(Tree* parent, char v){
    parent->root = (Node*) malloc(sizeof(Node));
    parent->root->val = v;
    parent->root->num = 0;
    parent->root->nodes = NULL;
    parent->root->parent = parent->root;
    return parent->root;
}

void printTree(Tree tree){
    printf("%c", tree.root->val);
    if (current == tree.root)
        printf("<-");
    printf("\n");
    int p = 0;
    printNode(tree.root, p);
}

void printNode(Node* node, int p){
    ++p;
    for (int i = 0; i < node->num; ++i){
        printf("%*.c%c", p, ' ', node->nodes[i]->val);
        if (current == node->nodes[i])
            printf("<-");
        printf("\n");
    }
    if (node->num > 0){
        //printf("\n");
        for (int i = 0; i < node->num; ++i){
            printNode(node->nodes[i], p);
        }
    }
}

Node* dellNode(Node* node){
    Node* p = node->parent;
    for (int i = 0; i < node->num; ++i){
        dellNode(node->nodes[i]);
    }
    if (node == current){
        int f = 0;
        for (int i = 0; i < node->parent->num; ++i){
            if (node == node->parent->nodes[i]){
                f = 1;
                free(node->parent->nodes[i]);
                --node->parent->num;
                node->parent->nodes[i] = i == node->parent->num ? NULL : node->parent->nodes[i + 1];
            }
            if (f == 1){
                node->parent->nodes[i] = node->parent->nodes[i + 1];
            }
        }
    }
    else{
        free(node);
    }
    return p;
}

int func(Node* node){
    if (node->num > 1)
        return 0;
    if (node->num == 0)
        return 1;
    return func(node->nodes[0]);
}

int menu(Node* node){
    printf("1. add new node;\n2. print tree;\n3. dellite node \n4. check the monotony of decreasing tree width\n5. go to oter node;\n6. exit\n");
    int ans;
    scanf("%d", &ans);
    if (ans <= 5 || ans > 0)
        return ans;
    return 0;
}
