#ifndef WEBSTATICFILE_HPP
#define WEBSTATICFILE_HPP

#include <larch_types.hpp>

namespace Larch {

class WebStaticFile {
 public:
  WebStaticFile();
  ~WebStaticFile();

  std::string url;
  std::string filename;
  std::string content_type;
  char *buffer;
  int content_length;
};
}

#endif
