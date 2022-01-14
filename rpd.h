
#ifndef RPD

#define CO 0		// Code for Cooperate
#define DF 1		// Code for Defect
#define INIT -1		// Code for the first run of the algorithm

typedef struct  _brd_	// This structure is used to track the moves made by players in one trial of the game. 
			// An array of these will constitute the whole game
{
 int x,y;		// x is the move of x (either CO or DF). Likewise for y
} board;

#endif /*RPD*/
