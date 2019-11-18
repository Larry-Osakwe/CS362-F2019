#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int NUM_CARDS = 17;
int NUM_TESTS = 1000;

void randomizeGame(struct gameState *g, int k[10]);
void tributeAssert(struct gameState *base, struct gameState *test, int k[10], int testNum, int revealed[]);

int main() {
	printf("Random Test Tribute Card Effect:\n");

	//set your card array
    int k[10] = { adventurer, council_room, feast, gardens, mine, minion, smithy, village, tribute, great_hall };

    // declare the game states
    srand(time(NULL));
    struct gameState baseGame;
    struct gameState testGame;



    for (int i = 0; i < NUM_TESTS; i++) {
    	randomizeGame(&testGame, k);
    	memcpy(&baseGame, &testGame, sizeof(struct gameState));
    	int revealed[2] = {-1, -1};
    	//Give the player a copy of the baron card to be played
        int handPos = rand() % testGame.handCount[0];
        testGame.hand[0][handPos] = tribute;
        tributeCardEffect(&testGame, 1, 0, revealed, handPos);
        tributeAssert(&baseGame, &testGame, k, i, revealed);
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

void tributeAssert(struct gameState *base, struct gameState *test, int k[10], int testNum, int revealed[]){
    int coins = 0;
    int actions = 0;
    int cards = 0;

    if (revealed[0] == revealed[1]) {
        revealed[1] = -1;
    }

    if (revealed[0] == copper || revealed[0] == silver || revealed[0] == gold) {
        coins += 2;
    } else if (revealed[0] == estate || revealed[0] == duchy || revealed[0] == province || revealed[0] == gardens || revealed[0] == great_hall) {
        cards += 2;
    } else if(revealed[0] != -1) {
        actions += 2;
    }

    if (revealed[1] == copper || revealed[1] == silver || revealed[1] == gold) {
        coins += 2;
    } else if (revealed[1] == estate || revealed[1] == duchy || revealed[1] == province || revealed[1] == gardens || revealed[1] == great_hall) {
        cards += 2;
    } else if(revealed[1] != -1) {
        actions += 2;
    }

    if (test->coins != base->coins + coins) {
        printf("Failed test %d: Wrong number of coins.\n", testNum);
    }
    if (test->numActions != base->numActions + actions) {
        printf("Failed test %d: Wrong number of actions.\n", testNum);
    }
    if (test->handCount[0] != base->handCount[0] + cards - 1) {
        printf("Failed test %d: Wrong number of cards.\n", testNum);
    }
}
