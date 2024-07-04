
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

    /* Date format */
    enum Format {
        RECORD,// Record date format (00-00-0000)
        STANDARD,// Standard date format (00/00/0000)
    };

    /* Date layout */
    enum Layout {
        M_D_YYYY,// (mm/dd/YYYY) [ Example: 01-13-2024 ]
        M_D_YY,// (mm/dd/YY) [ Example: 01-13-24 ]
        M_YYYY,// (mm/YYYY) [ Example: 01-2024 ]
        M_YY,// (mm/YY) [ Example: 01-24 ]
        M_D,// (mm/dd) [ Example: 01-13 ]
        YYYY_M_D,// (YYYY/mm/dd) [ Example: 2024-01-13 ]
        YY_M_D,// (YY/mm/dd) [ Example: 24-01-13 ]
        YYYY_D_M,// (YYYY/dd/mm) [ Example: 2024-13-01 ]
        YY_D_M,// (YY/dd/mm) [ Example: 24-13-01 ]
        YYYY_M,// (YYYY/mm) [ Example: 2024-01 ]
        YY_M,// (YY/mm) [ Example: 24-01 ]
        D_M,// (dd/mm) [ Example: 13-01 ]
    };

    Date(Chrono chrono) noexcept
        : DatetimeSequence<Year, Month, Day>{
            DatetimeType::DATE_DATETIME,
            Year(Year::YEAR_MIN),
            Month((uint16_t)1U),
            Day((uint16_t)1U)
        }
    {
        std::time_t timeT{ std::chrono::system_clock::to_time_t(chrono) };
        std::tm* tm_ptr{ std::localtime(&timeT) };

        // Retrieve date from time point
        uint16_t tmYear{ static_cast<uint16_t>(tm_ptr->tm_year) };// tm_year only measures years since 1900
        uint16_t tmMonth{ static_cast<uint16_t>(tm_ptr->tm_mon) };
        uint16_t tmDay{ static_cast<uint16_t>(tm_ptr->tm_mday) };

        Month* monthRef{ this->retrieveMonth() };
        Interval<uint16_t>* dayRef{ this->getInterval(DAY_INDEX) };

        // Set datetime interval valeus
        this->getInterval(YEAR_INDEX)->setPosition((tmYear + (uint16_t)1900U));
        monthRef->setPosition((tmMonth + (uint16_t)1U));
        dayRef->setPosition(tmDay);

        // Set day maximum
        dayRef->setThreshold(monthRef->getTotalDays());
    }

    Date(uint16_t year, uint16_t month, uint16_t day) noexcept
        : DatetimeSequence<Year, Month, Day>{
            DatetimeType::DATE_DATETIME,
            Year(year),
            Month(month),
            Day(day)
        }
    {
        this->adjustDayThreshold();
    }

    Date(uint16_t year, uint16_t month) noexcept
        : DatetimeSequence<Year, Month, Day>{
            DatetimeType::DATE_DATETIME,
            Year(year),
            Month(month),
            Day((uint16_t)1U)
        }
    {
        this->adjustDayThreshold();
    }

    Date(uint16_t year) noexcept
        : DatetimeSequence<Year, Month, Day>{
            DatetimeType::DATE_DATETIME,
            Year(year),
            Month((uint16_t)1U),
            Day((uint16_t)1U)
        }
    {
        this->adjustDayThreshold();
    }

    Date() noexcept
        : DatetimeSequence<Year, Month, Day>{
            DatetimeType::DATE_DATETIME,
            Year(Year::YEAR_MIN),
            Month((uint16_t)1U),
            Day((uint16_t)1U)
        }
    {
        this->adjustDayThreshold();
    }

    virtual ~Date() noexcept = default;

    friend std::ostream& operator<<(std::ostream& os, const Date& date) noexcept
    {
        os << date.dateStr();

        return os;
    }

    /* Returns year of date */
    uint16_t year() const noexcept
    {
        return this->getInterval(YEAR_INDEX)->position();
    }

    /* Returns month of date */
    uint16_t month() const noexcept
    {
        return this->getInterval(MONTH_INDEX)->position();
    }

    /* Returns day of date */
    uint16_t day() const noexcept
    {
        return this->getInterval(DAY_INDEX)->position();
    }

    /* Returns date day-of-week literal */
    const char* dayOfWeek() const noexcept
    {
        this->retrieveDay()->getDayOfWeek();
    }

    /* Returns date month literal */
    const char* monthTitle() const noexcept
    {
        this->retrieveMonth()->getName();
    }

    /* Returns date string with provided configuration */
    std::string dateStr(Format format, Layout layout) const noexcept
    {
        std::string date;
        date.reserve((size_t)10ULL);
        date = "";

        char delimiter{ '-' };

        if (format == Format::STANDARD)
            delimiter = '/';

        switch (layout) {
        case Layout::M_D_YYYY:
            date += (this->retrieveMonth()->toDoubleDigitStr() + delimiter);
            date += (this->retrieveDay()->toDoubleDigitStr() + delimiter);
            date += this->getInterval(YEAR_INDEX)->toStr();
            break;
        case Layout::M_D_YY:
            date += (this->retrieveMonth()->toDoubleDigitStr() + delimiter);
            date += (this->retrieveDay()->toDoubleDigitStr() + delimiter);
            date += this->retrieveYear()->toDoubleDigitStr();
            break;
        case Layout::M_YYYY:
            date += (this->retrieveMonth()->toDoubleDigitStr() + delimiter);
            date += this->getInterval(YEAR_INDEX)->toStr();
            break;
        case Layout::M_YY:
            date += (this->retrieveMonth()->toDoubleDigitStr() + delimiter);
            date += this->retrieveYear()->toDoubleDigitStr();
            break;
        case Layout::M_D:
            date += (this->retrieveMonth()->toDoubleDigitStr() + delimiter);
            date += this->retrieveDay()->toDoubleDigitStr();
            break;
        case Layout::YYYY_M_D:
            date += (this->getInterval(YEAR_INDEX)->toStr() + delimiter);
            date += (this->retrieveMonth()->toDoubleDigitStr() + delimiter);
            date += this->retrieveDay()->toDoubleDigitStr();
            break;
        case Layout::YY_M_D:
            date += (this->retrieveYear()->toDoubleDigitStr() + delimiter);
            date += (this->retrieveMonth()->toDoubleDigitStr() + delimiter);
            date += this->retrieveDay()->toDoubleDigitStr();
            break;
        case Layout::YYYY_D_M:
            date += (this->getInterval(YEAR_INDEX)->toStr() + delimiter);
            date += (this->retrieveDay()->toDoubleDigitStr() + delimiter);
            date += this->retrieveMonth()->toDoubleDigitStr();
            break;
        case Layout::YY_D_M:
            date += (this->retrieveYear()->toDoubleDigitStr() + delimiter);
            date += (this->retrieveDay()->toDoubleDigitStr() + delimiter);
            date += this->retrieveMonth()->toDoubleDigitStr();
            break;
        case Layout::YYYY_M:
            date += (this->getInterval(YEAR_INDEX)->toStr() + delimiter);
            date += this->retrieveMonth()->toDoubleDigitStr();
            break;
        case Layout::YY_M:
            date += (this->retrieveYear()->toDoubleDigitStr() + delimiter);
            date += this->retrieveMonth()->toDoubleDigitStr();
            break;
        case Layout::D_M:
            date += (this->retrieveDay()->toDoubleDigitStr() + delimiter);
            date += this->retrieveMonth()->toDoubleDigitStr();
            break;
        }

        return date;
    }

    /* Returns date string with provided configuration */
    std::string dateStr(Layout layout, Format format) const noexcept
    {
        return this->dateStr(format, layout);
    }

    /* Returns date string with provided format */
    std::string dateStr(Format format) const noexcept
    {
        return this->dateStr(format, Layout::M_D_YYYY);
    }

    /* Returns date string with provided layout */
    std::string dateStr(Layout layout) const noexcept
    {
        return this->dateStr(Format::RECORD, layout);
    }

    /* Returns date string */
    std::string dateStr() const noexcept
    {
        return this->dateStr(Format::RECORD, Layout::M_D_YYYY);
    }

    /* Returns year in date */
    Year& getYear() const noexcept
    {
        return *(this->retrieveYear());
    }

    /* Returns month in date */
    Month& getMonth() const noexcept
    {
        return *(this->retrieveMonth());
    }

    /* Returns day in date */
    Day& getDay() const noexcept
    {
        return *(this->retrieveDay());
    }

    ///* Returns date as standard chronological time point */   <--- This is going to take lots of work...
    //Chrono toChrono() const noexcept
    //{
    //    /*****************************************************************************\
    //    *             vvv           AI GENERATED CODE BELOW           vvv             *
    //    \*****************************************************************************/
    //
    //    //
    //
    //    /*****************************************************************************\
    //    *             ^^^           AI GENERATED CODE ABOVE           ^^^             *
    //    \*****************************************************************************/
    //
    //    //
    //}


private:
    static const uint8_t YEAR_INDEX{ 0 };
    static const uint8_t MONTH_INDEX{ 1 };
    static const uint8_t DAY_INDEX{ 2 };

    size_t timeUnitEnumToIndex(TimeUnit time_unit) noexcept
    {
        switch (time_unit) {
        case TimeUnit::YEAR:
            return YEAR_INDEX;
        case TimeUnit::MONTH:
            return MONTH_INDEX;
        case TimeUnit::DAY:
            return DAY_INDEX;
        default:
            return this->linkSize();// Results in nullptr interval
        }
    }

    TimeUnit indexToTimeUnitEnum(size_t index) noexcept
    {
        switch (index) {
        case YEAR_INDEX:
            return TimeUnit::YEAR;
        case MONTH_INDEX:
            return TimeUnit::MONTH;
        case DAY_INDEX:
            return TimeUnit::DAY;
        default:
            return TimeUnit::ARB;
        }
    }

    void adjustDayThreshold() noexcept
    {
        Month* monthRef{ this->retrieveMonth() };
        Interval<uint16_t>* dayRef{ this->getInterval(DAY_INDEX) };

        dayRef->setThreshold(monthRef->getTotalDays());
    }

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
