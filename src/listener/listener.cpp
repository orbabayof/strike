#include <listener/listener.hpp>
#include <wayland-server-core.h>
#include <wayland-util.h>
#include <wayland-server.h>


sk::listener_t::listener_t(signal_t* signal, const callback_t& callback)
  : m_wl_listener { .link = {}, .notify = wl_notify_helper  } 
  , m_signal { signal }
  , m_callback { callback }
{
  wl_signal_add(m_signal, &m_wl_listener);
}

sk::listener_t::listener_t(signal_t* signal)
  : m_wl_listener { .link = {}, .notify = wl_notify_helper  } 
  , m_signal { signal }
{}


void sk::listener_t::set_callback(const callback_t& callback)
{
  m_callback = callback;
  wl_signal_add(m_signal, &m_wl_listener);
}

sk::listener_t::~listener_t()
{
  wl_list_remove(&m_wl_listener.link);
}

void sk::listener_t::wl_notify_helper(wl_listener* wl_listener, void* data)
{
  listener_t* listener = wl_container_of(wl_listener, listener, m_wl_listener);
  
  listener->m_callback(listener, data);
}
