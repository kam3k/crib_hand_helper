#ifndef HAND_COUNTER_H
#define HAND_COUNTER_H

#include "crib_hand_helper/card.h"

namespace crib
{
  unsigned count_hand(const Hand&, const Card& cut);
} /* crib */

#endif /* HAND_COUNTER_H */
