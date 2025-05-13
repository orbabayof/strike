#include <globals/globals.hpp>
#include <wayland-server-core.h>

extern "C"
{
  #include <wlroots-0.19/wlr/backend.h>
}

constexpr sk::globals_t& sk::globals_t::singleton()
{
  static globals_t global {};
  return global;
}

void sk::globals_t::init_phase_1()
{
  m_display.reset(wl_display_create());
  
  m_backend.reset
  (
    wlr_backend_autocreate 
    (
      wl_display_get_event_loop(display()), nullptr 
    )
  );
  
  m_renderer2d.reset(wlr_renderer_autocreate(backend()));
  wlr_renderer_init_wl_display(renderer2d(), display());
  m_allocator.reset(wlr_allocator_autocreate(backend(), renderer2d()));

  m_scene_tree = wlr_scene_create();
}
