/*
 * Assignment:	Repeated Prisoners Dilemma Problem
 * Group: 	RN.12 and RN.24 (Nishchay and Shrikant)
 * File:	Solution Algorithm-2.
 * 
 * Description:
 * This algorithm keeps track of the history of the opponent's moves and of its tendency
   to either reciprocate or disregard cooperation.
    
   The probabilities of the opponent's moves are maintained exactly as in algorithm 1.
  
   The core of this algorithm is as follows --

   if current move of opponent is Defect
   	then Defect
   else
   	if pCD > pCC
   		then Defect
	else if pCC > pCD
		 	Cooperate
	   

   We tested this algorithm against the opponent with the following three cases of opponents--
   PD = 50 (Unpredictable opponent)
   PD = 10 (Generally cooperative, but can defect all of a sudden)
   PD = 70 (Mostly uncooperative)

   Results --
   Multiple trials, with different values of RSEED (see rpd_main.c) show that this algorithm 
   performs in the following way against different opponents --
   
   1. Against `wolf-in-sheep-clothing': Most wins, few lossess, maximum draws
   2. Against `mostly uncooperative':  Wins almost all the time.
   3. Against `unpredictable': Wins most of the time.


*/
#include<stdlib.h>
#include<stdio.h>
#include"rpd.h"

extern board *M;
extern int scoreX,scoreY;

int my_algorithm(int yi)
{
 static int n=0,nD=0,nC=0,pD,pC,nCD=0,nCC=0,pCC=0,pCD=0;
 int xi, xim1,yim1;

 if(yi==INIT)	// First call, prepare policy and probabilities.
	{
	 //fprintf(stderr,"\nn	nC	nD	pC	pD	nCC	nCD	pCC	pCD");
	 return CO;	// Optimistic policy. DF if pessimistic
	}
 else
	{
	 n++;
 	 if(yi==CO)	nC++;
 	 if(yi==DF)	nD++;
	 xim1 = M[n-1].x;
	 if(xim1==CO && yi==CO)	nCC++;	
	 if(xim1==CO && yi==DF)	nCD++;
	
	 pC = nC*100/n;
	 pD = nD*100/n;
	 pCC = nCC*100/n;
	 pCD = nCD*100/n;
//	 fprintf(stderr,"\n%d	%d	%d	%d	%d	%d	%d	%d	%d",n,nC,nD,pC,pD,nCC,nCD,pCC,pCD); // Scaffold code.
	
	 if (yi==DF)
		return DF;
	 else			// this means yi==CO, check
		{
		 if(pCD >= pCC)		// check if the opponent tends to reciprocate Cooperation
			return DF;	// defect if it doesn't
		 else
			return CO;	// else cooperate
		}
	}
}


