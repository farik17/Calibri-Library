/****************************************************************************
**
** Copyright (c) 2013 Calibri-Software <calibrisoftware@gmail.com>
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in
** all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
** THE SOFTWARE.
**
****************************************************************************/

//! Self Includes
#include "ceventdispatcher_config.h"

//! Std Includes
#include <iostream>

CEventDispatcherConfig::CEventDispatcherConfig()
    : m_event_config(nullptr)
{
    m_event_config = event_config_new();
    if (!m_event_config)
        std::cout << "CEventDispatcherConfig::CEventDispatcherConfig error: failed to initialize config" << std::endl;
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
        std::cout << "CEventDispatcherConfig::setFeatures error: invalid or platform specific features" << std::endl;
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
        std::cout << "CEventDispatcherConfig::setFlags error: invalid or platform specific flags" << std::endl;
}

void CEventDispatcherConfig::avoidMethod(const std::string &method)
{
    if (event_config_avoid_method(m_event_config, method.c_str()) != 0)
        std::cout << "CEventDispatcherConfig::avoidMethod error: invalid method" << std::endl;
}
