/*
 * Assignment:	Repeated Prisoners Dilemma Problem
 * Group: 	RN.12 and RN.24 (Nishchay and Shrikant)
 * File:	Solution Algorithm-1.
 * 
 * Description:
 * This algorithm keeps track of the history of the opponent's moves and of its tendency
   to either reciprocate or disregard cooperation.
   We keep track of the following --
   	1. Total number of moves so far (N)
	2. Number of times opponent has defected so far (nD)
	3. Number of times opponent has cooperated so far (nC)
	4. Number of times opponent has defected, in spite of us cooperating (nCD)
	5. Number of times opponent has reciprocated cooperation (nCC)

   Based on the above frequencies we keeps track of the following probabilities --
   	1. Probability of Defection (pD = nD/N)
	2. Probability of Cooperation (pC = nC/N)
	3. Probability of Cooperation when we we have cooperated in the previous move (pCC = nCC/N)
	4. Probability of Defection when we have cooperated  in the previous move (pCD = nCD/N)
  
   The core of the algorithm is as follows --

   if pC > pD
   	then Cooperate
   if pD > pC
   	then Defect
   
   if pD == pC
   	then if pCC > pCD
		then Cooperate
	     else
	     	Defect

   We tested this algorithm against the opponent with the following three cases of opponents--
   PD = 50 (Unpredictable opponent)
   PD = 10 (Generally cooperative, but can defect all of a sudden)
   PD = 70 (Mostly uncooperative)

   Results --
   Multiple trials, with different values of RSEED (see rpd_main.c) show that when the opponent tends to defect, 
   this algorithm detects its strategy properly and tends to win. Even when the opponent is unpredictable this 
   algorithm wins more often than it loses.

   However, when the opponent tends to cooperate most of the time and defects just a few 
   this algorithm loses by a narrow margin -- usually every time the opponent tries to 
   defect, it loses that trial.

   Thus, it's unable to detect the `wolf in sheeps clothing' 
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
	 //fprintf(stderr,"\n%d	%d	%d	%d	%d	%d	%d	%d	%d",n,nC,nD,pC,pD,nCC,nCD,pCC,pCD);
	 if(pC > pD)		// If opponent has higher probability of cooperation, cooperate
		return CO;
	 if(pD > pC)		// else defect
		return DF;
	 else			// If things are equally probable, check
		{
		 if(pCD >= pCC)		// if the opponent tends to reciprocate Cooperation
			return DF;	// defect if it doesn't
		 else
			return CO;	// else cooperate
		}
	}
}


