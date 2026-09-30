#pragma once
#include <string>
#include <stdexcept>
#include <iostream>
#include "../PlayerLib/player.h"

class Game {
private:
    Player _user;
    Player _computer;

    void user_init(const std::string& input);
    void computer_init(const std::string& input);
    State user_move(const std::string& input);
    State computer_move();
    bool is_end() const noexcept;
    void show_game_window() const;

public:
    Game();
    Game(const Game& other) = delete;
    Game& operator=(const Game& other) = delete;

    void start();
};