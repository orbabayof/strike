#include "compositor/compositor.hpp"
#include "listener/listener.hpp"
#include <globals/globals.hpp>

#include <cstdlib>
#include <iostream>
#include <wayland-server-core.h>

int main()
{
  auto& globals { sk::globals_t::singleton() }; 
  globals.init();

  sk::compositor_t compositor {};

  wlr_backend_start(globals.backend());

  //socket is converted from c_str so it is null terminated
  setenv("WAYLAND_DISPLAY", globals.socket().data(), true);

  wl_display_run(globals.display());
  return EXIT_SUCCESS;
}
