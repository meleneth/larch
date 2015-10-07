#include "web_static_file.hpp"

using namespace Larch;

WebStaticFile::WebStaticFile()
{
  buffer = nullptr;
}

WebStaticFile::~WebStaticFile()
{
  if(buffer) {
    free(buffer);
  }
}
