#include "pch.h"
#include "../ShipLib/ship.h"
#include "../PositionLib/position.h"

TEST(ShipConstructor, full_init_valid) {
    Position pos(1, 1);
    Ship ship(3, Horizontal, pos);
    EXPECT_EQ(ship.get_size(), 3);
    EXPECT_EQ(ship.get_direction(), Horizontal);
    EXPECT_EQ(ship.get_row(), 1);
    EXPECT_EQ(ship.get_col(), 1);
}

TEST(ShipConstructor, full_init_vertical) {
    Position pos(2, 3);
    Ship ship(4, Vertical, pos);
    EXPECT_EQ(ship.get_size(), 4);
    EXPECT_EQ(ship.get_direction(), Vertical);
    EXPECT_EQ(ship.get_row(), 2);
    EXPECT_EQ(ship.get_col(), 3);
}

TEST(ShipConstructor, full_init_size_zero) {
    Position pos(1, 1);
    EXPECT_THROW(Ship(0, Horizontal, pos), std::logic_error);
}

TEST(ShipConstructor, full_init_size_too_big) {
    Position pos(1, 1);
    EXPECT_THROW(Ship(5, Horizontal, pos), std::logic_error);
}

TEST(ShipConstructor, full_init_horizontal_overflow) {
    Position pos(1, 9);
    EXPECT_THROW(Ship(3, Horizontal, pos), std::logic_error);
}

TEST(ShipConstructor, full_init_vertical_overflow) {
    Position pos(9, 1);
    EXPECT_THROW(Ship(3, Vertical, pos), std::logic_error);
}

TEST(ShipConstructor, full_init_exact_fit) {
    Position pos(1, 8);
    Ship ship(3, Horizontal, pos);
    EXPECT_EQ(ship.get_col(), 8);

    Position pos2(8, 1);
    Ship ship2(3, Vertical, pos2);
    EXPECT_EQ(ship2.get_row(), 8);
}

TEST(ShipConstructor, partial_init) {
    Position pos(2, 2);
    Ship ship(3, pos);
    EXPECT_EQ(ship.get_size(), 3);
    EXPECT_EQ(ship.get_direction(), Horizontal);
    EXPECT_EQ(ship.get_row(), 2);
    EXPECT_EQ(ship.get_col(), 2);
}

TEST(ShipConstructor, partial_init_size_invalid) {
    Position pos(1, 1);
    EXPECT_THROW(Ship(0, pos), std::logic_error);
    EXPECT_THROW(Ship(5, pos), std::logic_error);
}

TEST(ShipConstructor, partial_init_overflow) {
    Position pos(1, 9);
    EXPECT_THROW(Ship(3, pos), std::logic_error);
}

TEST(ShipConstructor, char_init_horizontal) {
    Ship ship(3, 'H', 4, 'C');
    EXPECT_EQ(ship.get_size(), 3);
    EXPECT_EQ(ship.get_direction(), Horizontal);
    EXPECT_EQ(ship.get_row(), 4);
    EXPECT_EQ(ship.get_col(), 3);
}

TEST(ShipConstructor, char_init_vertical) {
    Ship ship(4, 'V', 1, 'A');
    EXPECT_EQ(ship.get_size(), 4);
    EXPECT_EQ(ship.get_direction(), Vertical);
    EXPECT_EQ(ship.get_row(), 1);
    EXPECT_EQ(ship.get_col(), 1);
}

TEST(ShipConstructor, char_init_lowercase_direction) {
    Ship ship(3, 'h', 4, 'c');
    EXPECT_EQ(ship.get_direction(), Horizontal);
    EXPECT_EQ(ship.get_col(), 3);
}

TEST(ShipConstructor, char_init_lowercase_col) {
    Ship ship(3, 'H', 4, 'e');
    EXPECT_EQ(ship.get_col(), 5);
}

TEST(ShipConstructor, char_init_bad_direction) {
    EXPECT_THROW(Ship(3, 'X', 4, 'C'), std::logic_error);
}

TEST(ShipConstructor, char_init_bad_col) {
    EXPECT_THROW(Ship(3, 'H', 4, 'K'), std::logic_error);
    EXPECT_THROW(Ship(3, 'H', 4, 'Z'), std::logic_error);
    EXPECT_THROW(Ship(3, 'H', 4, '1'), std::logic_error);
}

TEST(ShipConstructor, char_init_overflow) {
    EXPECT_THROW(Ship(3, 'H', 4, 'I'), std::logic_error);
    EXPECT_THROW(Ship(3, 'V', 9, 'A'), std::logic_error);
}

