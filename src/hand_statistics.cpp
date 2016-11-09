#include <algorithm>
#include <array>
#include <cassert>
#include <numeric>
#include <cmath>

#include "crib_hand_helper/constants.h"
#include "crib_hand_helper/hand_counter.h"
#include "crib_hand_helper/hand_statistics.h"

namespace crib
{
  using Deck = std::vector<Card>;

  Deck build_deck(const Hand& hand, const Hand& discard)
  {
    assert(hand.size() == 4);
    assert(discard.size() == 2);

    auto full_hand = hand;
    full_hand.insert(full_hand.end(), discard.begin(), discard.end());

    Deck deck;
    for (const auto& suit : CARD_SUITS)
    {
      for (const auto& name : CARD_NAMES)
      {
        bool in_deck = true;
        for (const auto& card : full_hand)
        {
          if (card.name == name && card.suit == suit)
          {
            in_deck = false;
            break;
          }
        }
        if (in_deck)
        {
          deck.emplace_back(name, suit);
        }
      }
    }
    return deck;
  }

  HandStatistics get_hand_statistics(const Hand& hand, const Hand& discard)
  {
    assert(hand.size() == 4);
    assert(discard.size() == 2);

    const auto deck = build_deck(hand, discard);

    std::vector<unsigned> counts;
    for (const auto& cut : deck)
    {
      counts.push_back(count_hand(hand, cut));
    }

    const auto sum =
        static_cast<double>(std::accumulate(counts.begin(), counts.end(), 0.0));
    const auto mean = sum / counts.size();

    const auto sq_sum = static_cast<double>(
        std::inner_product(counts.begin(), counts.end(), counts.begin(), 0.0));
    const auto std_dev = std::sqrt(sq_sum / counts.size() - mean * mean);

    const auto best = std::max_element(counts.begin(), counts.end());
    const auto worst = std::min_element(counts.begin(), counts.end());

    return HandStatistics(hand, discard, mean, std_dev, *best, *worst);
  }
} /* crib */
