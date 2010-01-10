#include "sdl_in_game_renderer.hpp"

#include "common/logging.hpp"
#include "common/resource_resolver_interface.hpp"

#include "engine/cell.hpp"

#include <assert.h>

#include "SDL.h"
#include "SDL_image.h"

#include "boost/format.hpp"
using namespace boost;

SdlInGameRenderer::~SdlInGameRenderer() {
  for (int cell_type = 0 ; cell_type < Cell::CELL_TYPES_COUNT ; cell_type++) {

    if (cell_images_.find(cell_type) != cell_images_.end()) {
      SDL_Surface * p_cell_image = cell_images_[cell_type];
      if (p_cell_image != NULL) {
	SDL_FreeSurface(p_cell_image);
      }
    }
  }
}

int
SdlInGameRenderer::init() {
  int res = -1;

  p_screen_ = SDL_SetVideoMode(640, 480, 8, SDL_SWSURFACE);
  if (p_screen_ != NULL) {
    res = load_cell_images();
    black_ = SDL_MapRGB(p_screen_->format, 0x00, 0x00, 0x00);
  }

  return res;
}

void
SdlInGameRenderer::clear() {
  assert(p_screen_ != NULL);
  SDL_FillRect(p_screen_, NULL, black_);
}

void 
SdlInGameRenderer::render_cell(int i_i, int i_j, int i_cell_type) {
  // TODO : make this a constant instead of recreating
  SDL_Rect src;
  src.x = 0;
  src.y = 0;
  src.w = 32;
  src.h = 32;

  // TODO : Optimize the computation, the multiplication is not
  // needed everytime. Plus, make it a constant !
  SDL_Rect dst;
  dst.x = i_j * 32;
  dst.y = i_i * 32;
  dst.w = 32;
  dst.h = 32;

  assert(cell_images_.find(i_cell_type) != cell_images_.end());
  assert(cell_images_[i_cell_type] != NULL);
  SDL_BlitSurface(cell_images_[i_cell_type], &src, p_screen_, &dst);

}

void 
SdlInGameRenderer::flush() {
  assert(p_screen_ != NULL);
  SDL_Flip(p_screen_);
}

int
SdlInGameRenderer::load_cell_images() {
  int res = 0;
  int i = 0;
  int cell_types_count = Cell::CELL_TYPES_COUNT;
  const int * cell_types = Cell::CELL_TYPES;
  while (res == 0 && i < cell_types_count) {
    SDL_Surface * p_new_surface = NULL;
    LOG_D("sdl_in_game_renderer") << "Loading image for cell_type : " << cell_types[i];
    res = load_cell_image(cell_types[i], &p_new_surface);
    if (res == 0) {
      assert(p_new_surface != NULL);
      cell_images_[cell_types[i]] = p_new_surface;
    } 
    i++;
  }
  return res;
}

int
SdlInGameRenderer::load_cell_image(int i_cell_type, SDL_Surface ** o_pp_surface) {
  int res = -1;
  SDL_Surface * p_tmp;

  std::string image_name = str(format("cell_%1%.png") % i_cell_type);

  p_tmp = IMG_Load(dep_resolver_.get_image_file_name(image_name.c_str()).c_str());
  if (p_tmp != NULL) {
    *o_pp_surface = SDL_DisplayFormat(p_tmp);
    SDL_FreeSurface(p_tmp);
    res = 0;
  }

  return res;
}