TEST(ShipGetters, all_getters) {
    Position pos(5, 6);
    Ship ship(2, Vertical, pos);
    EXPECT_EQ(ship.get_size(), 2);
    EXPECT_EQ(ship.get_direction(), Vertical);
    EXPECT_EQ(ship.get_row(), 5);
    EXPECT_EQ(ship.get_col(), 6);
}

TEST(ShipSetter, size_valid) {
    Ship ship(3, Position(1, 1));
    ship.size(4);
    EXPECT_EQ(ship.get_size(), 4);
}

TEST(ShipSetter, size_zero) {
    Ship ship(3, Position(1, 1));
    EXPECT_THROW(ship.size(0), std::logic_error);
}

TEST(ShipSetter, size_too_big) {
    Ship ship(3, Position(1, 1));
    EXPECT_THROW(ship.size(5), std::logic_error);
}

TEST(ShipSetter, size_overflow) {
    Ship ship(3, Position(1, 8));
    EXPECT_THROW(ship.size(4), std::logic_error);
}

TEST(ShipSetter, row_valid) {
    Ship ship(3, Position(1, 1));
    ship.row(5);
    EXPECT_EQ(ship.get_row(), 5);
}

TEST(ShipSetter, row_zero) {
    Ship ship(3, Position(1, 1));
    EXPECT_THROW(ship.row(0), std::logic_error);
}

TEST(ShipSetter, row_too_big) {
    Ship ship(3, Position(1, 1));
    EXPECT_THROW(ship.row(11), std::logic_error);
}

TEST(ShipSetter, row_overflow_vertical) {
    Ship ship(3, Vertical, Position(1, 1));
    EXPECT_THROW(ship.row(9), std::logic_error);
}

TEST(ShipSetter, row_horizontal) {
    Ship ship(3, Horizontal, Position(1, 1));
    ship.row(10);
    EXPECT_EQ(ship.get_row(), 10);
}

TEST(ShipSetter, col_valid) {
    Ship ship(3, Position(1, 1));
    ship.col(5);
    EXPECT_EQ(ship.get_col(), 5);
}

TEST(ShipSetter, col_zero) {
    Ship ship(3, Position(1, 1));
    EXPECT_THROW(ship.col(0), std::logic_error);
}

TEST(ShipSetter, col_too_big) {
    Ship ship(3, Position(1, 1));
    EXPECT_THROW(ship.col(11), std::logic_error);
}

TEST(ShipSetter, col_overflow_horizontal) {
    Ship ship(3, Horizontal, Position(1, 1));
    EXPECT_THROW(ship.col(9), std::logic_error);
}

TEST(ShipSetter, col_vertical) {
    Ship ship(3, Vertical, Position(1, 1));
    ship.col(10);
    EXPECT_EQ(ship.get_col(), 10);
}

TEST(ShipSetter, col_char_valid) {
    Ship ship(3, Position(1, 1));
    ship.col('E');
    EXPECT_EQ(ship.get_col(), 5);
}

TEST(ShipSetter, col_char_lowercase) {
    Ship ship(3, Position(1, 1));
    ship.col('e');
    EXPECT_EQ(ship.get_col(), 5);
}

TEST(ShipSetter, col_char_invalid) {
    Ship ship(3, Position(1, 1));
    EXPECT_THROW(ship.col('K'), std::logic_error);
    EXPECT_THROW(ship.col('1'), std::logic_error);
}

TEST(ShipSetter, direction_valid) {
    Ship ship(3, Horizontal, Position(1, 1));
    ship.direction(Vertical);
    EXPECT_EQ(ship.get_direction(), Vertical);
}

TEST(ShipSetter, direction_overflow) {
    Ship ship(3, Horizontal, Position(9, 1));
    EXPECT_THROW(ship.direction(Vertical), std::logic_error);
}

TEST(ShipSetter, direction_char_valid) {
    Ship ship(3, Horizontal, Position(1, 1));
    ship.direction('V');
    EXPECT_EQ(ship.get_direction(), Vertical);
    ship.direction('H');
    EXPECT_EQ(ship.get_direction(), Horizontal);
}

TEST(ShipSetter, direction_char_lowercase) {
    Ship ship(3, Horizontal, Position(1, 1));
    ship.direction('v');
    EXPECT_EQ(ship.get_direction(), Vertical);
}

TEST(ShipSetter, direction_char_invalid) {
    Ship ship(3, Horizontal, Position(1, 1));
    EXPECT_THROW(ship.direction('X'), std::logic_error);
}

TEST(ShipSetter, position_valid) {
    Ship ship(3, Horizontal, Position(1, 1));
    ship.position(Position(5, 5));
    EXPECT_EQ(ship.get_row(), 5);
    EXPECT_EQ(ship.get_col(), 5);
}

