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

#include <SDL.h>

#include <stdexcept>


namespace
{
  int const WIDTH  = 800;
  int const HEIGHT = 600;
  std::string const TITLE = "L-System";
}

struct Point
{
  int x,y;
};

SDL_Window* CreateSDLWindow()
{
  SDL_Window* window = SDL_CreateWindow(TITLE.c_str(),
                                        SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED,
                                        WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

  if (!window)
    throw std::runtime_error("Failed to create SDL window");

  return window;
}


SDL_Renderer* CreateSDLRenderer(SDL_Window* window)
{
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  if (!renderer)
    throw std::runtime_error("Failed to create SDL renderer");

  return renderer;
}

SDL_Point* GenerateLinesFromGeneratedString(std::string const& gen_str)
{
  SDL_Point current = {50, 50};
  int const size = gen_str.size();
  SDL_Point* points = new SDL_Point[size + 1];
  int index = 0;

  points[index++] = current;

  int diff_x = 2;
  int diff_y = 2;
  for (auto const& c : gen_str)
  {
    if (c == 'F' || c == 'G')
    {
      current.x += diff_x;
      current.y += diff_y;
      points[index++] = current;
    }
    else if (c == '+')
    {
      diff_x = -diff_x;
    }
    else
    {
      diff_y = -diff_y;
    }
  }

  return points;
}

void StartMainLoop()
{
  SDL_Window*   window   = CreateSDLWindow();
  SDL_Renderer* renderer = CreateSDLRenderer(window);

  SDL_Rect dest = {0, 0, 10, 10};

  // FIXME Do this a bit more dynamically later... hard code is just for testing
  std::unordered_map<char, std::string> rules;
  rules['F'] = "G-F-G-";
  rules['G'] = "F+G+F++";

  LSystem l_system(rules);
  std::string gen_str = l_system.GenerateString(10, "F");
  SDL_Point* points = GenerateLinesFromGeneratedString(gen_str);

  bool done = false;
  int current = 20;//gen_str.size()-1;
  while (!done)
  {
    // TODO Branch this off into Event handling code
    SDL_Event event;
    while (!SDL_PollEvent(&event))
    {
      switch (event.type)
      {
        case (SDL_KEYDOWN):
        {
          if (event.key.keysym.sym == SDLK_ESCAPE)
            done = true;
          break;
        }
        case (SDL_QUIT):
          done = true;
          break;
        default:
          break;
      }
    }

    // TODO Branch this off into Draw/Render code

    SDL_RenderClear(renderer);

    // Red
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(renderer, &dest);

    SDL_RenderDrawLines(renderer, points, current++ % gen_str.size());

    // Black 
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderPresent(renderer);
  }

  delete []points;
}

void InitSDL()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    throw std::runtime_error("Failed to Init SDL");
}

int main()
{
  InitSDL();

  StartMainLoop();

  return 0;
}
