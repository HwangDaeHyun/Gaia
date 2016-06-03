
// GaiaDoc.cpp : GaiaDoc Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "Gaia.h"
#endif

#include "GaiaDoc.h"

#include <propkey.h>

#include"GaiaDrawView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// GaiaDoc

IMPLEMENT_DYNCREATE(GaiaDoc, CDocument)

BEGIN_MESSAGE_MAP(GaiaDoc, CDocument)
END_MESSAGE_MAP()


// GaiaDoc ����/�Ҹ�

GaiaDoc::GaiaDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

}

GaiaDoc::~GaiaDoc()
{
}

BOOL GaiaDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// GaiaDoc serialization

void GaiaDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		printf("AR <<<<<<< \n");
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.	
		auto& e = SingleTon<GaiaDrawGrid>::use()->objects;

		for (int i = 0; i < e.size(); i++){
			GaiaObject* obj = e[i];
			ar << 10;
			ar << obj;

		}
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
		auto& e = SingleTon<GaiaDrawGrid>::use()->objects;
		e.clear();
		printf("ARRR >> \n");
		POSITION pos = GetFirstViewPosition();
		GaiaDrawView* dr = (GaiaDrawView*)m_viewList.GetHead();

		int sz;
		int x, y;
		GaiaObject* obj;
		ar >> sz;
		printf("sz : %d", sz);
		int tp;
		for (int i = 0; i < sz; i++){
			ar >> tp;
//			ar >> obj;
			ar >> x;
			ar >> y;

		}

	}
}

#ifdef SHARED_HANDLERS

// ����� �׸��� �����մϴ�.
void GaiaDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// ������ �����͸� �׸����� �� �ڵ带 �����Ͻʽÿ�.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// �˻� ó���⸦ �����մϴ�.
void GaiaDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������ �����Ϳ��� �˻� �������� �����մϴ�.
	// ������ �κ��� ";"�� ���еǾ�� �մϴ�.

	// ��: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void GaiaDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// GaiaDoc ����

#ifdef _DEBUG
void GaiaDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void GaiaDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// GaiaDoc ���


BOOL GaiaDoc::OnSaveDocument()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	printf("SAAAAAAAAAVE\n");
	CFileDialog fileDlg(FALSE);
	CFile f;
	CFileException e;
	CString strPathName;
	if (fileDlg.DoModal() == IDOK){
		strPathName = fileDlg.GetPathName();
		CString temp;
		temp.Format(L"%s%s", fileDlg.GetPathName(), L".gaia");
		if (!f.Open(temp, CFile::modeReadWrite | CFile::modeCreate, &e)){
			e.ReportError();
		}
		else{
			CArchive ar(&f, CArchive::store);
			printf("%s  \n", temp);
			Serialize(ar);
		}
	}


	return FALSE;
}


BOOL GaiaDoc::OnOpenDocument()
{
	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	printf("DDDDDOCN\n");
	CFileDialog fileDlg(TRUE);
	if (fileDlg.DoModal() == IDOK){
		auto& o = SingleTon<GaiaDrawGrid>::use()->objects;
		o.clear();
		CString strPath = fileDlg.GetPathName();
		CFile f;
		CFileException e;
		if (!f.Open(strPath, CFile::modeRead, &e)){
			e.ReportError();
		}
		else{
			CArchive ar(&f, CArchive::load);
			printf("%s\n", strPath);
			Serialize(ar);
			SingleTon<GaiaLayoutRepo>::use()->views[0]->Invalidate();
		}

	}
	return TRUE;
}
