#include "pch.h"
#include "../PlayerLib/player.h"

TEST(Player, default_not_ready) {
    Player p;
    EXPECT_FALSE(p.check_ready());
}

TEST(Player, default_not_lose) {
    Player p;
    EXPECT_FALSE(p.check_lose());
}

TEST(Player, place_four_singles_not_ready) {
    Player p;
    p.set_ship(Ship(1, 'H', 1, 'A'));
    p.set_ship(Ship(1, 'H', 1, 'C'));
    p.set_ship(Ship(1, 'H', 1, 'E'));
    p.set_ship(Ship(1, 'H', 1, 'G'));
    EXPECT_FALSE(p.check_ready());
}

TEST(Player, place_all_ready) {
    Player p;
    p.set_ship(Ship(4, 'H', 1, 'A'));
    p.set_ship(Ship(3, 'H', 3, 'A'));
    p.set_ship(Ship(3, 'H', 3, 'E'));
    p.set_ship(Ship(2, 'H', 6, 'A'));
    p.set_ship(Ship(2, 'H', 6, 'D'));
    p.set_ship(Ship(2, 'H', 6, 'G'));
    p.set_ship(Ship(1, 'H', 9, 'A'));
    p.set_ship(Ship(1, 'H', 9, 'C'));
    p.set_ship(Ship(1, 'H', 9, 'E'));
    p.set_ship(Ship(1, 'H', 9, 'G'));
    EXPECT_TRUE(p.check_ready());
}

TEST(Player, place_too_many_singles_throws) {
    Player p;
    p.set_ship(Ship(1, 'H', 1, 'A'));
    p.set_ship(Ship(1, 'H', 1, 'C'));
    p.set_ship(Ship(1, 'H', 1, 'E'));
    p.set_ship(Ship(1, 'H', 1, 'G'));
    EXPECT_THROW(p.set_ship(Ship(1, 'H', 3, 'A')), std::logic_error);
}

TEST(Player, place_too_many_doubles_throws) {
    Player p;
    p.set_ship(Ship(2, 'H', 1, 'A'));
    p.set_ship(Ship(2, 'H', 3, 'A'));
    p.set_ship(Ship(2, 'H', 5, 'A'));
    EXPECT_THROW(p.set_ship(Ship(2, 'H', 7, 'A')), std::logic_error);
}

TEST(Player, place_too_many_triples_throws) {
    Player p;
    p.set_ship(Ship(3, 'H', 1, 'A'));
    p.set_ship(Ship(3, 'H', 3, 'A'));
    EXPECT_THROW(p.set_ship(Ship(3, 'H', 5, 'A')), std::logic_error);
}

TEST(Player, place_two_battleships_throws) {
    Player p;
    p.set_ship(Ship(4, 'H', 1, 'A'));
    EXPECT_THROW(p.set_ship(Ship(4, 'H', 3, 'A')), std::logic_error);
}

TEST(Player, place_collision_throws) {
    Player p;
    p.set_ship(Ship(3, 'H', 1, 'A'));
    EXPECT_THROW(p.set_ship(Ship(3, 'H', 1, 'A')), std::logic_error);
}

TEST(Player, set_action_miss) {
    Player p;
    p.set_ship(Ship(1, 'H', 1, 'A'));
    EXPECT_EQ(p.set_action(5, 'E'), Missed);
}

TEST(Player, set_action_hit_not_destroyed) {
    Player p;
    p.set_ship(Ship(3, 'H', 1, 'A'));
    EXPECT_EQ(p.set_action(1, 'A'), Hit);
}

TEST(Player, set_action_destroy_boat) {
    Player p;
    p.set_ship(Ship(1, 'H', 1, 'A'));
    EXPECT_EQ(p.set_action(1, 'A'), BoatDestroyed);
}

TEST(Player, set_action_destroy_destroyer) {
    Player p;
    p.set_ship(Ship(2, 'H', 1, 'A'));
    p.set_action(1, 'A');
    EXPECT_EQ(p.set_action(1, 'B'), DestroyersDestroyed);
}

TEST(Player, set_action_destroy_cruiser) {
    Player p;
    p.set_ship(Ship(3, 'H', 1, 'A'));
    p.set_action(1, 'A');
    p.set_action(1, 'B');
    EXPECT_EQ(p.set_action(1, 'C'), CruisersDestroyed);
}

