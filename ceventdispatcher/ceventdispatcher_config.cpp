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

CEventDispatcherConfig::CEventDispatcherConfig()
    : m_event_config(nullptr)
{
    m_event_config = event_config_new();
#if defined(DEBUG)
    if (!m_event_config)
        C_DEBUG("failed to initialize config");
#endif
}

CEventDispatcherConfig::~CEventDispatcherConfig()
{
    event_config_free(m_event_config);
}

const c_int32 CEventDispatcherConfig::setFeatures(const c_uint16 methodFeatures)
{
    c_uint16 features = 0;

    if (methodFeatures & CEventDispatcherConfig::ET)
        features |= EV_FEATURE_ET;

    if (methodFeatures & CEventDispatcherConfig::O1)
        features |= EV_FEATURE_O1;

    if (methodFeatures & CEventDispatcherConfig::FDs)
        features |= EV_FEATURE_FDS;

#if defined(DEBUG)
    int result = event_config_require_features(m_event_config, features);

    if (result != 0)
        C_DEBUG("invalid or platform specific features");

    return result;
#else
    return event_config_require_features(m_event_config, features);
#endif
}

const c_int32 CEventDispatcherConfig::setFlags(const c_uint16 configFlags)
{
    c_uint16 flags = 0;

    if (configFlags & CEventDispatcherConfig::NoLock)
        flags |= EVENT_BASE_FLAG_NOLOCK;

    if (configFlags & CEventDispatcherConfig::IgnoreEnvironment)
        flags |= EVENT_BASE_FLAG_IGNORE_ENV;

    if (configFlags & CEventDispatcherConfig::StartupIOCP)
        flags |= EVENT_BASE_FLAG_STARTUP_IOCP;

    if (configFlags & CEventDispatcherConfig::NoCacheTime)
        flags |= EVENT_BASE_FLAG_NO_CACHE_TIME;

    if (configFlags & CEventDispatcherConfig::EPollChangelist)
        flags |= EVENT_BASE_FLAG_EPOLL_USE_CHANGELIST;

#if defined(DEBUG)
    int result = event_config_set_flag(m_event_config, flags);

    if (result != 0)
        C_DEBUG("invalid or platform specific flags");

    return result;
#else
    return event_config_set_flag(m_event_config, flags);
#endif
}

const c_int32 CEventDispatcherConfig::avoidMethod(const std::string &method)
{
#if defined(DEBUG)
    int result = event_config_avoid_method(m_event_config, method.c_str());

    if (result != 0)
        C_DEBUG("invalid method");

    return result;
#else
    return event_config_avoid_method(m_event_config, method.c_str());
#endif
}
