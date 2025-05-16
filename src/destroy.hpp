#pragma once 

#include <defines.hpp>

#include <wayland-server-core.h>
#include <xkbcommon/xkbcommon.h>
#include <memory>
#include <wayland-server.h>

extern "C"
{
  #include <wlroots-0.19/wlr/backend.h>
  #include <wlroots-0.19/wlr/render/allocator.h>
  #include <wlroots-0.19/wlr/render/wlr_renderer.h>
  #include <wlroots-0.19/wlr/types/wlr_compositor.h>
  #include <../wlroots_headers_for_cpp/wlr_scene.h>
}


template<typename T, void(*func)(T*)>
struct func_destroyer
{
  void operator()(T* ptr) 
  {
    func(ptr);
  }
};

inline void destroy_display_with_clients(wl_display* display)
{
  wl_display_destroy_clients(display);
  wl_display_destroy(display);
};

inline void remove_scene_node_of_wlr_scene_surface(wlr_scene_surface* wlr_scene_surface)
{
  wlr_scene_node_destroy(&wlr_scene_surface->buffer->node);
}

#define decl_destroyer(type, func) template <>\
  struct std::default_delete<type> : func_destroyer<type, func>{}

//libwayland
decl_destroyer(wl_display, destroy_display_with_clients);

//wlroots
decl_destroyer(wlr_allocator, wlr_allocator_destroy);
decl_destroyer(wlr_renderer, wlr_renderer_destroy);
decl_destroyer(wlr_scene_surface, remove_scene_node_of_wlr_scene_surface);

//libxkbcommon  
decl_destroyer(xkb_context, xkb_context_unref);
decl_destroyer(xkb_keymap, xkb_keymap_unref);

#undef decl_destroyer

