#include "stdafx.h"
#include "DblBufMaker.h"
DblBufMaker::DblBufMaker(CDC* pDC, CRect rect)
{
	this->m_bDC.CreateCompatibleDC(pDC);
	this->m_bmpBuffer.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	this->m_pOldBmp = (CBitmap*)this->m_bDC.SelectObject(&this->m_bmpBuffer);
	this->m_bDC.PatBlt(0, 0, rect.Width(), rect.Height(), WHITENESS);
}
DblBufMaker::~DblBufMaker()
{
	this->m_bDC.SelectObject(this->m_pOldBmp);
	this->m_bDC.DeleteDC();
	this->m_bmpBuffer.DeleteObject();
}
CDC& DblBufMaker::GetDC(){
		return this->m_bDC;
}
CBitmap* DblBufMaker::GetBitMap() {
	return &this->m_bmpBuffer;
}
