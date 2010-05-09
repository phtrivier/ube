/**
 * This is Free Software. See COPYING for information.
 */
#include "chapter_selection_view.hpp"
#include "chapter_selection_model.hpp"

#include "engine/game_event.hpp"
#include "mvc/controller_interface.hpp"

void
ChapterSelectionView::render_game()
{
  SelectionView::render_game();
}

void
ChapterSelectionView::handle_event(int i_event)
{
  SelectionView::handle_event(i_event);
  if (i_event == GameEvent::MOUSE_CLICKED && dep_model_.has_selected()) {
    dep_controller_.fire_event(GameEvent::CHAPTER_SELECTED);
  }
}
