#pragma once
#include <string>
#include "../PositionLib/position.h"

enum Direction {
    Horizontal,
    Vertical
};

class Ship {
private:
    int _size;
    Position _position;
    Direction _direction;

    static bool is_collision(int size, Direction direction, const Position& position);

public:
    Ship() = delete;
    Ship(const Ship& other) = delete;
    Ship& operator=(const Ship& other) = delete;

    Ship(int size, Direction direction, const Position& position);
    Ship(int size, const Position& position);
    Ship(int size, char direction, int row, char col);

    inline int get_size() const noexcept { return _size; }
    inline int get_row() const noexcept { return _position.row(); }
    inline int get_col() const noexcept { return _position.col(); }
    inline Direction get_direction() const noexcept { return _direction; }

    void size(int size);
    void row(int row);
    void col(int col);
    void col(char col);
    void direction(Direction direction);
    void direction(char direction);
    void position(const Position& position);

    void rotate();

    friend std::string to_string(const Ship& ship);
};