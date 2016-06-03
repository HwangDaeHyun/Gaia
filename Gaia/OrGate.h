#pragma once
#ifndef OR_GATE_H_7DF_INCLUDE
#define OR_GATE_H_7DF_INCLUDE
#include"GaiaObject.h"
#include"GaiaLLogic.h"

class OrGate :public GaiaLLogic
{
public:
	OrGate();
	void Draw(CDC* pDC)override;
	void Calculate() override;

	//}
};

#endif