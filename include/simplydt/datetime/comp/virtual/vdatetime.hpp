
#ifndef SIMPLYDTLIB_L_DATETIME_V_DATETIME_H_
#define SIMPLYDTLIB_L_DATETIME_V_DATETIME_H_



#include"simplydt/datetime/date/comp/virtual/dt_vdate.hpp"
#include"simplydt/datetime/time/comp/virtual/dt_vtime.hpp"


/* Virtualized datetime (YYYY-mm-dd-HH-MM-SS) */
class VDatetime {

public:
    /* Datetime time unit */
    using Unit = VDate::TimeUnit;
    /* Datetime type */
    using Type = VDate::DatetimeType;
    /* Standard library chronological time point (system clock) */
    using TimePoint = std::chrono::time_point<std::chrono::system_clock>;
    /* Julian Day Number (JDN) */
    using JDN = double;

    /* Datetime layout */
    enum Layout {
        DATE_TIME,// date - time
        TIME_DATE,// time - date
    };

    inline static const JDN EPOCH_JDN = ((JDN)VDate::EPOCH_JDN + (JDN).5);
    inline static const JDN MAX_JDN = ((JDN)VDate::MAX_JDN + (JDN)1.49999999);

    VDatetime(const TimePoint& sys_clock) noexcept;//      <--- INCOMPLETE!

    VDatetime(const VDate& v_date, const VTime& v_time) noexcept;//      <--- INCOMPLETE!

    VDatetime(VDate&& v_date, VTime&& v_time) noexcept;//      <--- INCOMPLETE!

    VDatetime(const VDate& v_date, VTime&& v_time) noexcept;//      <--- INCOMPLETE!

    VDatetime(VDate&& v_date, const VTime& v_time) noexcept;//      <--- INCOMPLETE!

    VDatetime(const VDate& v_date) noexcept;//      <--- INCOMPLETE!

    VDatetime(VDate&& v_date) noexcept;//      <--- INCOMPLETE!

    explicit VDatetime(const JDN& jdn) noexcept;//      <--- INCOMPLETE!

    VDatetime(const VDatetime& v_datetime) noexcept;//      <--- INCOMPLETE!

    VDatetime(VDatetime&& v_datetime) noexcept;//      <--- INCOMPLETE!

    VDatetime() noexcept;//      <--- INCOMPLETE!

    ~VDatetime() noexcept = default;

    friend std::ostream& operator<<(std::ostream& os, const VDatetime& v_datetime) noexcept;//      <--- INCOMPLETE!

    VDatetime& operator=(const VDatetime& v_datetime) noexcept;//      <--- INCOMPLETE!

    VDatetime& operator=(VDatetime&& v_datetime) noexcept;//      <--- INCOMPLETE!

    VDatetime& operator=(const TimePoint& sys_clock) noexcept;//      <--- INCOMPLETE!

    bool operator==(const VDatetime& v_datetime) const noexcept;//      <--- INCOMPLETE!

    bool operator==(const VDate& v_date) const noexcept;//      <--- INCOMPLETE!

    bool operator==(const VTime& v_time) const noexcept;//      <--- INCOMPLETE!

    bool operator==(const TimePoint& sys_clock) const noexcept;//      <--- INCOMPLETE!

    bool operator<(const VDatetime& v_datetime) const noexcept;//      <--- INCOMPLETE!

    bool operator<(const VDate& v_date) const noexcept;//      <--- INCOMPLETE!

    bool operator<(const VTime& v_time) const noexcept;//      <--- INCOMPLETE!

    bool operator<(const TimePoint& sys_clock) const noexcept;//      <--- INCOMPLETE!

    bool operator>(const VDatetime& v_datetime) const noexcept;//      <--- INCOMPLETE!

    bool operator>(const VDate& v_date) const noexcept;//      <--- INCOMPLETE!

    bool operator>(const VTime& v_time) const noexcept;//      <--- INCOMPLETE!

    bool operator>(const TimePoint& sys_clock) const noexcept;//      <--- INCOMPLETE!

    bool operator<=(const VDatetime& v_datetime) const noexcept;//      <--- INCOMPLETE!

    bool operator<=(const VDate& v_date) const noexcept;//      <--- INCOMPLETE!

    bool operator<=(const VTime& v_time) const noexcept;//      <--- INCOMPLETE!

    bool operator<=(const TimePoint& sys_clock) const noexcept;//      <--- INCOMPLETE!

