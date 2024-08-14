// Logger.inl

#include <stdexcept>
#include <vector>
#include <cstdio>
#include <cstring>

template<typename T>
void Logger::ThreadSafeQueue<T>::enqueue(T item) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_queue.push(std::move(item));
    m_cv.notify_one();
}

template<typename T>
T Logger::ThreadSafeQueue<T>::dequeue() {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_cv.wait(lock, [this] { return !m_queue.empty(); });
    T item = std::move(m_queue.front());
    m_queue.pop();
    return item;
}

template<typename T>
bool Logger::ThreadSafeQueue<T>::empty() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_queue.empty();
}

template<typename... Args>
void Logger::log(LogLevel level, const char* file, int line, const char* format, Args... args) {
    if (level < m_logLevel.load(std::memory_order_relaxed)) return;
    std::string message = formatString(format, args...);
    auto timestamp = std::chrono::system_clock::now();
    std::string formattedMessage;
    {
        std::lock_guard<std::mutex> lock(m_formatterMutex);
        formattedMessage = m_formatter->format(level, timestamp, file, line, message);
    }
    m_logQueue.enqueue(std::move(formattedMessage));
}

template<typename... Args>
std::string Logger::formatString(const char* format, Args... args) {
    int size_s = std::snprintf(nullptr, 0, format, args...) + 1;
    if (size_s <= 0) { throw std::runtime_error("Error during formatting."); }
    auto size = static_cast<size_t>(size_s);
    std::vector<char> buf(size);
    std::snprintf(buf.data(), size, format, args...);
    return std::string(buf.data(), buf.data() + size - 1);
}

