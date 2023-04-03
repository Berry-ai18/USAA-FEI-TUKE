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
int compare_pizza (const void * a, const void * b);
int main(){
	struct pizza jedalny_listok[POCET_JEDAL];
	// Na začiatku celé pole vynulujeme, všetky pizze sú nulové
	memset(jedalny_listok, 0,sizeof(struct pizza)*POCET_JEDAL);
	struct pizza *item = jedalny_listok;
	int counter = 0;
	while(read_pizza(item)){
		counter += 1;
		item = &jedalny_listok[counter];
	}
 
    qsort(jedalny_listok, counter, sizeof(struct pizza), compare_pizza);
    for(int i=0; i<counter; i++){
        printf("%s%.6f\n",jedalny_listok[i].name,jedalny_listok[i].prize);
    }
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
 
int compare_pizza (const void * a, const void * b){
    struct pizza* pizza_a = a;
    struct pizza* pizza_b = b;
    float prize1 = pizza_a->prize;
    char* name1 = pizza_a->name;
    float prize2 = pizza_b->prize;
    char* name2 = pizza_b->name;
    float r = prize1 - prize2;
    if(r == 0){
        return strcmp(name1,name2);
    } else if (r > 0){
        return 1;
    } else {
        return -1;
    }
}