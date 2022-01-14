/*
 * Assignment:	Repeated Prisoners Dilemma Problem
 * Group: 	RN.12 and RN.24 (Nishchay and Shrikant)
 * File:	Simulated Opponent for Testing Our Algorithm
 * Description:
 * 
 * We have defined beforehand how many times, the opponent will cooperate and
 * how many times it will defect. This is defined by the Macro `PD' --
 * probability of defection. So if there are 50 moves, then this algorithm
 * maintains an array of 50 moves. Then, it populates the array with PD% `Defect's 
 * and the rest will be `Cooperate'. Then it randomly permutes the array.
 * Now, we have an overall probability of defection = PD%. But the immediate
 * next move is random.
 *
 * If PD is defined as 50, then the opponent is most unpredictable -- since
 * there is equal probability of either move.
 * If PD>50 then the opponent is more uncooperative, but can randomly cooperate
 * sometime.
 * If PD<50 then the opponent is more often cooperative, but can randomly defect
 * and get an immediate benefit.
 *
 * By changing the value of PD, we can test our algorithm against these
 * categories of opponents. 
 *
 * The aim of doing this is -- to assess how the algorithm performs against
 * different opponents -- whose policy we do not know at all. This is our
 * strategy to generate different kinds of opponents.
*/

#include<stdio.h>
#include<stdlib.h>
#include"rpd.h"

extern board *M;
extern int N,scoreX,scoreY,RSEED;

#define PD 50		// Define the probability of defection. 
#define PC (100-PD)	// probability that the opponent will cooperate

int opponent_algorithm(int xi)		// Random order, predefined probability
{
 int i,j,t,y;
 static int *MO;
 static int  n=0;
  
 if(xi==INIT)	// First call
	{
	 MO = (int*)malloc(sizeof(int)*N);
	 // Populate the array of future moves with PD% of DF's and fill the rest with CO's
	 for(i=0;i<(N*PD/100);i++)
	 	{
		 MO[i] = DF;
		}
	 for(;i<N;i++)
	 	{
		 MO[i] = CO;
		}
	 // Now that we have the right distribution, time to (pseudo) randomly permute them
	 if(PD !=100 || PD !=0)		// No point in permuting if all DF or CO
	 {
	 srand48(RSEED);
	 for(i=0;i<N;i++)
	 	{
		 j = (int)lrand48() % N;	// Generate random position number
		 t = MO[i];		// Swap number at current position with number at random position
		 MO[i] = MO[j];
		 MO[j] = t;
		}
	 }
//	for(i=0;i<N;i++) fprintf(stderr,"%d\n",MO[i]);	// Check permutation.Scaffold code
	}
 else
	{
	 // For all other iterations, use the values from the table.
	 n++;
	}	
 return MO[n];		// return MO[i]
}
