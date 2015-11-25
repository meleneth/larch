#ifndef WEBSTATICFILE_HPP
#define WEBSTATICFILE_HPP

#include<sys/types.h>
#include <larch_types.hpp>

namespace Larch {

class WebStaticFile {
 public:
  std::string url;
  std::string filename;
  std::string content_type;

  std::vector<char> buffer;

  struct timespec st_atim;

  void load_file(std::string filename);
  void reload_if_stale();
  bool is_file_stale();
};
}

#endif
