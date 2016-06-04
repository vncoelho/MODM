// ===================================
// Main.cpp file generated by OptFrame
// Project MODM
// ===================================

#include <stdlib.h>
#include <math.h>
#include <iostream>

#include "../OptFrame/Loader.hpp"
#include "MODM/Evaluator.cpp"
#include "../OptFrame/Heuristics/VNS/MOVNSLevels.hpp"
#include "../OptFrame/Heuristics/2PPLS.hpp"
#include "../OptFrame/MultiEvaluator.hpp"
#include "../OptFrame/MultiObjSearch.hpp"
#include "../OptFrame/Heuristics/EvolutionaryAlgorithms/ES.hpp"
#include <string>
#include "MODM.h"

using namespace std;
using namespace optframe;
using namespace MODM;

int MOTOPDMC(int argc, char **argv)
{
	cout << "Welcome to the Bi-Objective TOPDMC!" << endl;
	// EXEC EXAMPLE:
	// .instance ./saidaMOTOPDMC ./saidaGeralMOTOPDMC 120 10 10 5 1

	int nOfArguments = 8;
	if (argc != (1 + nOfArguments))
	{
		cout << "Parametros incorretos!" << endl;
		cout << "Os parametros esperados sao: \n"
				"1 - instancia \n"
				"2 - saida - for saving solutions for each execution - type write\n"
				"3 - saida geral -- general file for savings all results - type append \n"
				"4 - timeMO\n"
				"5 - alphaBuilderInt\n"
				"6 - alphaNSInt \n"
				"7 - popSizeMOVNS \n"
				"8 - batch \n \n";
		exit(1);
	}

	RandGenMersenneTwister rg;
	long seed = time(NULL);

	seed = 30;

	srand(seed);
	rg.setSeed(seed);

	const char* instancia = argv[1];
	const char* saida = argv[2];
	const char* saidaGeral = argv[3];
	int argvTimeILS = atoi(argv[4]);
	double alphaBuilder = atof(argv[5]);
	double alphaNeighARProduct = atof(argv[6]);
	int initial_population_size = atoi(argv[7]);
	int argvNBatch = atoi(argv[11]);

	string filename = instancia;
	string output = saida;
	string outputGeral = saidaGeral;

	filename = filename + ".txt";
	filename = "./MyProjects/MODM/Instances/S3-15/S3-10-15-1-s.txt";
	//filename = "./MyProjects/MODM/Instances/L-15/L-10-15-1-l.txt";
	initial_population_size = 1000;

	cout << "filename = " << filename << endl;
	cout << "output = " << output << endl;
	cout << "outputGeral = " << outputGeral << endl;
	cout << "argvTimeILS = " << argvTimeILS << endl;
	cout << "alphaBuilder = " << alphaBuilder << endl;
	cout << "alphaNeighARProduct = " << alphaNeighARProduct << endl;
	cout << "initial population size = " << initial_population_size << endl;
	cout << "Seed = " << seed << endl;

	File* file;

	try
	{
		file = new File(filename);
	} catch (FileNotFound& f)
	{
		cout << "File '" << filename << "' not found" << endl;
		return false;
	}

	Scanner scanner(file);

	ProblemInstance p(scanner, rg);

	MODMADSManager adsMan(p);
	MODMEvaluator eval(p, adsMan);
	MODMRobustnessEvaluator evalRobustness(p, adsMan, rg);

	ConstructiveBasicGreedyRandomized grC(p, rg, adsMan);
	//	grC.setMessageLevel(4);

	NSSeqSWAP nsseq_swap(rg, &p);
	NSSeqSWAPInter nsseq_swapInter(rg, &p);
	NSSeqInvert nsseq_invert(rg, &p);
	NSSeqARProduct nsseq_arProduct(rg, &p, alphaNeighARProduct);
	NSSeqADD nsseq_add(rg, &p);

	vector<Evaluator<RepMODM, AdsMODM>*> v_e;
	v_e.push_back(&eval);
	v_e.push_back(&evalRobustness);

	vector<NSSeq<RepMODM, AdsMODM>*> neighboors;
	//neighboors.push_back(&nsseq_swapInter);
//	neighboors.push_back(&nsseq_swap);
	neighboors.push_back(&nsseq_arProduct);
	neighboors.push_back(&nsseq_add);

	GRInitialPopulation<RepMODM, AdsMODM> bip(grC, rg, alphaBuilder);

	MultiEvaluator<RepMODM, AdsMODM> mev(v_e);

	MOVNSLevels<RepMODM, AdsMODM> multiobjectvns(v_e, bip, initial_population_size, neighboors, rg, 10, 10);
	TwoPhaseParetoLocalSearch<RepMODM, AdsMODM> paretoSearch(mev, bip, initial_population_size, neighboors);

	Pareto<RepMODM, AdsMODM>* pf;
	int time2PPLS = 5000;
	for (int exec = 0; exec < 1; exec++)
	{
		//pf = multiobjectvns.search(20, 0);
		pf = paretoSearch.search(time2PPLS, 0, pf);
	}

	vector<vector<Evaluation*> > vEval = pf->getParetoFront();
	vector<Solution<RepMODM, AdsMODM>*> vSolPf = pf->getParetoSet();

	int nObtainedParetoSol = vEval.size();
	vector<vector<double> > paretoDoubleEval;
	vector<vector<double> > paretoDoubleEvalMin;

	cout << "MO optimization finished! Printing Pareto Front!" << endl;
	for (int i = 0; i < nObtainedParetoSol; i++)
	{

		Solution<RepMODM, AdsMODM>* sol = vSolPf[i];
		const RepMODM& rep = sol->getR();

		const AdsMODM& ads = sol->getADS();
		vector<double> solEvaluations;
		double foProfit = vEval[i][0]->getObjFunction();
		double foVolatility = vEval[i][1]->getObjFunction();
		solEvaluations.push_back(foProfit);
		solEvaluations.push_back(foVolatility);
		paretoDoubleEval.push_back(solEvaluations);
		solEvaluations[0] *= -1;
		solEvaluations[1] *= -1;
		paretoDoubleEvalMin.push_back(solEvaluations);

		vector<int> nPerCat = evalRobustness.checkNClientsPerCategory(rep, ads);
		cout << foProfit << "\t" << foVolatility << "\t";

		int nTotalClients = nPerCat[nPerCat.size() - 1];

		for (int cat = 0; cat < 6; cat++)
			cout << nPerCat[cat] << "\t";
		cout << endl;
	}

	MOMETRICS<RepMODM, AdsMODM> US(v_e);
	int nOF = 2;
	cout<<"ReadingPareto..."<<endl;
	vector<vector<double> > PF1 = US.readPF("./MyProjects/paretoCorsTesteS3-1", 291, nOF);
	vector<vector<double> > PF2 = US.readPF("./MyProjects/paretoCorsTesteS3-2", 262, nOF);
	vector<vector<double> > ref = US.unionSets(PF1, PF2);
	vector<vector<double> > refMin = ref;

	cout << PF1.size() << endl;
	cout << PF2.size() << endl;
	cout << ref.size() << endl;
	//	getchar();
	cout << "Reference set" << endl;
	for (int p = 0; p < ref.size(); p++)
	{
//		cout << ref[p][0] << "\t" << ref[p][1] << endl;
		refMin[p][0] *= -1;
		refMin[p][1] *= -1;
	}

	vector<double> utopicSol;
	utopicSol.push_back(-5226);
	utopicSol.push_back(-10);
	vector<double> objReferences;
	objReferences.push_back(10000);
	objReferences.push_back(10);

	int card = US.cardinalite(paretoDoubleEval, ref);
	double sCToRef = US.setCoverage(paretoDoubleEval, ref);
	double sCFromRef = US.setCoverage(ref, paretoDoubleEval);
	double hv = US.hipervolumeWithExecRequested(paretoDoubleEvalMin, objReferences);

	double delta = US.deltaMetric(paretoDoubleEvalMin, utopicSol);

	//Delta Metric and Hipervolume need to verify min
	cout << "Cardinalite = " << card << endl;
	cout << "Set Coverage to ref = " << sCToRef << endl;
	cout << "Set Coverage from ref  = " << sCFromRef << endl;
	cout << "delta  = " << delta << endl;
	cout << "deltaRef  = " << US.deltaMetric(refMin, utopicSol) << endl;
	cout << "hv  = " << hv << endl;
	cout << "ref  = " << US.hipervolumeWithExecRequested(refMin, objReferences) << endl;

	FILE* fGeral = fopen(outputGeral.c_str(), "a");

	size_t pos = filename.find("Instances/");
	string instName = filename.substr(pos);

	fprintf(fGeral, "%s \t %d \t %.7f \t %.7f \t %d \t %d \t %.7f \t %.7f \t %.7f \t %.7f \t %ld \n", instName.c_str(), initial_population_size, alphaBuilder, alphaNeighARProduct, nObtainedParetoSol, card, sCToRef, sCFromRef, hv, delta, seed);

	fclose(fGeral);

	cout << "Bi-Objective TOPDMC ended with success!" << endl;
	return 0;
}
