#pragma once
#include <string>

class Position {
private:
	int _row;
	int _col;
	static const int _max_row = 10;
	static const int _max_col = 10;
public:
	Position();
	Position(int row, int col);
	Position(const Position& other);
	Position(const std::string& str);

	inline int row() const noexcept { return _row; }
	inline int col() const noexcept { return _col; }

	void row(int row);
	void col(int col);

	friend std::string to_string(const Position& pos);
	friend Position parse(const std::string& str);
};