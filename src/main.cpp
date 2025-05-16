#include "compositor/compositor.hpp"
#include "listener/listener.hpp"
#include <globals/globals.hpp>

#include <cstdlib>
#include <iostream>
#include <wayland-server-core.h>
#include <unistd.h>
#include <boost/process/v1/spawn.hpp>

extern "C"
{
  #include <wlroots-0.19/wlr/types/wlr_xdg_shell.h>
}

int main()
{
  auto& globals { sk::globals_t::singleton() }; 
  globals.init();

  sk::compositor_t compositor {};

  wlr_xdg_shell_create(globals.display(), 2);
  wlr_backend_start(globals.backend());

  //socket is converted from c_str so it is null terminated
  setenv("WAYLAND_DISPLAY", globals.socket().data(), true);
  boost::process::v1::spawn("weston-flower");
  

  wl_display_run(globals.display());
  return EXIT_SUCCESS;
}
