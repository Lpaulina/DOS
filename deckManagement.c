#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include<stdbool.h>
#define deckSize 108
typedef struct card_s {
    struct card_s *previous;
    char color[10];
    int value;
    char action[15];
    struct card_s *next;
} card;
void printDeck(card *headpt){
    
        while(headpt!=NULL){  //print whole linked list
            
            if(headpt->value == 11){  //change 11 to #
                printf("# ");
            }
            else{
                printf(" %d ",headpt->value);
            }
            if(headpt->next == NULL){
                printf("%s\n",headpt->color);
            }
            else{
                printf("%s,",headpt->color);
            }
            
            headpt = headpt->next;  //update headpt to next card
        }
}
void deckCreation(FILE* inp, card deck[]){ //cited from slides
    int i=0;
    
    while(!feof(inp)){
        fscanf(inp,"%s%*c",deck[i].color);
        fscanf(inp,"%d",&deck[i].value);
        fscanf(inp,"%s%*c",deck[i].action);
        deck[i].previous = NULL;
        deck[i].next = NULL;
        i++;    //count number of card to be used as index
    }
    
}
void addCard(card deck,card **head, card **tail ){ //cited from slides
    
//make a clone of card that will be added
    card *temp;
    temp = (card*)malloc(sizeof (card));
    
    if (temp != NULL){
        strcpy(temp->color,deck.color);
        temp->value = deck.value;
        strcpy(temp ->action,deck.action );
        
            if(*head == NULL){ // if list is NULL
                *head = temp;
                *tail = temp;
                temp->previous = NULL;
                temp ->next = *tail;
            }
            else { // add to tail
                temp -> previous = *tail;
                (*tail)->next = temp;
                *tail = temp;
                temp ->next = NULL;
            }
    }
}
void deleteMember(card **h, card **t, card *p){  //cited from slides
    
    if (p == *h){ // if deleting the first element
        *h = p->next; // update the left headp
    }
    else {
        p->previous->next = p->next;
    }
    if (p == *t){
        *t = p->previous; // if deleting the last element
    }
    else {
        p->next->previous = p->previous;
    }
    free(p); // free memory
}
void shuffleDeck(card cards[]){
    int i;
    int randInt;
    card temp;
    srand((unsigned int)time(0));
    
    for(i = 0; i < deckSize; i++){
        randInt = rand() % (i+1);
        temp = cards[i];
        cards[i] = cards[randInt];
        cards[randInt] = temp;
        
    }
}
void checkMatch(card *phand1, card *phand2, card center, bool *sumMatch, int *colorMatch){
    if (strcmp(center.color, "black") == 0) {   // checking if centerCard accepts any color as color match and if both players cards are equal the same
        if (phand2 != NULL){
            if (strcmp(phand1->color, phand2->color) == 0){
                *colorMatch = 2;
            }
        }
        else {
            *colorMatch = 1;
        }
    }
    else if ((strcmp(phand1->color, "black") == 0) ){ //checking if color of phand1 is black
        if (phand2 != NULL){ //checking if player is playing two cards
            if (strcmp (phand1->color, phand2->color) == 0){ // checking if both cards are black
                *colorMatch = 2;
            }
        }
        else{
            *colorMatch = 1;
        }
    }
    
    if(strcmp(center.action, "AnyNumber") == 0){  // if centerline is #
        if (phand2 != NULL){          // Assigning center value to the sum of cards
            center.value = phand1->value + phand2->value;
        }
        else{ // assigning center to the value of 1 card if there is only 1 card
            center.value = phand1->value;
        }
    }
    else if (strcmp(phand1->action, "AnyNumber")== 0){   //Checking if phand1 is #
        if (phand2 != NULL){      // if sending 2 cards, assigning a value to phand1
            phand1->value = center.value - phand2->value;
        }
        else{  // if sending 1 card, assigning the value  of p1hand
            phand1->value = center.value;
        }
    }
    else if (phand2 != NULL){
        if (strcmp(phand2->action, "AnyNumber")== 0){ //checking if phand2 is #, and assigning it a value
            phand2->value = center.value - phand1->value;
        }
    }
    
    
    if (phand2 == NULL){     // checking if the player is placing only one card
        if (phand1->value == center.value){
            *sumMatch = true;    //if the values match then sumMatch is true
            if (strcmp(phand1->color, center.color) == 0){
                *colorMatch = 1; // if colors match for one card color match is equal to 1
            }
        }
    }
    else { //if player is placing 2 cards
        if ((phand1->value + phand2->value) == center.value){ //checking cards' sum
            *sumMatch = true;
            if (strcmp(phand1->color, phand2->color) == 0 && strcmp(phand1->color, center.color) == 0){
                // Checking if both cards are the same color as the center
                *colorMatch = 2;
            }
        }
    }
}

int pointCalc(card *head){
    int point = 0;
    
    while(head!=NULL){ //count points from p2 hand
        
        if( head->value == 11){
            point += 40;
        }
        else if(head->value == 2){
            point += 20;
        }
        else{
            point += head->value;
        }
        head = head->next;
    }
    
    return point;
}
