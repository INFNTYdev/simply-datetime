
#include"simplydt/datetime/time/time_interval.hpp"


//	TimeInterval : CONSTRUCTORS

//	TimeInterval : DESTRUCTOR

//	TimeInterval : FREE



//	TimeInterval : OPERATOR

TimeInterval& TimeInterval::operator=(const TimeInterval& time_interval) noexcept
{
    if (this == &time_interval)
        return *this;

    this->m_unitOfMeasure = time_interval.m_unitOfMeasure;
    Interval<uint16_t>::operator=(time_interval);

    return *this;
}

TimeInterval& TimeInterval::operator=(TimeInterval&& time_interval) noexcept
{
    if (this == &time_interval)
        return *this;

    this->m_unitOfMeasure = std::move(time_interval.m_unitOfMeasure);
    Interval<uint16_t>::operator=(static_cast<Interval<uint16_t>&&>(time_interval));

    return *this;
}

bool TimeInterval::operator==(const TimeInterval& time_interval) noexcept
{
    if (!this->isSameUnitOfTime(time_interval))
        return false;
    
    return Interval<uint16_t>::operator==(time_interval);
}
//	TimeInterval : OPERATOR END!



//	TimeInterval : PUBLIC

TimeInterval::Unit TimeInterval::unitOfTime() const noexcept
{
    return this->m_unitOfMeasure;
}

bool TimeInterval::isSameUnitOfTime(const TimeInterval& time_interval) const noexcept
{
    return (this->m_unitOfMeasure == time_interval.m_unitOfMeasure);
}
//	TimeInterval : PUBLIC END!



//	TimeInterval : PRIVATE
//	TimeInterval : PRIVATE END!



//	TimeInterval : PROTECTED
//	TimeInterval : PROTECTED END!
