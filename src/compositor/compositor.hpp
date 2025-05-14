#pragma once

#include <defines.hpp>
#include <listener/listener.hpp>

extern "C"
{
  #include <wlroots-0.19/wlr/types/wlr_compositor.h>
}

namespace sk
{
  class compositor_t
  {
  public:

    static constexpr int wlr_compositor_version { 5 };

    compositor_t();

    wlr_compositor* wlr() { return m_compositor; }

  private:
  
    wlr_compositor* m_compositor;
    listener_t m_on_new_surface; 
              
  };
}
