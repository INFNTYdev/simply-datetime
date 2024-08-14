
#ifndef SIMPLYDTLIB_L_DATETIME_V_DATE_SEQUENCE_H_
#define SIMPLYDTLIB_L_DATETIME_V_DATE_SEQUENCE_H_



#include<chrono>
#include<cmath>

#include"simplydt/datetime/sequence/dt_sequence.hpp"
#include"simplydt/datetime/date/unit/dt_year.hpp"
#include"simplydt/datetime/date/unit/dt_month.hpp"
#include"simplydt/datetime/date/unit/dt_day.hpp"
#include"simplydt/duration/comp/virtual/dt_vduration.hpp"


/* Full date ( YYYY-mm-dd ) */
class VDate : public DatetimeSequence<Year, Month, Day> {

public:
    /* Datetime time unit */
    using TimeUnit = DatetimeSequence<Year, Month, Day>::TimeUnit;
    /* Datetime type */
    using DatetimeType = DatetimeSequence<Year, Month, Day>::DatetimeType;
    /* Standard library chronological time point (system clock) */
    using TimePoint = std::chrono::time_point<std::chrono::system_clock>;
    /* Julian Day Number (JDN) */
    using JDN = uint32_t;

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

    static const uint16_t EPOCH_YEAR = 1970Ui16;// 1970
    static const uint8_t EPOCH_MONTH = 1Ui8;// January
    static const uint8_t EPOCH_DAY = 1Ui8;// 1st
    static const JDN EPOCH_JDN = 2'440'587Ui32;// December 31, 1970
    // Epoch date: Thursday - January 1, 1970

    static const JDN MAX_JDN = 25'657'225Ui32;// December 31, 65534
    // 25,657,225.9999999 is 11:59:59.99 UT on December 31, 65534

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

    explicit VDate(uint16_t year) noexcept
        : DatetimeSequence<Year, Month, Day>{
            DatetimeType::DATE_DATETIME,
            Year(year),
            Month(EPOCH_MONTH),
            Day(EPOCH_DAY)
        }
    {
        this->populateIntervalPointers();
    }

    explicit VDate(const JDN& jdn) noexcept
        : DatetimeSequence<Year, Month, Day>{
            DatetimeType::DATE_DATETIME,
            Year(EPOCH_YEAR),
            Month(EPOCH_MONTH),
            Day(EPOCH_DAY)
        }
    {
        this->populateIntervalPointers();

        this->assumeJDN(jdn);
    }

    explicit VDate(const double& jdn) noexcept
        : DatetimeSequence<Year, Month, Day>{
            DatetimeType::DATE_DATETIME,
            Year(EPOCH_YEAR),
            Month(EPOCH_MONTH),
            Day(EPOCH_DAY)
        }
    {
        this->populateIntervalPointers();

        this->assumeJDN(jdn);
    }

    VDate(const VDate& v_date) noexcept
        : DatetimeSequence<Year, Month, Day>{
            DatetimeType::DATE_DATETIME,
            Year(v_date.year()),
            Month(v_date.month()),
            Day(v_date.day())
        }
    {
        this->populateIntervalPointers();

        this->adjustDayThreshold();
    }

    VDate(VDate&& v_date) noexcept
        : DatetimeSequence<Year, Month, Day>{
            static_cast<DatetimeSequence<Year, Month, Day>&&>(v_date)
        }
    {
        this->populateIntervalPointers();
    }

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

    VDate& operator=(const VDate& v_date) noexcept
    {
        if (this == &v_date || *this == v_date)
            return *this;

        this->getInterval(YEAR_INDEX)->setPosition(v_date.year());
        this->getInterval(MONTH_INDEX)->setPosition(v_date.month());
        this->getInterval(DAY_INDEX)->setPosition(v_date.day());

        this->adjustDayThreshold();

        return *this;
    }

    VDate& operator=(VDate&& v_date) noexcept
    {
        if (this == &v_date)
            return *this;

        DatetimeSequence<Year, Month, Day>::operator=(
            static_cast<DatetimeSequence<Year, Month, Day>&&>(v_date)
        );

        this->populateIntervalPointers();

        return *this;
    }

    VDate& operator=(const TimePoint& sys_clock) noexcept
    {
        this->assumeTimePoint(sys_clock);

        return *this;
    }

    bool operator==(const VDate& v_date) const noexcept
    {
        if (this == &v_date)
            return true;

        return DatetimeSequence<Year, Month, Day>::operator==(v_date);
    }

    bool operator==(const TimePoint& sys_clock) const noexcept
    {
        uint16_t tpYear{ 0 };
        uint16_t tpMonth{ 0 };
        uint16_t tpDay{ 0 };

        this->interpretTimePointDate(sys_clock, tpYear, tpMonth, tpDay);

        if (this->year() != tpYear)
            return false;

        if (this->month() != tpMonth)
            return false;

        if (this->day() != tpDay)
            return false;

        return true;
    }

