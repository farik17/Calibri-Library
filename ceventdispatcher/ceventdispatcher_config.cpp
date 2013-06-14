//! Self Includes
#include "ceventdispatcher_config.h"

//! Std Includes
#include <iostream>

CEventDispatcherConfig::CEventDispatcherConfig()
    : m_event_config(nullptr)
{
    m_event_config = event_config_new();
    if (!m_event_config)
        std::cout << "EventDispatcherConfig::EventDispatcherConfig error: failed to initialize config" << std::endl;
}

CEventDispatcherConfig::~CEventDispatcherConfig()
{
    event_config_free(m_event_config);
}

void CEventDispatcherConfig::setFeatures(c_uint16 features)
{
    c_uint16 result = 0;

    if (features & CEventDispatcherConfig::ET)
        result |= EV_FEATURE_ET;
    if (features & CEventDispatcherConfig::O1)
        result |= EV_FEATURE_O1;
    if (features & CEventDispatcherConfig::FDs)
        result |= EV_FEATURE_FDS;

    if (event_config_require_features(m_event_config, result) != 0)
        std::cout << "EventDispatcherConfig::setFeatures error: invalid or platform specific features" << std::endl;
}

void CEventDispatcherConfig::setFlags(c_uint16 flags)
{
    c_uint16 result = 0;

    if (flags & CEventDispatcherConfig::NoLock)
        result |= EVENT_BASE_FLAG_NOLOCK;
    if (flags & CEventDispatcherConfig::IgnoreEnvironment)
        result |= EVENT_BASE_FLAG_IGNORE_ENV;
    if (flags & CEventDispatcherConfig::StartupIOCP)
        result |= EVENT_BASE_FLAG_STARTUP_IOCP;
    if (flags & CEventDispatcherConfig::NoCacheTime)
        result |= EVENT_BASE_FLAG_NO_CACHE_TIME;
    if (flags & CEventDispatcherConfig::EPollChangelist)
        result |= EVENT_BASE_FLAG_EPOLL_USE_CHANGELIST;

    if (event_config_set_flag(m_event_config, result) != 0)
        std::cout << "EventDispatcherConfig::setFlags error: invalid or platform specific flags" << std::endl;
}

void CEventDispatcherConfig::avoidMethod(const std::string &method)
{
    if (event_config_avoid_method(m_event_config, method.c_str()) != 0)
        std::cout << "EventDispatcherConfig::avoidMethod error: invalid method" << std::endl;
}
