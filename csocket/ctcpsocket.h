#ifndef CTCPSOCKET_H
#define CTCPSOCKET_H

//! CEventDispatcher Includes
#include "ceventdispatcher.h"

class CTcpSocket
{
public:
    CTcpSocket();
    virtual ~CTcpSocket();

    void setConnectedHandler(const std::function<void (socketinfo *)> &handler);
    void setDisconnectedHandler(const std::function<void (socketinfo *)> &handler);
    void setReadHandler(const std::function<void (socketinfo *)> &handler);
    void setErrorHandler(const std::function<void (socketinfo *, c_int32)> &handler);
    void unsetConnectedHandler();
    void unsetDisconnectedHandler();
    void unsetReadHandler();
    void unsetErrorHandler();
    void connectToHost(const std::string &address, c_uint16 port);
    void close(bool force = false);

    std::string address() const;
    std::string errorString() const;

    size_t bytesAvailable() const;
    size_t write(const char *data, size_t len);
    size_t read(char *data, size_t len);

    c_fdptr socketDescriptor() const;

    c_int32 error() const;

    c_uint16 port() const;

    CSocketState state() const;

    bool atEnd() const;
    bool setSocketDescriptor(c_fdptr fd);
    bool setNoDelay(c_uint32 flag);
    bool setKeepAlive(c_uint32 flag, c_uint32 idle = 0, c_uint32 interval = 0, c_uint32 count = 0);

protected:
    socketinfo *m_socketinfo;

private:    
    C_DISABLE_COPY(CTcpSocket)
};

#endif // CTCPSOCKET_H
