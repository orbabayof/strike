#pragma once

#include <defines.hpp>
#include <listener/listener.hpp>

extern "C"
{
  #include <wlr/types/wlr_output.h>
}
namespace sk
{
  class output_t
  {
  public:

    output_t(wlr_output* wlr_output);

    //sets size and refresh rate
    void set_mode();

  private:

    wlr_output* m_wlr_output;

    listener_t m_on_frame;
    listener_t m_on_destroy;
  };
}
