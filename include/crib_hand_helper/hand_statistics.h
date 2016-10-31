#ifndef HAND_STATISTICS_H
#define HAND_STATISTICS_H

#include "crib_hand_helper/card.h"

struct HandStatistics
{
  HandStatistics() = default;
  HandStatistics(const Hand& hand, const Hand& discard, double mean,
                 double std_dev, unsigned best, unsigned worst)
    : hand(hand)
    , discard(discard)
    , mean(mean)
    , std_dev(std_dev)
    , best(best)
    , worst(worst)
  {
  }
  Hand hand;
  Hand discard;
  double mean;
  double std_dev;
  unsigned best;
  unsigned worst;
};

HandStatistics get_hand_statistics(const Hand& hand, const Hand& discard);

#endif /* HAND_STATISTICS_H */
