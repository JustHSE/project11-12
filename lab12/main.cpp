#include <iostream>
#include <vector>
#include <string>
#include <iterator>

struct Event {
    int timestamp;
    std::string description;
};

class TimeIntervalIterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = Event;
    using difference_type = std::ptrdiff_t;
    using pointer = const Event*;
    using reference = const Event&;
    using BaseIterator = std::vector<Event>::const_iterator;

private:
    BaseIterator current_;
    BaseIterator end_;
    int start_time_;
    int end_time_;

    void advance_to_valid() {
        while (current_ != end_ && (current_->timestamp < start_time_ || current_->timestamp > end_time_)) {
            ++current_;
        }
    }

public:
    TimeIntervalIterator(BaseIterator curr, BaseIterator e, int start, int end_t)
        : current_(curr), end_(e), start_time_(start), end_time_(end_t) {
        advance_to_valid();
    }

    reference operator*() const { return *current_; }
    pointer operator->() const { return &(*current_); }

    TimeIntervalIterator& operator++() {
        if (current_ != end_) {
            ++current_;
            advance_to_valid();
        }
        return *this;
    }

    TimeIntervalIterator operator++(int) {
        TimeIntervalIterator tmp = *this;
        ++(*this);
        return tmp;
    }

    friend bool operator==(const TimeIntervalIterator& a, const TimeIntervalIterator& b) {
        return a.current_ == b.current_;
    }

    friend bool operator!=(const TimeIntervalIterator& a, const TimeIntervalIterator& b) {
        return a.current_ != b.current_;
    }
};

int main() {
    std::vector<Event> log = {
        {10, "Система запущена"},
        {25, "Подключение пользователя A"},
        {35, "Ошибка авторизации"},
        {50, "Отключение пользователя A"},
        {65, "Система остановлена"}
    };

    int filter_start = 20;
    int filter_end = 55;

    std::cout << "События в интервале [" << filter_start << ", " << filter_end << "]:\n";

    TimeIntervalIterator it(log.begin(), log.end(), filter_start, filter_end);
    TimeIntervalIterator end_it(log.end(), log.end(), filter_start, filter_end);

    for (; it != end_it; ++it) {
        std::cout << "Время: " << it->timestamp << " - " << it->description << "\n";
    }

    return 0;
}