    bool operator>=(const VDatetime& v_datetime) const noexcept;//      <--- INCOMPLETE!

    bool operator>=(const VDate& v_date) const noexcept;//      <--- INCOMPLETE!

    bool operator>=(const VTime& v_time) const noexcept;//      <--- INCOMPLETE!

    bool operator>=(const TimePoint& sys_clock) const noexcept;//      <--- INCOMPLETE!

    VDatetime operator+(const VDuration& v_duration) const noexcept;//      <--- INCOMPLETE!

    VDatetime operator-(const VDuration& v_duration) const noexcept;//      <--- INCOMPLETE!

    VDatetime& operator+=(const VDuration& v_duration) noexcept;//      <--- INCOMPLETE!

    VDatetime& operator-=(const VDuration& v_duration) noexcept;//      <--- INCOMPLETE!

    /* Returns true if datetime represents epoch datetime */
    bool isEpoch() const noexcept;//      <--- INCOMPLETE!

    /* Returns datetime year */
    uint16_t year() const noexcept;//      <--- INCOMPLETE!

    /* Returns datetime month */
    uint16_t month() const noexcept;//      <--- INCOMPLETE!

    /* Returns datetime day */
    uint16_t day() const noexcept;//      <--- INCOMPLETE!

    /* Returns datetime hour */
    uint16_t hour() const noexcept;//      <--- INCOMPLETE!

    /* Returns datetime minute */
    uint16_t minute() const noexcept;//      <--- INCOMPLETE!

    /* Returns datetime second */
    uint16_t second() const noexcept;//      <--- INCOMPLETE!

    /* Returns internal datetime date */
    const VDate& date() const noexcept;//      <--- INCOMPLETE!

    /* Returns internal datetime time */
    const VTime& time() const noexcept;//      <--- INCOMPLETE!

    /* Returns pointer to internal datetime date */
    VDate* getDate() noexcept;//      <--- INCOMPLETE!

    /* Returns pointer to internal datetime time */
    VTime* getTime() noexcept;//      <--- INCOMPLETE!

    /* Returns datetime string in provided configuration */
    std::string datetimeStr(Layout layout, VDate::Format date_format, VDate::Layout date_layout,
        VTime::Format time_format, VTime::Layout time_layout) const noexcept;//      <--- INCOMPLETE!
    
    /* Returns datetime string in provided configuration */
    std::string datetimeStr(VDate::Format date_format, VDate::Layout date_layout,
        VTime::Format time_format, VTime::Layout time_layout) const noexcept;//      <--- INCOMPLETE!
    
    /* Returns datetime string in provided configuration */
    std::string datetimeStr(VDate::Format date_format, VDate::Layout date_layout) const noexcept;//      <--- INCOMPLETE!

    /* Returns datetime string in provided configuration */
    std::string datetimeStr(VTime::Format time_format, VTime::Layout time_layout) const noexcept;//      <--- INCOMPLETE!

    /* Returns datetime string in provided configuration */
    std::string datetimeStr(VDate::Format date_format, VTime::Format time_format) const noexcept;//      <--- INCOMPLETE!

    /* Returns datetime string in provided configuration */
    std::string datetimeStr(VDate::Layout date_layout, VTime::Layout time_layout) const noexcept;//      <--- INCOMPLETE!

    /* Returns datetime string in provided configuration */
    std::string datetimeStr(VDate::Format date_format) const noexcept;//      <--- INCOMPLETE!

    /* Returns datetime string in provided configuration */
    std::string datetimeStr(VDate::Layout date_layout) const noexcept;//      <--- INCOMPLETE!

    /* Returns datetime string in provided configuration */
    std::string datetimeStr(VTime::Format time_format) const noexcept;//      <--- INCOMPLETE!

    /* Returns datetime string in provided configuration */
    std::string datetimeStr(VTime::Layout time_layout) const noexcept;//      <--- INCOMPLETE!
    
    /* Returns datetime string in provided layout */
    std::string datetimeStr(Layout layout) const noexcept;//      <--- INCOMPLETE!

    /* Returns datetime string */
    std::string datetimeStr() const noexcept;//      <--- INCOMPLETE!

    /* Returns datetime day-of-week literal */
    const char* dayOfWeek() const noexcept;//      <--- INCOMPLETE!

    /* Returns datetime day-of-week index */
    uint8_t dowIndex() const noexcept;//      <--- INCOMPLETE!

    /* Returns datetime month literal */
    const char* monthTitle() const noexcept;//      <--- INCOMPLETE!

