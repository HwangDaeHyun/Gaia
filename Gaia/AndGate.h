#pragma once
#ifndef GOEUN_EDITOR_AND_GATE_H_7DF_INCLUDE
#define GOEUN_EDITOR_AND_GATE_H_7DF_INCLUDE
#include"GaiaObject.h"
#include"GaiaLLogic.h"

class AndGate :public GaiaLLogic
{
public:
	AndGate(){}
	void Draw(CDC* pDC)override;
};

#endif