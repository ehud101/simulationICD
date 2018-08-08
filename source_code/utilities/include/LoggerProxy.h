#ifndef LOGGERPROXY_H
#define LOGGERPROXY_H

/*
* LoggerProxy.h
* Control multy-threaded log
* Author: Binyamin Appelbaum
* Date: 22.02.18
* The purpose of this class is to make logger thread safe. 
*/

#include "Logger.h"

template <class TLockObject>
class LoggerProxy {
private:
    Logger& m_logger;
    std::lock_guard<TLockObject> m_lockGuard;

public:
    LoggerProxy(Logger& logger, TLockObject& lockObj) : m_logger(logger), m_lockGuard(lockObj) {

    }

    LoggerProxy(Logger& logger, TLockObject& lockObj,
        LogLevel level, const std::string& sourceFile, const std::string& funcName, int lineNumber) : m_logger(logger), m_lockGuard(lockObj) {
        m_logger.SetTmpLevel(level);
        m_logger.Write(level, sourceFile, funcName, lineNumber);
    }

    // allow chain of calls to loggerproxy: LoggerProxy << "a" << 1 << "b" << ...
    template <typename T>
    inline LoggerProxy& operator << (const T& msg) {
        m_logger.Write(msg);
        return *this;
    }
};

#endif // LOGGERPROXY_H