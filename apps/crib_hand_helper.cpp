#include <algorithm>
#include <cassert>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "crib_hand_helper/card.h"
#include "crib_hand_helper/constants.h"
#include "crib_hand_helper/hand_counter.h"
#include "crib_hand_helper/hand_statistics.h"

using namespace crib;

bool validate_hand(const std::string& hand_string)
{
  if (hand_string.size() != 6)
  {
    return false;
  }

  for (const auto& card_char : hand_string)
  {
    // Must not be in hand more than four times
    if (std::count(hand_string.begin(), hand_string.end(), card_char) > 4)
    {
      return false;
    }

    // Capitalize letters
    auto card = card_char;
    if (!std::isdigit(card))
    {
      card = std::toupper(card);
    }

    // Must be in CARD_NAMES
    if (std::find(CARD_NAMES.begin(), CARD_NAMES.end(), card) ==
        CARD_NAMES.end())
    {
      return false;
    }
  }

  return true;
}

Hand parse_hand(const std::string& hand_string)
{
  assert(hand_string.size() == 6);

  const std::string suits = "cdhscd";

  Hand hand;
  for (std::string::size_type i = 0; i < hand_string.size(); ++i)
  {
    // Capitalize letters
    auto card = hand_string[i];
    if (!std::isdigit(card))
    {
      card = std::toupper(card);
    }

    hand.emplace_back(card, suits[i]);
  }

  return hand;
}

bool validate_suits(const std::string& suits, const Hand& hand)
{
  assert(suits.size() == 6);
  assert(hand.size() == 6);

  // Check if suits are all c, d, h, or s
  for (const auto& suit : suits)
  {
    if (std::find(CARD_SUITS.begin(), CARD_SUITS.end(), suit) ==
        CARD_SUITS.end())
    {
      std::cout << "One or more suits are invalid.\n";
      return false;
    }
  }

  // Check if two cards with the same rank have the same suit
  std::map<unsigned, std::vector<char>> rank_suits_map;
  auto suit_it = suits.cbegin();
  auto card_it = hand.cbegin();
  for (; suit_it != suits.cend() && card_it != hand.cend();
       ++suit_it, ++card_it)
  {
    auto& suits = rank_suits_map[card_it->rank];
    if (std::find(suits.begin(), suits.end(), *suit_it) != suits.end())
    {
      std::cout << "Two cards cannot have the same rank and suit.\n";
      return false;
    }
    suits.push_back(*suit_it);
  }

  return true;
}

void adjust_suits(Hand& hand)
{
  assert(hand.size() == 6);

  std::string suit_string;
  auto input_is_valid = false;
  while (!input_is_valid)
  {
    std::cout << "Enter suits: ";
    std::cin >> suit_string;
    if (suit_string.size() != 6)
    {
      std::cout << "Enter exactly six suits.\n";
      continue;
    }
    else if (!validate_suits(suit_string, hand))
    {
      continue;
    }
    input_is_valid = true;
  }

  // Adjust suits in hand
  for (std::string::size_type i = 0; i < suit_string.size(); ++i)
  {
    hand[i].suit = suit_string[i];
  }
}

void print_results(const std::vector<HandStatistics>& hand_statistics,
                   bool need_suits)
{
  assert(hand_statistics.size() == 15);

  auto discard_space = need_suits ? 12 : 10;
  std::cout << std::endl;
  std::cout << std::right << std::setw(discard_space) << "DISCARD" << std::right
            << std::setw(14) << "AVERAGE" << std::right << std::setw(7)
            << "HIGH" << std::setw(6) << std::right << "LOW" << std::endl;
  std::cout << std::right << std::setw(discard_space) << "-------" << std::right
            << std::setw(14) << "-----------" << std::right << std::setw(7)
            << "----" << std::setw(6) << std::right << "---" << std::endl;

  std::vector<std::string> previous_outputs;
  for (const auto& hs : hand_statistics)
  {
    std::string discard;
    if (need_suits)
    {
      discard = {hs.discard[0].name, hs.discard[0].suit, ' ',
                 hs.discard[1].name, hs.discard[1].suit};
    }
    else
    {
      discard = {hs.discard[0].name, ' ', hs.discard[1].name};
    }
    std::ostringstream output;
    output << std::setw(discard_space) << std::right << discard << std::setw(14)
           << std::right << std::fixed << std::setprecision(2) << std::setw(8)
           << std::right << hs.mean << " \u00b1 " << std::fixed
           << std::setprecision(1) << std::setw(3) << std::right << hs.std_dev
           << std::setw(7) << std::right << hs.best << std::setw(6)
           << std::right << hs.worst;

    // Don't print repeats
    if (std::find(previous_outputs.begin(), previous_outputs.end(),
                  output.str()) == previous_outputs.end())
    {
      std::cout << output.str() << std::endl;
      previous_outputs.push_back(output.str());
    }
  }
  std::cout << std::endl;
}

int main()
{
  while (true)
  {
    auto input_is_valid = false;
    std::string hand_string;

    // Get hand
    while (!input_is_valid)
    {
      std::cout << "Enter hand: ";
      std::cin >> hand_string;
      input_is_valid = validate_hand(hand_string);
      if (!input_is_valid)
      {
        std::cout << "Invalid hand. Try again.\n";
      }
    }

    // Make hand string upper case
    std::transform(hand_string.begin(), hand_string.end(), hand_string.begin(),
                   ::toupper);

    // Parse hand
    auto hand = parse_hand(hand_string);

    // Check if there is a Jack (will need suits in this case)
    bool need_suits = std::find(hand_string.begin(), hand_string.end(), 'J') !=
                      hand_string.end();
    if (need_suits)
    {
      std::cout << "You have a Jack in your hand. ";
    }

    // Check if there is a flush possibility (will need suits in this case);
    if (!need_suits)
    {
      input_is_valid = false;
      char response;
      while (!input_is_valid)
      {
        std::cout << "Are at least fours card the same suit? [y/n]: ";
        std::cin >> response;
        input_is_valid = response == 'y' || response == 'n';
        if (!input_is_valid)
        {
          std::cout << "Invalid selection. Please enter y or n.\n";
        }
      }
      need_suits = response == 'y';
    }

    // Adjust suits if necessary
    if (need_suits)
    {
      adjust_suits(hand);
    }

    // Get two all possible discards and corresponding keeps
    std::vector<Hand> all_discards, all_keeps;
    for (const auto& indices : SIX_CHOOSE_TWO_INDICES)
    {
      Hand discard, keep;
      for (Hand::size_type i = 0; i < hand.size(); ++i)
      {
        if (i == indices[0] || i == indices[1])
        {
          discard.push_back(hand[i]);
        }
        else
        {
          keep.push_back(hand[i]);
        }
      }
      all_discards.push_back(discard);
      all_keeps.push_back(keep);
    }

    // Calculate hand statistics
    std::vector<HandStatistics> all_hand_statistics;
    for (decltype(all_discards.size()) i = 0; i < all_discards.size(); ++i)
    {
      all_hand_statistics.push_back(
          get_hand_statistics(all_keeps[i], all_discards[i]));
    }

    // Sort from best average to worst average
    std::sort(all_hand_statistics.begin(), all_hand_statistics.end(),
              [](const HandStatistics& hs_1, const HandStatistics& hs_2) {
                return hs_1.mean > hs_2.mean;
              });

    print_results(all_hand_statistics, need_suits);
  }  // while (true)
}
