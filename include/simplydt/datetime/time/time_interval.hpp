
#ifndef SIMPLYDTLIB_L_TIME_INTERVAL_H_
#define SIMPLYDTLIB_L_TIME_INTERVAL_H_



#include"simplydt/common/interval/interval.hpp"


/* Datetime time interval */
class TimeInterval : public Interval<uint16_t> {

public:
	/* Time interval unit */
    enum Unit {
        ARB,// Arbitrary unit of time
        HOUR,// Hour unit
        MINUTE,// Minute unit
        SECOND,// Second unit
		MILLISECOND,// Millisecond unit
    };

    TimeInterval(Unit unit, uint16_t value) noexcept
        : Interval<uint16_t>{ getUnitMax(unit), (uint16_t)0U, value },
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

    ~TimeInterval() = default;

    /* Returns provided time unit max value */
    uint16_t getUnitMax(Unit unit) noexcept
    {
        switch (unit) {
        case Unit::HOUR:
            return (uint16_t)23U;
        case Unit::MINUTE:
            return (uint16_t)59U;
        case Unit::SECOND:
            return (uint16_t)59U;
        case Unit::MILLISECOND:
            return (uint16_t)999U;
        default:
            return std::numeric_limits<uint16_t>::max();
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
        if (this->position() > (uint16_t)9U && this->position() <= (uint16_t)99U)
            return this->toStr();

        if (this->position() < (uint16_t)10U)
            return std::string{ ('0' + this->toStr()) };

        std::string posStr{ this->toStr() };

        return posStr.substr((posStr.size() - (size_t)2));
    }


private:
    Unit m_unitOfMeasure;

};



#endif // SIMPLYDTLIB_L_TIME_INTERVAL_H_
