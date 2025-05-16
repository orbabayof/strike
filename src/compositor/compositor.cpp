#include <compositor/compositor.hpp>
#include <globals/globals.hpp>
#include <surface/surface.hpp>

sk::compositor_t::compositor_t()
  : m_compositor( wlr_compositor_create( globals_t::singleton().display(), wlr_compositor_version ,globals_t::singleton().renderer2d() ) )
  , m_on_new_surface { &m_compositor->events.new_surface }
{  
  m_on_new_surface.set_callback([](listener_t* , void* data)
  {
    auto* wlr_surface { static_cast<struct wlr_surface*>(data) };

    //will be deleted in destroy notify
    //declares his own listeners
    [[__maybe_unused__]]auto* surface = new surface_t{ wlr_surface };
  });
}
