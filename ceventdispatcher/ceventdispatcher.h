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
        Once            = 1,
        Nonblock        = 2,
        NoExitOnEmpty   = 3
    };

    static void initialize(CEventDispatcherConfig *config);

    static CEventDispatcher *instance();

    void execute();
    void execute(EventLoopFlag flag);
    void terminate();
    void acceptSocket(socketinfo *socket_info, c_fdptr fd);
    void connectSocket(socketinfo *socket_info, const std::string &address, c_uint16 port);
    void closeSocket(socketinfo *socket_info, bool force = false);
    void bindServer(serverinfo *server_info, const std::string &address, c_uint16 port, c_int32 backlog = -1);
    void closeServer(serverinfo *server_info);
    void startTimer(timerinfo *timer_info, c_uint32 msec, bool repeat = true);
    void restartTimer(timerinfo *timer_info, c_uint32 msec, bool repeat = true);
    void killTimer(timerinfo *timer_info);

    std::string socketAddress(c_fdptr fd) const;

    c_uint16 socketPort(c_fdptr fd) const;

private:
    C_DISABLE_COPY(CEventDispatcher)

    CEventDispatcher();
    CEventDispatcher(CEventDispatcherConfig *config);

#if defined(_WIN32)
    void initializeWSA();
#endif

    event_base *m_event_base;
    evdns_base *m_evdns_base;

    static CEventDispatcher *m_eventDispatcher;

    static void acceptNotification(evconnlistener *listener, c_fdptr fd, sockaddr *address, c_int32 socklen, void *ctx);
    static void acceptErrorNotification(evconnlistener *listener, void *ctx);
    static void readNotification(bufferevent *buffer_event, void *ctx);
    static void eventNotification(bufferevent *buffer_event, c_int16 events, void *ctx);
    static void timerNotification(c_fdptr fd, c_int16 events, void *ctx);
    static void outputBufferNotification(evbuffer *buffer, const evbuffer_cb_info *info, void *ctx);
};

#endif // CEVENTDISPATCHER_H
