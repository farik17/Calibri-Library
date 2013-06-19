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
        ET      = 1,
        O1      = 2,
        FDs     = 3
    };

    enum ConfigFlag : c_uint8 {
        NoLock              = 1,
        IgnoreEnvironment   = 2,
        StartupIOCP         = 3,
        NoCacheTime         = 4,
        EPollChangelist     = 5
    };

    void setFeatures(c_uint16 features);
    void setFlags(c_uint16 flags);
    void avoidMethod(const std::string &method);

private:
    C_DISABLE_COPY(CEventDispatcherConfig)

    event_config *m_event_config;

    friend class CEventDispatcher;
};

#endif // CEVENTDISPATCHER_CONFIG_H
