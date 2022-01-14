/*
 * Assignment:	Repeated Prisoners Dilemma Problem
 * Group: 	RN.12 and RN.24 (Nishchay and Shrikant)
 * File:	Main file for launching algorithms.
 * Description:
 * This file contains code for maintaining the scoreboard of the repeated
 * trials. 
 * */

#include<stdio.h>
#include<stdlib.h>

#include"rpd.h"		// We have defined the game-board structure in this file.

int scoreX,scoreY,RSEED;	// scoreX and scoreY maintain the total scores of the two algorithms. 
				// RSEED is used for seeding a random number generator which determines the opponent function's strategy
board *M;		// Array of moves, (allocated dynamically later)
int N;		// Total number of rounds in this game.

/* This function updates the scores after each trial. Input is the move made by
 * X and Y and the round number */

void update_board(int a,int b,int i)
{
 // Update the moves for this round
 M[i].x = a;	// M[i].x is X's move at the i-th iteration
 M[i].y = b;

 // Update the scores
 if(a==CO && b==CO)
	{
	 scoreX += 20;
	 scoreY += 20;
	}
 if(a==CO && b==DF)
	{
	 scoreY += 30;
	}
 if(a==DF && b==CO)
	{
	 scoreX += 30;
	}
 if(a==DF && b==DF)
	{
	 scoreX += 10;
	 scoreY += 10;
	}	
}

/* This main function takes two arguments. First argument is the number of
 * rounds in the game. The second argument is used to seed the RNG, i.e. it is
 * put into RSEED
 * */
int main(int argc,char*argv[1])
{
 int x,y;	// Initial moves of both algorithms.
 int i;
 
 if(argc == 1)
	{
 	 printf("Please enter number of iterations as the first argument, random number as second argument");
	 return;
	}
 N  = atoi(argv[1]);	// Total number of iterations.
 M = (board*) (malloc(sizeof(board)*N));	
 RSEED = atoi(argv[2]);

 /* Initialise both algorithms. The opponent algorithm (described in
    rpd_opponent.c gets initialised and makes the first move. Our algorithm (described in rpd_algo3.c)
    also gets initialised and also makes the first move,
 */
 x = my_algorithm(INIT);	
 y = opponent_algorithm(INIT);
 update_board(x,y,0);		// Update score and board after the first move.
  
 i=1;
 while(i<N)		// Play N rounds
	{
	 y = opponent_algorithm(x);	// My move from last time supplied to opponent's algorithm;
	 x = my_algorithm(y);		// Opponent's current move supplied to my algo. 
	 update_board(x,y,i);		// Update the board. Both algorithms can access the history of moves from the board for future moves.
	 i++;	
	}
 
 // Game ends.
 // The following code accesses the scoreboard and the moves board and prints
 // the result of the game.
 
 char moves[]={'C','D'};
 printf("Scoreboard\nX\tY\n------------");
 for(i=1;i<N;i++)
	{
	 printf("\n%c\t%c",moves[M[i].x],moves[M[i].y]);
	}
 printf("\n------------\n%d\t%d\n",scoreX,scoreY);
 if(scoreX>scoreY)
	printf("\nX wins!\n");
 else if(scoreY>scoreX)
	printf("\nY wins!\n");
      else printf("\nIt's a Draw\n");
	
}
