#pragma once

#include <vector>
#include "inter/Operator.h"

class HoveringOp :public Operator {
private:

public:

	ResultPtr result(EventPtr event) override;
};