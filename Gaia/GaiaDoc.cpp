
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
#include"AndGate.h"
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
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.	

		auto& e = SingleTon<GaiaDrawGrid>::use()->objects;
		auto&edges = SingleTon<GaiaDrawGrid>::use()->edges;
		auto&inBtns = SingleTon<GaiaDrawGrid>::use()->inBtns;
		auto&db = SingleTon<GaiaDrawGrid>::use()->dBoard;
		auto&grid = SingleTon<GaiaDrawGrid>::use()->grid;
		//object
		ar << e.size();
		for (int i = 0; i < e.size(); i++){
			ar << e.at(i)->objKind;
			ar << e[i];
		}
		//edges
		ar << edges.size();
		for (int i = 0; i < edges.size(); i++){
			ar << edges[i].first.first;
			ar << edges[i].first.second;
			ar << edges[i].second.size();
			for (int j = 0; j < edges[i].second.size(); j++){
				ar << edges[i].second[j];
			}
		}
		//inBtn
		ar << inBtns.size();
		for (int i = 0; i < inBtns.size(); i++){
			ar << inBtns[i];
		}
		//dBoard
		for (int i = 0; i < GSIZE; i++){
			for (int j = 0; j < GSIZE; j++){
				ar << db[i][j];
			}
		}
		//grid
		for (int i = 0; i < GSIZE; i++){
			for (int j = 0; j < GSIZE; j++){
				ar << (int)grid[i][j];

			}
		}
	}
	else{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
		auto& e = SingleTon<GaiaDrawGrid>::use()->objects;
		auto& edges = SingleTon<GaiaDrawGrid>::use()->edges;
		auto& grid = SingleTon<GaiaDrawGrid>::use()->grid;
		auto& inBtns = SingleTon<GaiaDrawGrid>::use()->inBtns;
		auto& db = SingleTon<GaiaDrawGrid>::use()->dBoard;
		//grid.~vector();
		e.clear();
		edges.clear();
		inBtns.clear();
		grid.assign(GSIZE, vector<bool>(GSIZE, false));
		int size;
		int tempKind;
		ar >> size;
		GaiaObject* obj;
		ObjectKind objKind;
		//objets
		for (int i = 0; i < size; i++){
			ar >> tempKind;
			objKind = (ObjectKind)tempKind;
			switch (objKind){
			case ObjectKind::AND:
				obj = new AndGate();
				ar >> obj;
				e.push_back(obj);
				break;
			}
		}
		//edges
		PDV tempEdge;
		int edgeSize;
		int wayCnt;
		ar >> edgeSize;
		for (int i = 0; i < edgeSize; i++){
			ar >> tempEdge.first.first;
			ar >> tempEdge.first.second;
			ar >> wayCnt;
			for (int j = 0; j < wayCnt; j++){
				CRect tempWay;
				ar >> tempWay;
				tempEdge.second.push_back(tempWay);
			}
			edges.push_back(tempEdge);
		}
		//btn
		int btnCnt;
		ar >> btnCnt;
		CRect tempBtn;
		for (int i = 0; i < btnCnt; i++){
			ar >> tempBtn;
			inBtns.push_back(tempBtn);
		}
		//dboard
		for (int i = 0; i < GSIZE; i++){
			for (int j = 0; j < GSIZE; j++){
				ar >> (int)db[i][j];
			}
		}
		//grid
		int temp;
		for (int i = 0; i < GSIZE; i++){
			for (int j = 0; j < GSIZE; j++){
				ar >> temp;
				grid[i][j] = (bool)temp;
			}
		}

		SingleTon<GaiaLayoutRepo>::use()->views[0]->Invalidate();
		SingleTon<GaiaLayoutRepo>::use()->views[1]->Invalidate();
		SingleTon<GaiaLayoutRepo>::use()->views[2]->Invalidate();
		SingleTon<GaiaLayoutRepo>::use()->views[3]->Invalidate();

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

		}

	}
	
	return TRUE;
}
