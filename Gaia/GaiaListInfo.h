#ifndef GAIALISTINFO_H
#define GAIALISTINFO_H

#include"stdafx.h"
#include"GaiaRepo.h"

class GaiaListInfo{
public:
	GaiaListInfo(){
		this->grid.assign(GSIZE, vector<bool>(GSIZE, false));
	}
public:
	vector<GaiaObject*> obj_list;
	vector<PDV> edges;
	vector<CRect> inBtns = vector<CRect>();
	int dBoard[GSIZE][GSIZE];
	vector<vector<bool>> grid;
};

#endif