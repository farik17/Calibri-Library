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

#ifndef CEVENTDISPATCHER_CONFIG_H
#define CEVENTDISPATCHER_CONFIG_H

//! Std Includes
#include <string>

//! LibEvent Includes
#include <event2/event.h>

//! Project Includes
#include "cdefines.h"

class CEventDispatcherConfig
{
public:
    CEventDispatcherConfig();
    virtual ~CEventDispatcherConfig();

    enum MethodFeature : c_uint8 {
        ET = 1,
        O1,
        FDs
    };

    enum ConfigFlag : c_uint8 {
        NoLock = 1,
        IgnoreEnvironment,
        StartupIOCP,
        NoCacheTime,
        EPollChangelist
    };

    const c_int32 setFeatures(const c_uint16 methodFeatures);
    const c_int32 setFlags(const c_uint16 configFlags);
    const c_int32 avoidMethod(const std::string &method);

private:
    C_DISABLE_COPY(CEventDispatcherConfig)

    event_config *m_event_config;

    friend class CEventDispatcher;
};

#endif // CEVENTDISPATCHER_CONFIG_H
