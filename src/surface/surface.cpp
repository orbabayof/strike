#include <surface/surface.hpp>
#include <globals/globals.hpp>

extern "C"
{
  #include "../wlroots_headers_for_cpp/wlr_scene.h"
  #include <wlroots-0.19/wlr/types/wlr_xdg_shell.h>
}

sk::surface_t::surface_t(struct wlr_surface* wlr_surface)
  : m_wlr_surface { wlr_surface }
  , m_scene_surface { wlr_scene_surface_create(&globals_t::singleton().scene()->tree, wlr_surface) }
  , m_on_destroy { &wlr_surface->events.destroy }
  , m_on_commit { &wlr_surface->events.commit }
{
  m_on_destroy.set_callback([this](listener_t*, void*)
  {
    delete this;   
  });

  m_on_commit.set_callback([this](listener_t*, void*)
  {
    if(auto* toplevel = wlr_xdg_toplevel_try_from_wlr_surface(this->m_wlr_surface); toplevel && toplevel->base->initial_commit)
    {
      wlr_xdg_toplevel_set_size(toplevel, 0, 0);
    }
  });
}
