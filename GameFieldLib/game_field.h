#pragma once
#include <string>
#include <stdexcept>
#include "../PositionLib/position.h"
#include "../ShipLib/ship.h"

enum State {
    Missed,
    BoatDestroyed,
    DestroyersDestroyed,
    CruisersDestroyed,
    BattleshipDestroyed,
    Hit
};


class GameField {
private:
    char** _field;
    const int _n;
    const int _m;

    int check_destroy(int row, int col);

public:
    GameField();
    ~GameField();

    void set(const Ship& ship);
    State set(int row, char col);

    friend std::string to_string(const GameField& field, bool show_ships);
    friend bool is_collision(const GameField& field, const Ship& ship);
};

