
#ifndef AND_GATE_H_7DF_INCLUDE
#define AND_GATE_H_7DF_INCLUDE

#include"GaiaLLogic.h"

class AndGate :public GaiaLLogic
{
public:
	AndGate();
	void Draw(CDC* pDC)override;
	void Calculate() override;
};

#endif