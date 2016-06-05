#ifndef OUTLAMP_H_INCLUDE
#define OUTLAMP_H_INCLUDE
#include "GaiaLLogic.h"
class OutLamp : public GaiaLLogic
{
public:
	OutLamp();
	void Draw(CDC* pDC)override;
	void Calculate()override;
};

#endif