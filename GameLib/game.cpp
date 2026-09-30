#include "game.h"
#include <sstream>
#include <cctype>

static void parse_col(char col) {
    char upper = std::toupper(static_cast<unsigned char>(col));
    if (upper < 'A' || upper > 'J') {
        throw std::logic_error("Invalid input: incorrect move");
    }
}

static void place_ships_from_string(Player& player, const std::string& input) {
    std::istringstream stream(input);
    std::string line;
    while (std::getline(stream, line)) {
        if (line.empty()) {
            continue;
        }
        std::istringstream line_stream(line);
        int size;
        char direction;
        int row;
        char col;
        if (!(line_stream >> size >> direction >> row >> col)) {
            throw std::logic_error("Invalid input: incorrect field");
        }
        Ship ship(size, direction, row, col);
        player.set_ship(ship);
    }
    if (!player.check_ready()) {
        throw std::logic_error("Invalid input: incorrect field");
    }
}

static void parse_move(const std::string& input, int& row, char& col) {
    std::istringstream stream(input);
    if (!(stream >> row >> col)) {
        throw std::logic_error("Invalid input: incorrect move");
    }
    parse_col(col);
}

Game::Game()
    : _user(), _computer() {
}

void Game::user_init(const std::string& input) {
    place_ships_from_string(_user, input);
}

void Game::computer_init(const std::string& input) {
    place_ships_from_string(_computer, input);
}

State Game::user_move(const std::string& input) {
    int row;
    char col;
    parse_move(input, row, col);
    return _computer.set_action(row, col);
}

State Game::computer_move() {
    for (int i = 0; i < 10; ++i) {
        try {
            return _user.set_action(i + 1, static_cast<char>('A' + i));
        }
        catch (const std::logic_error&) {}
    }
    for (int i = 0; i < 10; ++i) {
        try {
            return _user.set_action(i + 1, static_cast<char>('A' + (9 - i)));
        }
        catch (const std::logic_error&) {}
    }
    for (int r = 0; r < 10; ++r) {
        for (int c = 0; c < 10; ++c) {
            try {
                return _user.set_action(r + 1, static_cast<char>('A' + c));
            }
            catch (const std::logic_error&) {}
        }
    }
    throw std::logic_error("Invalid input: incorrect move");
}

bool Game::is_end() const noexcept {
    return _user.check_lose() || _computer.check_lose();
}

void Game::show_game_window() const {
    std::cout << "= COMPUTER GAME FIELD =" << std::endl;
    std::cout << std::endl;
    std::cout << to_string(_computer._gamefield, false) << std::endl;
    std::cout << std::endl;
    std::cout << "Ships Left:" << std::endl;
    std::cout << "* - " << _computer._alive_counts[0] << " "
        << "** - " << _computer._alive_counts[1] << " "
        << "*** - " << _computer._alive_counts[2] << " "
        << "**** - " << _computer._alive_counts[3] << std::endl;
    std::cout << std::endl;
    std::cout << "=== YOUR PLAY FIELD ===" << std::endl;
    std::cout << std::endl;
    std::cout << to_string(_user._gamefield, true) << std::endl;
    std::cout << std::endl;
    std::cout << "Ships Left:" << std::endl;
    std::cout << "* - " << _user._alive_counts[0] << " "
        << "** - " << _user._alive_counts[1] << " "
        << "*** - " << _user._alive_counts[2] << " "
        << "**** - " << _user._alive_counts[3] << std::endl;
}

void Game::start() {
    std::string user_input;
    std::string computer_input;
    std::string line;

    while (std::getline(std::cin, line)) {
        if (line.empty()) {
            break;
        }
        user_input += line;
        user_input += '\n';
    }

    while (std::getline(std::cin, line)) {
        if (line.empty()) {
            break;
        }
        computer_input += line;
        computer_input += '\n';
    }

    user_init(user_input);
    computer_init(computer_input);

    show_game_window();

    while (!is_end()) {
        bool user_turn = true;
        while (user_turn && !is_end()) {
            if (!std::getline(std::cin, line)) {
                break;
            }
            if (line.empty()) {
                continue;
            }
            State st = user_move(line);
            if (st == Missed) {
                user_turn = false;
            }
        }

        if (is_end()) {
            break;
        }

        bool computer_turn = true;
        while (computer_turn && !is_end()) {
            State st = computer_move();
            if (st == Missed) {
                computer_turn = false;
            }
        }
    }

    show_game_window();

    if (_computer.check_lose()) {
        std::cout << "USER WIN!" << std::endl;
    }
    else {
        std::cout << "COMPUTER WIN!" << std::endl;
    }
}