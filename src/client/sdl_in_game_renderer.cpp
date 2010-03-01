#include "sdl_in_game_renderer.hpp"

#include "common/logging.hpp"
#include "common/resource_resolver_interface.hpp"

#include "engine/cell.hpp"
#include "engine/move.hpp"

#include "in_game_model.hpp"

#include <assert.h>

#include "SDL.h"
#include "SDL_image.h"

#include <vector>

#include "boost/format.hpp"
using namespace boost;

SdlInGameRenderer::~SdlInGameRenderer() {
  for (int cell_type = 0 ;  
       cell_type < Cell::CELL_TYPES_COUNT ; 
       cell_type++) {

    if (cell_images_.find(cell_type) != cell_images_.end()) {
      SDL_Surface * p_cell_image = cell_images_[cell_type];
      if (p_cell_image != NULL) {
	SDL_FreeSurface(p_cell_image);
      }
    }

  }

  // FIXME(pht) : use a nicer list of move types, make it more dynamic, etc..
  for (int move_type = 0 ; move_type <= MoveType::KNIGHT ; move_type++) {
    if (move_images_.find(move_type) != move_images_.end()) {
      SDL_Surface * p_move_image = move_images_[move_type];
      if (p_move_image != NULL) {
	SDL_FreeSurface(p_move_image);
      }
    }
  }

  if (p_selected_cell_image_ != NULL) {
    SDL_FreeSurface(p_selected_cell_image_);
  }

  if (p_banned_cell_image_ != NULL) {
    SDL_FreeSurface(p_banned_cell_image_);
  }

  if (p_player_image_ != NULL) {
    SDL_FreeSurface(p_player_image_);
  }

}

int
SdlInGameRenderer::init() {
  int res = -1;
  bool done = false;
  p_screen_ = SDL_SetVideoMode(640, 480, 8, SDL_SWSURFACE);
  if (p_screen_ != NULL) {
    res = load_cell_images();
    res = load_move_images();
    black_ = SDL_MapRGB(p_screen_->format, 0x00, 0x00, 0x00);
    //    while (!done && res != -1) {
    // FIXME(pht) : use a clever loop to try and load images and 
    // report the first error ...
    res = load_image("selected_cell.png", &p_selected_cell_image_);
    res = load_image("banned_cell.png", &p_banned_cell_image_);
    res = load_image("player.png", &p_player_image_);      
    done = true;
    //}
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
SdlInGameRenderer::mouse_x_as_puzzle_column(int i_x) {
  // TODO(pht) : Handler case where the position is bigger than the screen size
  int res = -1;
  if (i_x >= 0) {
    res = (i_x / 32);
  }
  return res;
}

int
SdlInGameRenderer::mouse_y_as_puzzle_line(int i_y) {
  // TODO(pht) : Handler case where the position is bigger than the screen size
  int res = -1;
  if (i_y >= 0) {
    res = (i_y / 32);
  }
  return res;
}

int
SdlInGameRenderer::mouse_position_as_move_index(int i_x, int i_y) 
{

  int res = -1;
  
  int x = i_x - 40;
  int y = i_y - 300;
  int w = 64 + 10;

  if (y >0 && y < 128) {
    if (x % w < 64) {
      res = x / w;
    }
  }

  return res;
}

void
SdlInGameRenderer::render_selected_cell(int i_i, int i_j) 
{
  /*
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

  assert(p_selected_cell_image_ != NULL);
  // SDL_BlitSurface(p_selected_cell_image_, &src, p_screen_, &dst);
  SDL_BlitSurface(p_banned_cell_image_, &src, p_screen_, &dst);
  */
  render_cell_image(i_i, i_j, p_selected_cell_image_);
}

void
SdlInGameRenderer::render_banned_cell(int i_i, int i_j) 
{
  render_cell_image(i_i, i_j, p_banned_cell_image_);
}

void
SdlInGameRenderer::render_player(int i_i, int i_j) {
  /*
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

  SDL_BlitSurface(p_player_image_, &src, p_screen_, &dst);
  */
  render_cell_image(i_i, i_j, p_player_image_);
}

void
SdlInGameRenderer::render_moves(InGameModel & i_model)
{
  // Hack : the current move first
  if (i_model.current_move_index() != -1) {
    render_current_move(i_model.current_move_index());
  }
  // THen the other available move
  std::vector<Move> & moves = i_model.get_puzzle().moves();
  std::vector<Move>::iterator it = moves.begin();
  for ( int index = 0 ; it != moves.end() ; ++it ) {
    Move current = *it;

    // TODO(pht) : if the move is not available, 
    // display it with another color, or something
    if (i_model.get_puzzle().moves()[index].available()) {
      render_move(current, index);
    }

    index++;
  }
}

/* ----------------- */

void
SdlInGameRenderer::render_move(Move & i_move, int i_index) 
{
  SDL_Rect src;
  src.x = src.y = 0;
  src.w = 64;
  src.h = 128;

  SDL_Rect dst;
  dst.x = 40 + i_index*(64 + 10);
  dst.y = 300;
  dst.w = 64;
  dst.h = 128;

  assert(move_images_.find(i_move.type()) != move_images_.end());
  assert(move_images_[i_move.type()] != NULL);
  SDL_BlitSurface(move_images_[i_move.type()], &src, p_screen_, &dst);
}

// TODO(pht) : fix this
void
SdlInGameRenderer::render_current_move(int i_move_index) {
SDL_Rect dst;
  dst.x = 40 + i_move_index*(64 + 10) - 5;
  dst.y = 300 - 5;
  dst.w = 64 + 10;
  dst.h = 128 + 10;
  SDL_FillRect(p_screen_, &dst, SDL_MapRGB(p_screen_->format, 255,0,0));
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
SdlInGameRenderer::load_move_images() {
  int res = 0;
  // FIXME(pht) : use nicer list of move types
  for (int move_type = 0 ; move_type <= MoveType::KNIGHT ; move_type ++) {
    SDL_Surface * p_new_surface = NULL;
    LOG_D("sdl_in_game_renderer") << "Loading image for move_type : " << move_type;
    res = load_move_image(move_type, &p_new_surface);
    if (res == 0) {
      assert(p_new_surface != NULL);
      move_images_[move_type] = p_new_surface;
    } 
  }
  return res;
}


int
SdlInGameRenderer::load_cell_image(int i_cell_type, SDL_Surface ** o_pp_surface) {
  int res = -1;
  std::string image_name = str(format("cell_%1%.png") % i_cell_type);
  res = load_image(image_name, o_pp_surface);
  return res;
}

// TODO(pht) : refactor both codes
int
SdlInGameRenderer::load_move_image(int i_move_type, SDL_Surface ** o_pp_surface) {
  int res = -1;
  std::string image_name = str(format("move_%1%.png") % i_move_type);
  res = load_image(image_name, o_pp_surface);
  return res;
}

int
SdlInGameRenderer::load_image(std::string i_image_name, SDL_Surface ** o_pp_surface) {
  int res = -1;
  SDL_Surface * p_tmp = IMG_Load(dep_resolver_.get_image_file_name(i_image_name.c_str()).c_str());
  if (p_tmp != NULL) {
    *o_pp_surface = SDL_DisplayFormatAlpha(p_tmp);
    SDL_FreeSurface(p_tmp);
    res = 0;
  }
  return res;
}

void
SdlInGameRenderer::render_cell_image(int i_i, int i_j, SDL_Surface * i_p_surface) {
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

  SDL_BlitSurface(i_p_surface, &src, p_screen_, &dst);
}
