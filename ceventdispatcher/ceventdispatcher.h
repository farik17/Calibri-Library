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
    virtual ~CEventDispatcher();

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

    static void initialize(CEventDispatcherConfig *config);

    static const std::string socketAddress(const c_fdptr fd);

    static CEventDispatcher *instance();

    static const c_uint16 socketPort(const c_fdptr fd);

private:
    C_DISABLE_COPY(CEventDispatcher)

    CEventDispatcher();
    CEventDispatcher(CEventDispatcherConfig *config);

#if defined(_WIN32)
    static void initializeWSA();
#endif

    static void acceptNotification(evconnlistener *listener, const c_fdptr fd, sockaddr *address, const c_int32 socklen, void *ctx);
    static void acceptErrorNotification(evconnlistener *listener, void *ctx);
    static void readNotification(bufferevent *buffer_event, void *ctx);
    static void eventNotification(bufferevent *buffer_event, const c_int16 events, void *ctx);
    static void timerNotification(const c_fdptr fd, const c_int16 events, void *ctx);
    static void outputBufferNotification(evbuffer *buffer, const evbuffer_cb_info *info, void *ctx);

    event_base *m_event_base;
    evdns_base *m_evdns_base;

    static CEventDispatcher *m_eventDispatcher;
};

#endif // CEVENTDISPATCHER_H
