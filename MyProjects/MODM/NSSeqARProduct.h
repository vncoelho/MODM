#ifndef MODM_NSSEQARProduct_H_
#define MODM_NSSEQARProduct_H_

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

class MoveARProduct: public Move<RepMODM, AdsMODM>
{
private:

	ProblemInstance* dmproblem;
	int y; //produto
	vector<int> oldC;
	bool reverse;
	double tCost, tRevenue;

public:

	using Move<RepMODM, AdsMODM>::apply; // prevents name hiding
	using Move<RepMODM, AdsMODM>::canBeApplied; // prevents name hiding

	MoveARProduct(int _y, vector<int> _oldC, double _tCost, double _tRevenue, bool _reverse, ProblemInstance* _dmproblem) :
			y(_y), oldC(_oldC), tCost(_tCost), tRevenue(_tRevenue), reverse(_reverse), dmproblem(_dmproblem)
	{

	}

	virtual ~MoveARProduct()
	{
	}

	bool canBeApplied(const RepMODM& rep, const AdsMODM& ads)
	{
		return true;

	}

	Move<RepMODM, AdsMODM>& apply(RepMODM& rep, AdsMODM& ads)
	{
		int maxC = dmproblem->getNumberOfClients();

		if (reverse == false)
		{
			tCost = ads.totalCost[y];
			tRevenue = ads.totalRevenue[y];
			vector<int> oldC;
			for (int c = 0; c < maxC; c++)
			{
				oldC.push_back(rep[c][y]);
				rep[c][y] = 0;
				ads.clientOffers[c]--;

			}
			//update ADS
			ads.totalCost[y] = 0;
			ads.totalRevenue[y] = 0;

		}
		else
		{
			for (int c = 0; c < maxC; c++)
			{
				rep[c][y] = oldC[c];
				ads.totalCost[y] = tCost;
				ads.totalRevenue[y] = tRevenue;
			}
		}
		return *new MoveARProduct(y, oldC, tCost, tRevenue, true, dmproblem);
	}

	virtual bool operator==(const Move<RepMODM, AdsMODM>& _m) const
	{
		const MoveARProduct& m = (const MoveARProduct&) _m;
		return (m.y == y) && (m.oldC == oldC) && (m.tCost == tCost) && (m.tRevenue == tRevenue) && (m.reverse == reverse);
	}

	void print() const
	{
		cout << "MoveARProduct( ";
		cout << y << " )";
		cout << endl;
	}
};

class NSIteratorARProduct: public NSIterator<RepMODM, AdsMODM>
{
private:
	ProblemInstance* dmproblem;
	int y;
	int nClients, nProducts;
	const AdsMODM& ads;

public:
	NSIteratorARProduct(const AdsMODM& _ads, ProblemInstance* _dmproblem) :
			ads(_ads), dmproblem(_dmproblem)
	{
		nClients = dmproblem->getNumberOfClients();
		nProducts = dmproblem->getNumberOfProducts();

	}

	virtual ~NSIteratorARProduct()
	{
	}

	void first()
	{
		y = 0;
	}

	void next()
	{
		y++;
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
			cout << "NSSeqARProduct. Aborting." << endl;
			exit(1);
		}
		vector<int> vazio;
		return *new MoveARProduct(y, vazio, 0, 0, 0, dmproblem);
	}

};

class NSSeqARProduct: public NSSeq<RepMODM, AdsMODM>
{
private:
	ProblemInstance* dmproblem;
	RandGen& rg;
public:

	using NSSeq<RepMODM, AdsMODM>::move; // prevents name hiding

	NSSeqARProduct(RandGen& _rg, ProblemInstance* _dmproblem) :
			rg(_rg), dmproblem(_dmproblem)
	{
	}

	virtual ~NSSeqARProduct()
	{
	}

	virtual Move<RepMODM, AdsMODM>& move(const RepMODM& rep, const AdsMODM& ads)
	{
		int nProduts = dmproblem->getNumberOfProducts();

		int y = rg.rand(nProduts);

		vector<int> vazio;
		return *new MoveARProduct(y, vazio, 0, 0, 0, dmproblem); // return a random move
	}

	virtual NSIterator<RepMODM, AdsMODM>& getIterator(const RepMODM& rep, const AdsMODM& ads)
	{
		return *new NSIteratorARProduct(ads, dmproblem); // return an iterator to the neighbors of 'rep'
	}

	virtual void print() const
	{
	}
};

}

#endif /*MODM_NSSEQARProduct_H_*/
