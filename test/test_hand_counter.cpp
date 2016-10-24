#include "catch.hpp"
#include "crib_hand_helper/hand_counter.h"

TEST_CASE("Nobs")
{
  SECTION("Without nobs")
  {
    Hand hand = {Card("2c"), Card("4d"), Card("6h"), Card("Js")};
    Card cut("8c");

    REQUIRE(count_hand(hand, cut) == 0);
  }

  SECTION("With nobs")
  {
    Hand hand = {Card("2c"), Card("4d"), Card("6h"), Card("Js")};
    Card cut("8s");

    REQUIRE(count_hand(hand, cut) == 1);
  }
}

TEST_CASE("Flush")
{
  SECTION("Without flush")
  {
    Hand hand = {Card("2c"), Card("4d"), Card("6h"), Card("Js")};
    Card cut("8c");

    REQUIRE(count_hand(hand, cut) == 0);
  }

  SECTION("Without hand-only flush")
  {
    Hand hand = {Card("2d"), Card("4d"), Card("6d"), Card("Jd")};
    Card cut("8c");

    REQUIRE(count_hand(hand, cut) == 4);
  }

  SECTION("Without full flush")
  {
    Hand hand = {Card("2d"), Card("4d"), Card("6d"), Card("Qd")};
    Card cut("8d");

    REQUIRE(count_hand(hand, cut) == 5);
  }
}

TEST_CASE("Pairs")
{
  SECTION("No pairs")
  {
    Hand hand = {Card("2c"), Card("4d"), Card("6h"), Card("Js")};
    Card cut("8c");

    REQUIRE(count_hand(hand, cut) == 0);
  }

  SECTION("Single pair")
  {
    Hand hand = {Card("2d"), Card("2c"), Card("6d"), Card("Jd")};
    Card cut("8c");

    REQUIRE(count_hand(hand, cut) == 2);
  }

  SECTION("Two pairs")
  {
    Hand hand = {Card("2d"), Card("2c"), Card("6d"), Card("8d")};
    Card cut("8d");

    REQUIRE(count_hand(hand, cut) == 4);
  }

  SECTION("Three pairs")
  {
    Hand hand = {Card("2d"), Card("2c"), Card("6d"), Card("8d")};
    Card cut("2s");

    REQUIRE(count_hand(hand, cut) == 6);
  }

  SECTION("Six pairs")
  {
    Hand hand = {Card("2d"), Card("2c"), Card("2h"), Card("8d")};
    Card cut("2s");

    REQUIRE(count_hand(hand, cut) == 12);
  }
}

TEST_CASE("Runs")
{
  SECTION("No runs")
  {
    Hand hand = {Card("2c"), Card("4d"), Card("6h"), Card("Js")};
    Card cut("8c");

    REQUIRE(count_hand(hand, cut) == 0);
  }

  SECTION("Run of five")
  {
    Hand hand = {Card("9c"), Card("Td"), Card("Jh"), Card("Qs")};
    Card cut("Kc");

    REQUIRE(count_hand(hand, cut) == 5);
  }

  SECTION("Run of four")
  {
    Hand hand = {Card("Qc"), Card("Td"), Card("Kh"), Card("7s")};
    Card cut("Jc");

    REQUIRE(count_hand(hand, cut) == 4);
  }

  SECTION("Run of three")
  {
    Hand hand = {Card("Qc"), Card("Td"), Card("4h"), Card("7s")};
    Card cut("Jc");

    REQUIRE(count_hand(hand, cut) == 3);
  }
}

TEST_CASE("Fifteens")
{
}

TEST_CASE("Miscellaneous hands")
{
  SECTION("Like this one will ever happen")
  {
    Hand hand = {Card("5c"), Card("5d"), Card("5h"), Card("Js")};
    Card cut("5s");

    REQUIRE(count_hand(hand, cut) == 29);
  }
}
