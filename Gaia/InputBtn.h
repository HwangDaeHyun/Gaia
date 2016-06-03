#pragma once

#include "GaiaObject.h"
#include "GaiaLLogic.h"

#include "GaiaRepo.h"
class InputBtn :
	public GaiaLLogic
{
public:
	InputBtn();
	InputBtn(int x, int y);
public:
	void Draw(CDC* pDC)override;
	void Calculate() override;
};

