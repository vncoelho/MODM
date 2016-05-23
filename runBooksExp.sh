#!/bin/bash

BOOKS="10 20 50 100 200"


for b in $BOOKS
do
	for pp in `seq 15`
	do 

		./MyProjects/app_MODM ./a ./resultsVNS2016Books ./testeES 30 10 10 5 10 $pp $b 1
		./MyProjects/app_MODM ./a ./resultsVNS2016Books ./testeES 30 10 10 5 10 $pp $b 2
		./MyProjects/app_MODM ./a ./resultsVNS2016Books ./testeES 30 10 10 5 10 $pp $b 3

		./MyProjects/app_MODM ./a ./resultsVNS2016Books ./testeES 60 10 10 5 10 $pp $b 1
		./MyProjects/app_MODM ./a ./resultsVNS2016Books ./testeES 60 10 10 5 10 $pp $b 2
		./MyProjects/app_MODM ./a ./resultsVNS2016Books ./testeES 60 10 10 5 10 $pp $b 3

		./MyProjects/app_MODM ./a ./resultsVNS2016Books ./testeES 120 10 10 5 10 $pp $b 1
		./MyProjects/app_MODM ./a ./resultsVNS2016Books ./testeES 120 10 10 5 10 $pp $b 2
		./MyProjects/app_MODM ./a ./resultsVNS2016Books ./testeES 120 10 10 5 10 $pp $b 3
	done
done

