#include <compositor/compositor.hpp>
#include <globals/globals.hpp>

sk::compositor_t::compositor_t()
  : m_compositor( wlr_compositor_create( globals_t::singleton().display(), wlr_compositor_version ,globals_t::singleton().renderer2d() ) )
  , m_on_new_surface { &m_compositor->events.new_surface }
{  
  m_on_new_surface.set_callback([](listener_t* , void*)
  {

  });
}
