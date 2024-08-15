
#ifndef SIMPLYDTLIB_L_STANDARD_DATETIME_OBJ_H_
#define SIMPLYDTLIB_L_STANDARD_DATETIME_OBJ_H_



#include"simplydt/datetime/date/comp/dt_date.hpp"
#include"simplydt/datetime/time/comp/dt_stime.hpp"


/* Standard datetime (YYYY-mm-dd-HH-MM-SS) */
class VDatetime {

public:
    /* Datetime time unit */
    using Unit = VDate::TimeUnit;
    /* Datetime type */
    using Type = VDate::DatetimeType;
    /* Standard library chronological time point (system clock) */
    using TimePoint = std::chrono::time_point<std::chrono::system_clock>;

    /* Datetime layout */
    enum Layout {
        DATE_TIME,// date - time
        TIME_DATE,// time - date
    };

    VDatetime(TimePoint sys_clock) noexcept;

    VDatetime(const VDate& v_date, const VTime& v_time) noexcept;

    VDatetime(VDate&& v_date, VTime&& v_time) noexcept;

    VDatetime(const VDate& v_date, VTime&& v_time) noexcept;

    VDatetime(VDate&& v_date, const VTime& v_time) noexcept;

    VDatetime(const VDate& v_date) noexcept;

    VDatetime(VDate&& v_date) noexcept;

    VDatetime(const VDatetime& v_datetime) noexcept;

    VDatetime(VDatetime&& v_datetime) noexcept;

    VDatetime() noexcept;

    ~VDatetime() noexcept = default;

    friend std::ostream& operator<<(std::ostream& os, const VDatetime& v_datetime) noexcept;

    VDatetime& operator=(const VDatetime& v_datetime) noexcept;

    VDatetime& operator=(VDatetime&& v_datetime) noexcept;

    VDatetime& operator=(const TimePoint& sys_clock) noexcept;

    bool operator==(const VDatetime& v_datetime) const noexcept;

    bool operator<(const VDatetime& v_datetime) const noexcept;

    bool operator>(const VDatetime& v_datetime) const noexcept;

    bool operator<=(const VDatetime& v_datetime) const noexcept;

    bool operator>=(const VDatetime& v_datetime) const noexcept;

    VDatetime operator+(const VDuration& v_duration) const noexcept;

    VDatetime operator-(const VDuration& v_duration) const noexcept;

    VDatetime& operator+=(const VDuration& v_duration) noexcept;

    VDatetime& operator-=(const VDuration& v_duration) noexcept;


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
    bool isBefore(const VDatetime& v_datetime) const noexcept;

    /* Returns true if provided date occurs after this datetime date */
    bool isBefore(const VDate& v_date) const noexcept;

    /* Returns true if provided datetime occurs before this datetime */
    bool isAfter(const VDatetime& v_datetime) const noexcept;

    /* Returns true if provided date occurs before this datetime date */
    bool isAfter(const VDate& v_date) const noexcept;

    /* Returns pointer to datetime date */
    VDate* getDate() noexcept;

    /* Returns pointer to datetime time */
    VTimeEx* getTime() noexcept;

    /* Returns standard library chronological time point copy */
    TimePoint toChrono() const noexcept;

    /* Returns absolute total number of days from this datetime to provided datetime */
    size_t daysUntil(const VDatetime& v_datetime) const noexcept;

    /* Returns absolute total number of minutes from this datetime to provided datetime */
    size_t minutesUntil(const VDatetime& v_datetime) const noexcept;

    /* Returns absolute total number of seconds from this datetime to provided datetime */
    size_t secondsUntil(const VDatetime& v_datetime) const noexcept;

    /* Returns duration from this datetime to provided datetime */
    VDuration until(const VDatetime& v_datetime) const noexcept;

    /* Displace datetime using provided duration */
    void displace(const VDuration& v_duration) noexcept;


private:
    VDate m_date;
    VTime m_time;

    void linkDatetime() noexcept
    {
        this->m_time.linkDate(this->m_date);
    }

};



#endif // SIMPLYDTLIB_L_STANDARD_DATETIME_OBJ_H_
