#include <algorithm>
#include <cstdint>
#include <keyboard/keyboard.hpp>
#include <destroy.hpp>
#include <globals/globals.hpp>
#include <carray_wrapper.hpp>

#include <memory>
#include <wayland-server-core.h>
#include <xkbcommon/xkbcommon-keysyms.h>
#include <xkbcommon/xkbcommon.h>

sk::keyboard_t::keyboard_t(wlr_keyboard* wlr_keyboard, wlr_input_device* wlr_input_device)
  : m_wlr { wlr_keyboard }
  , m_on_destroy { &wlr_input_device->events.destroy }
  , m_on_key_press { &wlr_keyboard->events.key }
{
  m_on_destroy.set_callback([this](listener_t*, void*)
  {
    delete this;
  });

  m_on_key_press.set_callback([this](listener_t*, void* data)
  {
    auto* key_event { static_cast<wlr_keyboard_key_event*>(data) };
    auto keycode { xkb_keycode_to_wlr_keycode( key_event->keycode ) };

    const xkb_keysym_t* syms_ptr;
    auto nsyms { xkb_state_key_get_syms(this->m_wlr->xkb_state, keycode, &syms_ptr) };
    const carray_wrapper keysyms_array { syms_ptr, nsyms };
    
    std::ranges::for_each(keysyms_array, [](xkb_keysym_t keysym)
    {
      switch(keysym)
      {
        case XKB_KEY_Escape:
        {
          wl_display_terminate(globals_t::singleton().display());
          break; 
        }
        default:
        {
          break;
        }
      }
    });
    
    
  });
}

bool sk::keyboard_t::set_keymap()
{
  std::unique_ptr<xkb_context> context { xkb_context_new(XKB_CONTEXT_NO_FLAGS) };
  if(!context)
    return false;
  std::unique_ptr<xkb_keymap> keymap { xkb_keymap_new_from_names(context.get(), nullptr, XKB_KEYMAP_COMPILE_NO_FLAGS) };

  if(!keymap)
    return false;

  wlr_keyboard_set_keymap(m_wlr, keymap.get());
  return true;
}
