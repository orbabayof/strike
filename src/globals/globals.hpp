#include "listener/listener.hpp"
#include <ctime>
#include <defines.hpp>
#include <destroy.hpp>
#include <compositor/compositor.hpp>

#include <memory>
#include <string_view>

extern "C"
{
  #include <wlroots-0.19/wlr/backend.h>
  #include <wlroots-0.19/wlr/types/wlr_compositor.h>
  #include "../wlroots_headers_for_cpp/wlr_scene.h"
}

namespace sk
{
  class globals_t
  {
  public:

    static globals_t& singleton();

    globals_t() = default;

    void init();

    //using std::unique_ptr for destructors, the providing of alternative destroyers is in destroy.hpp
    ~globals_t() = default;

    wl_display* display() { return m_display.get(); }

    wlr_backend* backend() { return m_backend.get(); }
    wlr_allocator* allocator() { return m_allocator.get(); }
    wlr_renderer* renderer2d() { return m_renderer2d.get(); } 

    wlr_scene* scene() { return m_scene_tree; }

    std::string_view socket() { return m_socket; }

  private:
    
    std::unique_ptr<wl_display> m_display;

    std::unique_ptr<wlr_backend> m_backend;
    std::unique_ptr<wlr_allocator> m_allocator;
    std::unique_ptr<wlr_renderer> m_renderer2d;
    wlr_scene* m_scene_tree;

    std::string_view m_socket;

    listener_t m_on_new_output;
    listener_t m_on_new_input;

    
  };
}
