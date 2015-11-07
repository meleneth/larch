#ifndef RACKAMTYPES_HPP
#define RACKAMTYPES_HPP

#include <vector>
#include <map>
#include <list>
#include <string>
#include <memory>

namespace Larch {
class TCPConnection;
class TCPListener;

class WebServer;
class WebRequest;
class WebResponse;
class WebDataFetcher;
class WebStaticFile;

using WebStaticFileList =  std::list<std::shared_ptr<WebStaticFile>>;
using WebStaticFile_list_iterator =  std::list<std::shared_ptr<WebStaticFile>>::iterator;
}

#include <pthread.h>

#endif
