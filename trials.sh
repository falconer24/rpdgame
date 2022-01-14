#!/bin/bash

# This file runs the algorithm 500 times with, 50 rounds per game with different
# random seed for each game.

echo>/tmp/res;

i=1;
while [ $i -le 500 ]
do  
	j=`expr $i + 10`
	./algo$1 50 $j 2>/tmp/p | tail -1 >> /tmp/res;
	i=`expr $i + 1`;
done;

echo X `grep X /tmp/res | wc -l`;
echo Y `grep Y /tmp/res | wc -l` ;
echo Draw `grep Draw /tmp/res | wc -l`
