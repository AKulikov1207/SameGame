// SameGameDoc.h: интерфейс класса CSameGameDoc 
//

#pragma once
#include "SameGameBoard.h"
#include <stack>

class CSameGameDoc : public CDocument
{
protected: // создать только из сериализации
	CSameGameDoc() noexcept;
	DECLARE_DYNCREATE(CSameGameDoc)

// Атрибуты
public:

// Операции
public:
	// Геттеры для получения информации о параметрах игрового поля
	COLORREF GetBoardSpace(int row, int col)
	{
		return m_board->GetBoardSpace(row, col);
	}
	void SetupBoard(void) { m_board->SetupBoard(); }

	int GetWidth(void) { return m_board->GetWidth(); }
	void SetWidth(int nWidth) { m_board->SetWidth(nWidth); }

	int GetHeight(void) { return m_board->GetHeight(); }
	void SetHeight(int nHeight) { m_board->SetHeight(nHeight); }

	int GetColumns(void) { return m_board->GetColumns(); }
	void SetColumns(int nColumns) { m_board->SetColumns(nColumns); }

	int GetRows(void) { return m_board->GetRows(); }
	void SetRows(int nRows) { m_board->SetRows(nRows); }

	void DeleteBoard(void) { m_board->DeleteBoard(); }
	bool IsGameOver() { return m_board->IsGameOver(); }

	int DeleteBlocks(int row, int col); //{ return m_board->DeleteBlocks(row, col); }
	int GetRemainingCount() { return m_board->GetRemainingCount(); }
	int GetNumColors() { return m_board->GetNumColors(); }
	void SetNumColors(int nColors);
	//  Функции Отмены/Повтора 
	void UndoLast();
	bool CanUndo();
	void RedoLast();
	bool CanRedo();

// Переопределение
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Реализация
public:
	virtual ~CSameGameDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	// Функции очистки стеков Отмена/Повтор
	void ClearUndo();
	void ClearRedo();

	// Экземпляр класса нашей игровой доски
	CSameGameBoard *m_board;
	// Стек "Отмена"
	std::stack<CSameGameBoard*> m_undo;
	// Стек "Повтор"
	std::stack<CSameGameBoard*> m_redo;

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