    bool operator<(const VDate& v_date) const noexcept
    {
        return DatetimeSequence<Year, Month, Day>::operator<(v_date);
    }

    bool operator<(const TimePoint& sys_clock) const noexcept
    {
        uint16_t tpYear{ 0 };
        uint16_t tpMonth{ 0 };
        uint16_t tpDay{ 0 };

        this->interpretTimePointDate(sys_clock, tpYear, tpMonth, tpDay);

        if (this->year() > tpYear)
            return false;
        else if (this->year() < tpYear)
            return true;
        
        if (this->month() > tpMonth)
            return false;
        else if (this->month() < tpMonth)
            return true;

        if (this->day() >= tpDay)
            return false;

        return true;
    }

    bool operator>(const VDate& v_date) const noexcept
    {
        return DatetimeSequence<Year, Month, Day>::operator>(v_date);
    }

    bool operator>(const TimePoint& sys_clock) const noexcept
    {
        uint16_t tpYear{ 0 };
        uint16_t tpMonth{ 0 };
        uint16_t tpDay{ 0 };

        this->interpretTimePointDate(sys_clock, tpYear, tpMonth, tpDay);

        if (this->year() < tpYear)
            return false;
        else if (this->year() > tpYear)
            return true;
        
        if (this->month() < tpMonth)
            return false;
        else if (this->month() > tpMonth)
            return true;

        if (this->day() <= tpDay)
            return false;

        return true;
    }

    bool operator<=(const VDate& v_date) const noexcept
    {
        return DatetimeSequence<Year, Month, Day>::operator<=(v_date);
    }

    bool operator<=(const TimePoint& sys_clock) const noexcept
    {
        return (this->operator<(sys_clock) || this->operator==(sys_clock));
    }

    bool operator>=(const VDate& v_date) const noexcept
    {
        return DatetimeSequence<Year, Month, Day>::operator>=(v_date);
    }

