#ifndef _ABSTRACT_VIEW_HPP_
#define _ABSTRACT_VIEW_HPP_


/**
 * A generic view.
 */
class AbstractView { 

public:

  AbstractView(){
  }
  virtual ~AbstractView() {
  }

  virtual void render_game() = 0;
  
};

#endif // _ABSTRACT_VIEW_HPP_
