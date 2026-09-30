#include "game_field.h"
#include <stdexcept>

GameField::GameField() : _n(10), _m(10) {
    _field = new char* [_n];
    for (int i = 0; i < _n; ++i) {
        _field[i] = new char[_m];
        for (int j = 0; j < _m; ++j) {
            _field[i][j] = ' ';
        }
    }
}

GameField::~GameField() {
    for (int i = 0; i < _n; ++i) {
        delete[] _field[i];
    }
    delete[] _field;
}

int GameField::check_destroy(int row, int col) {
    int left = col;
    int right = col;
    while (left - 1 >= 0 && (_field[row][left - 1] == 'X' || _field[row][left - 1] == '*')) {
        --left;
    }
    while (right + 1 < _m && (_field[row][right + 1] == 'X' || _field[row][right + 1] == '*')) {
        ++right;
    }
    int up = row;
    int down = row;
    while (up - 1 >= 0 && (_field[up - 1][col] == 'X' || _field[up - 1][col] == '*')) {
        --up;
    }
    while (down + 1 < _n && (_field[down + 1][col] == 'X' || _field[down + 1][col] == '*')) {
        ++down;
    }

    int hLen = right - left + 1;
    int vLen = down - up + 1;

    if (hLen > 1 && vLen > 1) {
        return 0;
    }

    int len;
    int startR;
    int startC;
    int dr;
    int dc;
    if (hLen >= vLen) {
        len = hLen;
        startR = row;
        startC = left;
        dr = 0;
        dc = 1;
    }
    else {
        len = vLen;
        startR = up;
        startC = col;
        dr = 1;
        dc = 0;
    }

    for (int k = 0; k < len; ++k) {
        if (_field[startR + k * dr][startC + k * dc] != 'X') {
            return 0;
        }
    }
    return len;
}

void GameField::set(const Ship& ship) {
    if (is_collision(*this, ship)) {
        throw std::logic_error("Invalid input: incorrect move");
    }
    int r = ship.get_row() - 1;
    int c = ship.get_col() - 1;
    if (ship.get_direction() == Horizontal) {
        for (int k = 0; k < ship.get_size(); ++k) {
            _field[r][c + k] = '*';
        }
    }
    else {
        for (int k = 0; k < ship.get_size(); ++k) {
            _field[r + k][c] = '*';
        }
    }
}

State GameField::set(int row, char col) {
    if (row < 1 || row > _n || col < 'A' || col >= static_cast<char>('A' + _m)) {
        throw std::logic_error("Invalid input: incorrect move");
    }
    int r = row - 1;
    int c = col - 'A';
    char current = _field[r][c];
    if (current == '.' || current == 'X') {
        throw std::logic_error("Invalid input: incorrect move");
    }
    if (current == ' ') {
        _field[r][c] = '.';
        return Missed;
    }
    _field[r][c] = 'X';
    int destroyed = check_destroy(r, c);
    if (destroyed == 0) {
        return Hit;
    }
    if (destroyed == 1) {
        return BoatDestroyed;
    }
    if (destroyed == 2) {
        return DestroyersDestroyed;
    }
    if (destroyed == 3) {
        return CruisersDestroyed;
    }
    return BattleshipDestroyed;
}

std::string to_string(const GameField& field, bool show_ships = false) {
    std::string res;
    res += "  |";
    for (int j = 0; j < field._m; ++j) {
        if (j > 0) {
            res += ' ';
        }
        res += static_cast<char>('A' + j);
    }
    res += "|\n";
    res += "  +";
    for (int j = 0; j < 2 * field._m - 1; ++j) {
        res += '-';
    }
    res += "+\n";
    for (int i = 0; i < field._n; ++i) {
        res += std::to_string(i + 1);
        res += " |";
        for (int j = 0; j < field._m; ++j) {
            char ch = field._field[i][j];
            if (ch == '*' && !show_ships) {
                ch = ' ';
            }
            res += ch;
            res += '|';
        }
        res += '\n';
    }
    res += "  +";
    for (int j = 0; j < 2 * field._m - 1; ++j) {
        res += '-';
    }
    res += '+';
    return res;
}

bool is_collision(const GameField& field, const Ship& ship) {
    int r = ship.get_row() - 1;
    int c = ship.get_col() - 1;
    int size = ship.get_size();
    int dr = 0;
    int dc = 0;
    if (ship.get_direction() == Horizontal) {
        dc = 1;
    }
    else {
        dr = 1;
    }
    for (int k = 0; k < size; ++k) {
        int rr = r + k * dr;
        int cc = c + k * dc;
        if (rr < 0 || rr >= field._n || cc < 0 || cc >= field._m) {
            return true;
        }
        if (field._field[rr][cc] != ' ') {
            return true;
        }
        for (int di = -1; di <= 1; ++di) {
            for (int dj = -1; dj <= 1; ++dj) {
                if (di == 0 && dj == 0) {
                    continue;
                }
                int nr = rr + di;
                int nc = cc + dj;
                if (nr < 0 || nr >= field._n || nc < 0 || nc >= field._m) {
                    continue;
                }
                if (field._field[nr][nc] != ' ') {
                    return true;
                }
            }
        }
    }
    return false;
}