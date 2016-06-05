#ifndef JKFF_H_INCLUDE
#define JKFF_H_INCLUDE
#include"GaiaObject.h"
#include"GaiaLLogic.h"

class JKFF :public GaiaLLogic
{
	DECLARE_SERIAL(JKFF)
public:
	virtual void Serialize(CArchive& ar);
public:
	JKFF();
	inline void Draw(CDC* pDC)override;
	inline void Calculate() override;

};

#endif