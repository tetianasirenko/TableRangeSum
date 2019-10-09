#include "Table.h"
#include <regex>
#include <iostream> 
#include <gtest\gtest.h>

int main()
{
	::testing::InitGoogleTest();
	return RUN_ALL_TESTS();


	//regex rValue("[a-zA-Z][0-9]:[0-9]");
	//regex rRange("[a-zA-Z][0-9]:[a-zA-Z][0-9]");

	//string sTestValue = "A2:5";

	//string sTestRange = "A2:B5";

	//if (regex_match(sTestRange, rValue))
	//	cout << "True";

	//if (regex_match(sTestRange, rRange))
	//	cout << "True range";

	//if (regex_match(sTestValue, rValue))
	//	cout << "True range";

	////smatch m;
	////regex_search(sTestValue, m, rValue);

	////for (auto x : m)
	////	cout << x << " ";

	//return 0;
}

TEST(TableSumTests, Simple)
{
	
	Table mainTable;
	
	mainTable.AddCell(TableKey(1, 1), 1);
	mainTable.AddCell(TableKey(1, 2), 2);
	mainTable.AddCell(TableKey(1, 3), 3);
	mainTable.AddCell(TableKey(1, 4), 4);
	mainTable.AddCell(TableKey(2, 1), 5);
	mainTable.AddCell(TableKey(2, 2), 6);
	mainTable.AddCell(TableKey(2, 3), 7);
	mainTable.AddCell(TableKey(2, 4), 8);

	double sum = mainTable.GetRangeSum(TableKey(1, 2), TableKey(2, 3));
	EXPECT_EQ(sum, 18);
}

TEST(TableSumTests, Zero)
{

	Table mainTable;

	mainTable.AddCell(TableKey(1, 1), 1);
	mainTable.AddCell(TableKey(1, 2), 2);
	mainTable.AddCell(TableKey(1, 3), 3);
	mainTable.AddCell(TableKey(1, 4), 4);
	mainTable.AddCell(TableKey(2, 1), 5);
	mainTable.AddCell(TableKey(2, 2), 6);
	mainTable.AddCell(TableKey(2, 3), 7);
	mainTable.AddCell(TableKey(2, 4), 8);

	double sum = mainTable.GetRangeSum(TableKey(3, 2), TableKey(5, 3));
	EXPECT_EQ(sum, 0.0);
}

TEST(TableSumTests, BigTable)
{

	Table mainTable;

	for (int i=0; i<1000; i++)
		for (int j = 0; j<1000; j++)
			mainTable.AddCell(TableKey(i, j), 1);

	double sum = mainTable.GetRangeSum(TableKey(1, 2), TableKey(2, 3));
	EXPECT_EQ(sum, 6);

}

TEST(TableSumTests, OneCell)
{

	Table mainTable;

	for (int i = 0; i<1000; i++)
		for (int j = 0; j<1000; j++)
			mainTable.AddCell(TableKey(i, j), 1);

	double sum = mainTable.GetRangeSum(TableKey(1, 1), TableKey(1, 1));
	EXPECT_EQ(sum, 1);

}