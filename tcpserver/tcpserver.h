#ifndef TCPSERVER_H
#define TCPSERVER_H

//! EventDispatcher Includes
#include "eventdispatcher.h"

class CTcpServer
{
public:
    CTcpServer();
    virtual ~CTcpServer();

    void setAcceptHandler(const std::function<void (serverinfo *, c_fdptr)> &handler);
    void setAcceptErrorHandler(const std::function<void (serverinfo *, c_int32)> &handler);
    void unsetAcceptHandler();
    void unsetAcceptErrorHandler();
    void setEnable(bool enable = true);
    void close();

    bool isListening() const;
    bool listen(const std::string &address, c_uint16 port, c_int32 backlog = -1);

    std::string address() const;
    std::string errorString() const;

    c_fdptr socketDescriptor() const;

    c_int32 error() const;

    c_uint16 port() const;

private:    
    C_DISABLE_COPY(CTcpServer)

    serverinfo *m_serverinfo;
};

#endif // TCPSERVER_H