TEST(ShipSetter, position_overflow) {
    Ship ship(3, Horizontal, Position(1, 1));
    EXPECT_THROW(ship.position(Position(1, 9)), std::logic_error);
}

TEST(ShipRotate, horizontal_to_vertical) {
    Ship ship(3, Horizontal, Position(1, 1));
    ship.rotate();
    EXPECT_EQ(ship.get_direction(), Vertical);
}

TEST(ShipRotate, vertical_to_horizontal) {
    Ship ship(3, Vertical, Position(1, 1));
    ship.rotate();
    EXPECT_EQ(ship.get_direction(), Horizontal);
}

TEST(ShipRotate, double_rotate) {
    Ship ship(3, Horizontal, Position(1, 1));
    ship.rotate();
    ship.rotate();
    EXPECT_EQ(ship.get_direction(), Horizontal);
}

TEST(ShipRotate, horizontal_blocked) {
    Ship ship(3, Horizontal, Position(9, 1));
    ship.rotate();
    EXPECT_EQ(ship.get_direction(), Horizontal);
}

TEST(ShipRotate, vertical_blocked) {
    Ship ship(3, Vertical, Position(1, 9));
    ship.rotate();
    EXPECT_EQ(ship.get_direction(), Vertical);
}

TEST(ShipRotate, size_one_always_works) {
    Ship ship(1, Horizontal, Position(10, 10));
    ship.rotate();
    EXPECT_EQ(ship.get_direction(), Vertical);
    ship.rotate();
    EXPECT_EQ(ship.get_direction(), Horizontal);
}

TEST(ShipToString, horizontal_ship) {
    Ship ship(3, Horizontal, Position(4, 3));
    std::string s = to_string(ship);
    EXPECT_NE(s.find("3"), std::string::npos);
    EXPECT_NE(s.find("Horizontal"), std::string::npos);
    EXPECT_NE(s.find("(4, 3)"), std::string::npos);
}

TEST(ShipToString, vertical_ship) {
    Ship ship(4, Vertical, Position(1, 10));
    std::string s = to_string(ship);
    EXPECT_NE(s.find("4"), std::string::npos);
    EXPECT_NE(s.find("Vertical"), std::string::npos);
    EXPECT_NE(s.find("(1, 10)"), std::string::npos);
}

TEST(ShipIsCollision, size_less_than_one) {
    EXPECT_THROW(Ship(0, Horizontal, Position(1, 1)), std::logic_error);
}

TEST(ShipIsCollision, size_greater_than_four) {
    EXPECT_THROW(Ship(5, Horizontal, Position(1, 1)), std::logic_error);
}

TEST(ShipIsCollision, horizontal_right_edge) {
    EXPECT_NO_THROW(Ship(3, Horizontal, Position(1, 8)));
    EXPECT_THROW(Ship(3, Horizontal, Position(1, 9)), std::logic_error);
}

TEST(ShipIsCollision, vertical_bottom_edge) {
    EXPECT_NO_THROW(Ship(3, Vertical, Position(8, 1)));
    EXPECT_THROW(Ship(3, Vertical, Position(9, 1)), std::logic_error);
}

TEST(ShipComplex, all_sizes_horizontal) {
    EXPECT_NO_THROW(Ship(1, Horizontal, Position(1, 1)));
    EXPECT_NO_THROW(Ship(2, Horizontal, Position(1, 1)));
    EXPECT_NO_THROW(Ship(3, Horizontal, Position(1, 1)));
    EXPECT_NO_THROW(Ship(4, Horizontal, Position(1, 1)));
}

TEST(ShipComplex, all_sizes_vertical) {
    EXPECT_NO_THROW(Ship(1, Vertical, Position(1, 1)));
    EXPECT_NO_THROW(Ship(2, Vertical, Position(1, 1)));
    EXPECT_NO_THROW(Ship(3, Vertical, Position(1, 1)));
    EXPECT_NO_THROW(Ship(4, Vertical, Position(1, 1)));
}

TEST(ShipComplex, max_ship_bottom_right) {
    EXPECT_NO_THROW(Ship(4, Horizontal, Position(10, 7)));
    EXPECT_NO_THROW(Ship(4, Vertical, Position(7, 10)));
}

TEST(ShipComplex, setter_keeps_state_on_error) {
    Ship ship(3, Horizontal, Position(1, 1));
    try {
        ship.size(5);
    }
    catch (const std::logic_error&) {}
    EXPECT_EQ(ship.get_size(), 3);
    EXPECT_EQ(ship.get_row(), 1);
    EXPECT_EQ(ship.get_col(), 1);
    EXPECT_EQ(ship.get_direction(), Horizontal);
}