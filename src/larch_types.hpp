#ifndef RACKAMTYPES_HPP
#define RACKAMTYPES_HPP

#include<vector>
#include<map>
#include<list>
#include<string>
#include<memory>


namespace Larch {
  class TCPConnection;
  class TCPListener;

  class WebServer;
  class WebRequest;
  class WebResponse;
  class WebDataFetcher;
  class WebStaticFile;

  typedef std::list<std::shared_ptr<WebStaticFile>> WebStaticFileList;
  typedef std::list<std::shared_ptr<WebStaticFile>>::iterator WebStaticFile_list_iterator;

}

#include<pthread.h>

#endif
