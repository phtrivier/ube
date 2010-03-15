#include "sdl_puzzle_selection_renderer.hpp"

#include <assert.h>

int
SdlPuzzleSelectionRenderer::init() 
{
  // Load bg
  // Load font
  return 0;
}

SdlPuzzleSelectionRenderer::~SdlPuzzleSelectionRenderer()
{
  // Release font
  // Release bg
}

void
SdlPuzzleSelectionRenderer::clear() 
{
  assert(get_screen() != NULL);
  SDL_BlitSurface(p_bg_, NULL, get_screen(), NULL);
}

void
SdlPuzzleSelectionRenderer::flush() 
{
  SdlRenderer::flush();
}

void
SdlPuzzleSelectionRenderer::render_puzzle_name(std::string & i_name,
					       int i_index)
{
  // Compute position
  // Print the name at the proper place
}
