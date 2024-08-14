
#ifndef SIMPLYDTLIB_L_STANDARD_DATETIME_OBJ_H_
#define SIMPLYDTLIB_L_STANDARD_DATETIME_OBJ_H_



#include"simplydt/datetime/date/comp/dt_date.hpp"
#include"simplydt/datetime/time/comp/dt_stime.hpp"


/* Standard datetime (YYYY-mm-dd-HH-MM-SS) */
class SDatetime {

public:
    /* Datetime time unit */
    using Unit = VDate::TimeUnit;
    /* Datetime type */
    using Type = VDate::DatetimeType;
    /* Standard library chronological time point (system clock) */
    using Chrono = std::chrono::time_point<std::chrono::system_clock>;

    /* Datetime layout */
    enum Layout {
        DATE_TIME,// date - time
        TIME_DATE,// time - date
    };

    SDatetime(Chrono chrono) noexcept;

    SDatetime(const VDate& date, const VTime& s_time) noexcept;

    SDatetime(VDate&& date, VTime&& s_time) noexcept;

    SDatetime(const VDate& date, VTime&& s_time) noexcept;

    SDatetime(VDate&& date, const VTime& s_time) noexcept;

    SDatetime(const VDate& date) noexcept;

    SDatetime(VDate&& date) noexcept;

    SDatetime(const SDatetime& s_datetime) noexcept;

    SDatetime(SDatetime&& s_datetime) noexcept;

    SDatetime() noexcept;

    ~SDatetime() noexcept = default;

    friend std::ostream& operator<<(std::ostream& os, const SDatetime& s_datetime) noexcept;

    SDatetime& operator=(const SDatetime& s_datetime) noexcept;

    SDatetime& operator=(SDatetime&& s_datetime) noexcept;

    SDatetime& operator=(const Chrono& chrono) noexcept;

    bool operator==(const SDatetime& s_datetime) const noexcept;

    bool operator<(const SDatetime& s_datetime) const noexcept;

    bool operator>(const SDatetime& s_datetime) const noexcept;

    bool operator<=(const SDatetime& s_datetime) const noexcept;

    bool operator>=(const SDatetime& s_datetime) const noexcept;

    SDatetime operator+(const VDuration& duration) const noexcept;

    SDatetime operator-(const VDuration& duration) const noexcept;

    SDatetime& operator+=(const VDuration& duration) noexcept;

    SDatetime& operator-=(const VDuration& duration) noexcept;


    /* Returns datetime year */
    uint16_t year() const noexcept;

    /* Returns datetime month */
    uint16_t month() const noexcept;

    /* Returns datetime day */
    uint16_t day() const noexcept;

    /* Returns datetime hour */
    uint16_t hour() const noexcept;

    /* Returns datetime minute */
    uint16_t minute() const noexcept;

    /* Returns datetime second */
    uint16_t second() const noexcept;

    /* Datetime date object */
    const VDate& date() const noexcept;

    /* Datetime time object */
    const VTime& time() const noexcept;

    /* Returns datetime hour of day phase */
    Hour::Phase hourPhase() const noexcept;

    /* Returns datetime hour of day phase literal */
    std::string hourPhaseStr() const noexcept;

    /* Returns datetime string in provided configuration */
    std::string datetimeStr(Layout layout, VDate::Format date_format, VDate::Layout date_layout,
        VTime::Format time_format, VTime::Layout time_layout) const noexcept;
    
    /* Returns datetime string in provided configuration */
    std::string datetimeStr(VDate::Format date_format, VDate::Layout date_layout,
        VTime::Format time_format, VTime::Layout time_layout) const noexcept;
    
    /* Returns datetime string in provided configuration */
    std::string datetimeStr(VDate::Format date_format, VDate::Layout date_layout) const noexcept;

    /* Returns datetime string in provided configuration */
    std::string datetimeStr(VTime::Format time_format, VTime::Layout time_layout) const noexcept;

    /* Returns datetime string in provided configuration */
    std::string datetimeStr(VDate::Format date_format, VTime::Format time_format) const noexcept;

    /* Returns datetime string in provided configuration */
    std::string datetimeStr(VDate::Layout date_layout, VTime::Layout time_layout) const noexcept;

    /* Returns datetime string in provided configuration */
    std::string datetimeStr(VDate::Format date_format) const noexcept;

    /* Returns datetime string in provided configuration */
    std::string datetimeStr(VDate::Layout date_layout) const noexcept;

    /* Returns datetime string in provided configuration */
    std::string datetimeStr(VTime::Format time_format) const noexcept;

    /* Returns datetime string in provided configuration */
    std::string datetimeStr(VTime::Layout time_layout) const noexcept;
    
    /* Returns datetime string in provided layout */
    std::string datetimeStr(Layout layout) const noexcept;

    /* Returns datetime string */
    std::string datetimeStr() const noexcept;

    /* Returns datetime day-of-week literal */
    const char* dayOfWeek() const noexcept;

    /* Returns datetime month literal */
    const char* monthTitle() const noexcept;

    /* Returns true if provided datetime occurs after this datetime */
    bool isBefore(const SDatetime& s_datetime) const noexcept;

    /* Returns true if provided date occurs after this datetime date */
    bool isBefore(const VDate& date) const noexcept;

    /* Returns true if provided datetime occurs before this datetime */
    bool isAfter(const SDatetime& s_datetime) const noexcept;

    /* Returns true if provided date occurs before this datetime date */
    bool isAfter(const VDate& date) const noexcept;

    /* Returns pointer to datetime date */
    VDate* getDate() noexcept;

    /* Returns pointer to datetime time */
    VTimeEx* getTime() noexcept;

    /* Returns standard library chronological time point copy */
    Chrono toChrono() const noexcept;

    /* Returns absolute total number of days from this datetime to provided datetime */
    size_t daysUntil(const SDatetime& s_datetime) const noexcept;

    /* Returns absolute total number of minutes from this datetime to provided datetime */
    size_t minutesUntil(const SDatetime& s_datetime) const noexcept;

    /* Returns absolute total number of seconds from this datetime to provided datetime */
    size_t secondsUntil(const SDatetime& s_datetime) const noexcept;

    /* Returns duration from this datetime to provided datetime */
    VDuration until(const SDatetime& s_datetime) const noexcept;

    /* Displace datetime using provided duration */
    void displace(const VDuration& duration) noexcept;


private:
    VDate m_date;
    VTime m_time;

    void linkDatetime() noexcept
    {
        this->m_time.linkDate(this->m_date);
    }

};



#endif // SIMPLYDTLIB_L_STANDARD_DATETIME_OBJ_H_
