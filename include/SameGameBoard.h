#pragma once

class CSameGameBoard
{
public:
	CSameGameBoard(void); // Конструктор по-умолчанию

	CSameGameBoard(const CSameGameBoard& board); // Конструктор глубокого копирования

	~CSameGameBoard(void); // Деструктор

	void SetupBoard(void); // Функция для рандомной расстановкиблоков в начале игры

	COLORREF GetBoardSpace(int row, int col); // Получаем цвет в определённом участке игрового поля

	// Функции доступа для получения/изменения размера игровой доски
	int GetWidth(void) const { return m_nWidth; }
	void SetWidth(int nWidth) { m_nWidth = (nWidth >= 3) ? nWidth : 3; }

	int GetHeight(void) const { return m_nHeight; }
	void SetHeight(int nHeight) { m_nHeight = (nHeight >= 3) ? nHeight : 3; }

	int GetColumns(void) const { return m_nColumns; }
	void SetColumns(int nColumns) { m_nColumns = (nColumns >= 5) ? nColumns : 5; }

	int GetRows(void) const { return m_nRows; }
	void SetRows(int nRows) { m_nRows = (nRows >= 5) ? nRows : 5; }


	// Геттеры и Сеттеры для количества цветов
	int GetNumColors(void) { return m_nColors; }
	void SetNumColors(int nColors) { m_nColors = (nColors >= 3 && nColors <= 7) ? nColors : m_nColors; }

	// Мы закончили игру?
	bool IsGameOver(void) const;

	// Подсчет количества оставшихся блоков
	int GetRemainingCount(void) const { return m_nRemaining; }

	// Функция для удаления всех примыкающих блоков
	int DeleteBlocks(int row, int col);

	void DeleteBoard(void); // Функция для удаления игрового поля и освобождение памяти
private:
	void CreateBoard(void); // Функция для создания игрового поля и выделения памяти под него

	// Перечисление с вариантами направления (откуда мы пришли) потребуется для удаления блоков
	enum Direction
	{
		DIRECTION_UP,
		DIRECTION_DOWN,
		DIRECTION_LEFT,
		DIRECTION_RIGHT
	};

	// Вспомогательная рекурсивная функция для удаления примыкающих блоков
	int DeleteNeighborBlocks(int row, int col, int color, Direction direction);

	// Функция для сжатия доски после того, как были удалены блоки
	void CompactBoard(void);

	int** m_arrBoard; // Указатель на двумерный массив

	static COLORREF m_arrColors[8]; // Список цветов, 0 - это цвет фона, 1-7 - это цвета блоков

	// Информация о размере игрового поля
	int m_nColumns;
	int m_nRows;
	int m_nHeight;
	int m_nWidth;

	// Количество оставшихся блоков
	int m_nRemaining;

	// Количество цветов
	int m_nColors;
};