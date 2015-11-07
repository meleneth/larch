#ifndef ___webdatafetcher_inc
#define ___webdatafetcher_inc 1

#include <string>
#include <vector>

#include "larch_types.hpp"

namespace Larch {
class WebDataFetcher {
 public:
  WebDataFetcher(WebRequest *request);
  virtual ~WebDataFetcher();

  virtual int tick(void);
  virtual std::string info_update_string(void);
  std::string table_id(std::string id);

  WebRequest *request;

  std::vector<std::string> output_lines;
  unsigned int line_no;
  unsigned int num_lines;
  std::string title;

 private:
 protected:
};
}

#endif
