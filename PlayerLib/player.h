#pragma once
#include <string>
#include <stdexcept>
#include <iostream>
#include "../GameFieldLib/game_field.h"
#include "../ShipLib/ship.h"

class Player {
private:
    GameField _gamefield;
    int _placed_counts[4];
    int _alive_counts[4];
    static const int _max_ships_counts[4];

public:
    Player();
    Player(const Player& other) = delete;
    Player& operator=(const Player& other) = delete;

    void set_ship(const Ship& ship);
    State set_action(int row, char col);
    void show_field(bool show_ships = false) const;
    bool check_lose() const noexcept;
    bool check_ready() const noexcept;
};