// OptFrame - Optimization Framework

// Copyright (C) 2009, 2010, 2011
// http://optframe.sourceforge.net/
//
// This file is part of the OptFrame optimization framework. This framework
// is free software; you can redistribute it and/or modify it under the
// terms of the GNU Lesser General Public License v3 as published by the
// Free Software Foundation.

// This framework is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License v3 for more details.

// You should have received a copy of the GNU Lesser General Public License v3
// along with this library; see the file COPYING.  If not, write to the Free
// Software Foundation, 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
// USA.

// ===================================
// Main.cpp file generated by OptFrame
// Project Traveling Salesman Problem
// ===================================

#include <stdlib.h>
#include <math.h>

#include <iostream>

using namespace std;

#include <set>

#include "../OptFrame/Loader.hpp"
#include "../OptFrame/Util/CheckCommand.hpp"
#include "../OptFrame/Util/BuildCommand.hpp"
#include "TSP.h"

using namespace TSP;
using namespace scannerpp;

int main(int argc, char **argv)
{
	Loader<RepTSP, OPTFRAME_DEFAULT_ADS, MemTSP> optframe;
	TSPProblemCommand tsp;
	tsp.load("./TSP/tsplib/berlin52.txt", optframe.factory, optframe.dictionary, optframe.ldictionary);

	CheckCommand<RepTSP, OPTFRAME_DEFAULT_ADS, MemTSP> check(false);

	RandGen rg;
	RandomInitialSolutionTSP random(tsp.p, rg);
	NearestNeighborConstructive cnn(tsp.p, rg);
	ConstructiveBestInsertion cbi(tsp.p, rg);
	TSPEvaluator eval(tsp.p);
	NSEnumSwap enumswap(tsp.p, rg);

	NSSeqTSP2Opt<int, OPTFRAME_DEFAULT_ADS, MemTSP, DeltaMoveTSP2Opt, ProblemInstance> nsseq_delta_2opt(tsp.p);
	NSSeqTSP2Opt<int, OPTFRAME_DEFAULT_ADS, MemTSP> tsp2opt;
	NSSeqTSPOrOptk<int, OPTFRAME_DEFAULT_ADS, MemTSP, DeltaMoveTSPOrOptk, ProblemInstance> nsseq_delta_or1(1, tsp.p);
	NSSeqTSPOrOptk<int, OPTFRAME_DEFAULT_ADS, MemTSP> tspor1(1);
	NSSeqTSPOrOptk<int, OPTFRAME_DEFAULT_ADS, MemTSP> tspor2(2);
	NSSeqTSPOrOptk<int, OPTFRAME_DEFAULT_ADS, MemTSP> tspor3(3);
	NSSeqTSPSwap<int, OPTFRAME_DEFAULT_ADS, MemTSP> tspswap;

	check.add(random);
	check.add(cnn);
	check.add(cbi);
	check.add(eval);
	check.add(enumswap);
	check.add(nsseq_delta_2opt);
	check.add(tsp2opt);
	check.add(nsseq_delta_or1);
	check.add(tspor1);
	check.add(tspor2);
	check.add(tspor3);
	check.add(tspswap);

	check.run(100, 10);

	BuildCommand<RepTSP, OPTFRAME_DEFAULT_ADS, MemTSP> build;
	for(unsigned i = 0; i <= 7; i++)
	{
		stringstream ss;
		ss << "OptFrame:ComponentBuilder:LocalSearch:BI  OptFrame:Evaluator 0  OptFrame:NS:NSSeq " << i;
		string name = build.run(optframe.factory, optframe.dictionary, optframe.ldictionary, ss.str());
		cout << "BUILT: '" << name << "'" << endl;
	}

	/*
	echo building VND
	define vnd_list [ OptFrame:LocalSearch: 0 ,  OptFrame:LocalSearch: 1, OptFrame:LocalSearch: 2, OptFrame:LocalSearch: 3 ]
	component.create_list $vnd_list OptFrame:LocalSearch: comp_vnd_list
	build OptFrame:LocalSearch:VND   $Evaluator 0   $comp_vnd_list   vnd

	%component.list

	echo building ILS
	build OptFrame:ComponentBuilder:SingleObjSearch:ILS:ILSLevels   $Evaluator 0    $Constructive 0    $vnd   OptFrame:ILS:LevelPert:LPlus2 0    100    8  meu_ils

	test 2 3 7000 7000   $Evaluator 0   $meu_ils   output.txt   solucao_saida

	evaluate $Evaluator 0 $solucao_saida
	*/

	cout << "Program ended successfully" << endl;


	return 0;
}
