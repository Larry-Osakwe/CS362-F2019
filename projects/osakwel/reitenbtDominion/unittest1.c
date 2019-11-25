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

	printf("Test Baron Card Effect:\n");
    int numPlayers = 2;
    int seed = 10;

    //set your card array
    int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

    // declare the game states
    struct gameState cleanGame;
    struct gameState compareGame;
    struct gameState testGame;
    initializeGame(numPlayers, k, seed, &cleanGame);
    
    //Test 1: Gain estate card
    printf("\nTest: Gain estate card\n");
    memcpy(&testGame, &cleanGame, sizeof(struct gameState));
    testGame.hand[0][0] = baron;
    memcpy(&compareGame, &testGame, sizeof(struct gameState));
    cardEffectBaron(0, 0, &testGame);

    //Assert number of buys increased by 1
    printf("Results: %d Buys. Expected %d.\n", testGame.numBuys, compareGame.numBuys+1);
    myAssert(testGame.numBuys, compareGame.numBuys+1);

    //Assert gold isn't gained
    printf("Results: %d coins. Expected %d.\n", testGame.coins, compareGame.coins);
    myAssert(testGame.coins, compareGame.coins);

    //Asset estates in discard pile increased
    int testGameEstates = 0;
    int compareGameEstates = 0;
    for(int i = 0; i < testGame.handCount[0]; i++){
        if (testGame.discard[0][i] == estate){
            testGameEstates++;
        }
    }
    for(int i = 0; i < compareGame.handCount[0]; i++){
        if (compareGame.discard[0][i] == estate){
            compareGameEstates++;
        }
    }
    printf("Results: %d estates. Expected %d.\n", testGameEstates, compareGameEstates-1);
    myAssert(testGameEstates, compareGameEstates+1);


    //Test 2: Discard estate card
    printf("\n<<< Test 1 - Discard estate card >>>\n");
    memcpy(&testGame, &cleanGame, sizeof(struct gameState));
    testGame.hand[0][0] = baron;
    testGame.hand[0][1] = estate;
    memcpy(&compareGame, &testGame, sizeof(struct gameState));
    cardEffectBaron(0, 1, &testGame);

    //Assert number of buys increased by 1
    printf("Results: %d Buys. Expected %d.\n", testGame.numBuys, compareGame.numBuys+1);
    myAssert(testGame.numBuys, compareGame.numBuys+1);

    //Assert number of gold increased by 4
    printf("Results: %d coins. Expected %d.\n", testGame.coins, compareGame.coins+4);
    myAssert(testGame.coins, compareGame.coins+4);

    //Assert number of estate cards in hand reduced by 1
    testGameEstates = 0;
    compareGameEstates = 0;
    for(int i = 0; i < testGame.handCount[0]; i++){
        if (testGame.hand[0][i] == estate){
            testGameEstates++;
        }
    }
    for(int i = 0; i < compareGame.handCount[0]; i++){
        if (compareGame.hand[0][i] == estate){
            compareGameEstates++;
        }
    }

    printf("Results: %d estates. Expected %d.\n", testGameEstates, compareGameEstates-1);
    myAssert(testGameEstates, compareGameEstates-1);

    return 0;
}

