#ifndef LOGGER_MANAGER_H
#define LOGGER_MANAGER_H

#include "LoggerPCH.h"

namespace Core {

/**
 * @class LoggerManager
 * @brief Manages multiple Logger instances.
 *
 * The LoggerManager class provides functionality to create, retrieve, and manage
 * Logger instances. It ensures unique logger names and handles thread-safe access
 * to loggers.
 */
class LOGGER_API LoggerManager {
public:
    /**
     * @brief Creates a new logger with the specified name.
     * @param name The name of the logger to create.
     * @return A shared pointer to the created Logger.
     */
    std::shared_ptr<Logger> createLogger(const std::string& name);

    /**
     * @brief Retrieves an existing logger by name.
     * @param name The name of the logger to retrieve.
     * @return A shared pointer to the Logger, or nullptr if not found.
     */
    std::shared_ptr<Logger> getLogger(const std::string& name);

    /**
     * @brief Removes a logger with the specified name.
     * @param name The name of the logger to remove.
     */
    void removeLogger(const std::string& name);

private:
    std::map<std::string, std::shared_ptr<Logger>> m_loggers; ///< Map of logger names to Logger instances.
    std::mutex m_mutex; ///< Mutex for thread-safe access to loggers.
};

} // namespace Core

#endif // LOGGER_MANAGER_H
