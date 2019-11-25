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

	printf("Test Mine Card Effect:\n");
    int numPlayers = 2;
    int seed = 10;
    

    //set your card array
    int k[10] = { ambassador, council_room, feast, tribute, mine, remodel, smithy, village, baron, great_hall };

    // declare the game states
    struct gameState cleanGame;
    struct gameState compareGame;
    struct gameState testGame;
    initializeGame(numPlayers, k, seed, &cleanGame);
    
    //********Test 1: Trash and gain treasure**********
    printf("\nTest: Trash and gain treasure\n");
    memcpy(&testGame, &cleanGame, sizeof(struct gameState));
    testGame.hand[0][0] = mine;
    testGame.hand[0][1] = copper;
    memcpy(&compareGame, &testGame, sizeof(struct gameState));
    mineCardEffect(&testGame, 0, 1, silver, 0);

    //Assert silver coin was obtained
    int testGameSilvers = 0;
    int compareGameSilvers = 0;
    for(int i = 0; i < testGame.handCount[0]; i++) {
        if (testGame.hand[0][i] == silver) {
            testGameSilvers++;
        }
    }
    for(int i = 0; i < compareGame.handCount[0]; i++) {
        if (compareGame.hand[0][i] == silver) {
            compareGameSilvers++;
        }
    }
    printf("Results: %d silver coins. Expected %d.\n", testGameSilvers, compareGameSilvers + 1);
    myAssert(testGameSilvers, compareGameSilvers + 1);


    return 0;
}

