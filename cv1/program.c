#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LINESIZE 100
#define POCET_JEDAL 100
struct pizza {
    float prize;
    char name[LINESIZE];
};
 
int read_pizza(struct pizza* item);
int search_string(const char* heap, const char* needle);
char hacker_script(char c);
 
int main(){
    printf("Zadaj hladanu surovinu:\n");
    char search[LINESIZE];
    memset(search,0,LINESIZE);
    char* r = fgets(search,LINESIZE,stdin);
    char search_hacker[strlen(search)-1];
    memset(search_hacker,0,strlen(search)-1);
    for(int i=0; i<strlen(search)-1; i++){
        search_hacker[i] = hacker_script(search[i]);
    }
    printf("Zadaj jedalny listok:\n");
    struct pizza jedalny_listok[POCET_JEDAL];
    // Na začiatku celé pole vynulujeme, všetky pizze sú nulové
    memset(jedalny_listok, 0,sizeof(struct pizza)*POCET_JEDAL);
    struct pizza *item = jedalny_listok;
    int counter = 0;
    while(read_pizza(item)){
        counter += 1;
        item = &jedalny_listok[counter];
    }
    for(int i=0; i<counter; i++){
        char name_hacker[LINESIZE];
        memset(name_hacker,0,LINESIZE);
        for(int j=0; j<strlen(jedalny_listok[i].name); j++){
            name_hacker[j] = hacker_script(jedalny_listok[i].name[j]);
        }
        if(search_string(name_hacker, search_hacker) != -1){
            printf("%s%.2f\n",jedalny_listok[i].name,jedalny_listok[i].prize);
        }
    }
 
    printf("Nacitanych %d poloziek.\n", counter);
    return 0;
}
 
int read_pizza(struct pizza* item){
    char line[LINESIZE];
    memset(line,0,LINESIZE);
    char* r = fgets(line,LINESIZE,stdin);
    char line2[LINESIZE];
    memset(line2,0,LINESIZE);
    char* r2 = fgets(line2,LINESIZE,stdin);
    float value = strtof(line2, NULL);
    // Ak je návratová hodnota nula, premena reťazca sa nepodarila.
    if (value == 0.0F){
        return 0;
    }
    item->prize = value;
    strcpy(item->name, line);
    return 1;
}
int search_string(const char* heap, const char* needle){
    int len_needle = strlen(needle);
    int len_heap = strlen(heap);
    /* A loop to slide pat[] one by one */
    for (int i = 0; i <= len_heap - len_needle; i++) {
        int j;
        /* For current index i, check for pattern match */
        for (j = 0; j < len_needle; j++){
            if (heap[i + j] != needle[j]){
                break;
            }
        }
        if (j == len_needle) // if pat[0...len_needle-1] = txt[i, i+1, ...i+len_needle-1]
            return i;
    }
    return -1;
}
char hacker_script(char c){
    if(c >= 'A' && c <= 'Z'){
        c = c + 32;
    }
    char numbers[] = "0123456789";
    char letters[] = "oizeasbtbq";
    for (int i = 0; i < 10; i++){
        if (c == numbers[i]){
            return letters[i];
        }
    }
    return c;
}
