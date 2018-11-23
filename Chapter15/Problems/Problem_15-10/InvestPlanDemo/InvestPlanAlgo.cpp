#include "stdafx.h"
#include "InvestPlanAlgo.h"
#include <ctime>

InvestPlan::InvestPlan() : years(0), investments(0), fee1(0), fee2(0), initialMoney(0), totalIncome(0), ratePercent(NULL), investSelect(NULL)
{

}

InvestPlan::~InvestPlan()
{
	Clear();
}

void InvestPlan::Clear()
{
	years        = 0;
	investments  = 0;
	fee1         = 0;
	fee2         = 0;
	initialMoney = 0;
	totalIncome  = 0;

	if (ratePercent != NULL)
	{
		delete[] ratePercent;
		ratePercent = NULL;
	}

	if (investSelect != NULL)
	{
		delete[] investSelect;
		investSelect = NULL;
	}
}

bool InvestPlan::SetParameters(int y, int i, int f1, int f2, int im)
{
	if (y > 0 && i > 0 && f1 >= 0 && f2 >= 0 && im >= 0)
	{
		Clear();

		years        = y;
		investments  = i;
		fee1         = f1;
		fee2         = f2;
		initialMoney = im;
		totalIncome  = 0;

		ratePercent = new int[years*investments];
		//investSelect = new int[years];

		for (int i = 0; i < years*investments; ++i)
			ratePercent[i] = 100;

		return true;
	}
	else
	{
		return false;
	}
}

void InvestPlan::GenerateRandomRate()
{
	srand((unsigned int)time(0));

	for (int i = 0; i < years*investments; ++i)
		ratePercent[i] = rand()%11 + 100;

	if (investSelect != NULL)
	{
		delete[] investSelect;
		investSelect = NULL;
	}

	totalIncome = 0;
}

bool InvestPlan::CreateInvestPlan()
{
	if (years < 1 || investments < 1 || fee1 < 0 || fee2 < 0 || initialMoney < 0 || ratePercent == NULL)
		return false;

	double *subIncome = new double[years*investments];
	int *preYearInvestment = (years > 1) ? new int[(years-1)*investments] : NULL;

	for (int i = 0; i < investments; ++i)
		subIncome[i] = static_cast<double>(initialMoney)*ratePercent[i]/100;

	double *pIncome = subIncome + investments;
	int *pRate = ratePercent + investments;
	int *pInvestment = preYearInvestment;

	for (int j = 1; j < years; ++j)
	{
		double *pPrevYearIncome = pIncome - investments;

		for (int i = 0; i < investments; ++i)
		{
			*pIncome = (*(pPrevYearIncome+i) - fee1) * (*pRate) / 100;
			*pInvestment = i;

			for (int k = 0; k < investments; ++k)
			{
				if (k != i)
				{
					double t = (*(pPrevYearIncome+k) - fee2) * (*pRate) / 100;
					if (t > *pIncome)
					{
						*pIncome = t;
						*pInvestment = k;
					}
				}
			}

			pIncome++;
			pRate++;
			pInvestment++;
		}
	}

	pIncome = subIncome + (years-1)*investments;
	double maxIncome = *pIncome;
	int maxInvestmentIndex = 0;

	for (int i = 1; i < investments; ++i)
	{
		if (pIncome[i] > maxIncome)
		{
			maxIncome = pIncome[i];
			maxInvestmentIndex = i;
		}
	}

	if (investSelect == NULL) investSelect = new int[years];
	investSelect[years-1] = maxInvestmentIndex;

	for (int j = years-2; j >= 0; --j)
		investSelect[j] = *(preYearInvestment + j*investments + investSelect[j+1]);

	totalIncome = maxIncome;

	delete[] subIncome;
	if (preYearInvestment != NULL) delete[] preYearInvestment;
	return true;
}
