#!/bin/bash

PS=" 
S3-5/S3-5-5-1-s
 S3-5/S3-5-5-1-l
 S3-5/S3-5-5-2-s
 S3-5/S3-5-5-2-l
 S3-5/S3-5-5-3-s
 S3-5/S3-5-5-3-l
 S3-10/S3-5-10-1-s
 S3-10/S3-5-10-1-l
 S3-10/S3-5-10-2-s
 S3-10/S3-5-10-2-l
 S3-10/S3-5-10-3-s
 S3-10/S3-5-10-3-l
 S3-15/S3-5-15-1-s
 S3-15/S3-5-15-1-l
 S3-15/S3-5-15-2-s
 S3-15/S3-5-15-2-l
 S3-15/S3-5-15-3-s
 S3-15/S3-5-15-3-l
 S3-5/S3-10-5-1-s
 S3-5/S3-10-5-1-l
 S3-5/S3-10-5-2-s
 S3-5/S3-10-5-2-l
 S3-5/S3-10-5-3-s
 S3-5/S3-10-5-3-l
 S3-10/S3-10-10-1-s
 S3-10/S3-10-10-1-l
 S3-10/S3-10-10-2-s
 S3-10/S3-10-10-2-l
 S3-10/S3-10-10-3-s
 S3-10/S3-10-10-3-l
 S3-15/S3-10-15-1-s
 S3-15/S3-10-15-1-l
 S3-15/S3-10-15-2-s
 S3-15/S3-10-15-2-l
 S3-15/S3-10-15-3-s
 S3-15/S3-10-15-3-l
 S3-5/S3-15-5-1-s
 S3-5/S3-15-5-1-l
 S3-5/S3-15-5-2-s
 S3-5/S3-15-5-2-l
 S3-5/S3-15-5-3-s
 S3-5/S3-15-5-3-l
 S3-10/S3-15-10-1-s
 S3-10/S3-15-10-1-l
 S3-10/S3-15-10-2-s
 S3-10/S3-15-10-2-l
 S3-10/S3-15-10-3-s
 S3-10/S3-15-10-3-l
 S3-15/S3-15-15-1-s
 S3-15/S3-15-15-1-l
 S3-15/S3-15-15-2-s
 S3-15/S3-15-15-2-l
 S3-15/S3-15-15-3-s
 S3-15/S3-15-15-3-l
 M1-5/M1-5-5-1-s
 M1-5/M1-5-5-1-l
 M1-5/M1-5-5-2-s
 M1-5/M1-5-5-2-l
 M1-5/M1-5-5-3-s
 M1-5/M1-5-5-3-l
 M1-10/M1-5-10-1-s
 M1-10/M1-5-10-1-l
 M1-10/M1-5-10-2-s
 M1-10/M1-5-10-2-l
 M1-10/M1-5-10-3-s
 M1-10/M1-5-10-3-l
 M1-15/M1-5-15-1-s
 M1-15/M1-5-15-1-l
 M1-15/M1-5-15-2-s
 M1-15/M1-5-15-2-l
 M1-15/M1-5-15-3-s
 M1-15/M1-5-15-3-l
 M1-5/M1-10-5-1-s
 M1-5/M1-10-5-1-l
 M1-5/M1-10-5-2-s
 M1-5/M1-10-5-2-l
 M1-5/M1-10-5-3-s
 M1-5/M1-10-5-3-l
 M1-10/M1-10-10-1-s
 M1-10/M1-10-10-1-l
 M1-10/M1-10-10-2-s
 M1-10/M1-10-10-2-l
 M1-10/M1-10-10-3-s
 M1-10/M1-10-10-3-l
 M1-15/M1-10-15-1-s
 M1-15/M1-10-15-1-l
 M1-15/M1-10-15-2-s
 M1-15/M1-10-15-2-l
 M1-15/M1-10-15-3-s
 M1-15/M1-10-15-3-l
 M1-5/M1-15-5-1-s
 M1-5/M1-15-5-1-l
 M1-5/M1-15-5-2-s
 M1-5/M1-15-5-2-l
 M1-5/M1-15-5-3-s
 M1-5/M1-15-5-3-l
 M1-10/M1-15-10-1-s
 M1-10/M1-15-10-1-l
 M1-10/M1-15-10-2-s
 M1-10/M1-15-10-2-l
 M1-10/M1-15-10-3-s
 M1-10/M1-15-10-3-l
 M1-15/M1-15-15-1-s
 M1-15/M1-15-15-1-l
 M1-15/M1-15-15-2-s
 M1-15/M1-15-15-2-l
 M1-15/M1-15-15-3-s
 M1-15/M1-15-15-3-l
 M2-5/M2-5-5-1-s
 M2-5/M2-5-5-1-l
 M2-5/M2-5-5-2-s
 M2-5/M2-5-5-2-l
 M2-5/M2-5-5-3-s
 M2-5/M2-5-5-3-l
 M2-10/M2-5-10-1-s
 M2-10/M2-5-10-1-l
 M2-10/M2-5-10-2-s
 M2-10/M2-5-10-2-l
 M2-10/M2-5-10-3-s
 M2-10/M2-5-10-3-l
 M2-15/M2-5-15-1-s
 M2-15/M2-5-15-1-l
 M2-15/M2-5-15-2-s
 M2-15/M2-5-15-2-l
 M2-15/M2-5-15-3-s
 M2-15/M2-5-15-3-l
 M2-5/M2-10-5-1-s
 M2-5/M2-10-5-1-l
 M2-5/M2-10-5-2-s
 M2-5/M2-10-5-2-l
 M2-5/M2-10-5-3-s
 M2-5/M2-10-5-3-l
 M2-10/M2-10-10-1-s
 M2-10/M2-10-10-1-l
 M2-10/M2-10-10-2-s
 M2-10/M2-10-10-2-l
 M2-10/M2-10-10-3-s
 M2-10/M2-10-10-3-l
 M2-15/M2-10-15-1-s
 M2-15/M2-10-15-1-l
 M2-15/M2-10-15-2-s
 M2-15/M2-10-15-2-l
 M2-15/M2-10-15-3-s
 M2-15/M2-10-15-3-l
 M2-5/M2-15-5-1-s
 M2-5/M2-15-5-1-l
 M2-5/M2-15-5-2-s
 M2-5/M2-15-5-2-l
 M2-5/M2-15-5-3-s
 M2-5/M2-15-5-3-l
 M2-10/M2-15-10-1-s
 M2-10/M2-15-10-1-l
 M2-10/M2-15-10-2-s
 M2-10/M2-15-10-2-l
 M2-10/M2-15-10-3-s
 M2-10/M2-15-10-3-l
 M2-15/M2-15-15-1-s
 M2-15/M2-15-15-1-l
 M2-15/M2-15-15-2-s
 M2-15/M2-15-15-2-l
 M2-15/M2-15-15-3-s
 M2-15/M2-15-15-3-l
 L-5/L-5-5-1-s
 L-5/L-5-5-1-l
 L-5/L-5-5-2-s
 L-5/L-5-5-2-l
 L-5/L-5-5-3-s
 L-5/L-5-5-3-l
 L-10/L-5-10-1-s
 L-10/L-5-10-1-l
 L-10/L-5-10-2-s
 L-10/L-5-10-2-l
 L-10/L-5-10-3-s
 L-10/L-5-10-3-l
 L-15/L-5-15-1-s
 L-15/L-5-15-1-l
 L-15/L-5-15-2-s
 L-15/L-5-15-2-l
 L-15/L-5-15-3-s
 L-15/L-5-15-3-l
 L-5/L-10-5-1-s
 L-5/L-10-5-1-l
 L-5/L-10-5-2-s
 L-5/L-10-5-2-l
 L-5/L-10-5-3-s
 L-5/L-10-5-3-l
 L-10/L-10-10-1-s
 L-10/L-10-10-1-l
 L-10/L-10-10-2-s
 L-10/L-10-10-2-l
 L-10/L-10-10-3-s
 L-10/L-10-10-3-l
 L-15/L-10-15-1-s
 L-15/L-10-15-1-l
 L-15/L-10-15-2-s
 L-15/L-10-15-2-l
 L-15/L-10-15-3-s
 L-15/L-10-15-3-l
 L-5/L-15-5-1-s
 L-5/L-15-5-1-l
 L-5/L-15-5-2-s
 L-5/L-15-5-2-l
 L-5/L-15-5-3-s
 L-5/L-15-5-3-l
 L-10/L-15-10-1-s
 L-10/L-15-10-1-l
 L-10/L-15-10-2-s
 L-10/L-15-10-2-l
 L-10/L-15-10-3-s
 L-10/L-15-10-3-l
 L-15/L-15-15-1-s
 L-15/L-15-15-1-l
 L-15/L-15-15-2-s
 L-15/L-15-15-2-l
 L-15/L-15-15-3-s
 L-15/L-15-15-3-l
"

ALPHAGRASP="0.8"
ALPHANS="0.05 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1"
POP="1 5 10"

for i in `seq 5`
do
  for probl in $PS 
  do 
	  for ans in $ALPHANS
	  do
 		  	for pop in $POP
		 	do
		  		echo "Resolvendo o problema $probl batch $i alpha grasp $ag alpha neigh ARProduct ans"
		  		./app_MODMNormalC ./MODM/Instances/$probl.txt ./MODM/Solutions/$probl-$i-$ag-$ans ./MODM/Results/saidaGeralCheckNewNS 600 0.8 $ans $pop $i $probl

		  	done
	  done
  done
done


