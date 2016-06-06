
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
#include"OrGate.h"
#include"NotGate.h"
#include"XorGate.h"
#include"NandGate.h"
#include"NorGate.h"
#include"InputBtn.h"
#include"OutLamp.h"
#include"DFF.h"
#include"LibBox.h"
#include "SevenSegment.h"
#include"ClockCycle.h"
#include"TFF.h"
#include"JKFF.h""

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// GaiaDoc

IMPLEMENT_DYNCREATE(GaiaDoc, CDocument)

BEGIN_MESSAGE_MAP(GaiaDoc, CDocument)
	ON_COMMAND(ID_EDIT_UNDO, Undo)
	ON_COMMAND(ID_EDIT_REDO, Redo)
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
		auto& libName = SingleTon<GaiaGateInfo>::use()->libName;
		auto& lib_objects = SingleTon<GaiaDrawGrid>::use()->lib_objects;
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
		//
		//Gaiagateinfo -> libname
		ar << libName.size();
		for (int i = 0; i < libName.size(); i++){
			ar << libName[i];
		}
		// lib object
		ar << lib_objects.size();
		for (int i = 0; i < lib_objects.size(); i++){
			ar << lib_objects[i];
		}
	}
	else{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
		auto& e = SingleTon<GaiaDrawGrid>::use()->objects;
		auto& edges = SingleTon<GaiaDrawGrid>::use()->edges;
		auto& grid = SingleTon<GaiaDrawGrid>::use()->grid;
		auto& inBtns = SingleTon<GaiaDrawGrid>::use()->inBtns;
		auto& db = SingleTon<GaiaDrawGrid>::use()->dBoard;
		auto& libName = SingleTon<GaiaGateInfo>::use()->libName;
		libName.clear();
		SingleTon<GaiaDrawGrid>::use()->sel_objects.clear();
		SingleTon<GaiaDrawGrid>::use()->sel_idx.clear();
		auto& lib_obj = SingleTon<GaiaDrawGrid>::use()->lib_objects;
		lib_obj.clear();
		
		while (SingleTon<GaiaTableInfo>::use()->contents.size() > 2){
			SingleTon<GaiaTableInfo>::use()->contents.pop_back();
		}
		SingleTon<GaiaTableInfo>::use()->isSel = false;
		SingleTon<GaiaTableInfo>::use()->selNum = -1;
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
			case ObjectKind::LIBBOX:
				obj = new LibBox();
				ar >> obj;
				e.push_back(obj);
				break;
			case ObjectKind::AND:
				obj = new AndGate();
				ar >> obj;
				e.push_back(obj);
				break;
			case ObjectKind::NOT:
				obj = new NotGate();
				ar >> obj;
				e.push_back(obj);
				break;
			case ObjectKind::NAND:
				obj = new NandGate();
				ar >> obj;
				e.push_back(obj);
				break;
			case ObjectKind::NOR:
				obj = new NorGate();
				ar >> obj;
				e.push_back(obj);
				break;
			case ObjectKind::XOR:
				obj = new XorGate();
				ar >> obj;
				e.push_back(obj);
				break;
			case ObjectKind::DFLIP:
				obj = new DFF();
				ar >> obj;
				e.push_back(obj);
				break;
			case ObjectKind::JKFLIP:
				obj = new JKFF();
				ar >> obj;
				e.push_back(obj);
				break;
			case ObjectKind::TFLIP:
				obj = new TFF();
				ar >> obj;
				e.push_back(obj);
				break;
			case ObjectKind::SEVENSEG:
				obj = new SevenSegment();
				ar >> obj;
				e.push_back(obj);
				break;
			case ObjectKind::INBUTTON:
				obj = new InputBtn();
				ar >> obj;
				e.push_back(obj);
				break;
			case ObjectKind::CLOCKCYCLE:
				obj = new ClockCycle();
				ar >> obj;
				e.push_back(obj);
				break;
			case ObjectKind::OUTLAMP:
				obj = new OutLamp();
				ar >> obj;
				e.push_back(obj);
				break;
			case ObjectKind::OR:
				obj = new OrGate();
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
			tempEdge.second.clear();
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
		//Gaiagateinfo -> libname
		int nameSize;
		ar >> nameSize;
		CString tempName;
		for (int i = 0; i < nameSize; i++){
			ar >> tempName;
			libName.push_back(tempName);
			
		}
		int libSize;
		// lib object
		ar >> libSize;
		GaiaObject* libT;
		for (int i = 0; i < libSize; i++){
			libT = new LibBox();
			ar >> libT;
			lib_obj.push_back(libT);
		}
		

		SingleTon<GaiaLayoutRepo>::use()->views[0]->Invalidate();


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
	printf("-----%d------", SingleTon<GaiaDrawGrid>::use()->objects.size());
	return TRUE;
}
void GaiaDoc::Undo(){
	auto& g = SingleTon<GaiaDrawGrid>::use()->grid;
	if (!this->gaia_list.empty()){
		GaiaListInfo* forRedo = new GaiaListInfo();
		memcpy(forRedo->dBoard, SingleTon<GaiaDrawGrid>::use()->dBoard, GSIZE*GSIZE);
		for (int i = 0; i < SingleTon<GaiaDrawGrid>::use()->edges.size(); i++){
			forRedo->edges.push_back(SingleTon<GaiaDrawGrid>::use()->edges[i]);
		}
		forRedo->edges = SingleTon<GaiaDrawGrid>::use()->edges;
		for (int i = 0; i < SingleTon<GaiaDrawGrid>::use()->inBtns.size(); i++){
			forRedo->inBtns.push_back(SingleTon<GaiaDrawGrid>::use()->inBtns[i]);
		}
		bool temp;
		for (int i = 0; i < GSIZE; i++){
			for (int j = 0; j <GSIZE; j++){
				temp = g[i][j];
				forRedo->grid[i][j] = temp;
			}
		}
		//memcpy(&(forRedo->grid[0]), &(SingleTon<GaiaDrawGrid>::use()->grid[0]), sizeof(SingleTon<GaiaDrawGrid>::use()->grid));
		forRedo->obj_list.clear();
		for (int i = 0; i < SingleTon<GaiaDrawGrid>::use()->objects.size(); i++){
			forRedo->obj_list.push_back(SingleTon<GaiaDrawGrid>::use()->objects[i]);
		}
		this->redo_list.push_back(forRedo);
		if (redo_list.size()>100){
			redo_list.pop_front();
		}
		/////////////
		GaiaListInfo* node;
		node = this->gaia_list.back();
		memcpy(SingleTon<GaiaDrawGrid>::use()->dBoard, (node)->dBoard, sizeof(GSIZE*GSIZE));
		SingleTon<GaiaDrawGrid>::use()->edges = (node)->edges;
		for (int i = 0; i < GSIZE; i++){
			for (int j = 0; j < GSIZE; j++){
				temp = (node)->grid[i][j];
				g[i][j] = temp;

			}

		}
		/*for (int i = 0; i <SingleTon<GaiaDrawGrid>::use()->grid.size(); i++){
		for (int j = 0; j < SingleTon<GaiaDrawGrid>::use()->grid[i].size(); j++){
		SingleTon<GaiaDrawGrid>::use()->grid[i][j] = (node)->grid[i][j];
		}
		}*/
		SingleTon<GaiaDrawGrid>::use()->inBtns = (node)->inBtns;
		SingleTon<GaiaDrawGrid>::use()->objects = (node)->obj_list;
		this->gaia_list.pop_back();
		SingleTon<GaiaLayoutRepo>::use()->views[0]->Invalidate();
	}


}

