#ifndef _SDL_IN_GAME_RENDERER_HPP_
#define _SDL_IN_GAME_RENDERER_HPP_

#include "in_game_renderer_interface.hpp"

#include <map>
#include <string>
#include <vector>

#include "SDL.h"

class InGameModel;

class Move;

class ResourceResolverInterface;

/**
 * InGameRenderer that uses SDL to do the renderering.
 * Note(pht) : this could actually become simply an SdlRenderer, and
 * implements several interfaces, since I don't want to scater the code to init videos an stuff
 * everywhere in the code .... 
 */
class SdlInGameRenderer : 
  public InGameRendererInterface
{ 

public:
  explicit SdlInGameRenderer(ResourceResolverInterface & dep_resolver) : 
    InGameRendererInterface(),
    dep_resolver_(dep_resolver),
    p_screen_(NULL),
    p_selected_cell_image_(NULL),
    p_banned_cell_image_(NULL),
    p_player_image_(NULL)
  {

  }

  ~SdlInGameRenderer();

  /**
   * Initialize the renderer.
   * @return 0 if initialization went fine, -1 otherwise.
   *  If an error occurs, it is probably a good idea to look at SDL_GetError for
   *  more info.
   */ 
  int init();

  void clear();

  void render_cell(int i_i, int i_j, int i_cell_type);

  void flush();

  int mouse_x_as_puzzle_column(int i_x);

  int mouse_y_as_puzzle_line(int i_y);

  int mouse_position_as_move_index(int i_x, int i_y);
  
  void render_selected_cell(int i_i, int i_j);

  void render_player(int i_i, int i_j);

  void render_moves(InGameModel & i_model);

private:

  ResourceResolverInterface & dep_resolver_;

  std::map<int, SDL_Surface *> cell_images_;

  std::map<int, SDL_Surface *> move_images_;

  SDL_Surface * p_screen_;

  SDL_Surface * p_selected_cell_image_;

  SDL_Surface * p_banned_cell_image_;
  
  SDL_Surface * p_player_image_;

  Uint32 black_;

  /**
   * Load all the images necessary to display
   * cells.
   *
   * @returns 0 if image was loaded, -1 otherwise
   */
  int load_cell_images();

  /**
   * Load all the images necessary to display
   * moves.
   *
   * @returns 0 if image was loaded, -1 otherwise
   */
  int load_move_images();

  /**
   * Load the image necessary to display a cell.
   * 
   * @param i_cell_type 
   * @param o_pp_surface output address of the image after loading
   * @returns 0 if cell was loaded, -1 otherwise.
   */
  int load_cell_image(int i_cell_type, SDL_Surface ** o_pp_surface);

  /**
   * Load the image necessary to display a move.
   * 
   * @param i_move_type 
   * @param o_pp_surface output address of the image after loading
   * @returns 0 if cell was loaded, -1 otherwise.
   */
  int load_move_image(int i_move_type, SDL_Surface ** o_pp_surface);

  /**
   * Loads an image by its name.
   *
   * @param i_image_name name with suffix (eg "cell_0.png")
   * @param o_pp_surface output address of the surface afer loading
   * @returns 0 if image was loaded, -1 otherwise.
   */
  int load_image(std::string i_image_name, SDL_Surface ** o_pp_surface);

  /**
   * Display the icon of a given move.
   *
   * @param i_move : the move which icon has to be displayed
   * @param i_index : index of the move icon
   */
  void render_move(Move & i_move, int i_index);

  /**
   * Render the currently selected move
   */
  void render_current_move(int i_move_index);


};

#endif // _SDL_IN_GAME_RENDERER_HPP_
