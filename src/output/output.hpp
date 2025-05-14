#pragma once

#include <defines.hpp>
#include <listener/listener.hpp>

extern "C"
{
  #include <wlr/types/wlr_output.h>
  #include <../wlroots_headers_for_cpp/wlr_scene.h>
}
namespace sk
{
  class output_t
  {
  public:

    using state_t = wlr_output_state;
    using mode_t = wlr_output_mode;

    output_t(wlr_output* wlr_output);

    //sets size and refresh rate
    void set_mode();
    void create_global();

  private:

    wlr_output* m_wlr_output;
    wlr_scene_output* m_scene_output;

    listener_t m_on_frame;
    listener_t m_on_destroy;
  };
}
