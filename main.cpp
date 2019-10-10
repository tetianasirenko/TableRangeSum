#include "Table.h"
#include <regex>
#include <iostream> 
#include <gtest\gtest.h>

int main()
{
	::testing::InitGoogleTest();
	RUN_ALL_TESTS();

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

	getchar();
	return 0;
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
	EXPECT_EQ(sum, 4);

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

TEST(TableSumTests, WrongRange)
{

	Table mainTable;

	for (int i = 0; i<100; i++)
		for (int j = 0; j<100; j++)
			mainTable.AddCell(TableKey(i, j), 1);

	double sum = mainTable.GetRangeSum(TableKey(7, 8), TableKey(2, 3));
	EXPECT_EQ(sum, 0);

}

TEST(TableSumTests, TableSizeTimes)
{
	auto rBegin = TableKey(1, 1);
	auto rEnd = TableKey(10, 10);

	double calcSum = 100;

	int N = 10;
	Table mainTable;

	for (int i = 0; i<=N; i++)
		for (int j = 0; j<=N; j++)
			mainTable.AddCell(TableKey(i, j), 1);

	cout << "Range 10 x 10" << endl;
	cout << "Table: " << N <<" x " << N << endl;

	clock_t begin_time = clock();

	double actualSum = mainTable.GetRangeSum(rBegin, rEnd);
	EXPECT_EQ(calcSum, actualSum);

	cout << "Time: " << float(clock() - begin_time) / CLOCKS_PER_SEC << " sec" << endl;

	N = 100;
	mainTable.DeleteAllCells();

	for (int i = 0; i<=N; i++)
		for (int j = 0; j<=N; j++)
			mainTable.AddCell(TableKey(i, j), 1);

	
	cout << "Table: " << N << " x " << N << endl;

	begin_time = clock();

	actualSum = mainTable.GetRangeSum(rBegin, rEnd);
	EXPECT_EQ(calcSum, actualSum);

	cout << "Time: " << float(clock() - begin_time) / CLOCKS_PER_SEC << " sec" << endl;

	N = 1000;
	mainTable.DeleteAllCells();

	for (int i = 0; i<=N; i++)
		for (int j = 0; j<=N; j++)
			mainTable.AddCell(TableKey(i, j), 1);

	
	cout << "Table: " << N << " x " << N << endl;

	begin_time = clock();

	actualSum = mainTable.GetRangeSum(rBegin, rEnd);
	EXPECT_EQ(calcSum, actualSum);

	cout << "Time: " << float(clock() - begin_time) / CLOCKS_PER_SEC << " sec" << endl;

	/*N = 10000;
	mainTable.DeleteAllCells();

	for (int i = 0; i<=N; i++)
		for (int j = 0; j<=N; j++)
			mainTable.AddCell(TableKey(i, j), 1);

	begin_time = clock();

	cout << "N=" << N << endl;
	actualSum = mainTable.GetRangeSum(rBegin, rEnd);
	EXPECT_EQ(calcSum, actualSum);

	cout << "Time: " << float(clock() - begin_time) / CLOCKS_PER_SEC << " sec" << endl;
*/
}

TEST(TableSumTests, RangeSizeTimes)
{
	int N = 10;
	auto rBegin = TableKey(1, 1);
	auto rEnd = TableKey(N, N);

	double calcSum = N*N;

	cout << "Table 1000 x 1000" << endl;
	
	Table mainTable;

	for (int i = 0; i <= 1000; i++)
		for (int j = 0; j <=1000; j++)
			mainTable.AddCell(TableKey(i, j), 1);

	
	cout << "Range: " << N << " x " << N << endl;

	clock_t begin_time = clock();

	double actualSum = mainTable.GetRangeSum(rBegin, rEnd);
	EXPECT_EQ(calcSum, actualSum);

	cout << "Time: " << float(clock() - begin_time) / CLOCKS_PER_SEC << " sec" << endl;

	N = 100;
	rEnd = TableKey(N, N);
	
	calcSum = N*N;

	cout << "Range: " << N << " x " << N << endl;

	begin_time = clock();
	actualSum = mainTable.GetRangeSum(rBegin, rEnd);
	EXPECT_EQ(calcSum, actualSum);

	cout << "Time: " << float(clock() - begin_time) / CLOCKS_PER_SEC << " sec" << endl;

	N = 1000;
	rEnd = TableKey(N, N);

	calcSum = N*N;
		
	cout << "Range: " << N << " x " << N << endl;

	begin_time = clock();

	actualSum = mainTable.GetRangeSum(rBegin, rEnd);
	EXPECT_EQ(calcSum, actualSum);

	cout << "Time: " << float(clock() - begin_time) / CLOCKS_PER_SEC << " sec" << endl;

	/*N = 10000;
	rEnd = TableKey(N, N);

	calcSum = N*N;

	begin_time = clock();

	cout << "N=" << N << endl;
	actualSum = mainTable.GetRangeSum(rBegin, rEnd);
	EXPECT_EQ(calcSum, actualSum);

	cout << "Time: " << float(clock() - begin_time) / CLOCKS_PER_SEC << " sec" << endl;
*/
}

TEST(TableSumTests, CompareMethods)
{
	auto rBegin = TableKey(1, 1);
	auto rEnd = TableKey(10, 10);

	double calcSum = 100;

	int N = 10;
	Table mainTable;

	for (int i = 0; i <= N; i++)
		for (int j = 0; j <= N; j++)
			mainTable.AddCell(TableKey(i, j), 1);


	cout << "Table: " << N << " x " << N << endl;

	clock_t begin_time = clock();

	double actualSum = mainTable.GetRangeSum(rBegin, rEnd);
	EXPECT_EQ(calcSum, actualSum);

	cout << "Time: " << float(clock() - begin_time) / CLOCKS_PER_SEC << " sec" << endl;

	begin_time = clock();

	actualSum = mainTable.GetRangeSum2(rBegin, rEnd);
	EXPECT_EQ(calcSum, actualSum);

	cout << "Time old method: " << float(clock() - begin_time) / CLOCKS_PER_SEC << " sec" << endl;

	N = 100;
	mainTable.DeleteAllCells();

	for (int i = 0; i <= N; i++)
		for (int j = 0; j <= N; j++)
			mainTable.AddCell(TableKey(i, j), 1);


	cout << "Table: " << N << " x " << N << endl;

	begin_time = clock();

	actualSum = mainTable.GetRangeSum(rBegin, rEnd);
	EXPECT_EQ(calcSum, actualSum);

	cout << "Time: " << float(clock() - begin_time) / CLOCKS_PER_SEC << " sec" << endl;

	begin_time = clock();

	actualSum = mainTable.GetRangeSum2(rBegin, rEnd);
	EXPECT_EQ(calcSum, actualSum);

	cout << "Time old method: " << float(clock() - begin_time) / CLOCKS_PER_SEC << " sec" << endl;

	N = 1000;
	mainTable.DeleteAllCells();

	for (int i = 0; i <= N; i++)
		for (int j = 0; j <= N; j++)
			mainTable.AddCell(TableKey(i, j), 1);


	cout << "Table: " << N << " x " << N << endl;

	begin_time = clock();

	actualSum = mainTable.GetRangeSum(rBegin, rEnd);
	EXPECT_EQ(calcSum, actualSum);

	cout << "Time: " << float(clock() - begin_time) / CLOCKS_PER_SEC << " sec" << endl;

	begin_time = clock();

	actualSum = mainTable.GetRangeSum2(rBegin, rEnd);
	EXPECT_EQ(calcSum, actualSum);

	cout << "Time old method: " << float(clock() - begin_time) / CLOCKS_PER_SEC << " sec" << endl;

	/*N = 10000;
	mainTable.DeleteAllCells();

	for (int i = 0; i<=N; i++)
	for (int j = 0; j<=N; j++)
	mainTable.AddCell(TableKey(i, j), 1);

	begin_time = clock();

	cout << "N=" << N << endl;
	actualSum = mainTable.GetRangeSum(rBegin, rEnd);
	EXPECT_EQ(calcSum, actualSum);

	cout << "Time: " << float(clock() - begin_time) / CLOCKS_PER_SEC << " sec" << endl;
	*/
}