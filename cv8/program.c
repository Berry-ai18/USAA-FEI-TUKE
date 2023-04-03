#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#define SIZE 100

struct tree
{
    char value[SIZE];
    char question[SIZE];
    struct tree *left, *right;
};
struct tree *read_tree()
{
    char buffer[SIZE];
    memset(buffer, 0, SIZE);
    char *r = fgets(buffer, SIZE, stdin);
    assert(r);
    struct tree *node = calloc(1, sizeof(struct tree));
    memcpy(node->value, buffer, SIZE);
    // Ak je nacitany riadok listovy uzol ,tak netreba robit nic
    // inak rekurzivne nacitanie laveho syna
    // a rekurzivne nacitanie praveho syna
    if (buffer[0] != '*')
    {
        node->left = read_tree();
        node->right = read_tree();
    }
    return node;
}
void destroy_tree(struct tree *tree)
{
    if (tree->left)
    {
        destroy_tree(tree->left);
    }
    if (tree->right)
    {
        destroy_tree(tree->right);
    }
    free(tree);
}
void print_tree(struct tree *tree, int offset)
{
    for (int i = 0; i < offset; i++)
    {
        printf(" ");
    }
    printf("%s", tree->value);
    if (tree->left)
    {
        print_tree(tree->left, offset + 3);
        print_tree(tree->right, offset + 3);
    }
}
// https://www.geeksforgeeks.org/write-a-c-program-to-get-count-of-leaf-nodes-in-a-binary-tree/
unsigned int count_nodes(struct tree *node)
{
    if (node == NULL)
    {
        return 0;
    }
    if (node->left == NULL && node->right == NULL)
    {
        return 1;
    }
    else
    {
        return count_nodes(node->left) +
               count_nodes(node->right);
    }
}

int main()
{
    struct tree *node = read_tree();
    struct tree *original = node;
    count_nodes(node);
    char answer;
    printf("Expert z bufetu to vie.\n");
    printf("Pozna %d druhov ovocia a zeleniny.\n", count_nodes(node));
    printf("Odpovedajte 'a' pre prvu moznost alebo 'n' pre druhu moznost.\n");
    while (node->left != NULL)
    {
        printf("%s", node->value);
        int c = 0;
        c = getchar();
        c = getchar();
        if (c == 'n')
        {
            node = node->right;
        }
        else if (c == 'a')
        {
            node = node->left;
        }
        else if (c == -1)
        {
            destroy_tree(original);
            printf("Koniec vstupu\n");
            return 0;
        }
        else
        {
            destroy_tree(original);
            printf("Nerozumiem\n");
            return 0;
        }
    }
    printf("%s", node->value);
    printf("Koniec\n");
    destroy_tree(original);
    return 0;
}