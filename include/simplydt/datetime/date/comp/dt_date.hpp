
#ifndef SIMPLYDTLIB_L_DATETIME_DATE_SEQUENCE_OBJ_H_
#define SIMPLYDTLIB_L_DATETIME_DATE_SEQUENCE_OBJ_H_



#include<chrono>

#include"simplydt/datetime/sequence/dt_sequence.hpp"
#include"simplydt/datetime/date/unit/dt_year.hpp"
#include"simplydt/datetime/date/unit/dt_month.hpp"
#include"simplydt/datetime/date/unit/dt_day.hpp"
#include"simplydt/duration/comp/dt_duration.hpp"


/* Full date ( YYYY-mm-dd ) */
class VDate : public DatetimeSequence<Year, Month, Day> {

public:
    /* Datetime time unit */
    using TimeUnit = DatetimeSequence<Year, Month, Day>::TimeUnit;
    /* Datetime type */
    using DatetimeType = DatetimeSequence<Year, Month, Day>::DatetimeType;
    /* Standard library chronological time point (system clock) */
    using TimePoint = std::chrono::time_point<std::chrono::system_clock>;

    /* Date format */
    enum Format {
        RECORD,// Date record format (01-01-1970)
        STANDARD,// Date standard format (01/01/1970)
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

    static const uint16_t EPOCH_YEAR = 1970Ui16;
    static const uint8_t EPOCH_MONTH = 1Ui8;
    static const uint8_t EPOCH_DAY = 1Ui8;
    // Epoch date: Thursday - January 1, 1970

    VDate(const TimePoint& sys_clock) noexcept
        : DatetimeSequence<Year, Month, Day>{
            DatetimeType::DATE_DATETIME,
            Year(EPOCH_YEAR),
            Month(EPOCH_MONTH),
            Day(EPOCH_DAY)
        }
    {
        this->populateIntervalPointers();

        this->assumeTimePoint(sys_clock);
    }

    VDate(uint16_t year, uint16_t month, uint16_t day) noexcept
        : DatetimeSequence<Year, Month, Day>{
            DatetimeType::DATE_DATETIME,
            Year(year),
            Month(month),
            Day(day)
        }
    {
        this->populateIntervalPointers();

        this->adjustDayThreshold();
    }

    VDate(uint16_t year, uint16_t month) noexcept
        : DatetimeSequence<Year, Month, Day>{
            DatetimeType::DATE_DATETIME,
            Year(year),
            Month(month),
            Day(EPOCH_DAY)
        }
    {
        this->populateIntervalPointers();

        this->adjustDayThreshold();
    }

    VDate(uint16_t year) noexcept
        : DatetimeSequence<Year, Month, Day>{
            DatetimeType::DATE_DATETIME,
            Year(year),
            Month(EPOCH_MONTH),
            Day(EPOCH_DAY)
        }
    {
        this->populateIntervalPointers();
    }

    VDate(const VDate& v_date) noexcept;// <--- INCOMPLETE!

    VDate(VDate&& v_date) noexcept;// <--- INCOMPLETE!

    VDate() noexcept
        : DatetimeSequence<Year, Month, Day>{
            DatetimeType::DATE_DATETIME,
            Year(EPOCH_YEAR),
            Month(EPOCH_MONTH),
            Day(EPOCH_DAY)
        }
    {
        this->populateIntervalPointers();
    }

    virtual ~VDate() noexcept = default;

    friend std::ostream& operator<<(std::ostream& os, const VDate& v_date) noexcept
    {
        os << v_date.dateStr();

        return os;
    }

    VDate& operator=(const VDate& v_date) noexcept;// <--- INCOMPLETE!

    VDate& operator=(VDate&& v_date) noexcept;// <--- INCOMPLETE!

    VDate& operator=(const TimePoint& sys_clock) noexcept
    {
        this->assumeTimePoint(sys_clock);

        return *this;
    }

    bool operator==(const VDate& v_date) const noexcept;// <--- INCOMPLETE!

    bool operator==(const TimePoint& sys_clock) const noexcept;// <--- INCOMPLETE!

    bool operator<(const VDate& v_date) const noexcept;// <--- INCOMPLETE!

