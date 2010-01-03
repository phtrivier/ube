#ifndef _VIEW_INTERFACE_HPP_
#define _VIEW_INTERFACE_HPP_


/**
 * A generic view.
 */
class ViewInterface { 

public:

  virtual ~ViewInterface() {
  }

  virtual void render_game() = 0;
  
};

#endif // _VIEW_INTERFACE_HPP_
