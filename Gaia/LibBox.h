#pragma once

#ifndef	LIB_BOX_H_7DF_INCLUDE
#define LIB_BOX_H_7DF_INCLUDE
#include"GaiaLLogic.h"
#include"GaiaObject.h"
class LibBox : public GaiaLLogic
{
public:
	int in_size = 0;
	int out_size = 0;
	int clk_size = 0;
	int mx_sz;
	vector<vector<int>> result;
	vector<vector<int>> clk_result;
	vector<vector<int>> cal;
	LibBox();
	LibBox(int in_size, int out_size);
	void Draw(CDC* pDC)override;
	void mkLib();
	void Calculate() override;
};
#endif