TEST(Player, set_action_destroy_battleship) {
    Player p;
    p.set_ship(Ship(4, 'H', 1, 'A'));
    p.set_action(1, 'A');
    p.set_action(1, 'B');
    p.set_action(1, 'C');
    EXPECT_EQ(p.set_action(1, 'D'), BattleshipDestroyed);
}

TEST(Player, set_action_twice_throws) {
    Player p;
    p.set_ship(Ship(1, 'H', 1, 'A'));
    p.set_action(1, 'A');
    EXPECT_THROW(p.set_action(1, 'A'), std::logic_error);
}

TEST(Player, set_action_out_of_bounds_throws) {
    Player p;
    EXPECT_THROW(p.set_action(0, 'A'), std::logic_error);
    EXPECT_THROW(p.set_action(11, 'A'), std::logic_error);
    EXPECT_THROW(p.set_action(1, 'K'), std::logic_error);
}

TEST(Player, lose_after_all_destroyed) {
    Player p;
    p.set_ship(Ship(4, 'H', 1, 'A'));
    p.set_ship(Ship(3, 'H', 3, 'A'));
    p.set_ship(Ship(3, 'H', 3, 'E'));
    p.set_ship(Ship(2, 'H', 6, 'A'));
    p.set_ship(Ship(2, 'H', 6, 'D'));
    p.set_ship(Ship(2, 'H', 6, 'G'));
    p.set_ship(Ship(1, 'H', 9, 'A'));
    p.set_ship(Ship(1, 'H', 9, 'C'));
    p.set_ship(Ship(1, 'H', 9, 'E'));
    p.set_ship(Ship(1, 'H', 9, 'G'));
    EXPECT_FALSE(p.check_lose());

    p.set_action(1, 'A');
    p.set_action(1, 'B');
    p.set_action(1, 'C');
    p.set_action(1, 'D');

    p.set_action(3, 'A');
    p.set_action(3, 'B');
    p.set_action(3, 'C');

    p.set_action(3, 'E');
    p.set_action(3, 'F');
    p.set_action(3, 'G');

    p.set_action(6, 'A');
    p.set_action(6, 'B');

    p.set_action(6, 'D');
    p.set_action(6, 'E');

    p.set_action(6, 'G');
    p.set_action(6, 'H');

    p.set_action(9, 'A');
    p.set_action(9, 'C');
    p.set_action(9, 'E');
    p.set_action(9, 'G');

    EXPECT_TRUE(p.check_lose());
}

TEST(Player, lose_only_if_all_sizes_destroyed) {
    Player p;
    p.set_ship(Ship(4, 'H', 1, 'A'));
    p.set_ship(Ship(3, 'H', 3, 'A'));
    p.set_ship(Ship(3, 'H', 3, 'E'));
    p.set_ship(Ship(2, 'H', 6, 'A'));
    p.set_ship(Ship(2, 'H', 6, 'D'));
    p.set_ship(Ship(2, 'H', 6, 'G'));
    p.set_ship(Ship(1, 'H', 9, 'A'));
    p.set_ship(Ship(1, 'H', 9, 'C'));
    p.set_ship(Ship(1, 'H', 9, 'E'));
    p.set_ship(Ship(1, 'H', 9, 'G'));

    p.set_action(1, 'A');
    p.set_action(1, 'B');
    p.set_action(1, 'C');
    p.set_action(1, 'D');

    p.set_action(3, 'A');
    p.set_action(3, 'B');
    p.set_action(3, 'C');

    p.set_action(3, 'E');
    p.set_action(3, 'F');
    p.set_action(3, 'G');

    p.set_action(6, 'A');
    p.set_action(6, 'B');

    p.set_action(6, 'D');
    p.set_action(6, 'E');

    p.set_action(6, 'G');
    p.set_action(6, 'H');

    p.set_action(9, 'A');
    p.set_action(9, 'C');
    p.set_action(9, 'E');

    EXPECT_FALSE(p.check_lose());

    p.set_action(9, 'G');
    EXPECT_TRUE(p.check_lose());
}

TEST(Player, not_lose_before_ready) {
    Player p;
    EXPECT_FALSE(p.check_lose());
}