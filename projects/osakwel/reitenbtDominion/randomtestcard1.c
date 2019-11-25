#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int NUM_CARDS = 17;
int NUM_TESTS = 10000;

void randomizeGame(struct gameState *g, int k[10]);
void baronAssert(struct gameState *base, struct gameState *test, int choice, int k[10], int testNum);

int main() {
	printf("Random Test Baron Card Effect:\n");

	//set your card array
    int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

    // declare the game states
    srand(time(NULL));
    struct gameState baseGame;
    struct gameState testGame;

    for (int i = 0; i < NUM_TESTS; i++) {
    	randomizeGame(&testGame, k);
    	memcpy(&baseGame, &testGame, sizeof(struct gameState));
    	//Give the player a copy of the baron card to be played
        int handPos = rand() % testGame.handCount[0];
        testGame.hand[0][handPos] = baron;
        int choice1 = rand() % 2;
        cardEffectBaron(handPos, choice1, &testGame);
        baronAssert(&baseGame, &testGame, choice1, k, i);
    }
}

void randomizeGame(struct gameState *g, int k[10]) {
    int numPlayers = rand() % 3 + 2;
    initializeGame(numPlayers, k, 50, g);
    //Randomize deck/hand/discard counts of all players
    for (int i = 0; i < g->numPlayers; i++) {
        g->handCount[i] = rand() % 6 + 1;
        g->deckCount[i] = rand() % 11;
        g->discardCount[i] = rand() % 6;
    }

    //Randomize hand of all players
    for (int i = 0; i < g->numPlayers; i++) {
        for (int j = 0; j < g->handCount[i]; j++) {
            int card = rand() % NUM_CARDS;
            if (card < 7) {
                g->hand[i][j] = card;
            } else {
                g->hand[i][j] = k[card - 7];
            }
        }
    }

    //Randomize player decks
    for (int i = 0; i < g->numPlayers; i++) {
        for (int j = 0; j < g->deckCount[i]; j++) {
            int card = rand() % NUM_CARDS;
            if (card < 7){
                g->deck[i][j] = card;
            } else {
                g->deck[i][j] = k[card - 7];
            }
        }
    }

    //Randomize player discards
    for (int i = 0; i < g->numPlayers; i++) {
        for (int j = 0; j < g->discardCount[i]; j++) {
            int card = rand() % NUM_CARDS;
            if (card < 7) {
                g->discard[i][j] = card;
            } else {
                g->discard[i][j] = k[card - 7];
            }
        }
    }

    //Randomize supply counts
    for (int i = 0; i < 27; i++) {
        g->supplyCount[i] = rand() % 10;
    }
}

void baronAssert(struct gameState *base, struct gameState *test, 
int choice, int k[10], int testNum) {
    if (test->numBuys != base->numBuys + 1) {
        printf("Failed test %d. Incorrect number of buys.\n", testNum);
        return;
    }
    if (choice == 1) {
        //See if hand contains an Estate card
        int testEstates = 0;
        int baseEstates = 0;
        for(int i = 0; i < base->handCount[0]; i++) {
            if (base->hand[0][i] == estate){
                baseEstates++;
            }
        }
        for (int i = 0; i < test->handCount[0]; i++) {
            if (test->hand[0][i] == estate){
                testEstates++;
            }
        }
        if (baseEstates > 0) {
            if (testEstates != baseEstates - 1) {
                printf("Failed test %d: Wrong number of estates in hand.\n", testNum);
            }
            if (test->coins != base->coins + 4) {
                printf("Failed test %d: Wrong number of coins.\n", testNum);
            }
            if (test->handCount != base->handCount - 2) {
                printf("Failed test %d: Wrong number of cards in hand.\n", testNum);
            }
        } else {
            if (test->supplyCount[baron] != base->supplyCount[baron] - 1) {
                printf("Failed test %d: Wrong number of baron cards in supply.\n", testNum);
            }
            if (test->coins != base->coins) {
                printf("Failed test %d: Wrong number of coins.\n", testNum);
            }
            if (test->handCount != base->handCount - 1) {
                printf("Failed test %d: Wrong number of cards in hand.\n", testNum);
            }
            
        }
    } else {
        if (test->handCount != base->handCount - 1) {
            printf("Failed test %d: Wrong number of cards in hand.\n", testNum);
        }
        if (test->supplyCount[baron] != base->supplyCount[baron] - 1) {
            printf("Failed test %d: Wrong number of baron cards in supply.\n", testNum);
        }
        if (test->coins != base->coins) {
            printf("Failed test %d: Wrong number of coins.\n", testNum);
        }
    }
}