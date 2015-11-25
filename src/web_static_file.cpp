#include <sys/stat.h>
#include <iostream>
#include <fstream>

#include "easylogging++.h"

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
