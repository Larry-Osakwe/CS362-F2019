#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int NUM_CARDS = 17;
int NUM_TESTS = 500;

void randomizeGameState(struct gameState *g, int k[10]);
void minionAssert(struct gameState *base, struct gameState *test, int choice1, int choice2, int k[10], int testNum);

int main() {
	printf("Random Test Minion Card Effect:\n");

	//set your card array
    int k[10] = { adventurer, council_room, feast, gardens, mine, minion, smithy, village, baron, great_hall };

    // declare the game states
    srand(time(NULL));
    struct gameState baseGame;
    struct gameState testGame;



    for (int i = 0; i < NUM_TESTS; i++) {
    	randomizeGameState(&testGame, k);
    	memcpy(&baseGame, &testGame, sizeof(struct gameState));
    	//Give the player a copy of the baron card to be played
        int handPos = rand() % testGame.handCount[0];
        testGame.hand[0][handPos] = minion;
        int choice1 = rand() % 2;
        int choice2 = 1 - choice1;
        minionCardEffect(&testGame, handPos, 0, choice1, choice2);
        minionAssert(&base, &test, choice1, choice2, k, i);
    }
}


void randomizeGameState(struct gameState *g, int k[10]){
    int numPlayers = rand() % 3 + 2;
    initializeGame(numPlayers, k, 50, g);
    //Randomize deck/hand/discard counts of all players
    for(int i = 0; i < g->numPlayers; i++){
        g->deckCount[i] = rand() % 11;
        g->handCount[i] = rand() % 6 + 1;
        g->discardCount[i] = rand() % 6;
    }
    //Randomize decks of all players
    for(int i = 0; i < g->numPlayers; i++){
        for(int j = 0; j < g->deckCount[i]; j++){
            int card = rand() % NUM_CARDS;
            if(card < 7){
                g->deck[i][j] = card;
            }
            else{
                g->deck[i][j] = k[card - 7];
            }
        }
    }
    //Randomize randomize hands of all players
    for(int i = 0; i < g->numPlayers; i++){
        for(int j = 0; j < g->handCount[i]; j++){
            int card = rand() % NUM_CARDS;
            if(card < 7){
                g->hand[i][j] = card;
            }
            else{
                g->hand[i][j] = k[card - 7];
            }
        }
    }
    //Randomize discards of all players
    for(int i = 0; i < g->numPlayers; i++){
        for(int j = 0; j < g->discardCount[i]; j++){
            int card = rand() % NUM_CARDS;
            if(card < 7){
                g->discard[i][j] = card;
            }
            else{
                g->discard[i][j] = k[card - 7];
            }
        }
    }
    //Randomize all supply counts
    for(int i = 0; i < 27; i++){
        g->supplyCount[i] = rand() % 10;
    }
}

void minionAssert(struct gameState *base, struct gameState *test, 
int choice1, int choice2, int k[10], int testNum){
    
    for(int i = 0; i < 27; i++){
        if(test->supplyCount[i] != base->supplyCount[i]){
            printf("Failed test %d. Incorrect number of cards in supply.\n", testNum);
        }
    }
    
    if(test->numActions != base->numActions + 1){
        printf("Failed test %d. Incorrect number of actions.\n", testNum);
    }
    if(choice1){
        if(test->coins != base->coins + 2){
            printf("Failed test %d. Incorrect number of coins.\n", testNum);
        }
        if(test->handCount[0] != base->handCount[0] - 1){
            printf("Failed test %d. Incorrect number of coins.\n", testNum);
        }
    }
    else if(choice2){
        if(test->handCount[0] != 4){
            printf("Failed test %d. Incorrect number of cards in hand.\n", testNum);
        }
        for(int j = 1; j < base->numPlayers; j++){
            if(base->handCount[j] > 4){
                if(test->handCount[j] != 4){
                    printf("Failed test %d. Incorrect number of cards in opponent's hand.\n", testNum);
                }
            }
            else{
                if(test->handCount[j] != base->handCount[j]){
                    printf("Failed test %d. Incorrect number of cards in opponent's hand.\n", testNum);
                }
            }
        }
    }

}