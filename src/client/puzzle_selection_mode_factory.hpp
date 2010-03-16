#ifndef _PUZZLE_SELECTION_MODE_FACTORY_HPP_
#define _PUZZLE_SELECTION_MODE_FACTORY_HPP_

#include <string>

#include <boost/shared_ptr.hpp>

class GameMode;
class PuzzleSelectionRendererInterface;
class PuzzleSelectionView;
class PuzzleSelectionModel;
class SdlController;
class GameModeInterface;

/**
 * Factory to create and initialize a puzzle selection mode
 */
class PuzzleSelectionModeFactory { 

public:

  PuzzleSelectionModeFactory(PuzzleSelectionRendererInterface & dep_renderer) :
    dep_renderer_(dep_renderer)
  {
  }

  ~PuzzleSelectionModeFactory();

  int create_mode();

  boost::shared_ptr<GameModeInterface> & get_mode() {
    return mode_;
  }

private:

  PuzzleSelectionRendererInterface & dep_renderer_;
  
  SdlController * p_controller_;
  PuzzleSelectionModel * p_model_;
  PuzzleSelectionView * p_view_;

  boost::shared_ptr<GameModeInterface> mode_;

};

#endif // _PUZZLE_SELECTION_MODE_FACTORY_HPP_
