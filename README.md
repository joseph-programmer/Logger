# Logger

## Overview

The **Logger** provides a robust and flexible logging system designed for use in various C++ applications. It supports multiple log levels, customizable output destinations, and pattern-based message formatting. The system is built with thread safety in mind, making it suitable for multi-threaded applications.

## Features

- **Multiple Log Levels**: Includes `DEBUG`, `INFO`, `WARNING`, `ERROR`, and `FATAL` log levels to categorize log messages by severity.
- **Customizable Output Destinations**: Log messages can be directed to various destinations such as the console or files. New destinations can be added by extending the `LogDestination` class.
- **Pattern-Based Formatting**: Allows for customized log message formatting using patterns.
- **Thread-Safe Logging**: Built with thread safety in mind, ensuring reliable logging in multi-threaded environments.
- **Logging Assertions**: Includes macros for assertions that can automatically log messages and terminate the program on failure.

## Installation

### Prerequisites

- **C++17** or higher.
- A compatible C++ compiler (e.g., GCC, Clang, MSVC).
- CMake for build configuration.

### Building the Logger

1. **Clone the repository**:
   ```bash
   git clone https://github.com/yourusername/logger.git
   cd logger
   ```

2. **Configure the project with CMake**:
   ```bash
   mkdir build
   cd build
   cmake ..
   ```

3. **Build the project**:
   ```bash
   cmake --build .
   ```

## Usage

### Basic Logging

To start logging, create a `Logger` instance using the `LoggerManager` and configure it with the desired log level and destinations.

```cpp
#include "Logger.h"
#include "LoggerManager.h"
#include "LogLevel.h"
#include "LogDestination.h"

void exampleLogging() {
    auto logger = LoggerManager().createLogger("ExampleLogger");
    logger->setLogLevel(LogLevel::DEBUG);
    logger->addDestination(std::make_unique<ConsoleDestination>());
    logger->start();

    LOG_DEBUG(logger, "This is a debug message");
    LOG_INFO(logger, "This is an info message");
    LOG_WARNING(logger, "This is a warning message");
    LOG_ERROR(logger, "This is an error message");

    logger->stop();
}
```

### File Logging

```cpp
auto logger = LoggerManager().createLogger("FileLogger");
logger->setLogLevel(LogLevel::INFO);
logger->addDestination(std::make_unique<FileDestination>("logs/output.log", 1024 * 1024, 5)); // 1 MB per file, up to 5 files
logger->start();

LOG_INFO(logger, "Logging to file");

logger->stop();
```

### Custom Formatting

```cpp
auto logger = LoggerManager().createLogger("CustomLogger");
logger->setLogLevel(LogLevel::DEBUG);
logger->addDestination(std::make_unique<ConsoleDestination>());
logger->setFormatter(std::make_unique<PatternFormatter>("[%Y-%m-%d %H:%M:%S] [%l] %v"));
logger->start();

LOG_DEBUG(logger, "Custom formatted debug message");

logger->stop();
```

### Multi-Threaded Logging

```cpp
auto logger = LoggerManager().createLogger("MultiThreadLogger");
logger->setLogLevel(LogLevel::INFO);
logger->addDestination(std::make_unique<ConsoleDestination>());
logger->start();

std::thread t1([&](){ LOG_INFO(logger, "Log from thread 1"); });
std::thread t2([&](){ LOG_INFO(logger, "Log from thread 2"); });

t1.join();
t2.join();

logger->stop();
```

### Assertions

```cpp
int x = 5, y = 10;
ASSERT(x < y, "x should be less than y");
ASSERT_EQ(x, 5, "x should equal 5");
ASSERT_NE(x, y, "x should not equal y");
ASSERT_GT(y, x, "y should be greater than x");
```

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request with your changes. Ensure that all new code is covered by unit tests.

## License



## Contact

For questions or suggestions, please open an issue on the GitHub repository.

---

This README should serve as a good starting point for the `Logger` project, providing an overview, installation instructions, usage examples, and contribution guidelines.
