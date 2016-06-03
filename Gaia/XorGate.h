#pragma once
#ifndef XOR_GATE_H_7DF_INCLUDE
#define XOR_GATE_H_7DF_INCLUDE
#include"GaiaObject.h"
#include"GaiaLLogic.h"

class XorGate :public GaiaLLogic
{
public:
	XorGate();
	void Draw(CDC* pDC)override;
	void Calculate() override;

};

#endif