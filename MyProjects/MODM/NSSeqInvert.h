#ifndef MODM_NSSEQInvert_H_
#define MODM_NSSEQInvert_H_

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

class MoveInvert: public Move<RepMODM, AdsMODM>
{
private:

	ProblemInstance* dmproblem;
	int y; //produto
	int c;

public:

	using Move<RepMODM, AdsMODM>::apply; // prevents name hiding
	using Move<RepMODM, AdsMODM>::canBeApplied; // prevents name hiding

	MoveInvert(int _y, int _c, ProblemInstance* _dmproblem) :
			y(_y), c(_c), dmproblem(_dmproblem)
	{

	}

	virtual ~MoveInvert()
	{
	}

	bool canBeApplied(const RepMODM& rep, const AdsMODM& ads)
	{
		return true;

	}

	MoveCost* cost(const Evaluation<>&, const RepMODM& rep, const AdsMODM& ads)
	{
		double f = 0;

		double costDiff = (!rep[c][y] * dmproblem->getCost(c, y)) - (rep[c][y] * dmproblem->getCost(c, y));
		double revDiff = (!rep[c][y] * dmproblem->getRevenue(c, y)) - (rep[c][y] * dmproblem->getRevenue(c, y));

		f = revDiff - costDiff;

		return new MoveCost(f, 0);
	}

	Move<RepMODM, AdsMODM>& apply(RepMODM& rep, AdsMODM& ads)
	{
		int oldC = rep[c][y];
		rep[c][y] = !rep[c][y];

		//update ADS
		ads.totalCost[y] += (rep[c][y] * dmproblem->getCost(c, y)) - (oldC * dmproblem->getCost(c, y));
		ads.totalRevenue[y] += (rep[c][y] * dmproblem->getRevenue(c, y)) - (oldC * dmproblem->getRevenue(c, y));

		ads.clientOffers[c] += oldC - rep[c][y];

		return *new MoveInvert(y, c, dmproblem);
	}

	virtual bool operator==(const Move<RepMODM, AdsMODM>& _m) const
	{
		const MoveInvert& m = (const MoveInvert&) _m;
		return (m.y == y) && (m.c == c);
	}

	void print() const
	{
		cout << "MoveInvert( ";
		cout << y << ", " << c << " )";
		cout << endl;
	}
};

class NSIteratorInvert: public NSIterator<RepMODM, AdsMODM>
{
private:
	ProblemInstance* dmproblem;
	int y, c;
	int nClients, nProducts;
	const AdsMODM& ads;

public:
	NSIteratorInvert(const AdsMODM& _ads, ProblemInstance* _dmproblem) :
			ads(_ads), dmproblem(_dmproblem)
	{
		nClients = dmproblem->getNumberOfClients();
		nProducts = dmproblem->getNumberOfProducts();

	}

	virtual ~NSIteratorInvert()
	{
	}

	void first()
	{
		y = 0;
		c = 0;
	}

	void next()
	{
		c++;
		if (c >= (nClients))
		{
			y++;
			c=0;
		}
	}

	bool isDone()
	{
		return (y == nProducts);
	}

	Move<RepMODM, AdsMODM>& current()
	{
		if (isDone())
		{
			cout << "There isnt any current element!" << endl;
			cout << "NSSeqInvert. Aborting." << endl;
			exit(1);
		}

		return *new MoveInvert(y, c, dmproblem);
	}

};

class NSSeqInvert: public NSSeq<RepMODM, AdsMODM>
{
private:
	ProblemInstance* dmproblem;
	RandGen& rg;
public:

	using NSSeq<RepMODM, AdsMODM>::move; // prevents name hiding

	NSSeqInvert(RandGen& _rg, ProblemInstance* _dmproblem) :
			rg(_rg), dmproblem(_dmproblem)
	{
	}

	virtual ~NSSeqInvert()
	{
	}

	virtual Move<RepMODM, AdsMODM>& move(const RepMODM& rep, const AdsMODM& ads)
	{
		int nProduts = dmproblem->getNumberOfProducts();

		int y = rg.rand(nProduts);

		while (ads.productOffers[y] == 0)
		{
			y = rg.rand(nProduts);
		}

		int nClients = dmproblem->getNumberOfClients();
		int c = rg.rand(nClients);

		return *new MoveInvert(y, c, dmproblem); // return a random move
	}

	virtual NSIterator<RepMODM, AdsMODM>& getIterator(const RepMODM& rep, const AdsMODM& ads)
	{
		return *new NSIteratorInvert(ads, dmproblem); // return an iterator to the neighbors of 'rep'
	}

	virtual void print() const
	{
	}
};

}

#endif /*MODM_NSSEQInvert_H_*/
