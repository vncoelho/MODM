#include "NSSeqSWAPInter.h"

using namespace MODM;

// ============ MoveSWAPInter ==============

bool MoveSWAPInter::canBeApplied(const RepMODM& rep, const MY_ADS&)
{
    return true;
}

Move< RepMODM , MY_ADS  >& MoveSWAPInter::apply(RepMODM& rep, MY_ADS&)
{
    // apply this move to 'rep'
    // rep. (...) = (...)
    // return reverse move
    return * new MoveSWAPInter; 
}

MoveCost* MoveSWAPInter::cost(const Evaluation<  >&, const RepMODM& rep, const MY_ADS& ads)
{
   return NULL;
   // Implement if a more efficient evaluation of the move is available
   //double move_cost = ...;
   //double move_cost_infeasible = ...;
   //return new MoveCost(move_cost, move_cost_infeasible);
}



// ============ NSIteratorSWAPInter ==============

void NSIteratorSWAPInter::first(){};

void NSIteratorSWAPInter::next(){};
	
bool NSIteratorSWAPInter::isDone(){};
	
Move< RepMODM , MY_ADS  >& NSIteratorSWAPInter::current(){};




// ============ NSSeqSWAPInter ==============


Move<RepMODM , MY_ADS >& NSSeqSWAPInter::move(const RepMODM& rep, const MY_ADS&)
{
   // return a random move (that is, a move operator that generates a neighbor solution of 'rep')
   // you may need to use the random number generator 'rg'
   
   return * new MoveSWAPInter; 
}
