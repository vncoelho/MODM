#include "Evaluator.h"

using namespace MODM;

MODMEvaluator::MODMEvaluator(ProblemInstance& _pMODM): // If necessary, add more parameters
pMODM(_pMODM)
{
	// Put the rest of your code here
}
	
MODMEvaluator::~MODMEvaluator()
{
}

EvaluationMODM& MODMEvaluator::evaluate(const RepMODM& rep)
{
    // 'rep' is the representation of the solution

    double fo = 0; // Evaluation Function Value

    return * new EvaluationMODM(fo  , * new int);
}

bool MODMEvaluator::betterThan(double f1, double f2)
{
    // MAXIMIZATION
    return (f1 > (f2 + EPSILON_MODM));
}

bool MODMEvaluator::isMinimization() const
{
	// MAXIMIZATION
	return false;
}
