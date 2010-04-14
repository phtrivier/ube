/**
 * This is Free Software. See COPYING for information.
 */
#ifndef _SILENT_OSTREAM_HPP_
#define _SILENT_OSTREAM_HPP_

#include <iostream>

/**
 * Silent ostream. Can't believe I'm the first one in the world to need that ...
 */
class SilentOstream :
  public std::ostream
{ 
private:

  std::streambuf* setbuf(char_type* s, std::streamsize n) {
    return NULL;
  }

  int_type overflow(int_type c) {
    return traits_type::not_eof( c ) ;
  }

  int sync() { 
    return 0; 
  }

};

#endif // _SILENT_OSTREAM_HPP_