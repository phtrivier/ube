/**
 * This is Free Software. See COPYING for information.
 */

#ifndef _CHAPTER_SELECTION_GEOMETRY_HPP_
#define _CHAPTER_SELECTION_GEOMETRY_HPP_

#define CHAPTERS_X0 50
#define CHAPTERS_Y0 100
#define CHAPTERS_H 40
#define CHAPTERS_W 700
#define CHAPTERS_DELTA 20

// FIXME(pht) : adapt the geometry of this for later

/**
 * Geometry of the chapter selection screen
 */
class ChapterSelectionGeometry { 

public:

  int get_mouse_position_as_chapter_index(int i_x, int i_y);

  int get_chapter_name_x(int i_index);

  int get_chapter_name_y(int i_index);

};

#endif // _CHAPTER_SELECTION_GEOMETRY_HPP_
