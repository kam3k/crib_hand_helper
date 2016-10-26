#include <algorithm>
#include <array>

#include "crib_hand_helper/hand_counter.h"
#include "crib_hand_helper/hand_statistics.h"

using Deck = std::vector<Card>;

const std::vector<char> NAMES = {'A', '2', '3', '4', '5', '6', '7',
                                 '8', '9', 'T', 'J', 'Q', 'K'};
const std::vector<char> SUITS = {'c', 'd', 'h', 's'};

Deck build_deck(const Hand& hand)
{
  Deck deck;
  for (const auto& suit : SUITS)
  {
    for (const auto& name : NAMES)
    {
      bool in_hand = false;
      for (const auto& card : hand)
      {
        if (card.name == name && card.suit == suit)
        {
          in_hand = true;
          break;
        }
      }
      if (!in_hand)
      {
        deck.emplace_back(name, suit);
      }
    }
  }
  return deck;
}

HandStatistics get_hand_statistics(const Hand& hand)
{
  const auto deck = build_deck(hand);

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

  return HandStatistics(mean, std_dev, *best, *worst);
}