    /* Returns datetime month index */
    uint8_t monthIndex() const noexcept;//      <--- INCOMPLETE!

    /* Returns true if provided datetime occurs after this datetime */
    bool isBefore(const VDatetime& v_datetime) const noexcept;//      <--- INCOMPLETE!

    /* Returns true if provided date occurs after this datetime date */
    bool isBefore(const VDate& v_date) const noexcept;//      <--- INCOMPLETE!

    /* Returns true if provided datetime occurs after this datetime */
    bool isBefore(const TimePoint& sys_clock) const noexcept;//      <--- INCOMPLETE!

    /* Returns true if provided datetime occurs before this datetime */
    bool isAfter(const VDatetime& v_datetime) const noexcept;//      <--- INCOMPLETE!

    /* Returns true if provided date occurs before this datetime date */
    bool isAfter(const VDate& v_date) const noexcept;//      <--- INCOMPLETE!

    /* Returns true if provided datetime occurs before this datetime */
    bool isAfter(const TimePoint& sys_clock) const noexcept;//      <--- INCOMPLETE!

    /* Returns datetime as Julian Day Number (JDN) */
    JDN toJulianDayNumber() const noexcept;//      <--- INCOMPLETE!

    /* Returns standard library chronological time point copy */
    TimePoint toTimePoint() const noexcept;//      <--- INCOMPLETE!

    /* Returns absolute total number of days from this datetime to provided datetime */
    uint32_t daysUntil(const VDatetime& v_datetime) const noexcept;//      <--- INCOMPLETE!

    /* Returns absolute total number of days from this datetime to provided date */
    uint32_t daysUntil(const VDate& v_date) const noexcept;//      <--- INCOMPLETE!

    /* Returns absolute total number of days from this datetime to provided datetime */
    uint32_t daysUntil(const TimePoint& sys_clock) const noexcept;//      <--- INCOMPLETE!

    /* Returns absolute total number of hours from this datetime to provided datetime */
    uint32_t hoursUntil(const VDatetime& v_datetime) const noexcept;//      <--- INCOMPLETE!

    /* Returns absolute total number of hours from this datetime to provided date */
    uint32_t hoursUntil(const VDate& v_date) const noexcept;//      <--- INCOMPLETE!

    /* Returns absolute total number of hours from this datetime to provided datetime */
    uint32_t hoursUntil(const TimePoint& sys_clock) const noexcept;//      <--- INCOMPLETE!

    /* Returns absolute total number of minutes from this datetime to provided datetime */
    uint32_t minutesUntil(const VDatetime& v_datetime) const noexcept;//      <--- INCOMPLETE!

    /* Returns absolute total number of minutes from this datetime to provided date */
    uint32_t minutesUntil(const VDate& v_date) const noexcept;//      <--- INCOMPLETE!

    /* Returns absolute total number of minutes from this datetime to provided datetime */
    uint32_t minutesUntil(const TimePoint& sys_clock) const noexcept;//      <--- INCOMPLETE!

    /* Returns absolute total number of seconds from this datetime to provided datetime */
    size_t secondsUntil(const VDatetime& v_datetime) const noexcept;//      <--- INCOMPLETE!

    /* Returns absolute total number of seconds from this datetime to provided datetime */
    size_t secondsUntil(const VDate& v_date) const noexcept;//      <--- INCOMPLETE!

    /* Returns absolute total number of seconds from this datetime to provided datetime */
    size_t secondsUntil(const TimePoint& sys_clock) const noexcept;//      <--- INCOMPLETE!

    /* Returns duration from this datetime to provided datetime */
    VDuration until(const VDatetime& v_datetime) const noexcept;//      <--- INCOMPLETE!

    /* Returns duration from this datetime to provided date */
    VDuration until(const VDate& v_date) const noexcept;//      <--- INCOMPLETE!

    /* Returns duration from this datetime to provided datetime */
    VDuration until(const TimePoint& sys_clock) const noexcept;//      <--- INCOMPLETE!

    /* Displace datetime using provided duration */
    void displace(const VDuration& v_duration) noexcept;//      <--- INCOMPLETE!

    /* Reset datetime to epoch */
    void reset() noexcept;//      <--- INCOMPLETE!


private:
    VDate m_date;
    VTime m_time;

    void linkDatetime() noexcept
    {
        this->m_time.linkDate(this->m_date);
    }

};



#endif // SIMPLYDTLIB_L_DATETIME_V_DATETIME_H_
