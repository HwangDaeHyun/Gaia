#ifndef DBLBUFMAKER_H
#define DBLBUFMAKER_H
#include <afxwin.h>
class DblBufMaker{
protected:
	CDC m_bDC;
	CBitmap m_bmpBuffer;
	CBitmap* m_pOldBmp;
public:
	DblBufMaker(CDC* pDC, CRect rect);
	~DblBufMaker();
	CDC& GetDC();
	CBitmap* GetBitMap();
private:
	DblBufMaker(const DblBufMaker&) = delete;
	DblBufMaker& operator=(const DblBufMaker&) = delete;
};
#endif