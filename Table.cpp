#include "Table.h"
#include <algorithm>
#include <numeric>
#include <iterator>


Table::Table()
{
}


Table::~Table()
{
}

void Table::AddCell(TableKey aKey, double aValue)
{
	//check if already exist
	auto it = fTable.find(aKey);
	if (it != fTable.end())
	{
		//change exist value
		it->second = aValue;
	}
	else
	{
		//add new cell to table
		fTable.insert(pair<TableKey, double>(aKey, aValue));
	}
}

void Table::AddCell(string aInputStr)
{
}

double Table::GetRangeSum(TableKey aBegin, TableKey aEnd)
{
	
	//create vector with all cells in range
	//vector<TableKey> rangeCells;
	map<TableKey, double> rangeCells;

	for (int i= aBegin.Row; i<=aEnd.Row; i++)
		for (int j = aBegin.Col; j <= aEnd.Col; j++)
		{
			//rangeCells.push_back(TableKey( i, j ));
			rangeCells.insert(pair<TableKey, double>(TableKey(i, j),0));
		}

	//find intersection - inpur range cells with fTable
	map<TableKey, int> sumCells;
	
	set_intersection(
		fTable.begin(), fTable.end(), 
		rangeCells.begin(), rangeCells.end(), 
		inserter(sumCells, sumCells.begin()),
		[](pair<TableKey, double> p1, pair<TableKey, double>p2)
		{
			return p1.first < p2.first;
		}
		);
	
	double sum = std::accumulate(sumCells.begin(), sumCells.end(), 0.0,
		[](int value, const std::map<TableKey, double>::value_type& p)
			{ return value + p.second; }
	);

	return sum;
}


