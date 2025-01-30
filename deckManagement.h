#ifndef deckManagement_h
#define deckManagement_h
typedef struct card_s {
    struct card_s *previous;
    char color[10];
    int value;
    char action[15];
    struct card_s *next;
} card;
void printDeck(card *headpt,card*tails); //print cards  value and color (if number is 11 , change into #)
void deckCreation(FILE* inp, card deck[]);  //get dech of cards from file
void addCard( card deck, card **head, card **tail ); // (p--next) be changed into  (p--deck[]--next)
void deleteMember(card **h, card **t, card *p); //delete cards from double linked list
void shuffleDeck(card cards[]);

//pass two selected cards and centercard
// return true if sum of two is center card
// return 1 if one color matched 2 if 2 color matched 0 if color not matched
void checkMatch(card *phand1, card *phand2, card center, bool *sumMatch, int *colorMatch);

int pointCalc(card *head);
#endif /* deckManagement_h */

