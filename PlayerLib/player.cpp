#include "player.h"

const int Player::_max_ships_counts[4] = { 4, 3, 2, 1 };

Player::Player() : _gamefield() {
    for (int i = 0; i < 4; ++i) {
        _placed_counts[i] = 0;
        _alive_counts[i] = 0;
    }
}

void Player::set_ship(const Ship& ship) {
    int size = ship.get_size();
    if (size < 1 || size > 4) {
        throw std::logic_error("Invalid input: incorrect field");
    }
    if (_placed_counts[size - 1] >= _max_ships_counts[size - 1]) {
        throw std::logic_error("Invalid input: incorrect field");
    }
    _gamefield.set(ship);
    _placed_counts[size - 1]++;
    _alive_counts[size - 1]++;
}

State Player::set_action(int row, char col) {
    State result = _gamefield.set(row, col);

    if (result == BoatDestroyed) {
        _alive_counts[0]--;
    }
    else if (result == DestroyersDestroyed) {
        _alive_counts[1]--;
    }
    else if (result == CruisersDestroyed) {
        _alive_counts[2]--;
    }
    else if (result == BattleshipDestroyed) {
        _alive_counts[3]--;
    }

    return result;
}

void Player::show_field(bool show_ships) const {
    std::cout << to_string(_gamefield, show_ships) << std::endl;
    std::cout << "Ships Left:" << std::endl;
    std::cout << "* - " << _alive_counts[0] << " "
        << "** - " << _alive_counts[1] << " "
        << "*** - " << _alive_counts[2] << " "
        << "**** - " << _alive_counts[3] << std::endl;
}

bool Player::check_lose() const noexcept {
    if (!check_ready()) {
        return false;
    }
    return (_alive_counts[0] == 0 &&
        _alive_counts[1] == 0 &&
        _alive_counts[2] == 0 &&
        _alive_counts[3] == 0);
}

bool Player::check_ready() const noexcept {
    return (_placed_counts[0] == _max_ships_counts[0] &&
        _placed_counts[1] == _max_ships_counts[1] &&
        _placed_counts[2] == _max_ships_counts[2] &&
        _placed_counts[3] == _max_ships_counts[3]);
}