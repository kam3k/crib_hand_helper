#include "catch.hpp"
#include "crib_hand_helper/hand_statistics.h"

TEST_CASE("Bad hands")
{
  auto hand_statistics =
      get_hand_statistics({Card("2h"), Card("4d"), Card("7c"), Card("Qs")},
                          {Card("As"), Card("Ah")});
  REQUIRE(hand_statistics.worst == 0);
  REQUIRE(hand_statistics.best == 5);
  REQUIRE(hand_statistics.best > hand_statistics.mean);
  REQUIRE(hand_statistics.worst < hand_statistics.mean);

  hand_statistics =
      get_hand_statistics({Card("2h"), Card("4h"), Card("7h"), Card("Qh")},
                          {Card("As"), Card("Ah")});
  REQUIRE(hand_statistics.worst == 4);
  REQUIRE(hand_statistics.best == 10);
  REQUIRE(hand_statistics.best > hand_statistics.mean);
  REQUIRE(hand_statistics.worst < hand_statistics.mean);

  hand_statistics =
      get_hand_statistics({Card("Ac"), Card("4h"), Card("7h"), Card("7s")},
                          {Card("As"), Card("Ah")});
  REQUIRE(hand_statistics.worst == 4);
  REQUIRE(hand_statistics.best == 12);
  REQUIRE(hand_statistics.best > hand_statistics.mean);
  REQUIRE(hand_statistics.worst < hand_statistics.mean);

  hand_statistics =
      get_hand_statistics({Card("Ac"), Card("Th"), Card("Js"), Card("Ks")},
                          {Card("As"), Card("Ah")});
  REQUIRE(hand_statistics.worst == 0);
  REQUIRE(hand_statistics.best == 7);
  REQUIRE(hand_statistics.best > hand_statistics.mean);
  REQUIRE(hand_statistics.worst < hand_statistics.mean);
}

TEST_CASE("Good hands")
{
  auto hand_statistics =
      get_hand_statistics({Card("2h"), Card("3d"), Card("3c"), Card("3s")},
                          {Card("As"), Card("Ah")});
  REQUIRE(hand_statistics.worst == 6);
  REQUIRE(hand_statistics.best == 17);
  REQUIRE(hand_statistics.best > hand_statistics.mean);
  REQUIRE(hand_statistics.worst < hand_statistics.mean);

  hand_statistics =
      get_hand_statistics({Card("5h"), Card("5c"), Card("Th"), Card("Ts")},
                          {Card("As"), Card("Ah")});
  REQUIRE(hand_statistics.worst == 12);
  REQUIRE(hand_statistics.best == 22);
  REQUIRE(hand_statistics.best > hand_statistics.mean);
  REQUIRE(hand_statistics.worst < hand_statistics.mean);

  hand_statistics =
      get_hand_statistics({Card("7s"), Card("8h"), Card("8s"), Card("9s")},
                          {Card("As"), Card("Ah")});
  REQUIRE(hand_statistics.worst == 12);
  REQUIRE(hand_statistics.best == 24);
  REQUIRE(hand_statistics.best > hand_statistics.mean);
  REQUIRE(hand_statistics.worst < hand_statistics.mean);

  hand_statistics =
      get_hand_statistics({Card("5s"), Card("5h"), Card("5c"), Card("5d")},
                          {Card("As"), Card("Ah")});
  REQUIRE(hand_statistics.worst == 20);
  REQUIRE(hand_statistics.best == 28);
  REQUIRE(hand_statistics.best > hand_statistics.mean);
  REQUIRE(hand_statistics.worst < hand_statistics.mean);
}
