#ifndef GAIA_SEVENSEGMENT_H_INCLUDE
#define GAIA_SEVENSEGMENT_H_INCLUDE
#include "GaiaLLogic.h"
class SevenSegment :public GaiaLLogic{
	DECLARE_SERIAL(SevenSegment)
public:
	virtual void Serialize(CArchive& ar);
public:
	SevenSegment();
	void Draw(CDC* pDC)override;
	void Calculate() override;
};
#endif 