    bool operator<(const TimePoint& sys_clock) const noexcept;// <--- INCOMPLETE!

    bool operator>(const VDate& v_date) const noexcept;// <--- INCOMPLETE!

    bool operator>(const TimePoint& sys_clock) const noexcept;// <--- INCOMPLETE!

    bool operator<=(const VDate& v_date) const noexcept;// <--- INCOMPLETE!

    bool operator<=(const TimePoint& sys_clock) const noexcept;// <--- INCOMPLETE!

    bool operator>=(const VDate& v_date) const noexcept;// <--- INCOMPLETE!
    
    bool operator>=(const TimePoint& sys_clock) const noexcept;// <--- INCOMPLETE!

    VDate operator+(const VDuration& v_duration) const noexcept
    {
        VDate result{ *this };

        result.displace(v_duration);

        return result;
    }

    VDate operator-(const VDuration& v_duration) const noexcept
    {
        VDate result{ *this };

        switch (v_duration.sign()) {
        case VDuration::Sign::NEGATIVE:
            // Double negative = positive
            result.positiveDisplace(v_duration);
            break;

        default:
            result.displace(v_duration);
        }

        return result;
    }

    VDate& operator+=(const VDuration& v_duration) noexcept
    {
        this->displace(v_duration);

        return *this;
    }

    VDate& operator-=(const VDuration& v_duration) noexcept
    {
        switch (v_duration.sign()) {
        case VDuration::Sign::NEGATIVE:
            // Double negative = positive
            this->positiveDisplace(v_duration);
            break;

        default:
            this->displace(v_duration);
        }

        return *this;
    }

    /* Returns true if date represents epoch date */
    bool isEpoch() const noexcept;// <--- INCOMPLETE!

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
        return this->m_day_ptr->getDayOfWeek();
    }

    /* Returns date month literal */
    const char* monthTitle() const noexcept
    {
        return this->m_month_ptr->getTitle();
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
    Year& yearRef() const noexcept
    {
        return *(this->m_year_ptr);
    }

    /* Returns month in date */
    Month& monthRef() const noexcept
    {
        return *(this->m_month_ptr);
    }

    /* Returns day in date */
    Day& dayRef() const noexcept
    {
        return *(this->m_day_ptr);
    }

    /* Returns year in date */
    Year* getYear() noexcept
    {
        return this->m_year_ptr;
    }

    /* Returns month in date */
    Month* getMonth() noexcept
    {
        return this->m_month_ptr;
    }

    /* Returns day in date */
    Day* getDay() noexcept
    {
        return this->m_day_ptr;
    }

    /* Returns date as Julian Day Number (JDN) */
    size_t toJulianDayNumber() const noexcept;// <--- INCOMPLETE!

    /* Returns absolute total number of days from this date until provided date */
    size_t daysUntil(const VDate& v_date) const noexcept
    {
        // NOTE: This method is changing, new solution found
        // (^ Use Julian day number system to obtain results)

        size_t totalDays{ 0 };

        if (this == &v_date || *this == v_date)
            return totalDays;

        std::pair<const VDate*, const VDate*> dateRef{ nullptr, nullptr };// (high, low)

        if (this->isAfter(v_date)) {
            dateRef.first = this;
            dateRef.second = &v_date;
        }
        else {
            dateRef.first = &v_date;
            dateRef.second = this;
        }

        // Dates in same month time frame
        if (this->year() == v_date.year() && this->month() == v_date.month())
            return (dateRef.first->day() - dateRef.second->day());

        // Lambda: Returns true if simulated year-month frame matches dates
        auto monthFrameMatch = [](const VDate* date, uint16_t year, uint16_t month)-> bool {
            return (year == date->year() && month == date->month());
        };

        // Lambda: Increment simulated year-month time frame
        auto incrementMonthFrame = [](uint16_t& year, uint16_t& month)-> void {
            if (month < (uint16_t)12U)
                ++month;
            else if (month == (uint16_t)12U) {
                month = (uint16_t)1U;
                ++year;
            }
        };

        // Dates in different month time frames
        uint16_t yearSim{ dateRef.second->year() };
        uint16_t monthSim{ dateRef.second->month() };

        totalDays += dateRef.second->dayRef().untilThreshold();
        incrementMonthFrame(yearSim, monthSim);

        while (!monthFrameMatch(dateRef.first, yearSim, monthSim)) {

            totalDays += simplydt::getTotalDaysInMonth(yearSim, monthSim);

            incrementMonthFrame(yearSim, monthSim);

        }

        totalDays += dateRef.first->day();

        return totalDays;
    }

    /* Returns duration between this date and provided date */
    VDuration until(const VDate& v_date) const noexcept
    {
        if (this == &v_date || *this == v_date)
            return VDuration{};

        if (this->isAfter(v_date)) {
            VDuration newDur{ VDuration::Sign::NEGATIVE };

            newDur.getDays()->largeDisplace(
                VDuration::Sign::POSITIVE,
                this->daysUntil(v_date)
            );

            return newDur;
        }
        else {
            VDuration newDur{ VDuration::Sign::POSITIVE };

            newDur.getDays()->largeDisplace(
                VDuration::Sign::POSITIVE,
                this->daysUntil(v_date)
            );

            return newDur;
        }
    }

    /* Returns date as standard library system time point */
    TimePoint toTimePoint() const noexcept
    {
        TimePoint timePoint{};

        VDate epoch{};
        VDuration sinceEpoch{ epoch.until(*this) };

        timePoint = (timePoint + sinceEpoch.toChronoDuration());

        return timePoint;
    }

    /* Displace date using provided duration */
    void displace(const VDuration& duration) noexcept
    {
        switch (duration.sign()) {
        case VDuration::Sign::NEGATIVE:
            return this->negativeDisplace(duration);
        default:
            return this->positiveDisplace(duration);
        }
    }

    /* Reset date to epoch date */
    void reset() noexcept;// <--- INCOMPLETE!


private:
    static const uint8_t YEAR_INDEX{ 0 };
    static const uint8_t MONTH_INDEX{ 1 };
    static const uint8_t DAY_INDEX{ 2 };

    Year* m_year_ptr;
    Month* m_month_ptr;
    Day* m_day_ptr;

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
        this->m_month_ptr->updateDayThreshold();
    }

