
#ifndef SIMPLYDTLIB_L_DATE_INTERVAL_H_
#define SIMPLYDTLIB_L_DATE_INTERVAL_H_



#include"simplydt/common/interval/interval.hpp"
#include"simplydt/datetime/date/date_utility.hpp"


/* Datetime date interval */
class DateInterval : public Interval<uint16_t> {

public:
    /* Date interval translation modes */
	using Trans = Interval<uint16_t>::Trans;

    /* Date interval unit */
    enum Unit {
        ARB,// Arbitrary unit of time
        YEAR,// Year unit
        MONTH,// Month unit
        DAY,// Day unit
    };

    DateInterval(Unit unit, uint16_t value) noexcept
        : Interval<uint16_t>{ getUnitMax(unit), (uint16_t)1Ui16, value },
        m_unitOfMeasure{ unit }
    {
        //
    }

    DateInterval(const DateInterval& date_interval) noexcept
        : Interval<uint16_t>{
        date_interval.threshold(),
        date_interval.startPosition(),
        date_interval.position()
        },
        m_unitOfMeasure{ date_interval.m_unitOfMeasure }
    {
        //
    }

    DateInterval(DateInterval&& date_interval) noexcept
        : Interval<uint16_t>{ static_cast<Interval&&>(date_interval) },
        m_unitOfMeasure{ std::move(date_interval.m_unitOfMeasure) }
    {
        //
    }

    virtual ~DateInterval() = default;

    /* Returns provided date unit max value */
    uint16_t getUnitMax(Unit unit) noexcept
    {
        switch (unit) {
        case Unit::MONTH:
            return (uint16_t)12Ui16;
        case Unit::DAY:
            return (uint16_t)31Ui16;
        default:
            return (uint16_t)(std::numeric_limits<uint16_t>::max() - (uint16_t)1Ui16);
        }
    }

    DateInterval& operator=(const DateInterval& date_interval) noexcept
    {
        if (this == &date_interval)
            return *this;

        this->m_unitOfMeasure = date_interval.m_unitOfMeasure;
        Interval<uint16_t>::operator=(date_interval);

        return *this;
    }

    DateInterval& operator=(DateInterval&& date_interval) noexcept
    {
        if (this == &date_interval)
            return *this;

        this->m_unitOfMeasure = std::move(date_interval.m_unitOfMeasure);
        Interval<uint16_t>::operator=(static_cast<Interval<uint16_t>&&>(date_interval));

        return *this;
    }

    /* Returns true if both date intervals have same unit of measure and position attributes */
    bool operator==(const DateInterval& date_interval) noexcept
    {
        if (!this->isSameUnitOfTime(date_interval))
            return false;

        return Interval<uint16_t>::operator==(date_interval);
    }

    /* Returns date interval unit of measure */
    Unit unitOfTime() const noexcept
    {
        return this->m_unitOfMeasure;
    }

    /* Returns true if provided date interval uses same unit of measure */
    bool isSameUnitOfTime(const DateInterval& date_interval) const noexcept
    {
        return (this->m_unitOfMeasure == date_interval.m_unitOfMeasure);
    }

    /* Returns date interval value in double digit format */
    std::string toDoubleDigitStr() const noexcept
    {
        if (this->position() > (uint16_t)9Ui16 && this->position() <= (uint16_t)99Ui16)
            return this->toStr();

        if (this->position() < (uint16_t)10Ui16)
            return std::string{ ('0' + this->toStr()) };

        std::string pos{ this->toStr() };

        return pos.substr((pos.size() - (size_t)2Ui64));
    }

    /* Returns true if interval is composed in date */
    bool isDateLinked() const noexcept
    {
        switch (this->m_unitOfMeasure) {
        case Unit::YEAR:
            if (!this->hasSubsequentInterval())
                return false;// No month linked to year

            if (!this->subsequentNode().hasSubsequentInterval())
                return false;// No day linked to month

            return true;

        case Unit::MONTH:
            if (!this->hasPrecedingInterval())
                return false;// No year linked to month

            if (!this->hasSubsequentInterval())
                return false;// No day linked to month

            return true;

        case Unit::DAY:
            if (!this->hasPrecedingInterval())
                return false;// No month linked to day

            if (!this->precedingNode().hasPrecedingInterval())
                return false;// No year linked to month

            return true;
        }

        return false;
    }

