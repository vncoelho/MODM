#ifndef MODM_PROBLEMINSTANCE_H_
#define MODM_PROBLEMINSTANCE_H_

#include <iostream>

#include "../../OptFrame/Scanner++/Scanner.h"
#include "../../OptFrame/Component.hpp"
#include "../../OptFrame/Util/Matrix.hpp"
#include "../../OptFrame/RandGen.hpp"
#include "../../OptFrame/Util/printable.h"

using namespace std;
using namespace scannerpp;
using namespace optframe;

namespace MODM
{

class ProblemInstance: public Component
{

private:
	// Your private vars
	RandGen& rg;

public:
	ProblemInstance(Scanner& scanner, RandGen& _rg) :
			rg(_rg)
	{
		// Put here your code
		// You can read the input data from the 'scanner' object

		//Problem data
		cout << "========= THAYS Start Reading Problem Instance =========" << endl;
		//number of clients
		c = scanner.nextInt();
		cout << "number of clients: ";
		cout << c << endl;

		//number of products
		n = scanner.nextInt();
		cout << "number of products: ";
		cout << n << endl;

		//Hurdle rate
		cout << "hurdle rate: ";
		R = scanner.nextDouble();
		cout << R << endl;

		cost = new Matrix<int>(c, n);
		revenue = new Matrix<int>(c, n);
		//reading cost, revenue and maxOffers
		cout << "cost(" << n << "), revenue(" << n << ") and maxOffers(1)" << endl;
		for (int client = 0; client < c; client++)
		{
			cout << "[";
			//cost
			for (int product = 0; product < n; product++)
			{
				int costProduct = scanner.nextInt();
				cout << costProduct << ",";
				(*cost)(client, product) = costProduct;
			}

			//cost
			for (int product = 0; product < n; product++)
			{
				int revenueProduct = scanner.nextInt();
				cout << revenueProduct << ",";
				(*revenue)(client, product) = revenueProduct;
			}

			int maxOffer = scanner.nextInt();
			cout << maxOffer << "]" << endl;
			maxOffers.push_back(maxOffer);
		}

		//reading minClients to offer each product of the campain
		cout << "minClients of clients to offer each product during the campain" << endl;
		for (int products = 0; products < n; products++)
		{
			int nMinClients = scanner.nextInt();
			cout << nMinClients << ",";
			minClients.push_back(nMinClients);

		}
		cout << endl;

		//reading budget to offer each product of the campain
		cout << "avaiable budge for each product" << endl;
		for (int products = 0; products < n; products++)
		{
			int vBudget = scanner.nextInt();
			cout << vBudget << ",";
			budget.push_back(vBudget);
		}
		cout << endl;

		//reading fixedCost to offer each product of the campain
		cout << "fixedCost of each product" << endl;
		for (int products = 0; products < n; products++)
		{
			int vFixedCost = scanner.nextInt();
			cout << vFixedCost << ",";
			fixedCost.push_back(vFixedCost);

		}
		cout << endl;
		cout << "========= Finish Reading Problem Instance =========" << endl;

		/*
		 cout<< R<<endl;
		 cout<< c<<endl;
		 cout<< n<<endl;
		 cout<< *cost<<endl;
		 cout<< *revenue<<endl;
		 cout<< maxOffers<<endl;
		 cout<< fixedCost<<endl;
		 cout<< budget<<endl;
		 cout<< minClients<<endl;
		 getchar();
		 */
	}

	int getNumberOfProducts()
	{
		return n;
	}

	int getNumberOfClients()
	{
		return c;
	}
	int getHurdleRate()
	{
		return R;
	}

	int getRevenue(int i, int j)
	{
		return (*revenue)(i, j);
	}

	int getCost(int i, int j)
	{
		return (*cost)(i, j);
	}

	int getProductFixedCost(int j)
	{
		return fixedCost[j];
	}

	int getProductBudget(int j)
	{
		return budget[j];
	}

	int getProductMinClients(int j)
	{
		return minClients[j];
	}

	int getClientMaxOffers(int i)
	{
		return maxOffers[i];
	}

	virtual ~ProblemInstance()
	{
	}

