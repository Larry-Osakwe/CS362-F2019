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

	printf("Test tribute Card Effect:\n");
    int numPlayers = 2;
    int seed = 10;
    int tributeRevealedCards[2] = {-1, -1};

    //set your card array
    int k[10] = { ambassador, council_room, feast, tribute, mine, remodel, smithy, village, baron, great_hall };

    // declare the game states
    struct gameState cleanGame;
    struct gameState compareGame;
    struct gameState testGame;
    initializeGame(numPlayers, k, seed, &cleanGame);
    
    //********Test 1: Reveal two treasure cards**********
    printf("\nTest: Left player reveals two treaure cards\n");
    memcpy(&testGame, &cleanGame, sizeof(struct gameState));
    testGame.hand[0][0] = tribute;
    testGame.deckCount[1] = 2;
    testGame.deck[1][0] = copper;
    testGame.deck[1][1] = copper;
    memcpy(&compareGame, &testGame, sizeof(struct gameState));
    cardEffectTribute(0, &testGame);

    //Assert coins increase by 4
    printf("Results: %d coins. Expected %d.\n", testGame.coins, compareGame.coins + 4);
    myAssert(testGame.coins, compareGame.coins + 4);

    return 0;
}

