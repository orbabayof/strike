#include "listener/listener.hpp"
#include <defines.hpp>
#include <xkbcommon/xkbcommon.h>

extern "C"
{
  #include <wlroots-0.19/wlr/types/wlr_keyboard.h>
}

namespace sk
{
  class keyboard_t
  {
  public:

    keyboard_t(wlr_keyboard* keyboard, wlr_input_device* wlr_input_device);

    bool set_keymap();
      

  private:
       
    wlr_keyboard* m_wlr;

    listener_t m_on_destroy;
    listener_t m_on_key_press;

    static uint32_t xkb_keycode_to_wlr_keycode(uint32_t xkb_keycode) { return xkb_keycode + 8; }
    
  };
}
