#include<stdio.h>
# include<stdlib.h>
#include<stdbool.h>
#include <time.h>
# define MAXHAND 50
#include "deckManagement.h"
#define deckSize 108
int main(void){
    bool shuffle = false;
    int start,startSum = 0;
    card deck[deckSize];
    //card *head = NULL, *temp = NULL, *tail = NULL;
    card *p1head = NULL, *p1tail = NULL;
    card *p2head = NULL, *p2tail = NULL;
    card *chead = NULL, *ctail = NULL;
    card *headCurr, *tailCurr;
    card *centerCard;
    int nump1 =0 , nump2 =0, numpCurr;//number of cards in each players hands & one pointer to switch these two numbers by turn
    int countCenter ; //count number of cards to be added center before switch player
    char input ='_';
    bool gameDone = false; //flag if game is done
    int player = 2; //flag to switch players turn
    bool sumMatch = false;
    int colorMatch = 0;
    int count;
    int i ; //index for deck increment by 1 throuout whole one game
    int numPlay,card1,card2; //number of playing card
    FILE* inp;
    inp = fopen("CardDeck.txt","r");
    card *temp1 = NULL;
    card *temp2 = NULL;
    bool aMatch = false;
    
    
    srand((int)time(0));
    while(!shuffle){
        
        printf("Press 1 to shuffle the DOS deck or 2 to load a deck from a file: ");
        scanf("%d", &start);
        startSum += start;
        if (start == 1){
            if(startSum <= 1){
                printf("Deck is not created\n");
            }
            else{
                shuffleDeck(deck);
                shuffle = true;
            }
            
        }
        else if(start == 2){
            if(inp==NULL){
                printf("Deckcreation failed\n");
                return -1;
            }
            else{
                deckCreation(inp, deck);
            }
        }
    }
    
    printf("The deck is shuffled. Press any key to deal cards:");
    scanf(" %c",&input);
    
    
    //distribute cards to two players & set two cards in centerline
    for(i = 0; i<14 ;i += 2){
        addCard( deck[i], &p1head, &p1tail);
        nump1++;
        addCard( deck[i + 1], &p2head, &p2tail);
        nump2++;
    }
    i -=1;
    addCard(deck[i] , &chead, &ctail);  //add cards to centerline
    i++;
    addCard(deck[i], &chead, &ctail);  //
    i++;
    countCenter = 2;
    
    
    //start playing until player wins
    while(!gameDone){
        
        if(player == 2){
            
            headCurr = p1head;
            tailCurr = p1tail;
            numpCurr = nump1;
            colorMatch = 0;
            player = 1;
            printf("\nPlayer's one turn.\n\n");
        }
        else{
            
            headCurr = p2head;
            tailCurr = p2tail;
            numpCurr = nump2;
            colorMatch = 0;
            player = 2;
            printf("\nPlayer's two turn.\n\n");
        }
        
        //keep center line >= 2
        while(countCenter < 2){
            addCard(deck[i], &chead, &ctail);
            i++;
            countCenter ++;
        }
        centerCard = chead;
        aMatch = false;
        while(centerCard != NULL){
            
            printf("Centerline:");
            printDeck( chead, ctail);
            
            //print hand
            if(player == 1){
                printf("\nPlayer’s one hand: ");
            }
            else{
                printf("\nPlayer’s two hand:");
            }
            printDeck(headCurr, tailCurr);
            
            
            if(centerCard->value == 11){
                printf("\n\nHow many cards do you want to play on # %s: ",centerCard->color);
            }
            else{
                printf("\n\nHow many cards do you want to play on %d %s: ",centerCard->value,centerCard->color);
            }
            scanf("%d", &numPlay);
            
            if( numPlay == 1){ //if one card play
                aMatch = true;
                if(numpCurr==1){
                    printf("\n\nSelect a card from 1:");
                }
                else{
                    printf("\n\nSelect a card from 1-%d:", numpCurr);
                }
                scanf("%d", &card1);
                
                //
                temp1 = headCurr;
                temp2 = NULL;
                count = 0;
                while (count < (card1-1)){
                    count++;
                    temp1 = temp1->next;
                    //
                    
                }
                
                //check if selected card is valid
                checkMatch(temp1, temp2, *centerCard, &sumMatch, &colorMatch);
                while(sumMatch != true){
                    printf("\n\nThat selection does not total to the center row card. Select again.:");
                    scanf("%d", &card1);
                    
                    //
                    temp1 = headCurr;
                    temp2 = NULL;
                    count = 0;
                    while (count < (card1-1)){
                        count++;
                        temp1 = temp1->next;
                        
                        //
                    }
                    checkMatch(temp1, temp2, *centerCard, &sumMatch, &colorMatch);
                }
                deleteMember( &headCurr , &tailCurr, temp1);
                if(centerCard -> next == NULL){
                    deleteMember( &chead , &ctail , centerCard);
                    centerCard = NULL;
                }
                else{
                    centerCard = centerCard->next;
                    deleteMember( &chead , &ctail , centerCard->previous);
                }
                numpCurr-=1;
                sumMatch = false;
                countCenter --;
                
                
                
                if (colorMatch == 1){
                    printf("One color matched.");
                    printf("\n\nSelect 1 additional card(s) to place to the center row.\n");
                    scanf("%d", &card1);
                    
                    //
                    temp1 = headCurr;
                    temp2 = NULL;
                    count = 0;
                    while (count < (card1-1)){
                        count++;
                        temp1 = temp1->next;
                    }
                    //
                    
                    // addCardExample(&headCurr, &chead,  *temp1 );
                    
                    addCard( *temp1, &chead, &ctail);
                    deleteMember( &headCurr , &tailCurr, temp1);
                    numpCurr-=1;
                    countCenter ++;
                }
               
            }
                else if( numPlay == 2 ){
                    aMatch = true;
                    printf("\nSelect two cards from 1-%d:", numpCurr);
                    scanf("%d%*c%d",&card1, &card2);
                    
                    //check if selected card is valid
                    
                    
                    //
                    temp1 = headCurr;
                    temp2 = headCurr;
                    count = 0;
                    while (count < (card1-1)){ //Getting first card
                        count++;
                        temp1 = temp1->next;
                    }
                    
                    count = 0;
                    while (count < (card2-1)){ // Getting second card
                        count++;
                        temp2 = temp2->next;
                    }
                    //
                    
                    
                    checkMatch(temp1, temp2, *centerCard, &sumMatch, &colorMatch);
                    while(sumMatch != true){
                        printf("\nThat selection does not total to the center row card. Select again.:");
                        scanf("%d%d", &card1, &card2);
                        
                        //
                        temp1 = headCurr;
                        temp2 = headCurr;
                        count = 0;
                        while (count < (card1-1)){ //Getting first card
                            count++;
                            temp1 = temp1->next;
                        }
                        
                        count = 0;
                        while (count < (card2-1)){ // Getting second card
                            count++;
                            temp2 = temp2->next;
                        }
                        //
                        checkMatch(temp1, temp2, *centerCard, &sumMatch, &colorMatch);
                    }
                    
                    deleteMember( &headCurr, &tailCurr, temp1);
                    deleteMember( &headCurr, &tailCurr, temp2);
                    if(centerCard -> next == NULL){
                        deleteMember( &chead , &ctail , centerCard);
                        centerCard = NULL;
                    }
                    else{
                        centerCard = centerCard->next;
                        deleteMember( &chead , &ctail , centerCard->previous);
                    }
                    countCenter--;
                    numpCurr -= 2;
                    sumMatch = false;
                    
                    
                    if (colorMatch == 2){
                        printf("\nDouble color match! Select an additional card to place in the centerline. One additional card added to opponent.\n");
                        printf("Hand :");
                        printDeck( headCurr, tailCurr);
                        printf("Select a card to add to center line: ");
                        scanf("%d", &card1);
                        
                        
                        //
                        temp1 = headCurr;
                        temp2 = NULL;
                        count = 0;
                        while (count < (card1-1)){ //Getting first card
                            count++;
                            temp1 = temp1->next;
                        }
                        //
                        
                        addCard(*temp1, &chead, &ctail);
                        deleteMember( &headCurr , &tailCurr, temp1);
                        
                        if (player == 1){
                            addCard(deck[i], &p2head, &p2tail);
                            i++;
                            nump2++;
                        }
                        else {
                            addCard(deck[i], &p1head, &p2tail);
                            i++;
                            nump1++;
                        }
                        
                        numpCurr -= 2;
                        countCenter +=1;
                        
                        
                    }
                  
                }
                
                else if( (centerCard -> next == NULL) && (aMatch == false) ) {
                    // if player does not have any cards to play on the centerline
                    centerCard = centerCard->next;
                    printf("Player does not have any cards to match to the centerline, card has been added to player's hand from the deck.\n\n");
                    addCard(deck[i], &headCurr, &tailCurr);
                    i++;
                    numpCurr += 1;
                    
                    printf("Hand: ");
                    printDeck(headCurr, tailCurr);
                    
                    printf("Select a card to put into the centerline:\n");
                    scanf("%d", &card1);
                    
                    temp1 = headCurr;
                    temp2 = NULL;
                    count = 0;
                    while (count < (card1-1)){ //Getting first card
                        count++;
                        temp1 = temp1->next;
                    }
                    
                    addCard(*temp1, &chead, &ctail);
                    deleteMember(&headCurr, &tailCurr, temp1);
                    numpCurr --;
                    
                }
                else{
                    centerCard = centerCard -> next;
                }
                    
                    
               
            if(headCurr == NULL){
                gameDone = true;
                centerCard = NULL;
                }
            }
            
            //check color match before pass to next player
            printf("\nThere are no more center row cards to match.");
                  
            if(player == 1){
                p1head = headCurr;
                p1tail = tailCurr;
                nump1 = numpCurr;
            }
            else{
                p2head = headCurr;
                p2tail = tailCurr;
                nump2 = numpCurr;
            }
            
            
            //check if player win
            if (p1head == NULL){ //p1 win
                printf("\n\nPlayer one wins with %d points!\n", pointCalc(p2head));
                gameDone = true;
            }
            else if(p2head == NULL ){ //p2 wins
                printf("\n\nPlayer two wins with %d points!\n", pointCalc(p1head));
                gameDone = true;
            }
            
        }
        
    }
    
    

