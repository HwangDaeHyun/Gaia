#ifndef CLOCKCYCLE_H_INCLUDED
#define CLOCKCYCLE_H_INCLUDED
#include "GaiaLLogic.h"
class ClockCycle :
	public GaiaLLogic
{
	DECLARE_SERIAL(ClockCycle)
public:
	virtual void Serialize(CArchive& ar);
	ClockCycle();
	ClockCycle(int x, int y);
public:
	void Draw(CDC* pDC)override;
	void Calculate() override;
};

#endif