
#ifndef SIMPLYDTLIB_L_TIME_INTERVAL_H_
#define SIMPLYDTLIB_L_TIME_INTERVAL_H_



#include"simplydt/common/interval/interval.hpp"
#include"simplydt/datetime/date/date_interval.hpp"


/* Datetime time interval */
class TimeInterval : public Interval<uint16_t> {

public:
	/* Time interval translation modes */
	using Trans = Interval<uint16_t>::Trans;

    /* Time interval unit */
    enum Unit {
        ARB,// Arbitrary unit of time
        HOUR,// Hour unit
        MINUTE,// Minute unit
        SECOND,// Second unit
		MILLISECOND,// Millisecond unit
    };

    TimeInterval(Unit unit, uint16_t value) noexcept
        : Interval<uint16_t>{ getUnitMax(unit), (uint16_t)0Ui16, value },
        m_unitOfMeasure{ unit }
    {
        //
    }

    TimeInterval(const TimeInterval& time_interval) noexcept
		: Interval<uint16_t>{
			time_interval.threshold(),
			time_interval.startPosition(),
			time_interval.position()
		},
		m_unitOfMeasure{ time_interval.m_unitOfMeasure }
    {
        //
    }

    TimeInterval(TimeInterval&& time_interval) noexcept
		: Interval<uint16_t>{ static_cast<Interval&&>(time_interval) },
		m_unitOfMeasure{ std::move(time_interval.m_unitOfMeasure) }
	{
		//
	}

    virtual ~TimeInterval() = default;

    /* Returns provided time unit max value */
    static uint16_t getUnitMax(Unit unit) noexcept
    {
        switch (unit) {
        case Unit::HOUR:
            return (uint16_t)23Ui16;
        case Unit::MINUTE:
            return (uint16_t)59Ui16;
        case Unit::SECOND:
            return (uint16_t)59Ui16;
        case Unit::MILLISECOND:
            return (uint16_t)999Ui16;
        default:
            return (uint16_t)(std::numeric_limits<uint16_t>::max() - (uint16_t)1Ui16);
        }
    }

    TimeInterval& operator=(const TimeInterval& time_interval) noexcept
	{
        if (this == &time_interval)
            return *this;

        this->m_unitOfMeasure = time_interval.m_unitOfMeasure;
        Interval<uint16_t>::operator=(time_interval);

        return *this;
	}

    TimeInterval& operator=(TimeInterval&& time_interval) noexcept
    {
        if (this == &time_interval)
            return *this;

        this->m_unitOfMeasure = std::move(time_interval.m_unitOfMeasure);
        Interval<uint16_t>::operator=(static_cast<Interval<uint16_t>&&>(time_interval));

        return *this;
    }

    /* Returns true if both time intervals have same unit of measure and position attributes */
    bool operator==(const TimeInterval& time_interval) noexcept
    {
        if (!this->isSameUnitOfTime(time_interval))
            return false;

        return Interval<uint16_t>::operator==(time_interval);
    }

    /* Returns time interval unit of measure */
    Unit unitOfTime() const noexcept
    {
        return this->m_unitOfMeasure;
    }

    /* Returns true if provided time interval uses same unit of measure */
    bool isSameUnitOfTime(const TimeInterval& time_interval) const noexcept
    {
        return (this->m_unitOfMeasure == time_interval.m_unitOfMeasure);
    }

    /* Returns date interval value in double digit format */
    std::string toDoubleDigitStr() const noexcept
    {
        if (this->position() > (uint16_t)9Ui16 && this->position() <= (uint16_t)99Ui16)
            return this->toStr();

        if (this->position() < (uint16_t)10Ui16)
            return std::string{ ('0' + this->toStr()) };

        std::string posStr{ this->toStr() };

        return posStr.substr((posStr.size() - (size_t)2Ui64));
    }

    /* Displace time interval in provided direction with provided units */
    void displace(Trans trans, uint16_t units) noexcept
    {
        if (this->m_unitOfMeasure != Unit::HOUR)
            return Interval<uint16_t>::displace(trans, units);

        Interval<uint16_t>::TransResult destination{
            this->calculateTranslation(trans, units)
        };

        this->setPosition(destination.second);

        if (this->hasPrecedingInterval()) {
            // hour interval invokes DateInterval behavior on lap
            DateInterval* preceding_ptr{
                static_cast<DateInterval*>(this->getPreceding())
            };

            preceding_ptr->dateDisplace(trans, destination.first);
        }
    }

    /* Displace time interval in provided direction with provided units */
    void largeDisplace(Trans trans, size_t units) noexcept
    {
        if (this->m_unitOfMeasure != Unit::HOUR)
            return Interval<uint16_t>::largeDisplace(trans, units);

        Interval<uint16_t>::LargeTransResult destination{
            this->calculateLargeTranslation(trans, units)
        };

        this->setPosition(destination.second);

        if (this->hasPrecedingInterval()) {
            // Check if this is linked like a datetime
            // (if not send laps to preceding as usual)
            if (!this->precedingNode().hasPrecedingInterval())
                return this->getPreceding()->largeDisplace(trans, destination.first);

            // hour interval invokes DateInterval behavior on lap
            DateInterval* preceding_ptr{
                static_cast<DateInterval*>(this->getPreceding())
            };

            preceding_ptr->dateDisplace(trans, destination.first);
        }
    }

    /* Increase time interval value by provided amount of units */
    void increase(size_t units = (size_t)1Ui64) noexcept
    {
        this->largeDisplace(Trans::POSITIVE, units);
    }

    /* Decrease time interval value by provided amount of units */
    void decrease(size_t units = (size_t)1Ui64) noexcept
    {
        this->largeDisplace(Trans::NEGATIVE, units);
    }


private:
    Unit m_unitOfMeasure;

};



#endif // SIMPLYDTLIB_L_TIME_INTERVAL_H_