	void generateInstance(int nClients, int nBooks, Matrix<vector<double> >& prob)
	{
		//generate book prices
		vector<int> booksProfit(nBooks);
		vector<int> booksCost(nBooks);
		vector<int> booksDeliverCost(nClients);

		double profitRate = 1.7;
		for (int i = 0; i < nClients; i++)
		{
			booksDeliverCost[i] = rg.rand(20) + 5;
		}

		for (int i = 0; i < nBooks; i++)
		{
			booksCost[i] = rg.rand(90) + 10;
			booksProfit[i] = booksCost[i] * profitRate;
		}

		Matrix<int> instanceTODMCProfit(nClients, nBooks); // matrix composed of profits and costs for each client and book offer
		Matrix<int> instanceTODMCCosts(nClients, nBooks); // matrix composed of profits and costs for each client and book offer

		for (unsigned c = 0; c < nClients; c++)
		{
			for (unsigned b = 0; b < nBooks; b++)
			{
				double revenue = 0;
				for (unsigned w = 0; w < nBooks; w++)
				{
					revenue += prob(c, b)[w] * booksProfit[w];
				}
				instanceTODMCProfit(c, b) = revenue;
				instanceTODMCCosts(c, b) = booksCost[b] + booksDeliverCost[c];
			}
		}

		double hurdleRate = 0.15; // 0.05 and 0.1

		double maxPerClients = 3; // 0.05 and 0.1
		vector<int> maxOffersPerClient;
		int sumMOffers = 0;
		for (unsigned c = 0; c < nClients; c++)
		{
			maxOffersPerClient.push_back(rg.rand(maxPerClients) + 1);
			sumMOffers += maxOffersPerClient[c];
		}

		//calculating maxBudjet total cost
		vector<int> maxCostBooks(nBooks, 0);
		for (unsigned b = 0; b < nBooks; b++)
		{
			for (unsigned c = 0; c < nClients; c++)
			{
				maxCostBooks[b] += instanceTODMCCosts(c, b);
			}
		}

		vector<int> minProducts(nBooks);
		vector<int> availableBudget(nBooks);

		for (unsigned b = 0; b < nBooks; b++)
		{
			int bookMinOffers = rg.rand(sumMOffers / nBooks, 2 * sumMOffers / nBooks);
			minProducts[b] = bookMinOffers;
			availableBudget[b] = rg.rand(minProducts[b] * maxCostBooks[b] / nClients, 2 * maxCostBooks[b] / nClients);
		}

		FILE* out = fopen("testInstanceBookOfferCampaing.txt", "w");
		fprintf(out, "%d\t%d\t%.2f\n", nClients, nBooks, hurdleRate);

		for (unsigned c = 0; c < nClients; c++)
		{

			for (unsigned b = 0; b < nBooks; b++)
			{
				fprintf(out, "%d\t", instanceTODMCCosts(c, b));
			}
			fprintf(out, "\t\t");
			for (unsigned b = 0; b < nBooks; b++)
			{
				fprintf(out, "%d\t", instanceTODMCProfit(c, b));
			}

			fprintf(out, "%d\n", maxOffersPerClient[c]);
		}

		//Generating min number of offer per product
		for (unsigned b = 0; b < nBooks; b++)
		{

			fprintf(out, "%d\t", minProducts[b]);
		}
		fprintf(out, "\n");

		//Generating budget for each product
		for (unsigned b = 0; b < nBooks; b++)
		{
			fprintf(out, "%d\t", availableBudget[b]);
		}
		fprintf(out, "\n");

		//generating fixed cost
		for (unsigned b = 0; b < nBooks; b++)
		{
			fprintf(out, "%d\t", 1);
		}
		fprintf(out, "\n");
		fclose(out);

	}

	void computeProb(int nClients, int nBooks, Matrix<vector<double> >& prob, Matrix<bool> graph, vector<int> degC, vector<int> degB)
	{
		for (unsigned c = 0; c < nClients; c++)
			for (unsigned b = 0; b < nBooks; b++) // ofertando livro 'b' para cliente 'c'
			{
				//cout << "dando b=" << b << " para c=" << c << endl;

				for (unsigned w = 0; w < nBooks; w++) // chance de comprar livro 'w' depois de ganhar 'b'
				{
					if (graph(c, w) || graph(c, b) || (b == w))
						prob(c, b)[w] = 0.0; // ja tem o livro indicado, ou comprado, ou livro indicado é igual ao comprado
					else
					{
						// vai ganhar o 'b'
						graph(c, b) = true;
						degC[c]++;
						degB[b]++;

						// ganhou book
						// calcular probabilidade

						// soma graus dos livros que ainda não tem
						double soma = 0.0;
						for (unsigned i = 0; i < nBooks; i++)
							if (!graph(c, i))
								soma += degB[i];
						if (soma == 0)
						{
							cout << "SOMA DO CLIENTE " << c << " DEU ZERO!" << endl;
							getchar();
						}

						if (soma != 0)
							if (!graph(c, w))
							{
								prob(c, b)[w] = degB[w] / soma;
								//cout << "prob=" << prob(c, b)[w] << endl;
							}

						// retira livro 'b' de 'c'
						graph(c, b) = false;
						degC[c]--;
						degB[b]--;
					}
				}
			}

		// end calculation
	}

