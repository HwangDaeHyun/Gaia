#ifndef OUTLAMP_H_INCLUDE
#define OUTLAMP_H_INCLUDE
#include "GaiaLLogic.h"
class OutLamp : public GaiaLLogic
{
	DECLARE_SERIAL(OutLamp)
public:
	virtual void Serialize(CArchive& ar);
public:
	OutLamp();
	void Draw(CDC* pDC)override;
	void OutLamp::Calculate()override;
};

#endif