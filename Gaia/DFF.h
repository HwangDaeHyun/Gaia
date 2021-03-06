#ifndef DFF_H_INCLUDE
#define DFF_H_INCLUDE
#include"GaiaObject.h"
#include"GaiaLLogic.h"

class DFF :public GaiaLLogic
{
	DECLARE_SERIAL(DFF)
public:
	virtual void Serialize(CArchive& ar);
public:
	DFF();
	inline void Draw(CDC* pDC)override;
	inline void Calculate() override;

};

#endif