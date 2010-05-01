/**
 * This is Free Software. See COPYING for information.
 */
#ifndef _SDL_IN_GAME_RENDERER_HPP_
#define _SDL_IN_GAME_RENDERER_HPP_

#include "in_game_renderer_interface.hpp"
#include "in_game_renderer_geometry.hpp"

#include "sdl_renderer.hpp"

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
  public InGameRendererInterface,
  public InGameRendererGeometry,
  public SdlRenderer
{ 

public:
  SdlInGameRenderer(ResourceResolverInterface & dep_resolver, SDL_Surface * dep_p_screen) : 
    InGameRendererInterface(),
    InGameRendererGeometry(),
    SdlRenderer(dep_resolver, dep_p_screen),
    p_selected_cell_image_(NULL), p_banned_cell_image_(NULL),
    p_player_image_(NULL),
    p_bg_(NULL), p_undo_image_(NULL), p_redo_image_(NULL),
    p_disabled_undo_image_(NULL), p_disabled_redo_image_(NULL),
    p_msg_box_image_(NULL),
    p_msg_font_(NULL)
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

  void flush();

  void render_cell(int i_i, int i_j, int i_cell_type);

  int mouse_x_as_puzzle_column(int i_x);

  int mouse_y_as_puzzle_line(int i_y);

  int mouse_position_as_move_index(int i_x, int i_y);
  
  void render_cell_in_path(int i_i, int i_j, int i_move_type);

  void render_banned_cell(int i_i, int i_j);

  void render_player(int i_i, int i_j);

  void render_moves(InGameModel & i_model);

  void render_ui(bool i_can_undo, bool i_can_redo);

  bool is_on_undo_button(int i_x, int i_y);
  
  bool is_on_redo_button(int i_x, int i_y);

  void render_overlay(int i_i, int i_j, int i_overlay_type); 

  void render_message(std::string i_msg);
    
  bool is_on_msg_button(int i_x, int i_y);

private:

  std::map<int, SDL_Surface *> cell_images_;
  std::map<int, SDL_Surface *> move_images_;
  std::map<int, SDL_Surface *> grayed_move_images_;
  std::map<int, SDL_Surface *> overlay_images_;
  std::map<int, SDL_Surface *> path_images_;

  SDL_Surface * p_selected_cell_image_;

  SDL_Surface * p_banned_cell_image_;
  
  SDL_Surface * p_player_image_;

  SDL_Surface * p_bg_;

  SDL_Surface * p_undo_image_;
  SDL_Surface * p_redo_image_;
  SDL_Surface * p_disabled_undo_image_;
  SDL_Surface * p_disabled_redo_image_;

  SDL_Surface * p_msg_box_image_;

  TTF_Font * p_msg_font_;


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
   * Load all the images necessary to display
   * overlays.
   *
   * @returns 0 if image was loaded, -1 otherwise
   */
  int load_overlay_images();

  /**
   * Load all the images necessary to display
   * paths.
   *
   * @returns 0 if image was loaded, -1 otherwise
   */
  int load_path_images();

  /**
   * Load images by move types, based on a format
   *
   * @param i_map map to contain the images
   * @param i_format boost:format string format to get the image (eg : 'move_%1%.png'.) 
   *   %1% is replaced by the move_type.
   */
  int load_images_for_move_types(std::map<int, SDL_Surface *> & i_map, std::string i_format);

  /**
   * Load one image by move types, based on a format
   *
   * @param i_move_type
   * @param i_format boost:format string format to get the image (eg : 'move_%1%.png'.) 
   *   %1% is replaced by the move_type.
   * @param o_pp_surface address of the surface to hold the image
   */
  int load_image_for_move_type(int i_move_type, std::string & i_format, SDL_Surface ** o_pp_surface);

  /**
   * Load the image necessary to display a cell.
   * 
   * @param i_cell_type 
   * @param o_pp_surface output address of the image after loading
   * @returns 0 if cell was loaded, -1 otherwise.
   */
  int load_cell_image(int i_cell_type, SDL_Surface ** o_pp_surface);

  /**
   * Display the icon of a given move.
   *
   * @param i_move : the move which icon has to be displayed
   * @param i_index : index of the move icon
   * @param i_is_available : is the move available
   */
  void render_move(Move & i_move, int i_index, bool i_is_available);

  /**
   * Render the currently selected move
   */
  void render_current_move(int i_move_index);

  /**
   * Render the move that mouse is rolling one
   */
  void render_hovered_move(int i_move_index);

  /**
   * Render an image on a cell.
   */
  void render_cell_image(int i_i, int i_j, SDL_Surface * i_p_surface);

  /**
   * Clears a map, attempting to free surfaces
   * for all integer values.
   */
  void clear_image_map(std::map<int, SDL_Surface * > & i_map, int i_limit);
  
  /**
   * A rectangle to surround a move button at a given index
   * @param i_move_index index of the move, should be valid.
   */
  SDL_Rect move_surrounding_rect(int i_move_index);


};

#endif // _SDL_IN_GAME_RENDERER_HPP_
