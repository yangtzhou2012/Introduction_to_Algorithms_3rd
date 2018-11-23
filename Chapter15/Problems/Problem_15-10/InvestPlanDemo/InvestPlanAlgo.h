#ifndef _INVEST_PLAN_ALGO_H_
#define _INVEST_PLAN_ALGO_H_

class InvestPlan
{
public:
	InvestPlan();
	~InvestPlan();

	void Clear();
	bool SetParameters(int y, int i, int f1, int f2, int im);
	void GenerateRandomRate();
	bool CreateInvestPlan();

	const int GetYears() const { return years; }
	const int GetInvestments() const { return investments; }
	const double GetTotalIncome() const { return totalIncome; }
	const int* GetRatePercent() const { return ratePercent; }
	const int* GetInvestSelect() const { return investSelect; }

private:
	int years;
	int investments;
	int fee1;
	int fee2;
	int initialMoney;
	double totalIncome;
	int *ratePercent;
	int *investSelect;
};

#endif // #ifndef _INVEST_PLAN_ALGO_H_
