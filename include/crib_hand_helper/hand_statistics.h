#include "crib_hand_helper/card.h"

struct HandStatistics
{
  HandStatistics() = default;
  HandStatistics(double mean, double std_dev, unsigned best, unsigned worst)
    : mean(mean), std_dev(std_dev), best(best), worst(worst)
  {
  }
  double mean;
  double std_dev;
  unsigned best;
  unsigned worst;
};

HandStatistics get_hand_statistics(const Hand& hand);
