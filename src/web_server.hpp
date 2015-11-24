#ifndef WEBSERVER_HPP
#define WEBSERVER_HPP

#include <larch_types.hpp>

#include <string>
#include <list>
#include <memory>

// This entire webserver is such a non-standard-using
// non RFC piece of work, that this program shouldn't
// even be using it.

namespace Larch {

class WebServer {
 public:
  WebServer(std::string web_root, int port_no) : web_root(web_root), listener{ std::make_unique<TCPListener>(port_no) } {}

  void log_to_file(std::string filename);
  void handle_request(WebRequest *request);
  void handle_new_connection(void);
  void register_file(std::string url, std::string filename,
                     std::string content_type);
  void tick(void);

  std::unique_ptr<Larch::TCPListener> listener;
  std::list<TCPConnection *> connections;
  std::list<WebDataFetcher *> handlers;
  std::string web_root;

  WebStaticFileList static_contents;

 private:
 protected:
};
}

#endif
