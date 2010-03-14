#ifndef _CLOCK_INTERFACE_HPP_
#define _CLOCK_INTERFACE_HPP_

/**
 * Clock used to time what happens in the game loop
 *
 */
class ClockInterface { 

public:

  ClockInterface() {
  }

  virtual ~ClockInterface(){
  }

  /**
   * Initialize the loop.
   */
  virtual void init() = 0;
  
  /**
   * Reset the clock for the beginning of a new game loop.
   */
  virtual void restart() = 0;

  
  /**
   * Should there be a rendering now ?
   */
  virtual bool is_time_to_render() = 0;

  /**
   * Advance in time.
   */
  virtual void tick() = 0;

  /**
   * Get the number of milliseconds elapsed since last tick.
   */
  virtual int get_delta() = 0;

};

#endif // _CLOCK_INTERFACE_HPP_
