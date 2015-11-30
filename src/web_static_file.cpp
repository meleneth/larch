#include <sys/stat.h>
#include <iostream>
#include <fstream>

#include "easylogging++.h"
#include "pstream.h"

#include "web_static_file.hpp"

using namespace Larch;

void WebStaticFile::load_file(std::string filename) {
  struct stat file_stats;
  stat(filename.c_str(), &file_stats);
  st_atim = file_stats.st_atim;

  auto num_bytes = file_stats.st_size;
  buffer.resize(num_bytes);

  std::ifstream infile;
  infile.open(filename, std::ios::binary | std::ios::in);
  infile.read(&buffer[0], num_bytes);
  infile.close();

  this->filename = filename;

  LOG(INFO) << "Loaded file " << filename;
}

bool WebStaticFile::is_file_stale() {
  struct stat file_stats;
  stat(filename.c_str(), &file_stats);
  return st_atim.tv_sec < file_stats.st_atim.tv_sec;
}

void WebStaticFile::reload_if_stale() {
  if (is_file_stale()) {
    load_file(filename);
  }
}

void WebStaticFile::compile_coffeescript() {
  LOG(INFO) << "compile_coffeescript()";
  using namespace redi;
  std::vector<char> temp_buffer;

  const pstreams::pmode mode = pstreams::pstdout | pstreams::pstdin;
  ipstream child("coffee -p -s", mode);
  child.write(&buffer[0], buffer.size());
  temp_buffer.reserve(256000);
  child.out().read(&temp_buffer[0], temp_buffer.capacity());
  buffer = temp_buffer;
}