	void generateExample()
	{
		int nClients = 3;
		int nBooks = 4;

		Matrix<bool> graph(nClients, nBooks);
		Matrix<bool> graphComplete(nClients, nBooks);
		vector<int> degC(nClients, 0);  // degree of customers
		vector<int> degB(nBooks, 0);    // degree of books
		graph.fill(true);

		graph(0, 1) = false;
		graph(0, 2) = false;
		graph(0, 3) = false;
		graph(1, 1) = false;

		degC[0] = 1;
		degC[1] = 2;
		degC[2] = 3;
		degB[0] = 3;
		degB[1] = 1;
		degB[2] = 2;
		degB[3] = 2;

		Matrix<vector<double> > prob(nClients, nBooks);
		vector<double> ex(nBooks, 0.0);
		prob.fill(ex);

		printGraph(nClients, nBooks, graph);

		computeProb(nClients, nBooks, prob, graph, degC, degB);

		for (unsigned c = 0; c < nClients; c++)
			for (unsigned b = 0; b < nBooks; b++)
				if (!graph(0, b))
				{
					cout << "doando livro " << b << " para clinete " << c << endl;
					cout << "prob:" << endl;
					cout << prob(0, b) << endl;
				}
		cout << "finish example" << endl;
	}

	void generateBicliqueProblem(int nClients, int nBooks)
	{
		cout << "generating biclique for nClients=" << nClients << " and nBooks=" << nBooks << endl;
		Matrix<bool> graph(nClients, nBooks);
		Matrix<bool> graphComplete(nClients, nBooks);
		vector<int> degC(nClients, 0);  // degree of customers
		vector<int> degB(nBooks, 0);    // degree of books
		graph.fill(0);

		int nMaxClientsBiclique = nClients / 3;
		int nMaxBooksBiclique = nBooks / 2;

		vector<pair<vector<int>, vector<int> > > bicliques;
		vector<int> vecClients;
		vector<int> vecBooks;
		for (int i = 0; i < nClients; i++)
			vecClients.push_back(i);
		for (int i = 0; i < nBooks; i++)
			vecBooks.push_back(i);

		while (vecClients.size() > 0 && vecBooks.size() > 0)
		{
			pair<vector<int>, vector<int> > currentBiclique;
			int minBiliqueSize = 3;
			int bicliqueCSize = rg.rand(nMaxClientsBiclique - minBiliqueSize) + minBiliqueSize; // minimum size 2
			int bicliqueBSize = rg.rand(nMaxBooksBiclique - minBiliqueSize) + minBiliqueSize;   // minimum size 2
			bicliqueCSize = min(bicliqueCSize, int(vecClients.size()));
			bicliqueBSize = min(bicliqueBSize, int(vecBooks.size()));
			if (vecClients.size() - bicliqueCSize < minBiliqueSize)
				bicliqueCSize = vecClients.size();
			if (vecBooks.size() - bicliqueBSize < minBiliqueSize)
				bicliqueBSize = vecBooks.size();

			for (int i = 0; i < bicliqueCSize; i++)
			{
				int indexC = rg.rand(vecClients.size());
				int c = vecClients[indexC];
				vecClients.erase(vecClients.begin() + indexC);
				currentBiclique.first.push_back(c);
			}

			for (int i = 0; i < bicliqueBSize; i++)
			{
				int indexB = rg.rand(vecBooks.size());
				int b = vecBooks[indexB];
				vecBooks.erase(vecBooks.begin() + indexB);
				currentBiclique.second.push_back(b);
			}

			// add remaining books to biclique, if it's the last
			if (vecClients.size() == 0)
				while (vecBooks.size() > 0)
				{
					currentBiclique.second.push_back(vecBooks[0]);
					vecBooks.erase(vecBooks.begin() + 0);
				}
			// add remaining clients to biclique, if it's the last
			if (vecBooks.size() == 0)
				while (vecClients.size() > 0)
				{
					currentBiclique.first.push_back(vecClients[0]);
					vecClients.erase(vecClients.begin() + 0);
				}

			//====================================================================
			// adding biclique to the graph

			int count_edges = 0;
			for (int c = 0; c < currentBiclique.first.size(); c++)
				for (int b = 0; b < currentBiclique.second.size(); b++)
				{
					int addGraphC = currentBiclique.first[c];
					int addGraphB = currentBiclique.second[b];
					graph(addGraphC, addGraphB) = true;
					degC[addGraphC]++;
					degB[addGraphB]++;
					count_edges++;
				}

			//====================================================================
			// remove some edges from biclique
			int final_edges = count_edges * 0.7; // TODO: random
			if (final_edges == 0)
				final_edges = 1;

			cout << "removing edges. count=" << count_edges << " final=" << final_edges << endl;
			while (count_edges > final_edges)
			{
				// random client and book, remove edge (if not last)
//				cout << "clients=" << currentBiclique.first.size() << " ";
//				cout << "biclique=" << currentBiclique.second.size() << endl;

				int c = rg.rand(currentBiclique.first.size());
				int b = rg.rand(currentBiclique.second.size());

				int remGraphC = currentBiclique.first[c];
				int remGraphB = currentBiclique.second[b];

				if (!graph(remGraphC, remGraphB)) // already removed
					continue;

//				cout << "c=" << remGraphC << " b=" << remGraphB << endl;

				if (degC[remGraphC] == 1 || degB[remGraphB] == 1)
					continue; // try again
				graph(remGraphC, remGraphB) = false;
				degC[remGraphC]--;
				degB[remGraphB]--;
				count_edges--;

			}

			bicliques.push_back(currentBiclique);

		}

		printBiclique(bicliques);
		printGraph(nClients, nBooks, graph);
		cout << "end while bicliques" << endl;
		// end while

		FILE* out = fopen("bicliques.txt", "w");
		for (unsigned i = 0; i < nClients; i++)
		{
			for (unsigned b = 0; b < nBooks; b++)
			{
				fprintf(out, "%d\t", graph(i, b));
			}
			fprintf(out, "\n");
		}
		fclose(out);

		cout << "finished generation" << endl;

		Matrix<vector<double> > prob(nClients, nBooks);
		vector<double> ex(nBooks, 0.0);
		prob.fill(ex);

		computeProb(nClients, nBooks, prob, graph, degC, degB);

		generateInstance(nClients, nBooks, prob);

		// imprime probabilidades

		cout << "end calculation" << endl;
	}

