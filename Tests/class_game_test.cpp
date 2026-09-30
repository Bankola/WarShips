#include "pch.h"
#include "../GameLib/game.h"
#include <sstream>
#include <iostream>
#include <string>

class StreamRedirect {
    std::streambuf* _old_cin;
    std::streambuf* _old_cout;
public:
    StreamRedirect(std::istringstream& in, std::ostringstream& out) {
        _old_cin = std::cin.rdbuf(in.rdbuf());
        _old_cout = std::cout.rdbuf(out.rdbuf());
    }
    ~StreamRedirect() {
        std::cin.rdbuf(_old_cin);
        std::cout.rdbuf(_old_cout);
    }
};

TEST(Game, user_wins) {
    std::istringstream in(
        "1 H 1 A\n1 H 1 C\n1 H 1 E\n1 H 1 G\n"
        "2 H 3 A\n2 H 3 D\n2 H 3 G\n"
        "3 H 5 A\n3 H 5 E\n"
        "4 H 7 A\n"
        "\n"
        "1 H 1 A\n1 H 1 C\n1 H 1 E\n1 H 1 G\n"
        "2 H 3 A\n2 H 3 D\n2 H 3 G\n"
        "3 H 5 A\n3 H 5 E\n"
        "4 H 7 A\n"
        "\n"
        "1 A\n1 C\n1 E\n1 G\n"
        "3 A\n3 B\n3 D\n3 E\n3 G\n3 H\n"
        "5 A\n5 B\n5 C\n5 E\n5 F\n5 G\n"
        "7 A\n7 B\n7 C\n7 D\n"
    );
    std::ostringstream out;

    {
        StreamRedirect redirect(in, out);
        Game game;
        game.start();
    }

    EXPECT_NE(out.str().find("USER WIN!"), std::string::npos);
}

TEST(Game, insufficient_ships_throws) {
    std::istringstream in(
        "1 H 1 A\n"
        "\n"
    );
    std::ostringstream out;

    StreamRedirect redirect(in, out);
    Game game;
    EXPECT_THROW(game.start(), std::logic_error);
}

TEST(Game, invalid_move_throws) {
    std::istringstream in(
        "1 H 1 A\n1 H 1 C\n1 H 1 E\n1 H 1 G\n"
        "2 H 3 A\n2 H 3 D\n2 H 3 G\n"
        "3 H 5 A\n3 H 5 E\n"
        "4 H 7 A\n"
        "\n"
        "1 H 1 A\n1 H 1 C\n1 H 1 E\n1 H 1 G\n"
        "2 H 3 A\n2 H 3 D\n2 H 3 G\n"
        "3 H 5 A\n3 H 5 E\n"
        "4 H 7 A\n"
        "\n"
        "11 A\n"
    );
    std::ostringstream out;

    StreamRedirect redirect(in, out);
    Game game;
    EXPECT_THROW(game.start(), std::logic_error);
}