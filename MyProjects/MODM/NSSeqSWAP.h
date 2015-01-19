#ifndef MODM_NSSEQSWAP_H_
#define MODM_NSSEQSWAP_H_

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

class MoveSWAP: public Move< RepMODM , MY_ADS  >
{
private:
    // MOVE PARAMETERS

public:
    using Move< RepMODM , MY_ADS  >::apply; // prevents name hiding
    using Move< RepMODM , MY_ADS  >::canBeApplied; // prevents name hiding

    MoveSWAP() // ADD PARAMETERS
    {
    }

    virtual ~MoveSWAP()
    {
    }
    
    void print() const
    {
        cout << id() << " with params: '" << "ADD MY PARAMETERS" << "'" << endl;
    }
    
    string id() const
    {
        return Move<RepMODM , MY_ADS >::idComponent().append(":MoveSWAP");
    }
    
    bool operator==(const Move< RepMODM , MY_ADS  >& _m) const
    {
        const MoveSWAP& m = (const MoveSWAP&) _m;
        // COMPARE PARAMETERS AND RETURN TRUE IF EQUALS
        return false;
    }
    
    // Implement these methods in the .cpp file
    
    bool canBeApplied(const RepMODM& rep, const MY_ADS&);

    Move< RepMODM , MY_ADS  >& apply(RepMODM& rep, MY_ADS&);
    
    MoveCost* cost(const Evaluation<  >&, const RepMODM& rep, const MY_ADS& ads);
};



class NSIteratorSWAP: public NSIterator< RepMODM , MY_ADS  >
{
private:
    // ITERATOR PARAMETERS

public:
    NSIteratorSWAP() // ADD ITERATOR PARAMETERS
    {
    }

    virtual ~NSIteratorSWAP()
    {
    }
    
    // Implement these methods in the .cpp file

    void first();
    void next();
    bool isDone();
    Move< RepMODM , MY_ADS  >& current();
};



class NSSeqSWAP: public NSSeq< RepMODM , MY_ADS  >
{
private:
    // YOU MAY REMOVE THESE PARAMETERS IF YOU DON'T NEED (BUT PROBABLY WILL...)
    ProblemInstance& pMODM; // problem instance data
    RandGen& rg;                // random number generator

public:

    using NSSeq< RepMODM , MY_ADS  >::move; // prevents name hiding

    // YOU MAY REMOVE THESE PARAMETERS IF YOU DON'T NEED (BUT PROBABLY WILL...)
    NSSeqSWAP(ProblemInstance& _pMODM, RandGen& _rg):
        pMODM(_pMODM), rg(_rg)
    {
    }

    virtual ~NSSeqSWAP()
    {
    }
    
    void print() const
    {
        cout << "NSSeqSWAP" << endl;
    }
    
    string id() const
    {
        return NSSeq<RepMODM , MY_ADS >::idComponent().append(":NSSeqSWAP");
    }
    
    NSIterator<RepMODM , MY_ADS >& getIterator(const RepMODM& rep, const MY_ADS&)
    {
        // return an iterator to the neighbors of 'rep' 
        return * new NSIteratorSWAP;  // ADD POSSIBLE ITERATOR PARAMETERS
    }
        
    // Implement this method in the .cpp file

    Move<RepMODM , MY_ADS >& move(const RepMODM& rep, const MY_ADS&);
};

}

#endif /*MODM_NSSEQSWAP_H_*/
