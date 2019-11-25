#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

void myAssert(int x, int y) {
	if (x == y) {
		printf("PASSED\n");
	} else {
		printf("FAILED\n");
	}
}

int main () {

	printf("Test Minion Card Effect:\n");
    int numPlayers = 2;
    int seed = 10;

    //set your card array
    int k[10] = { adventurer, minion, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

    // declare the game states
    struct gameState cleanGame;
    struct gameState compareGame;
    struct gameState testGame;
    initializeGame(numPlayers, k, seed, &cleanGame);
    
    //********Test 1: Gain coins**********
    printf("\nTest: Gain gain coins choice\n");
    memcpy(&testGame, &cleanGame, sizeof(struct gameState));
    testGame.hand[0][0] = minion;
    memcpy(&compareGame, &testGame, sizeof(struct gameState));
    cardEffectMinion(0, 0, &testGame);

    //Assert number of actions increased by 1
    printf("Results: %d Actions. Expected %d.\n", testGame.numActions, compareGame.numActions+1);
    myAssert(testGame.numActions, compareGame.numActions+1);

    //Assert gold increases +2
    printf("Results: %d coins. Expected %d.\n", testGame.coins, compareGame.coins+2);
    myAssert(testGame.coins, compareGame.coins+2);

    //*******Test 2: Discard your hand and draw 4*********
    printf("\nTest: Discard hand\n");
    memcpy(&testGame, &cleanGame, sizeof(struct gameState));
    testGame.hand[0][0] = minion;

    memcpy(&compareGame, &testGame, sizeof(struct gameState));
    cardEffectMinion(0, 1, &testGame);

    //Assert number of actions increased by 1
    printf("Results: %d Actions. Expected %d.\n", testGame.numActions, compareGame.numActions+1);
    myAssert(testGame.numActions, compareGame.numActions+1);

    printf("Results %d hand cards. Expected %d.\n", testGame.handCount[0], 4);
    myAssert(testGame.handCount[0], 4);

    return 0;
}

