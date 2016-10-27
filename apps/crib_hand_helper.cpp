#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>

#include "crib_hand_helper/card.h"
#include "crib_hand_helper/hand_counter.h"

const std::string CARD_NAMES = "A23456789TJQK";

bool validate_input(const std::string& hand_string)
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

int main()
{
  bool input_is_valid = false;
  std::string hand_string;

  while (!input_is_valid)
  {
    std::cout << "Enter hand: ";
    std::cin >> hand_string;
    input_is_valid = validate_input(hand_string);
    if (!input_is_valid)
    {
      std::cout << "Invalid hand. Try again.\n";
    }
  }

  auto hand = parse_hand(hand_string);
  
  input_is_valid = false;
  char yes_or_no;
  while (!input_is_valid)
  {
    std::cout << "Are at least fours card the same suit? [y/n]: ";
    std::cin >> yes_or_no;
    input_is_valid = yes_or_no == 'y' || yes_or_no == 'n';
    if (!input_is_valid)
    {
      std::cout << "Invalid selection. Please enter y or n.\n";
    }
  }

  if (yes_or_no == 'y')
  {

  }
}
