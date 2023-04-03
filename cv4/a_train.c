#include "a_train.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
struct car* add_car(struct car* first, const char* target) {
    struct car* newcar = calloc(1,sizeof(struct car));
    strcpy(newcar->value, target);
    struct car* this = first;
    if(this == NULL){
        return newcar;
    }
    while(this->next != NULL){
        this = this->next;
    }
    this->next = newcar;
    return first;
}
 
void print_train(struct car* first) {
    struct car* this = first;
    if(this != NULL){
        printf("%s\n", this->value);
        this = this->next;
        print_train(this);
    }
}
 
void cancel_train(struct car* first) {
    struct car* this;
    while (first != NULL)
    {
       this = first;
       first = first->next;
       free(this);
    }
}
 
 
struct car* clear_train(struct car* first, const char* target) {
    struct car* prev = first;
    if(prev == NULL){
        return NULL;   
    } else if(prev->next == NULL){
        if(strcmp(target, prev->value)){
            return prev;
        }
        return NULL;
    } else {
        // Už sme si istí, že  prev a prev->next nie sú NULL
        while (prev->next->next != NULL){
            if(strcmp(target, prev->next->value) == 0){
                struct car* third = prev->next->next;
                free(prev->next);
                prev->next = third;
                return first;
            }
            prev = prev->next;
        }
 
    }
	return NULL;
}