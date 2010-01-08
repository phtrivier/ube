#ifndef _IN_GAME_RENDERER_INTERFACE_HPP_
#define _IN_GAME_RENDERER_INTERFACE_HPP_


/**
 * renderer for in game view.
 */
class InGameRendererInterface { 

public:

  virtual ~InGameRendererInterface() {
  }

  /**
   * Clears the screen
   */
  virtual void clear() = 0;
  
  /**
   * Renders a cell at a given position.
   */
  virtual void render_cell(int i_i, int i_j, int i_cell_type) = 0;

  /**
   * Finalize renderering
   */
  virtual void flush() = 0;
  
};

#endif // _IN_GAME_RENDERER_INTERFACE_HPP_
