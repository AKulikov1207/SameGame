// SameGameDoc.cpp: реализация класса CSameGameDoc 
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "SameGame.h"
#endif

#include "SameGameDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSameGameDoc

IMPLEMENT_DYNCREATE(CSameGameDoc, CDocument)

BEGIN_MESSAGE_MAP(CSameGameDoc, CDocument)
END_MESSAGE_MAP()


// Создание или уничтожение CSameGameDoc
CSameGameDoc::CSameGameDoc() noexcept
{
	// Здесь всегда должна быть игровая доска
	m_board = new CSameGameBoard();
}

CSameGameDoc::~CSameGameDoc()
{
	// Удаляем текущую игровую доску
	delete m_board;
	// Удаляем все из стека Отмена
	ClearUndo();
	// Удаляем все из стека Повтор
	ClearRedo();
}

BOOL CSameGameDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// Установка (или сброс) параметров доски
	m_board->SetupBoard();

	// Очистка стеков Отмена/Повтор
	ClearUndo();
	ClearRedo();

	return TRUE;
}

void CSameGameDoc::SetNumColors(int nColors)
{
	// Сначала задаем количество цветов...
	m_board->SetNumColors(nColors);
	// ...затем устанавливаем параметры игровой доски
	m_board->SetupBoard();
}

int CSameGameDoc::DeleteBlocks(int row, int col)
{
	// Сохранение текущего состояния доски в стеке Отмена
	m_undo.push(new CSameGameBoard(*m_board));
	// Очищаем стек Повтор
	ClearRedo();
	// Затем удаляем блоки
	int blocks = m_board->DeleteBlocks(row, col);
	// Очищаем стек Отмена в конце игры
	if (m_board->IsGameOver())
		ClearUndo();
	// Возвращаем количество блоков
	return blocks;
}

void CSameGameDoc::UndoLast() 
{
	// Смотрим, есть ли у нас что-нибудь в стеке Отмена
	if (m_undo.empty())
		return;
	// Помещаем текущую игровую доску в стек Повтор
	m_redo.push(m_board);
	// Назначаем верхний элемент стека Отмена текущим
	m_board = m_undo.top();
	m_undo.pop();
}

bool CSameGameDoc::CanUndo()
{
	// Убеждаемся, что у нас есть возможность выполнить отмену действия
	return !m_undo.empty();
}

void CSameGameDoc::RedoLast()
{
	// Смотрим, есть ли у нас что нибудь в стеке Повтор
	if (m_redo.empty())
		return;
	// Помещаем текущую игровую доску в стек Отмена
	m_undo.push(m_board);
	// Назначаем верхний элемент стека Повтор текущим
	m_board = m_redo.top();
	m_redo.pop();
}

bool CSameGameDoc::CanRedo()
{
	// Убеждаемся, сможем ли мы выполнить повтор действия(не пуст ли стек)
	return !m_redo.empty();
}

void CSameGameDoc::ClearUndo()
{
	// Очищаем стек Отмена
	while (!m_undo.empty())
	{
		delete m_undo.top();
		m_undo.pop();
	}
}

void CSameGameDoc::ClearRedo()
{
	// Очищаем стек Повтор
	while (!m_redo.empty())
	{
		delete m_redo.top();
		m_redo.pop();
	}
}

// Сериализация CSameGameDoc

void CSameGameDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: добавьте код сохранения
	}
	else
	{
		// TODO: добавьте код загрузки
	}
}

#ifdef SHARED_HANDLERS

// Поддержка для эскизов
void CSameGameDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Измените этот код для отображения данных документа
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Поддержка обработчиков поиска
void CSameGameDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Задание содержимого поиска из данных документа.
	// Части содержимого должны разделяться точкой с запятой ";"

	// Например:  strSearchContent = _T("точка;прямоугольник;круг;объект ole;");
	SetSearchContent(strSearchContent);
}

void CSameGameDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// Диагностика CSameGameDoc

#ifdef _DEBUG
void CSameGameDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSameGameDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

// Команды CSameGameDoc
