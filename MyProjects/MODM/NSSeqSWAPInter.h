#ifndef MODM_NSSEQSWAPInter_H_
#define MODM_NSSEQSWAPInter_H_

// Framework includes
#include "../../OptFrame/NSSeq.hpp"
#include "../../OptFrame/RandGen.hpp"

// Own includes
#include "ProblemInstance.h"
#include "DeltaStructure.h"
#include "Solution.h"

using namespace std;

namespace MODM
{

class MoveSWAPInter: public Move< RepMODM , MY_ADS  >
{
private:
    // MOVE PARAMETERS

public:
    using Move< RepMODM , MY_ADS  >::apply; // prevents name hiding
    using Move< RepMODM , MY_ADS  >::canBeApplied; // prevents name hiding

    MoveSWAPInter() // ADD PARAMETERS
    {
    }

    virtual ~MoveSWAPInter()
    {
    }
    
    void print() const
    {
        cout << id() << " with params: '" << "ADD MY PARAMETERS" << "'" << endl;
    }
    
    string id() const
    {
        return Move<RepMODM , MY_ADS >::idComponent().append(":MoveSWAPInter");
    }
    
    bool operator==(const Move< RepMODM , MY_ADS  >& _m) const
    {
        const MoveSWAPInter& m = (const MoveSWAPInter&) _m;
        // COMPARE PARAMETERS AND RETURN TRUE IF EQUALS
        return false;
    }
    
    // Implement these methods in the .cpp file
    
    bool canBeApplied(const RepMODM& rep, const MY_ADS&);

    Move< RepMODM , MY_ADS  >& apply(RepMODM& rep, MY_ADS&);
    
    MoveCost* cost(const Evaluation<  >&, const RepMODM& rep, const MY_ADS& ads);
};



class NSIteratorSWAPInter: public NSIterator< RepMODM , MY_ADS  >
{
private:
    // ITERATOR PARAMETERS

public:
    NSIteratorSWAPInter() // ADD ITERATOR PARAMETERS
    {
    }

    virtual ~NSIteratorSWAPInter()
    {
    }
    
    // Implement these methods in the .cpp file

    void first();
    void next();
    bool isDone();
    Move< RepMODM , MY_ADS  >& current();
};



class NSSeqSWAPInter: public NSSeq< RepMODM , MY_ADS  >
{
private:
    // YOU MAY REMOVE THESE PARAMETERS IF YOU DON'T NEED (BUT PROBABLY WILL...)
    ProblemInstance& pMODM; // problem instance data
    RandGen& rg;                // random number generator

public:

    using NSSeq< RepMODM , MY_ADS  >::move; // prevents name hiding

    // YOU MAY REMOVE THESE PARAMETERS IF YOU DON'T NEED (BUT PROBABLY WILL...)
    NSSeqSWAPInter(ProblemInstance& _pMODM, RandGen& _rg):
        pMODM(_pMODM), rg(_rg)
    {
    }

    virtual ~NSSeqSWAPInter()
    {
    }
    
    void print() const
    {
        cout << "NSSeqSWAPInter" << endl;
    }
    
    string id() const
    {
        return NSSeq<RepMODM , MY_ADS >::idComponent().append(":NSSeqSWAPInter");
    }
    
    NSIterator<RepMODM , MY_ADS >& getIterator(const RepMODM& rep, const MY_ADS&)
    {
        // return an iterator to the neighbors of 'rep' 
        return * new NSIteratorSWAPInter;  // ADD POSSIBLE ITERATOR PARAMETERS
    }
        
    // Implement this method in the .cpp file

    Move<RepMODM , MY_ADS >& move(const RepMODM& rep, const MY_ADS&);
};

}

#endif /*MODM_NSSEQSWAPInter_H_*/
