/**
 * This is Free Software. See COPYING for information.
 */
#ifndef _RENDERER_INTERFACE_HPP_
#define _RENDERER_INTERFACE_HPP_


/**
 * Anything that can render to the screen.
 */
class RendererInterface { 

public:

  virtual ~RendererInterface() {
  }

  /**
   * Clears the screen
   */
  virtual void clear() = 0;

  /**
   * Finalize renderering
   */
  virtual void flush() = 0;

};

#endif // _RENDERER_INTERFACE_HPP_