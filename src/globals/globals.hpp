#include <ctime>
#include <defines.hpp>
#include <destroy.hpp>

#include <memory>

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

    static constexpr globals_t& singleton();

    globals_t() = default;

    void init_phase_1();
    void init_phase_2();

    //using std::unique_ptr for destructors, the providing of alternative destroyers is in destroy.hpp
    ~globals_t() = default;

    wl_display* display() { return m_display.get(); }

    wlr_backend* backend() { return m_backend.get(); }
    wlr_allocator* allocator() { return m_allocator.get(); }
    wlr_renderer* renderer2d() { return m_renderer2d.get(); } 
    wlr_compositor* compositor() { return m_compositor.get(); }

    wlr_scene* scene_tree() { return m_scene_tree; }

  private:
    
    std::unique_ptr<wl_display> m_display;

    std::unique_ptr<wlr_backend> m_backend;
    std::unique_ptr<wlr_allocator> m_allocator;
    std::unique_ptr<wlr_renderer> m_renderer2d;
    std::unique_ptr<wlr_compositor> m_compositor;
    wlr_scene* m_scene_tree;
  };
}
