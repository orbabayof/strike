#include "compositor/compositor.hpp"
#include "listener/listener.hpp"
#include <globals/globals.hpp>
#include <util/util.hpp>

#include <cstdlib>
#include <iostream>
#include <string_view>
#include <wayland-server-core.h>
#include <util/util.hpp>

extern "C"
{
  #include <wlroots-0.19/wlr/types/wlr_xdg_shell.h>
  #include <wlroots-0.19/wlr/types/wlr_subcompositor.h>
  #include <wlroots-0.19/wlr/types/wlr_data_device.h>
  #include <wlroots-0.19/wlr/util/log.h>
}


int main(int argv, const char* argc[])
{
  wlr_log_init(WLR_DEBUG, nullptr);
  auto& globals { sk::globals_t::singleton() }; 
  globals.init();

  sk::compositor_t compositor {};

  wlr_xdg_shell_create(globals.display(), 2);
  wlr_backend_start(globals.backend());

  wlr_subcompositor_create(globals.display());
  wlr_data_device_manager_create(globals.display());

  //socket is converted from c_str so it is null terminated
  setenv("WAYLAND_DISPLAY", globals.socket().data(), true);
  namespace su = sk::util;
  if(argv == 2)
    su::proccess::spawn_proccess(argc[1]);
  

  wl_display_run(globals.display());
  return EXIT_SUCCESS;
}
