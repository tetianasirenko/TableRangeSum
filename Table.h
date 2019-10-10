#pragma once
#include <map>
#include <vector>

using namespace std;

struct TableKey
{
	size_t Row;
	size_t Col;

	TableKey(size_t aRow, size_t aCol)
	{
		Row = aRow;
		Col = aCol;
	}

	bool operator== (const TableKey& rhs) const
	{
		if ((Row == rhs.Row) && (Col == rhs.Col))
			return true;
		return false;
	}

	bool operator< (const TableKey& rhs) const
	{
		if (Row < rhs.Row)
			return true;
		else if ((Row == rhs.Row) && (Col < rhs.Col))
			return true;
		else
		return false;
	}
};

class Table
{
public:
	Table();
	~Table();

	void AddCell(TableKey aKey, double aValue);
	void AddCell(string aInputStr);

	void DeleteAllCells();

	double GetRangeSum(TableKey aBegin, TableKey aEnd);
	double GetRangeSum2(TableKey aBegin, TableKey aEnd);

private:
	map<TableKey, double>  fTable;



};

