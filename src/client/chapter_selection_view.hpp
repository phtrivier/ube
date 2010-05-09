#ifndef _CHAPTER_SELECTION_VIEW_HPP_
#define _CHAPTER_SELECTION_VIEW_HPP_

#include "selection_renderer_interface.hpp"
#include "selection_view.hpp"
#include "chapter_selection_model.hpp"

/**
 * view to display the selection of a chapter
 */
class ChapterSelectionView : 
  public SelectionView
{ 

public:

  ChapterSelectionView(SelectionRendererInterface & dep_renderer,
		      ChapterSelectionModel & dep_model,
		      ControllerInterface & dep_controller) :
    SelectionView(dep_renderer, dep_model, dep_controller)
  {
  }

  ~ChapterSelectionView() {
  }

  void render_game();

  void handle_event(int iEventCode);

};

#endif // _CHAPTER_SELECTION_VIEW_HPP_
