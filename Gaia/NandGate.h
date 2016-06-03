#pragma once
#ifndef NAND_GATE_H_7DF_INCLUDE
#define NAND_GATE_H_7DF_INCLUDE
#include"GaiaObject.h"
#include"GaiaLLogic.h"

class NandGate :public GaiaLLogic
{
public:
	NandGate();
	void Draw(CDC* pDC)override;
	void Calculate() override;
};

#endif