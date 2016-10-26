#include "catch.hpp"
#include "crib_hand_helper/hand_statistics.h"

TEST_CASE("Bad hands")
{
  const auto hand_statistics =
      get_hand_statistics({Card("2h"), Card("4d"), Card("7c"), Card("Qs")});
  REQUIRE(hand_statistics.worst == 0);
  REQUIRE(hand_statistics.best == 5);
}
