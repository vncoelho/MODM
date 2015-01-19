#include "NSSeqSWAP.h"

using namespace MODM;

// ============ MoveSWAP ==============

bool MoveSWAP::canBeApplied(const RepMODM& rep, const MY_ADS&)
{
    return true;
}

Move< RepMODM , MY_ADS  >& MoveSWAP::apply(RepMODM& rep, MY_ADS&)
{
    // apply this move to 'rep'
    // rep. (...) = (...)
    // return reverse move
    return * new MoveSWAP; 
}

MoveCost* MoveSWAP::cost(const Evaluation<  >&, const RepMODM& rep, const MY_ADS& ads)
{
   return NULL;
   // Implement if a more efficient evaluation of the move is available
   //double move_cost = ...;
   //double move_cost_infeasible = ...;
   //return new MoveCost(move_cost, move_cost_infeasible);
}



// ============ NSIteratorSWAP ==============

void NSIteratorSWAP::first(){};

void NSIteratorSWAP::next(){};
	
bool NSIteratorSWAP::isDone(){};
	
Move< RepMODM , MY_ADS  >& NSIteratorSWAP::current(){};




// ============ NSSeqSWAP ==============


Move<RepMODM , MY_ADS >& NSSeqSWAP::move(const RepMODM& rep, const MY_ADS&)
{
   // return a random move (that is, a move operator that generates a neighbor solution of 'rep')
   // you may need to use the random number generator 'rg'
   
   return * new MoveSWAP; 
}
