#include <functional>
#include <output/output.hpp>

#include <globals/globals.hpp>



sk::output_t::output_t(wlr_output* wlr_output)
  : m_wlr_output { wlr_output }
  , m_on_frame { &wlr_output->events.frame }
  , m_on_destroy { &wlr_output->events.destroy }
{
  m_on_destroy.set_callback([](listener_t* listener, void* data)
  {
  
  });

  m_on_frame.set_callback([](listener_t* listener, void* data)
  {
  
  });
}
