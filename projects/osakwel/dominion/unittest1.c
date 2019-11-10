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

	// int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

	// struct gameState G;

	// // declarethe arrays 
	// int coppers[MAX_HAND];
	// int silvers[MAX_HAND];
	// int golds[MAX_HAND];

	// printf("Begin Testing baronCardEffect():\n");

	// // set the state of your variables
	// // comment on what this is going totest

	// memset(&G, 23, sizeof(structgameState));   // setthe game state
	// r = initializeGame(2, k, seed, &G); // initialize a new game
	// G.handCount[p] = handCount;                 // setany other variables
	// memcpy(G.hand[p], coppers, sizeof(int) * handCount); 

	// // call the refactoredfunction
	// myrefactoredfunction(p, &G, bonus);

	// // verify that your assertspass, for the bugs your asserts may fail
	// assert(G.coins == something); // check acondition
	// assert(some condition); 
	// assert(some condition);

	// // adjustthe state of your variables to continue testing the function
	// // comment on what this is going to test

	// memset(&G, 0, sizeof(structgameState));   // setthe game state
	// r = initializeGame(3, k, seed, &G); // initialize a new game
	// G.handCount[p] = handCount;
	// memcpy(G.hand[p], silvers, sizeof(int) * handCount);

	// // call the refactoredfunctionagain
	// myrefactoredfunction(p, &G, bonus);

	// // verify that your assertspass, for the bugs your asserts may fail
	// assert(G.coins == something); // check acondition
	// assert(some condition); 
	// assert(some condition); 

	// printf("Testcompleted!\n");


	    printf("***************Beginning Tests for Baron***************\n");
    int seed = 10;
    int numPlayers = 2;
    //set your card array
    int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

    // declare the game states
    struct gameState initial;
    struct gameState G;
    struct gameState test;
    initializeGame(numPlayers, k, seed, &initial);
    memcpy(&test, &initial, sizeof(struct gameState));

    //Test1 - Discard estate card
    printf("\n<<< Test 1 - Discard estate card >>>\n");
    test.hand[0][0] = baron;
    test.hand[0][1] = estate;
    memcpy(&G, &test, sizeof(struct gameState));
    baronEffect(1, &test, 0, 0);
    //Assert number of buys increased by 1
    printf("Result %d Buys. Expected %d.\n", test.numBuys, G.numBuys+1);
    assert(test.numBuys, G.numBuys+1);
    //Assert number of gold increased by 4
    printf("Result %d coins. Expected %d.\n", test.coins, G.coins+4);
    myAssert(test.coins, G.coins+4);
    //Assert number of estate cards in hand reduced by 1
    int testEstates = 0;
    int GEstates = 0;
    for(int i = 0; i < test.handCount[0]; i++){
        if (test.hand[0][i] == estate){
            testEstates++;
        }
    }
    for(int i = 0; i < G.handCount[0]; i++){
        if (G.hand[0][i] == estate){
            GEstates++;
        }
    }
    printf("Result %d estates. Expected %d.\n", testEstates, GEstates-1);

}

