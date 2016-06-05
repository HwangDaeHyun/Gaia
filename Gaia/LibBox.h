#pragma once

#ifndef	LIB_BOX_H_7DF_INCLUDE
#define LIB_BOX_H_7DF_INCLUDE
#include"GaiaLLogic.h"
#include"GaiaObject.h"
class LibBox : public GaiaLLogic
{
	DECLARE_SERIAL(LibBox);
public:
	virtual void Serialize(CArchive& ar);
public:
	LibBox();
	LibBox(CString name);
	LibBox(int sel);
	void Draw(CDC* pDC)override;
	void mkLib();
	void Calculate() override;
};


#endif