void GaiaDoc::Redo(){
	GaiaListInfo* node;
	auto& g = SingleTon<GaiaDrawGrid>::use()->grid;
	if (!redo_list.empty()){
		/*memcpy(node->dBoard, redo_list.back()->dBoard, sizeof(GSIZE*GSIZE));
		for (int i = 0; i < redo_list.back()->edges.size(); i++){
		node->edges.push_back(redo_list.back()->edges[i]);
		}
		bool temp;
		for (int i = 0; i < GSIZE; i++){
		for (int j = 0; j < GSIZE; j++){
		temp = redo_list.back()->grid[i][j];
		(node)->grid[i][j] =temp;
		}
		}
		for (int i = 0; i < redo_list.back()->inBtns.size(); i++){
		node->inBtns.push_back(redo_list.back()->inBtns[i]);
		}
		for (int i = 0; i < redo_list.back()->obj_list.size(); i++){
		node->obj_list.push_back(redo_list.back()->obj_list[i]);
		}

		memcpy(SingleTon<GaiaDrawGrid>::use()->dBoard, (node)->dBoard, sizeof(GSIZE*GSIZE));
		SingleTon<GaiaDrawGrid>::use()->edges = (node)->edges;

		for (int i = 0; i < GSIZE; i++){
		for (int j = 0; j < GSIZE; j++){
		temp = (node)->grid[i][j];
		g[i][j] = temp;
		}
		}*/
		this->PushGaiaList();
		//memcpy(&(SingleTon<GaiaDrawGrid>::use()->grid[0]), &(node->grid[0]), sizeof(SingleTon<GaiaDrawGrid>::use()->grid));
		/*
		SingleTon<GaiaDrawGrid>::use()->inBtns = (node)->inBtns;
		auto& obj = SingleTon<GaiaDrawGrid>::use()->objects;
		obj.clear();
		for (int i = 0; i < (node)->obj_list.size(); i++){
		obj.push_back(node->obj_list[i]);
		}*/
		node = this->redo_list.back();
		memcpy(SingleTon<GaiaDrawGrid>::use()->dBoard, (node)->dBoard, sizeof(GSIZE*GSIZE));
		bool temp;
		SingleTon<GaiaDrawGrid>::use()->edges = (node)->edges;
		for (int i = 0; i < GSIZE; i++){
			for (int j = 0; j < GSIZE; j++){
				temp = (node)->grid[i][j];
				g[i][j] = temp;
			}
		}
		SingleTon<GaiaDrawGrid>::use()->inBtns = (node)->inBtns;
		SingleTon<GaiaDrawGrid>::use()->objects = (node)->obj_list;

		redo_list.pop_back();
		SingleTon<GaiaLayoutRepo>::use()->views[0]->Invalidate();
	}


}
void GaiaDoc::PushGaiaList(){
	GaiaListInfo* myList = new GaiaListInfo();
	auto& g = SingleTon<GaiaDrawGrid>::use()->grid;
	memcpy(myList->dBoard, SingleTon<GaiaDrawGrid>::use()->dBoard, GSIZE*GSIZE);
	myList->edges.clear();
	for (int i = 0; i < SingleTon<GaiaDrawGrid>::use()->edges.size(); i++){
		myList->edges.push_back(SingleTon<GaiaDrawGrid>::use()->edges[i]);
	}
	for (int i = 0; i < SingleTon<GaiaDrawGrid>::use()->inBtns.size(); i++){
		myList->inBtns.push_back(SingleTon<GaiaDrawGrid>::use()->inBtns[i]);
	}
	bool temp;
	for (int i = 0; i < GSIZE; i++){
		for (int j = 0; j < GSIZE; j++){
			temp = g[i][j];
			myList->grid[i][j] = temp;
		}
	}
	myList->obj_list.clear();
	//memcpy(&(myList.grid[0]), &(SingleTon<GaiaDrawGrid>::use()->grid[0]), sizeof(SingleTon<GaiaDrawGrid>::use()->grid));
	for (int i = 0; i < SingleTon<GaiaDrawGrid>::use()->objects.size(); i++){
		myList->obj_list.push_back(SingleTon<GaiaDrawGrid>::use()->objects[i]);
	}
	this->gaia_list.push_back(myList);
	if (gaia_list.size()>100){
		gaia_list.pop_front();
	}
}
void GaiaDoc::SetTempGaiaListNode(){
	this->tempNode = new GaiaListInfo();
	auto& g = SingleTon<GaiaDrawGrid>::use()->grid;
	memcpy(this->tempNode->dBoard, SingleTon<GaiaDrawGrid>::use()->dBoard, GSIZE*GSIZE);
	this->tempNode->edges.clear();
	for (int i = 0; i < SingleTon<GaiaDrawGrid>::use()->edges.size(); i++){
		this->tempNode->edges.push_back(SingleTon<GaiaDrawGrid>::use()->edges[i]);
	}
	for (int i = 0; i < SingleTon<GaiaDrawGrid>::use()->inBtns.size(); i++){
		this->tempNode->inBtns.push_back(SingleTon<GaiaDrawGrid>::use()->inBtns[i]);
	}
	bool temp;
	for (int i = 0; i < GSIZE; i++){
		for (int j = 0; j < GSIZE; j++){
			temp = g[i][j];
			this->tempNode->grid[i][j] = temp;
		}
	}
	this->tempNode->obj_list.clear();
	//memcpy(&(this->tempNode.grid[0]), &(SingleTon<GaiaDrawGrid>::use()->grid[0]), sizeof(SingleTon<GaiaDrawGrid>::use()->grid));
	for (int i = 0; i < SingleTon<GaiaDrawGrid>::use()->objects.size(); i++){
		this->tempNode->obj_list.push_back(SingleTon<GaiaDrawGrid>::use()->objects[i]);
	}
}
void GaiaDoc::PushTempNode(){
	if (this->tempNode != nullptr){
		this->gaia_list.push_back(this->tempNode);
	}
	this->tempNode = nullptr;
}