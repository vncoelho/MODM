#include "NSSeqADD.h"

using namespace MODM;

// ============ MoveADD ==============

bool MoveADD::canBeApplied(const RepMODM& rep, const MY_ADS&)
{
    return true;
}

Move< RepMODM , MY_ADS  >& MoveADD::apply(RepMODM& rep, MY_ADS&)
{
    // apply this move to 'rep'
    // rep. (...) = (...)
    // return reverse move
    return * new MoveADD; 
}

MoveCost* MoveADD::cost(const Evaluation<  >&, const RepMODM& rep, const MY_ADS& ads)
{
   return NULL;
   // Implement if a more efficient evaluation of the move is available
   //double move_cost = ...;
   //double move_cost_infeasible = ...;
   //return new MoveCost(move_cost, move_cost_infeasible);
}



// ============ NSIteratorADD ==============

void NSIteratorADD::first(){};

void NSIteratorADD::next(){};
	
bool NSIteratorADD::isDone(){};
	
Move< RepMODM , MY_ADS  >& NSIteratorADD::current(){};




// ============ NSSeqADD ==============


Move<RepMODM , MY_ADS >& NSSeqADD::move(const RepMODM& rep, const MY_ADS&)
{
   // return a random move (that is, a move operator that generates a neighbor solution of 'rep')
   // you may need to use the random number generator 'rg'
   
   return * new MoveADD; 
}
