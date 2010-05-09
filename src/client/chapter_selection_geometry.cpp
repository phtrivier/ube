/**
 * This is Free Software. See COPYING for information.
 */

#include "chapter_selection_geometry.hpp"

int
ChapterSelectionGeometry::get_mouse_position_as_chapter_index(int i_x, int i_y) 
{
  int res = -1;
  int x = i_x - CHAPTERS_X0;
  int y = i_y - CHAPTERS_Y0;
  if (x > 0 && x < CHAPTERS_W) {
    if (y > 0 ) {
      // NOTE(pht) : I know, this does'nt take the delta into
      // account, but that's just not important for the 
      // moment
      res = (y / CHAPTERS_H); 
    }
  }
  return res;

}

int
ChapterSelectionGeometry::get_chapter_name_x(int i_index)
{
  return CHAPTERS_X0;
}

int
ChapterSelectionGeometry::get_chapter_name_y(int i_index)
{
  return CHAPTERS_Y0 + (CHAPTERS_H *i_index + CHAPTERS_DELTA);
}
