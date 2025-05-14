#pragma once 

#include <defines.hpp>
#include <functional>
#include <optional>
#include <wayland-server-core.h>
extern "C"
{
  #include <wlroots-0.19/wlr/backend.h>
}

namespace sk
{

  using signal_t = wl_signal;

  class listener_t
  {
    public:

    using callback_t = std::function<void(listener_t* listener, void* data)>;

    listener_t(signal_t* signal, const callback_t& callback);
    listener_t(signal_t* signal);
  

    //for contructors that will set_callback later
    listener_t();
    void set_signal(signal_t* signal);
    void set_callback(const callback_t& callback);

    ~listener_t();

    private:

      static void wl_notify_helper(wl_listener* wl_listener, void*);

      wl_listener m_wl_listener; 
      signal_t* m_signal;
      callback_t m_callback;

  };
}

