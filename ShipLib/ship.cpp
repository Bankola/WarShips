#include "ship.h"
#include <stdexcept>
#include <cctype>

static int col_from_char(char col) {
    char upper = std::toupper(static_cast<unsigned char>(col));
    if (upper < 'A' || upper > 'J') {
        throw std::logic_error("Invalid argument");
    }
    return upper - 'A' + 1;
}

static Direction direction_from_char(char direction) {
    char upper = std::toupper(static_cast<unsigned char>(direction));
    if (upper == 'H') return Horizontal;
    if (upper == 'V') return Vertical;
    throw std::logic_error("Invalid argument");
}

bool Ship::is_collision(int size, Direction direction, const Position& position) {
    if (size < 1 || size > 4) {
        return true;
    }
    if (direction == Horizontal) {
        return position.col() + size - 1 > 10;
    }
    else {
        return position.row() + size - 1 > 10;
    }
}

Ship::Ship(int size, Direction direction, const Position& position) {
    if (size < 1 || size > 4 || is_collision(size, direction, position)) {
        throw std::logic_error("Invalid argument");
    }
    _size = size;
    _position = position;
    _direction = direction;
}

Ship::Ship(int size, const Position& position) {
    if (size < 1 || size > 4 || is_collision(size, Horizontal, position)) {
        throw std::logic_error("Invalid argument");
    }
    _size = size;
    _position = position;
    _direction = Horizontal;
}

Ship::Ship(int size, char direction, int row, char col) {
    Direction dir = direction_from_char(direction);
    int column = col_from_char(col);
    Position position(row, column);
    if (size < 1 || size > 4 || is_collision(size, dir, position)) {
        throw std::logic_error("Invalid argument");
    }
    _size = size;
    _position = position;
    _direction = dir;
}

void Ship::size(int size) {
    if (size < 1 || size > 4 || is_collision(size, _direction, _position)) {
        throw std::logic_error("Invalid argument");
    }
    _size = size;
}

void Ship::row(int row) {
    if (row < 1 || row > 10) {
        throw std::logic_error("Invalid argument");
    }
    Position newPosition(row, _position.col());
    if (is_collision(_size, _direction, newPosition)) {
        throw std::logic_error("Invalid argument");
    }
    _position = newPosition;
}

void Ship::col(int col) {
    if (col < 1 || col > 10) {
        throw std::logic_error("Invalid argument");
    }
    Position newPosition(_position.row(), col);
    if (is_collision(_size, _direction, newPosition)) {
        throw std::logic_error("Invalid argument");
    }
    _position = newPosition;
}

void Ship::col(char col) {
    this ->col(col_from_char(col));
}

void Ship::direction(Direction direction) {
    if (is_collision(_size, direction, _position)) {
        throw std::logic_error("Invalid argument");
    }
    _direction = direction;
}

void Ship::direction(char direction) {
    this->direction(direction_from_char(direction));
}

void Ship::position(const Position& position) {
    if (is_collision(_size, _direction, position)) {
        throw std::logic_error("Invalid argument");
    }
    _position = position;
}

void Ship::rotate() {
    Direction newDirection;
    if (_direction == Horizontal) {
        newDirection = Vertical;
    }
    else {
        newDirection = Horizontal;
    }
    if (is_collision(_size, newDirection, _position)) {
        return;
    }
    _direction = newDirection;
}

std::string to_string(const Ship& ship) {
    std::string res;
    res += "Ship(size=";
    res += std::to_string(ship._size);
    res += ", direction=";
    if (ship._direction == Horizontal) {
        res += "Horizontal";
    }
    else {
        res += "Vertical";
    }
    res += ", position=";
    res += to_string(ship._position);
    res += ")";
    return res;
}