// -*- Mode: C++; indent-tabs-mode: nil; tab-width: 2 -*-
/*
 * Copyright (C) 2014 Brandon Schaefer
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Brandon Schaefer <brandontschaefer@gmail.com>
 */

#include "LSystem.h"

// FIXME Look into generating the rules our selfs vs hard coded mapping
LSystem::LSystem(std::unordered_map<char, std::string> const& rules)
  : rules_(rules)
{
}

/*
Recursion:

Base case: iteration <= 0
Recursive Step:
  - Replace each char in string with a new set up rules
  - Continue (iterations - 1, str);

This will be tail recursion

*/

std::string LSystem::GenerateString(int iterations, std::string const& start)
{
  if (iterations <= 0)
    return start;

  // Attempt to replace each char with a rule
  std::string start_plus_1;
  for (auto const& c : start)
  {
    if (rules_.find(c) != rules_.end())
      start_plus_1 += rules_[c];
    else
      start_plus_1 += c;
  }

  return GenerateString(iterations - 1, start_plus_1);
}