    bool operator>=(const TimePoint& sys_clock) const noexcept
    {
        return (this->operator>(sys_clock) || this->operator==(sys_clock));
    }

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
    bool isEpoch() const noexcept
    {
        if (this->year() != EPOCH_YEAR)
            return false;
        
        if (this->month() != EPOCH_MONTH)
            return false;
        
        if (this->day() != EPOCH_DAY)
            return false;
        
        return true;
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
    const Year& yearRef() const noexcept
    {
        return *(this->m_year_ptr);
    }

    /* Returns month in date */
    const Month& monthRef() const noexcept
    {
        return *(this->m_month_ptr);
    }

    /* Returns day in date */
    const Day& dayRef() const noexcept
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

    /* Returns date as cardinal Julian Day Number (JDN) */
    JDN toJulianDayNumber() const noexcept
    {
        // Date implementation of JDN truncates decimal (0.5)

        JDN dtYear{ this->year() };
        JDN dtMonth{ this->month() };
        JDN dtDay{ this->day() };

        // Adjust for January and February
        if (dtMonth < (JDN)3Ui32) {
            dtYear -= (JDN)1Ui32;
            dtMonth += (JDN)12Ui32;
        }

        // Calculate intermediate values
        double A = std::floor(dtYear / (double)100.);
        double B = std::floor(A / (double)4.);
        double C = ((double)2. - A + B);
        double D = std::floor((double)365.25 * (dtYear + (JDN)4716Ui32));
        double E = std::floor((double)30.6001 * (dtMonth + (JDN)1Ui32));

        // Calculate final Julian Day Number
        // (JDN decimal truncated here)
        JDN dateJDN = (JDN)std::floor((C + dtDay + D + E - (double)1524.5));

        return dateJDN;
    }

    /* Returns absolute total number of days from this date until provided date */
    uint32_t daysUntil(const VDate& v_date) const noexcept
    {
        uint32_t totalDays{ 0 };

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

        // Dates in same year/month time frame
        if (this->year() == v_date.year() && this->month() == v_date.month())
            return (uint32_t)(dateRef.first->day() - dateRef.second->day());

        totalDays = (
            dateRef.first->toJulianDayNumber() - dateRef.second->toJulianDayNumber()
        );

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

    /* Increase date by provided amount of days */
    void increase(uint32_t days) noexcept
    {
        JDN newDateJDN{ (this->toJulianDayNumber() + days) };

        // Catches new JDN overflow
        if (newDateJDN < EPOCH_JDN)
            return;
        
        if (newDateJDN > MAX_JDN)
            return;

        this->assumeJDN(newDateJDN);
    }

    /* Decrease date by provided amount of days */
    void decrease(uint32_t days) noexcept
    {
        JDN newDateJDN{ (this->toJulianDayNumber() - days) };

        if (newDateJDN < EPOCH_JDN)
            return;
        
        // Catches new JDN overflow
        if (newDateJDN > MAX_JDN)
            return;

        this->assumeJDN(newDateJDN);
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
    void reset() noexcept
    {
        if (this->isEpoch())
            return;

        this->getInterval(YEAR_INDEX)->setPosition(EPOCH_YEAR);
        this->getInterval(MONTH_INDEX)->setPosition(EPOCH_MONTH);
        this->getInterval(DAY_INDEX)->setPosition(EPOCH_DAY);
    }


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

    void interpretJDNDate(const JDN& jdn,
        uint16_t& year, uint16_t& month, uint16_t& day) const noexcept
    {
        // Date implementation of JDN has truncated decimal
        // JDN Zero date: 49'594'124 (1/1/0)

        // Handle JDN value below VDate representable range
        if (jdn < EPOCH_JDN)
            return this->interpretJDNDate(EPOCH_JDN, year, month, day);

        // Handle JDN value above VDate representable range
        if (jdn > MAX_JDN)
            return this->interpretJDNDate(MAX_JDN, year, month, day);

        JDN jdnGiven{ (jdn + (JDN)1Ui32) };// +1 to account for decimal truncation

        // Calculate intermediate values
        JDN a = (JDN)4Ui32 * jdnGiven + (JDN)274'277Ui32;
        JDN b = a / (JDN)146'097Ui32;
        JDN c = (b * (JDN)3Ui32) / (JDN)4Ui32;

        JDN f = (jdnGiven + (JDN)1'401Ui32 + c - (JDN)38Ui32);
        JDN e = ((JDN)4Ui32 * f + (JDN)3Ui32);
        JDN g = (e % (JDN)1'461Ui32 / (JDN)4Ui32);
        JDN h = ((JDN)5Ui32 * g + (JDN)2Ui32);

        // Calculate gregorian calendar date values
        uint16_t gregorianDay = (
            (h % (uint16_t)153Ui16) / (uint16_t)5Ui16 + (uint16_t)1Ui16
        );

        uint16_t gregorianMonth = (
            ((h / (uint16_t)153Ui16 + (uint16_t)2Ui16)
            % (uint16_t)12Ui16) + (uint16_t)1Ui16
        );

        uint16_t gregorianYear = (
            e / (uint16_t)1'461Ui16 - (uint16_t)4'716Ui16 + ((uint16_t)14Ui16 - month)
            / (uint16_t)12Ui16
        );

        // Adjust year for non "13th" and "14th" months
        if (gregorianMonth > (uint16_t)2Ui16)
            gregorianYear -= (uint16_t)1Ui16;

        year = gregorianYear;
        month = gregorianMonth;
        day = gregorianDay;
    }

    void interpretJDNDate(const double& jdn,
        uint16_t& year, uint16_t& month, uint16_t& day) const noexcept
    {
        // Standard JDN implementation
        // JDN Zero date: 49,594,124.5 (1/1/0)

        // Handle JDN value below VDate representable range
        if (jdn < (double)EPOCH_JDN)
            return this->interpretJDNDate(EPOCH_JDN, year, month, day);

        // Handle JDN value above VDate representable range
        if (jdn >= ((double)MAX_JDN + (double)1.))
            return this->interpretJDNDate(MAX_JDN, year, month, day);

        this->interpretJDNDate((JDN)std::floor(jdn), year, month, day);
    }

    void assumeTimePoint(const TimePoint& time_point) noexcept
    {
        uint16_t gregorianYear{ 0 };
        uint16_t gregorianMonth{ 0 };
        uint16_t gregorianDay{ 0 };

        this->interpretTimePointDate(time_point, gregorianYear, gregorianMonth, gregorianDay);

        // Set date interval values
        this->getInterval(YEAR_INDEX)->setPosition(gregorianYear);
        this->getInterval(MONTH_INDEX)->setPosition(gregorianMonth);
        this->getInterval(DAY_INDEX)->setPosition(gregorianDay);

        // Set day threshold
        this->m_day_ptr->setThreshold(this->m_month_ptr->getTotalDays());
    }

    void assumeJDN(const JDN& jdn) noexcept
    {
        uint16_t gregorianYear{ 0 };
        uint16_t gregorianMonth{ 0 };
        uint16_t gregorianDay{ 0 };

        this->interpretJDNDate(jdn, gregorianYear, gregorianMonth, gregorianDay);

        // Set date interval values
        // Day threshold is updated in calls below
        this->getInterval(DAY_INDEX)->setPosition(gregorianDay);
        this->getInterval(MONTH_INDEX)->setPosition(gregorianMonth);
        this->getInterval(YEAR_INDEX)->setPosition(gregorianYear);
    }

    void assumeJDN(const double& jdn) noexcept
    {
        this->assumeJDN((JDN)std::floor(jdn));
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
        this->increase(duration.days());
    }

    void negativeDisplace(const VDuration& duration) noexcept
    {
        this->decrease(duration.days());
    }

    void populateIntervalPointers() noexcept
    {
        this->m_year_ptr = this->retrieveYear();
        this->m_month_ptr = this->retrieveMonth();
        this->m_day_ptr = this->retrieveDay();
    }

};



#endif // SIMPLYDTLIB_L_DATETIME_V_DATE_SEQUENCE_H_
