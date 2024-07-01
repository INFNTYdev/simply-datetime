
#include"simplydt/datetime/date/date_interval.hpp"


//	DateInterval : CONSTRUCTORS

//	DateInterval : DESTRUCTOR

//	DateInterval : FREE



//	DateInterval : OPERATOR

DateInterval& DateInterval::operator=(const DateInterval& date_interval) noexcept
{
    if (this == &date_interval)
        return *this;
    
    this->m_unitOfMeasure = date_interval.m_unitOfMeasure;
    Interval<uint16_t>::operator=(date_interval);

    return *this;
}

DateInterval& DateInterval::operator=(DateInterval&& date_interval) noexcept
{
    if (this == &date_interval)
        return *this;
    
    this->m_unitOfMeasure = std::move(date_interval.m_unitOfMeasure);
    Interval<uint16_t>::operator=(static_cast<Interval<uint16_t>&&>(date_interval));

    return *this;
}

bool DateInterval::operator==(const DateInterval& date_interval) noexcept
{
    if (!this->isSameUnitOfTime(date_interval))
        return false;
    
    return Interval<uint16_t>::operator==(date_interval);
}
//	DateInterval : OPERATOR END!



//	DateInterval : PUBLIC

DateInterval::Unit DateInterval::unitOfTime() const noexcept
{
    return this->m_unitOfMeasure;
}

bool DateInterval::isSameUnitOfTime(const DateInterval& date_interval) const noexcept
{
    return (this->m_unitOfMeasure == date_interval.m_unitOfMeasure);
}
//	DateInterval : PUBLIC END!



//	DateInterval : PRIVATE
//	DateInterval : PRIVATE END!



//	DateInterval : PROTECTED
//	DateInterval : PROTECTED END!
