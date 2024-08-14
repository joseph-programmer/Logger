#include "LoggerManager.h"

namespace Core {
	
std::shared_ptr<Logger> LoggerManager::createLogger(const std::string& name) {
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_loggers.find(name);
    if (it != m_loggers.end()) {
        return it->second;
    } else {
        auto logger = std::make_shared<Logger>();
        m_loggers[name] = logger;
        return logger;
    }
}

std::shared_ptr<Logger> LoggerManager::getLogger(const std::string& name) {
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_loggers.find(name);
    if (it != m_loggers.end()) {
        return it->second;
    }
    return nullptr;
}

void LoggerManager::removeLogger(const std::string& name) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_loggers.erase(name);
}

}