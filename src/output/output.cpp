#include "listener/listener.hpp"
#include <ctime>
#include <output/output.hpp>
#include <globals/globals.hpp>
#include <iostream>




sk::output_t::output_t(wlr_output* wlr_output)
  : m_wlr_output { wlr_output }
  , m_scene_output { wlr_scene_output_create(globals_t::singleton().scene_tree(), wlr_output) }
  , m_on_frame { &wlr_output->events.frame }
  , m_on_destroy { &wlr_output->events.destroy }
{
  set_mode();
  m_on_destroy.set_callback([this](listener_t*, void*)
  {
    delete this;    
  });

  m_on_frame.set_callback([this](listener_t*, void*)
  {
    if(!wlr_scene_output_commit(m_scene_output, nullptr))
      std::cout << "wlr_scene not rendered";

    std::timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    wlr_scene_output_send_frame_done(m_scene_output, &now);
  });
}

//sets size and refresh rate
void sk::output_t::set_mode()
{
  auto& globals { globals_t::singleton() };
  wlr_output_init_render(m_wlr_output, globals.allocator(), globals.renderer2d());
  state_t state;
  wlr_output_state_init(&state);
  wlr_output_state_set_enabled(&state, true);

  if(auto* mode = wlr_output_preferred_mode(m_wlr_output))
    wlr_output_state_set_mode(&state, mode);

  wlr_output_commit_state(m_wlr_output, &state);
  wlr_output_state_finish(&state);
}

void sk::output_t::create_global()
{
  wlr_output_create_global(m_wlr_output, globals_t::singleton().display());
}
