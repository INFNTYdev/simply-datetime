
#ifndef SIMPLYDTLIB_L_DATE_INTERVAL_H_
#define SIMPLYDTLIB_L_DATE_INTERVAL_H_



#include"simplydt/common/interval/interval.hpp"


/* Datetime date interval */
class DateInterval : public Interval<uint16_t> {

public:
    /* Date interval unit */
    enum Unit {
        ARB,// Arbitrary unit of time
        YEAR,// Year unit
        MONTH,// Month unit
        DAY,// Day unit
    };

    DateInterval(Unit unit, uint16_t value) noexcept
        : Interval<uint16_t>{ getUnitMax(unit), (uint16_t)1U, value },
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
            return (uint16_t)12U;
        case Unit::DAY:
            return (uint16_t)31U;
        default:
            return (std::numeric_limits<uint16_t>::max() - (uint16_t)1Ui16);
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
        if (this->position() > (uint16_t)9U && this->position() <= (uint16_t)99U)
            return this->toStr();

        if (this->position() < (uint16_t)10U)
            return std::string{ ('0' + this->toStr()) };

        std::string pos{ this->toStr() };

        return pos.substr((pos.size() - (size_t)2));
    }


private:
    Unit m_unitOfMeasure;

};



#endif // SIMPLYDTLIB_L_DATE_INTERVAL_H_
