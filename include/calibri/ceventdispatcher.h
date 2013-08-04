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

#ifndef CEVENTDISPATCHER_H
#define CEVENTDISPATCHER_H

//! LibEvent Includes
#include <event2/event.h>
#include <event2/buffer.h>
#include <event2/dns.h>

//! CEventDispatcher Includes
#include "ceventdispatcher_types.h"
#include "ceventdispatcher_config.h"

class CEventDispatcher
{

public:
    enum EventLoopFlag : c_uint8 {
        Once = 1,
        NonBlock,
        NoExitOnEmpty
    };

    void acceptSocket(socketinfo *socket_info, const c_fdptr fd);
    void connectSocket(socketinfo *socket_info, const std::string &address, const c_uint16 port);
    void closeSocket(socketinfo *socket_info, const bool force = false);
    void bindServer(serverinfo *server_info, const std::string &address, const c_uint16 port, const c_int32 backlog = -1);
    void closeServer(serverinfo *server_info);
    void startTimer(timerinfo *timer_info, const c_uint32 msec, const bool repeat = true);
    void restartTimer(timerinfo *timer_info, const c_uint32 msec, const bool repeat = true);
    void killTimer(timerinfo *timer_info);

    const c_int32 execute();
    const c_int32 execute(const EventLoopFlag eventLoopFlag);
    const c_int32 terminate();

    static std::string socketAddress(const c_fdptr fd);

    static CEventDispatcher *initialize(const CEventDispatcherConfig &config);
    static CEventDispatcher *instance();

    static const c_uint16 socketPort(const c_fdptr fd);

private:
    C_DISABLE_COPY(CEventDispatcher)

    CEventDispatcher();
    CEventDispatcher(const CEventDispatcherConfig &config);
    ~CEventDispatcher();

    event_base *m_event_base;
    evdns_base *m_evdns_base;
};

#endif // CEVENTDISPATCHER_H
