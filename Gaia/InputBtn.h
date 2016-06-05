#pragma once

#include "GaiaObject.h"
#include "GaiaLLogic.h"

#include "GaiaRepo.h"
class InputBtn :
	public GaiaLLogic
{
	DECLARE_SERIAL(InputBtn)
public:
	virtual void Serialize(CArchive& ar);
public:
	InputBtn();
	InputBtn(int x, int y);
public:
	void Draw(CDC* pDC)override;
	void Calculate() override;
};

