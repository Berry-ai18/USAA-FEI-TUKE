#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#define SIZE 100

struct tree //struktura co obsahuje hodnotu uzlu a jeho 2 poduzly
{
    char value[SIZE];
    struct tree *left, *right;
};
struct tree *read_tree() //struktura na citanie stromu, uklada do buffera
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
    if (buffer[0] == '#')
    {
        node->left = read_tree();
        node->right = read_tree();
    }
    return node;
}

void read_string(char* code){ //nacita si posledny riadok kod(101010101010),ulozi ho do code
    char buffer[SIZE];
    memset(buffer, 0, SIZE);
    char *r = fgets(buffer, SIZE, stdin);
    //assert(r);
    struct tree *node = calloc(1, sizeof(struct tree));
    memcpy(code, buffer, SIZE);
}

void destroy_tree(struct tree *tree) //rekurzivne mazanie stromu
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

int traverse_tree(struct tree *node, char* code, int start){ //pohubybuje sa po strome 0 je dolava 1 je dopraava, zobere code a pozerq na hodnoty
    int i = start;
    while(!isalnum(node->value[0])){
        if(code[i] == '0'){
            node = node->left;
        } else if(code[i] == '1'){
            node = node->right;
        }
        i++;
    } 
    printf("%c", node->value[0]); 
    
    return i;
}

//nacita si strom, do nodu, nacita si code, skontroluje cely kode ci tam nie je znak ktory tam nema byt,
//zacne prechadzat strom a dekodovat
int main()
{
    struct tree *node = read_tree();
    char code[SIZE];
    read_string(code);
    int i = 0;
    for(i=0; i<strlen(code)-1; i++){
        if(code[i] == 13 || code[i] == 10){
            break;
        }
        if(!isdigit(code[i]) && code[i] > 32){
            printf("neplatny znak %d\n", code[i]);
            return 0;
        }
        if(code[i] != '1' && code[i] != '0'){
            printf("neplatny vstup\n");
            return 0;
        }
        
    }
    int start = 0;
    while(start < i){
        start = traverse_tree(node, code, start);
    }
    printf("\n");
    destroy_tree(node);
    
    
    return 0;
}