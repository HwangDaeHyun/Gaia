#pragma once
#ifndef NOR_GATE_H_7DF_INCLUDE
#define NOR_GATE_H_7DF_INCLUDE
#include"GaiaObject.h"
#include"GaiaLLogic.h"

class NorGate :public GaiaLLogic
{
public:
	NorGate();
	void Draw(CDC* pDC)override;
	void Calculate() override;
};

#endif