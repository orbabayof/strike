#include "listener/listener.hpp"
#include <cstdint>
#include <globals/globals.hpp>
#include <wayland-server-core.h>
#include <output/output.hpp>
#include <input/keyboard.hpp>

#include <iostream>
#include <wayland-server-protocol.h>

extern "C"
{
  #include <wlroots-0.19/wlr/backend.h>
  #include <wlroots-0.19/wlr/types/wlr_output.h>
  #include <wlroots-0.19/wlr/types/wlr_input_device.h>
  #include <wlroots-0.19/wlr/types/wlr_keyboard.h>
  #include <wlroots-0.19/wlr/types/wlr_seat.h>
  #include <xkbcommon/xkbcommon.h>
}

sk::globals_t& sk::globals_t::singleton()
{
  static globals_t global {};
  return global;
}

void sk::globals_t::init()
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

  m_socket = wl_display_add_socket_auto(display());
  std::cout << "running on socket " << socket() << '\n';

  m_on_new_output.set_signal(&backend()->events.new_output);
  m_on_new_output.set_callback([](listener_t*, void* data)
  {
    auto* wlr_output { static_cast<struct wlr_output*>(data) };

    auto* output { new output_t { wlr_output } };

    output->set_mode(); 
    output->create_global();

    //output will be deleted in the wlr_output_destroy listener
  });

  m_on_new_input.set_signal(&backend()->events.new_input);
  m_on_new_input.set_callback([this](listener_t*, void* data)
  {
    auto* device { static_cast<wlr_input_device*>(data) };
    std::uint32_t capabilities { 0 };

    switch(device->type)
    {
      case WLR_INPUT_DEVICE_KEYBOARD:
      {
        auto* wlr_keyboard = wlr_keyboard_from_input_device(device);
        
        auto* keyboard = new keyboard_t { wlr_keyboard, device};
        keyboard->set_keymap();

        capabilities |= WL_SEAT_CAPABILITY_KEYBOARD;
      }
      default:
      {
        break;
      }
    }

    wlr_seat_set_capabilities(this->seat().wlr(), capabilities);

  });
  
  m_seat.init();
}
