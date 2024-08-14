#include "LogDestination.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <filesystem>

namespace Core {
	
// ConsoleDestination implementation
ConsoleDestination::ConsoleDestination(bool useColor) : m_useColor(useColor) {}

void ConsoleDestination::write(const std::string& message) {
    if (m_useColor) {
        // Implement color output here if needed
        std::cout << message << std::endl;
    } else {
        std::cout << message << std::endl;
    }
}

void ConsoleDestination::flush() {
    std::cout.flush();
}

// FileDestination implementation
FileDestination::FileDestination(const std::string& filename, size_t maxFileSize, int maxFiles)
    : m_filename(filename), m_maxFileSize(maxFileSize), m_maxFiles(maxFiles) {
    openLogFile();
}

FileDestination::~FileDestination() {
    if (m_logFile.is_open()) {
        m_logFile.close();
    }
}

void FileDestination::write(const std::string& message) {
    if (!m_logFile.is_open()) {
        openLogFile();
    }
    m_logFile << message << std::endl;
    if (m_logFile.tellp() > static_cast<std::streampos>(m_maxFileSize)) {
        rotateLogFiles();
    }
}

void FileDestination::flush() {
    if (m_logFile.is_open()) {
        m_logFile.flush();
    }
}

void FileDestination::openLogFile() {
    m_logFile.open(m_filename, std::ios::app);
    if (!m_logFile.is_open()) {
        throw std::runtime_error("Failed to open log file: " + m_filename);
    }
}

void FileDestination::rotateLogFiles() {
    m_logFile.close();
    for (int i = m_maxFiles - 1; i > 0; --i) {
        std::filesystem::path oldName = std::filesystem::path(m_filename).replace_extension("." + std::to_string(i));
        std::filesystem::path newName = std::filesystem::path(m_filename).replace_extension("." + std::to_string(i + 1));
        if (std::filesystem::exists(oldName)) {
            std::filesystem::rename(oldName, newName);
        }
    }
    std::filesystem::rename(m_filename, std::filesystem::path(m_filename).replace_extension(".1"));
    openLogFile();
}

}