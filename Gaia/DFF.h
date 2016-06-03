#ifndef DFF_H_INCLUDE
#define DFF_H_INCLUDE
#include"GaiaObject.h"
#include"GaiaLLogic.h"

class DFF :public GaiaLLogic
{
public:
	DFF();
	inline void Draw(CDC* pDC)override;
	inline void Calculate() override;

};

#endif