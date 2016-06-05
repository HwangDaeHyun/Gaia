#ifndef TFF_H_INCLUDE
#define TFF_H_INCLUDE
#include"GaiaObject.h"
#include"GaiaLLogic.h"

class TFF :public GaiaLLogic
{
	DECLARE_SERIAL(TFF)
public:
	virtual void Serialize(CArchive& ar);
public:
	TFF();
	inline void Draw(CDC* pDC)override;
	inline void Calculate() override;

};

#endif