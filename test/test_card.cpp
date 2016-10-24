#include "catch.hpp"
#include "crib_hand_helper/card.h"

TEST_CASE("Rank and suit constructor")
{
  SECTION("Mid-rank")
  {
    Card card('5', 'h');

    REQUIRE(card.rank == 5);
    REQUIRE(card.value == 5);
    REQUIRE(card.name == '5');
    REQUIRE(card.suit == 'h');
  }

  SECTION("Jack")
  {
    Card card('J', 'c');

    REQUIRE(card.rank == 11);
    REQUIRE(card.value == 10);
    REQUIRE(card.name == 'J');
    REQUIRE(card.suit == 'c');
  }

  SECTION("Queen")
  {
    Card card('Q', 'd');

    REQUIRE(card.rank == 12);
    REQUIRE(card.value == 10);
    REQUIRE(card.name == 'Q');
    REQUIRE(card.suit == 'd');
  }

  SECTION("King")
  {
    Card card('K', 'h');

    REQUIRE(card.rank == 13);
    REQUIRE(card.value == 10);
    REQUIRE(card.name == 'K');
    REQUIRE(card.suit == 'h');
  }

  SECTION("Ace")
  {
    Card card('A', 's');

    REQUIRE(card.rank == 1);
    REQUIRE(card.value == 1);
    REQUIRE(card.name == 'A');
    REQUIRE(card.suit == 's');
  }
}

TEST_CASE("String constructor")
{
  SECTION("Mid-rank")
  {
    Card card("5h");

    REQUIRE(card.rank == 5);
    REQUIRE(card.value == 5);
    REQUIRE(card.name == '5');
    REQUIRE(card.suit == 'h');
  }

  SECTION("Jack")
  {
    Card card("Jc");

    REQUIRE(card.rank == 11);
    REQUIRE(card.value == 10);
    REQUIRE(card.name == 'J');
    REQUIRE(card.suit == 'c');
  }

  SECTION("Queen")
  {
    Card card("Qd");

    REQUIRE(card.rank == 12);
    REQUIRE(card.value == 10);
    REQUIRE(card.name == 'Q');
    REQUIRE(card.suit == 'd');
  }

  SECTION("King")
  {
    Card card("Kh");

    REQUIRE(card.rank == 13);
    REQUIRE(card.value == 10);
    REQUIRE(card.name == 'K');
    REQUIRE(card.suit == 'h');
  }

  SECTION("Ace")
  {
    Card card('A', 's');

    REQUIRE(card.rank == 1);
    REQUIRE(card.value == 1);
    REQUIRE(card.name == 'A');
    REQUIRE(card.suit == 's');
  }
}
