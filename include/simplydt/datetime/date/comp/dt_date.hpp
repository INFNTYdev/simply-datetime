
#ifndef SIMPLYDTLIB_L_DATETIME_DATE_SEQUENCE_OBJ_H_
#define SIMPLYDTLIB_L_DATETIME_DATE_SEQUENCE_OBJ_H_



#include<chrono>

#include"simplydt/datetime/sequence/dt_sequence.hpp"


/* Full date (YYYY-mm-dd) */
class Date : public DatetimeSequence<Year, Month, Day> {

public:
    /* Datetime time unit */
    using TimeUnit = DatetimeSequence<Year, Month, Day>::TimeUnit;
    /* Datetime type */
    using DatetimeType = DatetimeSequence<Year, Month, Day>::DatetimeType;
    /* Standard library chronological time point (system clock) */
    using Chrono = std::chrono::time_point<std::chrono::system_clock>;

    enum Format {
        RECORD,// Record date format (00-00-0000)
        STANDARD,// Standard date format (00/00/0000)
    };

    enum Layout {
        M_D_YYYY,// (mm/dd/YYYY) [Example: 01-13-2024]
        M_D_YY,// (mm/dd/YY) [Example: 01-13-24]
        M_D,// (mm/dd) [Example: 01-13]
        YYYY_M_D,// (YYYY/mm/dd) [Example: 2024-01-13]
        YY_M_D,// (YY/mm/dd) [Example: 24-01-13]
        YYYY_D_M,// (YYYY/dd/mm) [Example: 2024-13-01]
        YY_D_M,// (YY/dd/mm) [Example: 24-13-01]
    };

    Date(Chrono chrono) noexcept;

    Date(uint16_t year, uint16_t month, uint16_t day) noexcept;

    Date(uint16_t year, uint16_t month) noexcept;

    Date(uint16_t year) noexcept;

    Date() noexcept;

    Date(const Date& date) noexcept;

    Date(Date&& date) noexcept;

    ~Date() noexcept = default;

    friend std::ostream& operator<<(std::ostream& os, const Date& date) noexcept;

    /* Returns year of date */
    uint16_t year() const noexcept;

    /* Returns month of date */
    uint16_t month() const noexcept;

    /* Returns day of date */
    uint16_t day() const noexcept;

    /* Returns date day-of-week literal */
    const char* dayOfWeek() const noexcept;

    /* Returns date month literal */
    const char* monthTitle() const noexcept;

    /* Returns date string with provided configuration */
    std::string dateStr(Format format, Layout layout) const noexcept;

    /* Returns date string with provided configuration */
    std::string dateStr(Layout layout, Format format) const noexcept;

    /* Returns date string with provided format */
    std::string dateStr(Format format) const noexcept;

    /* Returns date string with provided layout */
    std::string dateStr(Layout layout) const noexcept;

    /* Returns date string */
    std::string dateStr() const noexcept;

    /* Returns year in date */
    Year& getYear() const noexcept;

    /* Returns month in date */
    Month& getMonth() const noexcept;

    /* Returns day in date */
    Day& getDay() const noexcept;

    /* Returns date as standard chronological time point */
    Chrono toChrono() const noexcept;


private:
    static const uint8_t YEAR_INDEX{ 0 };
    static const uint8_t MONTH_INDEX{ 1 };
    static const uint8_t DAY_INDEX{ 2 };

    Year* retrieveYear() const noexcept
    {
        Interval<uint16_t>* rawInterval{ this->getInterval(YEAR_INDEX) };

        return static_cast<Year*>(rawInterval);
    }

    Month* retrieveMonth() const noexcept
    {
        Interval<uint16_t>* rawInterval{ this->getInterval(MONTH_INDEX) };

        return static_cast<Month*>(rawInterval);
    }

    Day* retrieveDay() const noexcept
    {
        Interval<uint16_t>* rawInterval{ this->getInterval(DAY_INDEX) };

        return static_cast<Day*>(rawInterval);
    }

};



#endif // SIMPLYDTLIB_L_DATETIME_DATE_SEQUENCE_OBJ_H_