    void interpretTimePointDate(const TimePoint& time_point,
        uint16_t& year, uint16_t& month, uint16_t& day) const noexcept
    {
        std::time_t timeT{ std::chrono::system_clock::to_time_t(time_point) };
        std::tm* tm_ptr{ std::localtime(&timeT) };

        // Retrieve date from time point
        year = static_cast<uint16_t>(tm_ptr->tm_year);// tm_year only measures years since 1900
        month = static_cast<uint16_t>(tm_ptr->tm_mon);
        day = static_cast<uint16_t>(tm_ptr->tm_mday);

        year += (uint16_t)1900Ui16;
        month += (uint16_t)1Ui16;
    }

    void assumeTimePoint(const TimePoint& time_point) noexcept
    {
        uint16_t tmYear{ 0 };
        uint16_t tmMonth{ 0 };
        uint16_t tmDay{ 0 };

        this->interpretTimePointDate(time_point, tmYear, tmMonth, tmDay);

        // Set date interval values
        this->getInterval(YEAR_INDEX)->setPosition(tmYear);
        this->getInterval(MONTH_INDEX)->setPosition(tmMonth);
        this->getInterval(DAY_INDEX)->setPosition(tmDay);

        // Set day threshold
        this->m_day_ptr->setThreshold(this->m_month_ptr->getTotalDays());
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

    void positiveDisplace(const VDuration& duration) noexcept
    {
        this->getDay()->dateDisplace(
            Day::Trans::POSITIVE,
            duration.convertedTo(VDuration::TimeUnit::DAY)
        );
    }

    void negativeDisplace(const VDuration& duration) noexcept
    {
        this->getDay()->dateDisplace(
            Day::Trans::POSITIVE,
            duration.convertedTo(VDuration::TimeUnit::DAY)
        );
    }

    void populateIntervalPointers() noexcept
    {
        this->m_year_ptr = this->retrieveYear();
        this->m_month_ptr = this->retrieveMonth();
        this->m_day_ptr = this->retrieveDay();
    }

};



#endif // SIMPLYDTLIB_L_DATETIME_DATE_SEQUENCE_OBJ_H_
