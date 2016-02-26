#!/bin/bash

PS=" 
S3-15/S3-10-15-1-s
"

ALPHAGRASP="0"
ALPHANS="0 1 2 3 5 7 10"
POP="5000"

for i in `seq 20`
do
  for probl in $PS 
  do 
	  for ag in $ALPHAGRASP
	  do
	 	  for ans in $ALPHANS
	    	  do
 		  	for pop in $POP
		 	do
		  		echo "Resolvendo o problema $probl batch $i alpha grasp $ag alpha neigh ARProduct ans"
		  		./app_MODM ./MODM/Instances/$probl.txt ./MODM/Solutions/$probl-$i-$ag-$ans ./MODM/Results/saidaGeral 600 $ag $ans $pop
		  	done
		  done
	  done
  done
done