	void printBiclique(vector<pair<vector<int>, vector<int> > > bicliques)
	{
		for (int i = 0; i < bicliques.size(); i++)
		{
			cout << bicliques[i].first << endl;
			cout << bicliques[i].second << endl;
		}
	}

	void printGraph(int nClients, int nBooks, Matrix<bool> graph)
	{
		// print biclique
		cout << "Graph is being printed....\n" << endl;
		cout << "graph G {" << endl;
		cout << "graph [rankdir=LR, splines=true ];" << endl;
		cout << "overlap=false; splines=true" << endl;
		cout << "edge [style=dotted, weight=10, len=.2]" << endl;
		cout << "subgraph cluster_left {" << endl;
		//cout << "left [pos=\"-1,0!\", color=red /* , style=invis */]" << endl;
		for (unsigned i = 0; i < nClients; i++)
			cout << "\"c" << i << '\"' << endl;
		//cout << "\"c" << i << "\" -- left" << endl;

		cout << "}" << endl;
		cout << "subgraph cluster_right {" << endl;
		//cout << "right [pos=\"1,0!\", color=blue /* , style=invis */]" << endl;
		for (unsigned i = 0; i < nBooks; i++)
			//cout << "\"b" << i << "\" -- right" << endl;
			cout << "\"b" << i << '\"' << endl;
		cout << "}" << endl;
		cout << "edge [style=\"\", weight=1, len=1,minlen=\"10.0\"]" << endl;
		for (unsigned i = 0; i < nClients; i++)
		{
			for (unsigned b = 0; b < nBooks; b++)
				if (graph(i, b))
				{
					cout << "\"c" << i << '\"' << " -- " << "\"b" << b << '\"' << endl;
				}
			//cout << graph(i, b) << " ";
			//cout << endl;
		}
		cout << "}" << endl;
	}
	double R;
	int c;
	int n;
	Matrix<int>* cost;
	Matrix<int>* revenue;
	vector<int> maxOffers;
	vector<int> fixedCost;
	vector<int> budget;
	vector<int> minClients;
};

}

#endif /*MODM_PROBLEMINSTANCE_H_*/

