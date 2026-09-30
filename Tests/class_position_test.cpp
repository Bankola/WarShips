#include "pch.h"
#include "../PositionLib/position.h"

//TEST FOR CONSTRUCTORS
TEST(CONSTRPositionTest, default_constructor) {
	Position p;

	EXPECT_EQ(p.row(), 1);
	EXPECT_EQ(p.col(), 1);
}

TEST(CONSTRPositionTest, init_constructor) {
	Position p(6, 8);

	EXPECT_EQ(p.row(), 6);
	EXPECT_EQ(p.col(), 8);
}

TEST(CONSTRPositionTest, copy_constructor) {
	Position p(6, 8);
	Position p_copy(p);

	EXPECT_EQ(p.row(), 6);
	EXPECT_EQ(p.col(), 8);
	EXPECT_EQ(p_copy.row(), 6);
	EXPECT_EQ(p_copy.col(), 8);
}

TEST(CONSTRPositionTest, copy_constructor_no_change) {
	Position p(6, 8);
	Position p_copy(p);

	p_copy.row(7);

	EXPECT_EQ(p.row(), 6);
	EXPECT_EQ(p.col(), 8);
	EXPECT_EQ(p_copy.row(), 7);
	EXPECT_EQ(p_copy.col(), 8);
}

TEST(CONSTRPositionTest, string_constructor) {
	Position p("(5, 7)");
	EXPECT_EQ(p.row(), 5);
	EXPECT_EQ(p.col(), 7);
}

//TEST FOR LOGIC ERRORS
TEST(ERRORPositionTest, logic_error_set_row) {
	Position p(4, 8);

	EXPECT_ANY_THROW(p.row(11));
	EXPECT_ANY_THROW(p.row(0));
}

TEST(ERRORPositionTest, logic_error_set_col) {
	Position p(4, 8);

	EXPECT_ANY_THROW(p.col(12));
	EXPECT_ANY_THROW(p.col(0));
}

TEST(ERRORPositionTest, logic_error_init_constructor) {
	Position p(4, 8);

	EXPECT_ANY_THROW(p.col(11));
	EXPECT_ANY_THROW(Position(11, 5));
	EXPECT_ANY_THROW(Position(5, 11));
	EXPECT_ANY_THROW(Position(0, 5));
}

TEST(ERRORPositionTest, logic_error_on_valid_format) {
	EXPECT_THROW(parse("(1,2"), std::logic_error);
	EXPECT_THROW(parse("(1 2)"), std::logic_error);
	EXPECT_THROW(parse(""), std::logic_error);
}

TEST(PositionParseTest, invalid_argument_nonumber_values) {
	EXPECT_THROW(parse("(abc, 5)"), std::invalid_argument);
	EXPECT_THROW(parse("(5, xyz)"), std::invalid_argument);
}

//TEST FOR PARSE
TEST(PositionParseTest, valid_parse_without_spaces) {
	Position pos = parse("(5,7)");

	EXPECT_EQ(pos.row(), 5);
	EXPECT_EQ(pos.col(), 7);
}

TEST(PositionParseTest, valid_parse_with_spaces) {
	Position pos = parse("(  3  , \t 4  )");

	EXPECT_EQ(pos.row(), 3);
	EXPECT_EQ(pos.col(), 4);
}

//TEST FOR TO_STRING
TEST(PositionToStringTest, convert_to_string_coordinates) {
	Position pos(5, 7);

	std::string result = to_string(pos);

	EXPECT_EQ(result, "(5, 7)");
}