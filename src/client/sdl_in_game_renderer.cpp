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

  clear_image(p_bg_);
  clear_image(p_undo_image_);
  clear_image(p_redo_image_);
  clear_image(p_disabled_undo_image_);
  clear_image(p_disabled_redo_image_);

}

int
SdlInGameRenderer::init() {
  int res = -1;
  res = load_cell_images();
  res = load_move_images();
  //    while (!done && res != -1) {
  // FIXME(pht) : use a clever loop to try and load images and 
  // report the first error ...
  res = load_image("selected_cell.png", &p_selected_cell_image_);
  res = load_image("banned_cell.png", &p_banned_cell_image_);
  res = load_image("player.png", &p_player_image_);      
  res = load_image("bg.png", &p_bg_);
  
  res = load_image("undo.png", &p_undo_image_);
  res = load_image("redo.png", &p_redo_image_);
  res = load_image("disabled_undo.png", &p_disabled_undo_image_);
  res = load_image("disabled_redo.png", &p_disabled_redo_image_);

  return res;
}

void
SdlInGameRenderer::clear() {
  assert(get_screen() != NULL);
  SDL_BlitSurface(p_bg_, NULL, get_screen(), NULL);
}

void
SdlInGameRenderer::flush() 
{
  SdlRenderer::flush();
}

void 
SdlInGameRenderer::render_cell(int i_i, int i_j, int i_cell_type) {
  assert(cell_images_.find(i_cell_type) != cell_images_.end());
  assert(cell_images_[i_cell_type] != NULL);
  render_cell_image(i_i, i_j, cell_images_[i_cell_type]);
}

void
SdlInGameRenderer::render_selected_cell(int i_i, int i_j) 
{
  render_cell_image(i_i, i_j, p_selected_cell_image_);
}

void
SdlInGameRenderer::render_banned_cell(int i_i, int i_j) 
{
  render_cell_image(i_i, i_j, p_banned_cell_image_);
}

void
SdlInGameRenderer::render_player(int i_i, int i_j) {
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
  src.w = MOVES_W;
  src.h = MOVES_H;

  SDL_Rect dst;
  dst.x = MOVES_X + i_index*(MOVES_W + 10);
  dst.y = MOVES_Y;
  dst.w = MOVES_W;
  dst.h = MOVES_H;

  assert(move_images_.find(i_move.type()) != move_images_.end());
  assert(move_images_[i_move.type()] != NULL);
  SDL_BlitSurface(move_images_[i_move.type()], &src, get_screen(), &dst);
}

// TODO(pht) : fix this
void
SdlInGameRenderer::render_current_move(int i_move_index) {
SDL_Rect dst;
  dst.x = MOVES_X + i_move_index*(MOVES_W + 10) - 5;
  dst.y = MOVES_Y - 5;
  dst.w = MOVES_W + 10;
  dst.h = MOVES_H + 10;
  SDL_FillRect(get_screen(), &dst, SDL_MapRGB(get_screen()->format, 255,0,0));
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


void
SdlInGameRenderer::render_cell_image(int i_i, int i_j, SDL_Surface * i_p_surface) {
  // TODO : make this a constant instead of recreating
  SDL_Rect src;
  src.x = 0;
  src.y = 0;
  src.w = CELLS_W;
  src.h = CELLS_H;
  // TODO : Optimize the computation, the multiplication is not
  // needed everytime. Plus, make it a constant !
  SDL_Rect dst;
  dst.x = CELLS_X + (i_j * CELLS_W);
  dst.y = CELLS_Y + (i_i * CELLS_H);
  dst.w = CELLS_W;
  dst.h = CELLS_H;

  SDL_BlitSurface(i_p_surface, &src, get_screen(), &dst);
}

int 
SdlInGameRenderer::mouse_x_as_puzzle_column(int i_x) {
  return InGameRendererGeometry::mouse_x_as_puzzle_column(i_x);
}

int 
SdlInGameRenderer::mouse_y_as_puzzle_line(int i_y) {
  return InGameRendererGeometry::mouse_y_as_puzzle_line(i_y);
}

int 
SdlInGameRenderer::mouse_position_as_move_index(int i_x, int i_y) {
  return InGameRendererGeometry::mouse_position_as_move_index(i_x,i_y);
}

void
SdlInGameRenderer::render_ui(bool i_can_undo, bool i_can_redo) {

  SDL_Rect dst;
  dst.x = UNDO_X;
  dst.y = UNDO_Y;
  if (i_can_undo) {
    SDL_BlitSurface(p_undo_image_, NULL, get_screen(), &dst);
  } else {
    SDL_BlitSurface(p_disabled_undo_image_, NULL, get_screen(), &dst);
  }

  dst.x = REDO_X;
  dst.y = REDO_Y;
  if (i_can_redo) {
    SDL_BlitSurface(p_redo_image_, NULL, get_screen(), &dst);
  } else {
    SDL_BlitSurface(p_disabled_redo_image_, NULL, get_screen(), &dst);
  }


}

bool
SdlInGameRenderer::is_on_undo_button(int i_x, int i_y) {
  return InGameRendererGeometry::is_on_undo_button(i_x,i_y);
}

bool
SdlInGameRenderer::is_on_redo_button(int i_x, int i_y) {
  return InGameRendererGeometry::is_on_redo_button(i_x,i_y);
}

