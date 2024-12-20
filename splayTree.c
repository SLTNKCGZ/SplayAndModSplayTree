#include <stdio.h>
#include <stdlib.h>
int comparision[2];
int rotation[2];

typedef struct node
{
    int num;
    struct node *left;
    struct node *right;
    struct node *parent;
    int frequency;
} node;

void printPreorder(node *root, int type);
void rotations(node *x, node **root, int type);
void insert(node *xnode, node **root, int type);
void readFile(node **root, FILE *inputFile, int type);
node *createTemp(int num);
void zigzig(node *X, node *P, node *G);
void zigzag(node *X, node *P, node *G);
void zig(node *X, node *P, node *G);

node *createTemp(int num)
{
    node *template = (node *)malloc(sizeof(node));
    if (template == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    template->num = num;
    template->left = NULL;
    template->right = NULL;
    template->parent = NULL;
    template->frequency = 0;
    return template;
}
void printPreorder(node *Node, int type)
{
    if (Node == NULL)
    {
        return;
    }

    if (type == 0)
    {
        printf("%d,", Node->num);
    }
    else if (type == 1)
    {
        printf("(%d,%d),", Node->num, Node->frequency);
    }

    printPreorder(Node->left, type);
    printPreorder(Node->right, type);
}
void readFile(node **root, FILE *inputFile, int type)
{
    while (1)
    {
        int num = fgetc(inputFile) - '0';
        if (feof(inputFile))
        {
            break;
        }
        node *xnode = NULL;
        if (num >= 0)
        {
            node *xnode = createTemp(num);
            insert(xnode, root, type);
        }
    }
}
void insert(node *xnode, node **root, int type)
{
    if (*root == NULL)
    {
        *root = xnode;
        return;
    }

    node *current = *root;
    while (1)
    {
        if (xnode->num < current->num)
        {
            comparision[type]++;
            if (current->left == NULL)
            {
                current->left = xnode;
                xnode->parent = current;
                if (type == 0)
                {
                    rotations(xnode, root, type);
                }
                else if (type == 1)
                {
                    if ((*root)->frequency < xnode->frequency)
                    {
                        rotations(xnode, root, type);
                    }
                }

                break;
            }
            else
            {
                current = current->left;
            }
        }
        else if (xnode->num > current->num)
        {
            comparision[type]++;
            if (current->right == NULL)
            {
                current->right = xnode;
                xnode->parent = current;
                if (type == 0)
                {
                    rotations(xnode, root, type);
                }
                else if (type == 1)
                {
                    if ((*root)->frequency < xnode->frequency)
                    {
                        rotations(xnode, root, type);
                    }
                }

                break;
            }
            else
            {
                current = current->right;
            }
        }
        else if (xnode->num == current->num)
        {
            comparision[type]++;
            if (type == 0)
            {
                rotations(current, root, type);
            }
            else if (type == 1)
            {
                current->frequency++;
                if ((*root)->frequency < current->frequency)
                {
                    rotations(current, root, type);
                }
            }
            break;
        }
        else
        {
            printf("Error!");
            break;
        }
    }
}
void rotations(node *x, node **root, int type)
{
    while (x->parent != NULL)
    {
        node *p = x->parent;
        node *g = p->parent;
        node *gg = g != NULL ? g->parent : NULL;
        if (g == NULL)
        {
            rotation[type]++;
            zig(x, p, g);
            break;
        }

        else if ((p->left == x && g->right == p) || (p->right == x && g->left == p))
        {
            rotation[type] += 2;
            zigzag(x, p, g);
            if (x->parent == NULL)
            {
                break;
            }
        }

        else if ((p->left == x && g->left == p) || (p->right == x && g->right == p))
        {
            rotation[type] += 2;
            zigzig(x, p, g);
            if (x->parent == NULL)
            {
                break;
            }
        }
    }

    *root = x;
}
void zigzag(node *X, node *P, node *G)
{
    node *GG = G->parent;

    if ((P->right == X) && (G->left == P))
    {
        if ((G->left = X->right) != NULL)
        {
            G->left->parent = G;
        }

        if ((P->right = X->left) != NULL)
        {
            P->right->parent = P;
        }

        X->right = G;
        X->left = P;
        G->parent = X;
        P->parent = X;
    }
    else if ((P->left == X) && (G->right == P))
    {
        if ((G->right = X->left) != NULL)
        {
            G->right->parent = G;
        }

        if ((P->left = X->right) != NULL)
        {
            P->left->parent = P;
        }

        X->left = G;
        X->right = P;
        G->parent = X;
        P->parent = X;
    }
    else
    {
        printf("ERROR IN ZIGZAG FUNCTION (-1)\n");
        return;
    }

    if (GG != NULL)
    {
        if (GG->left == G)
        {
            GG->left = X;
        }
        else if (GG->right == G)
        {
            GG->right = X;
        }
        else
        {
            printf("ERROR IN ZIGZAG FUNCTION (-1)\n");
            return;
        }
    }

    X->parent = GG;
}
void zigzig(node *X, node *P, node *G)
{

    node *GG = G->parent;

    if ((P->right == X) && (G->right == P))
    {
        if ((G->right = P->left) != NULL)
        {
            G->right->parent = G;
        }

        if ((P->right = X->left) != NULL)
        {
            P->right->parent = P;
        }

        P->left = G;
        P->left->parent = P;

        X->left = P;
        X->left->parent = X;
    }
    else if ((P->left == X) && (G->left == P))
    {
        if ((G->left = P->right) != NULL)
        {
            G->left->parent = G;
        }

        P->right = G;
        P->right->parent = P;
        if ((P->left = X->right) != NULL)
        {
            P->left->parent = P;
        }

        X->right = P;
        X->right->parent = X;
    }
    else
    {
        printf("ERROR IN ZIGZIG FUNCTION (-1)\n");
        return;
    }

    if (GG != NULL)
    {
        if (GG->left == G)
        {
            GG->left = X;
        }
        else if (GG->right == G)
        {
            GG->right = X;
        }
        else
        {
            printf("ERROR IN ZIGZIG FUNCTION (-1)\n");
            return;
        }
    }

    X->parent = GG;
}
void zig(node *X, node *P, node *G)
{

    if (P->left == X)
    {
        if ((P->left = X->right) != NULL)
        {
            P->left->parent = P;
        }

        X->right = P;
        X->right->parent = X;
    }
    else if (P->right == X)
    {
        if ((P->right = X->left) != NULL)
        {
            P->right->parent = P;
        }

        X->left = P;
        X->left->parent = X;
    }
    else
    {
        printf("ERROR IN ZIG FUNCTION(-1)\n");
        return;
    }
    X->parent = NULL;
}
int main()
{
    FILE *inputFile = fopen("input.txt", "r");
    if (inputFile == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    node *root1 = NULL;

    readFile(&root1, inputFile, 0);
    printf("\nSplay tree:\n");
    printPreorder(root1, 0);
    printf("\nSplay cost:%d + %d= %d", comparision[0], rotation[0], comparision[0] + rotation[0]);
    fseek(inputFile, 0, SEEK_SET);

    node *root2 = NULL;
    readFile(&root2, inputFile, 1);
    printf("\nMod-Splay tree:\n");
    printPreorder(root2, 1);
    printf("\nMod-Splay cost:%d + %d= %d", comparision[1], rotation[1], comparision[1] + rotation[1]);

    fclose(inputFile);

    return 0;
}