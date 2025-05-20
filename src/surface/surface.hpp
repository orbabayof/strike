#pragma once

#include "listener/listener.hpp"
#include <defines.hpp>
#include <memory>
#include <destroy.hpp>

extern "C"
{
  #include "../wlroots_headers_for_cpp/wlr_scene.h"
}
namespace sk
{
  class surface_t
  {
  public:

    using scene_surface_t = wlr_scene_surface;

    surface_t(struct wlr_surface* wlr_surface);
  private:

  
    wlr_surface* m_wlr_surface;
    std::unique_ptr<scene_surface_t> m_scene_surface;

    listener_t m_on_destroy;
    listener_t m_on_commit;
  };
}
