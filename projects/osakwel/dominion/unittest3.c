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

	printf("Test Ambassador Card Effect:\n");
    int numPlayers = 2;
    int seed = 10;

    //set your card array
    int k[10] = { ambassador, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

    // declare the game states
    struct gameState cleanGame;
    struct gameState compareGame;
    struct gameState testGame;
    initializeGame(numPlayers, k, seed, &cleanGame);
    
    //********Test 1: Return 2 cards**********
    printf("\nTest: Returning 2 cards from hand\n");
    memcpy(&testGame, &cleanGame, sizeof(struct gameState));
    testGame.hand[0][0] = ambassador;
    testGame.hand[0][1] = copper;
    testGame.hand[0][2] = copper;
    memcpy(&compareGame, &testGame, sizeof(struct gameState));
    ambassadorCardEffect(smithy, 2, 0, &test, 0);

    //Assert coppers removed from hand
    int testGameCoppers = 0;
    int compareGameCoppers = 0;
    for (int i = 0; i < testGame.handCount[0]; i++) {
        if (testGame.hand[0][i] == copper) {
            testGameCoppers++;
        }
    }
    for (int i = 0; i < compareGame.handCount[0]; i++) {
        if (compareGame.hand[0][i] == copper) {
            compareGameCoppers++;
        }
    }
    printf("Results: %d coppers. Expected %d.\n", testGameCoppers, compareGameCoppers-2);
    myAssert(testGameCoppers, compareGameCoppers-2);

    //Assert opponent has copper increases +2
    printf("Results: %d coins. Expected %d.\n", testGame.hand[1][0], copper);
    myAssert(testGame.hand[1][0], copper);

    return 0;
}

