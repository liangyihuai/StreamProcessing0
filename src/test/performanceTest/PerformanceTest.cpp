#include "../../stdafx.h"
#include <iostream>
#include "../../gui/RuleRegisterUtils.h"
#include "../../gui/MultiThreads.h"
#include "../../execution/ExecuteScheduler.h"
#include "RuleSpecOfEventCapture.h"

using namespace std;

int main() {
	RuleRegisterUtils::registerEventFilter(ef_rule1_name, ef_rule1);
	RuleRegisterUtils::registerEventCapture(ec_rule2_name, ec_rule2);
	RuleRegisterUtils::registerCQ(cq_rule3_name, cq_rule3);
	RuleRegisterUtils::registerCEP(cep_rule4_name, cep_rule4);

	RuleRegisterUtils::registerEventCapture(ec_rule5_name, ec_rule5);
	RuleRegisterUtils::registerCQ(cq_rule6_name, cq_rule6);
	RuleRegisterUtils::registerCQ(cq_rule7_name, cq_rule7);
	RuleRegisterUtils::registerCEP(cep_rule8_name, cep_rule8);
	RuleRegisterUtils::registerCEP(cep_rule9_name, cep_rule9);

	//thread for event filtering.
	ThreadOfEventFilter* threadOfEventFilter = new ThreadOfEventFilter();
	threadOfEventFilter->runThread().detach();

	ExecuteScheduler::initialize();

	//thread for EventCapture, CQ and CEP.
	ThreadOfProcessUnit * threadOfProcessUnit = new ThreadOfProcessUnit();
	threadOfProcessUnit->runThread().detach();

	//thread for getting the results of CEP.
	ThreadOfTimerToPerformCEP * threadOfTimerToPerformCEP = new ThreadOfTimerToPerformCEP();
	threadOfTimerToPerformCEP->runThread().detach();

	system("pause");
	return 0;
}