#include "pch.h"
#include "../GameFieldLib/game_field.h"
#include <string>
#include <stdexcept>

TEST(GameField, default_field_empty) {
    GameField field;
    std::string s = to_string(field, true);
    EXPECT_NE(s.find("  |A B C D E F G H I J|"), std::string::npos);
    EXPECT_NE(s.find("1 | | | | | | | | | | |"), std::string::npos);
}

TEST(GameField, place_ship_horizontal) {
    GameField field;
    Ship ship(3, 'H', 4, 'C');
    field.set(ship);
    std::string s = to_string(field, true);
    EXPECT_NE(s.find("4 | | |*|*|*| | | | | |"), std::string::npos);
}

TEST(GameField, place_ship_vertical) {
    GameField field;
    Ship ship(3, 'V', 2, 'D');
    field.set(ship);
    std::string s = to_string(field, true);
    EXPECT_NE(s.find("2 | | | |*| | | | | | |"), std::string::npos);
    EXPECT_NE(s.find("4 | | | |*| | | | | | |"), std::string::npos);
}

TEST(GameField, hidden_ship_not_shown) {
    GameField field;
    Ship ship(3, 'H', 4, 'C');
    field.set(ship);
    std::string s = to_string(field, false);
    EXPECT_EQ(s.find("*"), std::string::npos);
}

TEST(GameField, overlap_throws) {
    GameField field;
    Ship a(3, 'H', 1, 'A');
    Ship b(3, 'H', 1, 'A');
    field.set(a);
    EXPECT_THROW(field.set(b), std::logic_error);
}

TEST(GameField, diagonal_touch_throws) {
    GameField field;
    Ship a(3, 'H', 1, 'A');
    Ship b(3, 'H', 2, 'D');
    field.set(a);
    EXPECT_THROW(field.set(b), std::logic_error);
}

TEST(GameField, one_cell_gap_ok) {
    GameField field;
    Ship a(3, 'H', 1, 'A');
    Ship b(3, 'H', 1, 'E');
    field.set(a);
    field.set(b);
}

TEST(GameField, miss_returns_missed) {
    GameField field;
    EXPECT_EQ(field.set(1, 'A'), Missed);
}

TEST(GameField, hit_returns_hit) {
    GameField field;
    Ship ship(3, 'H', 1, 'A');
    field.set(ship);
    EXPECT_EQ(field.set(1, 'A'), Hit);
}

TEST(GameField, destroy_boat_size1) {
    GameField field;
    Ship ship(1, 'H', 1, 'A');
    field.set(ship);
    EXPECT_EQ(field.set(1, 'A'), BoatDestroyed);
}

TEST(GameField, destroy_destroyer_size2) {
    GameField field;
    Ship ship(2, 'H', 1, 'A');
    field.set(ship);
    field.set(1, 'A');
    EXPECT_EQ(field.set(1, 'B'), DestroyersDestroyed);
}

TEST(GameField, destroy_cruiser_size3) {
    GameField field;
    Ship ship(3, 'H', 1, 'A');
    field.set(ship);
    field.set(1, 'A');
    field.set(1, 'B');
    EXPECT_EQ(field.set(1, 'C'), CruisersDestroyed);
}

TEST(GameField, destroy_battleship_size4) {
    GameField field;
    Ship ship(4, 'H', 1, 'A');
    field.set(ship);
    field.set(1, 'A');
    field.set(1, 'B');
    field.set(1, 'C');
    EXPECT_EQ(field.set(1, 'D'), BattleshipDestroyed);
}

TEST(GameField, out_of_range_row) {
    GameField field;
    EXPECT_THROW(field.set(0, 'A'), std::logic_error);
    EXPECT_THROW(field.set(11, 'A'), std::logic_error);
}

TEST(GameField, out_of_range_col) {
    GameField field;
    EXPECT_THROW(field.set(1, '@'), std::logic_error);
    EXPECT_THROW(field.set(1, 'K'), std::logic_error);
}

TEST(GameField, shoot_same_cell_twice_throws) {
    GameField field;
    field.set(1, 'A');
    EXPECT_THROW(field.set(1, 'A'), std::logic_error);
}

TEST(GameField, is_collision_empty) {
    GameField field;
    Ship ship(3, 'H', 1, 'A');
    EXPECT_FALSE(is_collision(field, ship));
}

TEST(GameField, is_collision_adjacent) {
    GameField field;
    Ship a(3, 'H', 1, 'A');
    Ship b(3, 'H', 1, 'D');
    field.set(a);
    EXPECT_TRUE(is_collision(field, b));
}

TEST(GameField, is_collision_one_gap_ok) {
    GameField field;
    Ship a(3, 'H', 1, 'A');
    Ship b(3, 'H', 1, 'E');
    field.set(a);
    EXPECT_FALSE(is_collision(field, b));
}