    /* Translate date interval position in provided direction with provided units */
    virtual void dateDisplace(Trans trans, size_t units) noexcept
    {
        switch (this->m_unitOfMeasure) {
        case Unit::YEAR:
        case Unit::MONTH:
            Interval<uint16_t>::largeDisplace(trans, units);// <--- Manually do this?

            if (!this->isDateLinked())
                return;
            
            return this->updateDayThreshold();

        case Unit::DAY:
            this->dayDisplace(trans, units);

            return;// Day displace updates threshold

        default:
            return;
        }
    }


protected:
    /* Update date managed day interval threshold */
    void updateDayThreshold() noexcept
    {
        if (!this->isDateLinked())
            return;

        uint16_t newDayMax{ 0 };
        uint16_t dayOffset{ 0 };

        LinkedInterval day_ptr{ nullptr };

        switch (this->m_unitOfMeasure) {
        case Unit::YEAR:
            newDayMax = simplydt::getTotalDaysInMonth(
                this->position(),// Year value
                this->subsequentNode().position()// Month value
            );

            day_ptr = this->getSubsequent()->getSubsequent();

            break;

        case Unit::MONTH:
            newDayMax = simplydt::getTotalDaysInMonth(
                this->precedingNode().position(),// Year value
                this->position()// Month value
            );

            day_ptr = this->getSubsequent();

            break;

        case Unit::DAY:
            newDayMax = simplydt::getTotalDaysInMonth(
                this->precedingNode().precedingNode().position(),// Year value
                this->precedingNode().position()// Month value
            );

            day_ptr = this;
        }

        // Invalid circumstances
        if (day_ptr == nullptr || newDayMax < (uint16_t)28Ui16)
            return;

        if (day_ptr->threshold() == newDayMax)
            return;

        // Adjust day position if above new month threshold
        if (day_ptr->position() > newDayMax) {
            dayOffset = (uint16_t)(day_ptr->position() - newDayMax);

            day_ptr->setPosition(newDayMax);
        }

        // Set day interval new threshold
        day_ptr->setThreshold(newDayMax);

        // Handle day offset if any
        if (dayOffset > (uint16_t)0Ui16) {
            day_ptr->displace(Trans::POSITIVE, dayOffset);

            this->updateDayThreshold();// 1-deep recursive call
        }
    }


private:
    Unit m_unitOfMeasure;

    void dayDisplace(Trans trans, size_t units) noexcept
    {
        // This method is only to be invoked by day intervals
        if (this->m_unitOfMeasure != Unit::DAY)
            return;

        if (units <= this->untilThreshold() || !this->isDateLinked())
            return Interval<uint16_t>::displace(trans, units);

        // NOTE: Make a simplydt::daysInDecade() method?
        // (could prove useful here)

        uint16_t translate{ 0 };

        // Loop by year (if applicable)
        if (units > (size_t)364Ui64) {
            uint16_t offset{ 7 };// for 7 days lost using 31 as threshold

            while (units != (size_t)0Ui64) {

                // Set day threshold to 31 for calculations
                // (this simplifies things)
                if (this->threshold() != (uint16_t)31Ui16)
                    this->setThreshold(31);

                if (simplydt::isLeapYear(this->precedingNode().precedingNode().position()))
                    offset = (uint16_t)6Ui16;// 6 days lost instead if leap year
                else if (offset != (uint16_t)7Ui16)
                    offset = (uint16_t)7Ui16;

                // Units needed to reach 1 year from date
                translate = (
                    simplydt::getTotalDaysInYear(
                        this->precedingNode().precedingNode().position()// Year value
                    ) + offset
                );

                // If 1 year from date exceeds desired displace units:
                // (offset applies to Interval class only)
                if ((translate - offset) > units)
                    break;// Loop by month next

                // Go to next year and update day threshold
                Interval<uint16_t>::displace(trans, translate);
                this->updateDayThreshold();

                // Decrease units by days in year
                units -= (translate - offset);

            }
        }

        // Loop by month
        while (units != (size_t)0Ui64) {

            // Units needed to reach 1st of next month
            translate = (this->untilThreshold() + (uint16_t)1Ui16);

            // If 1st of next month exceeds desired displace units:
            if (translate > units)
                return Interval<uint16_t>::displace(trans, units);

            // Go to 1st of next month and update threshold
            Interval<uint16_t>::displace(trans, translate);
            this->updateDayThreshold();

            units -= translate;

        }
    }

};



#endif // SIMPLYDTLIB_L_DATE_INTERVAL_H_
