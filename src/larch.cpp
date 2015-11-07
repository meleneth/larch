#include <iostream>
#include "easylogging++.h"

#include "web_server.hpp"
#include "tcplistener.hpp"
#include "tcpconnection.hpp"

INITIALIZE_EASYLOGGINGPP

using namespace std;

int main(int argc, char *argv[]) {
  cout << "larch: larch\n";

  auto server = Larch::WebServer{"site", 4042};
  server.register_file("index.html", "bin/site/index.html", "text/html");

  fd_set read_fds;
  struct timeval tv;
  tv.tv_sec = 1;
  tv.tv_usec = 0;
  int fdmax = 0;
  int still_running = 1;

  // check for new incoming web request

  while (still_running) {
    FD_ZERO(&read_fds);

    FD_SET(server.listener->sockfd, &read_fds);
    fdmax = server.listener->sockfd;

    for (auto connection : server.connections) {
      int fd = connection->sockfd;
      FD_SET(fd, &read_fds);
      if (fdmax < fd) {
        fdmax = fd;
      }
    }

    int result;
    do {
      // result = select(fdmax+1, &read_fds, NULL, NULL, &tv);
      result = select(fdmax + 1, &read_fds, nullptr, nullptr, nullptr);
    } while ((result == -1) && (errno == EINTR));

    if (result == -1) {
      perror("select");
      exit(1);
    }

    if (FD_ISSET(server.listener->sockfd, &read_fds)) {
      server.handle_new_connection();
    }

    for (auto connection : server.connections) {
      if (FD_ISSET(connection->sockfd, &read_fds)) {
        connection->read_packets();
      }
    }

    server.tick();
  }

  return 0;
}
