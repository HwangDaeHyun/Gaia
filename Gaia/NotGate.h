#pragma once
#ifndef NOT_GATE_H_7DF_INCLUDE
#define NOT_GATE_H_7DF_INCLUDE
#include"GaiaObject.h"
#include"GaiaLLogic.h"

class NotGate :public GaiaLLogic
{
	DECLARE_SERIAL(NotGate)
public:
	virtual void Serialize(CArchive& ar);
public:
	NotGate();
	void Draw(CDC* pDC)override;
	void Calculate() override;
};

#endif