#include "stdafx.h"
#include "Gaia.h"
#include "GaiaMainView.h"

IMPLEMENT_DYNCREATE(GaiaMainView, GaiaCView)
GaiaMainView::GaiaMainView()
{
}


GaiaMainView::~GaiaMainView()
{
}
void GaiaMainView::DrawSplitterBar() {
	this->OnNcPaint();
}
BEGIN_MESSAGE_MAP(GaiaMainView, GaiaCView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_NCPAINT()
END_MESSAGE_MAP()