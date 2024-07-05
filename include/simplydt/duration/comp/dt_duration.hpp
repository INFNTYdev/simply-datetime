
#ifndef SIMPLYDTLIB_L_DATETIME_DURATION_SEQUENCE_OBJ_H_
#define SIMPLYDTLIB_L_DATETIME_DURATION_SEQUENCE_OBJ_H_



#include"simplydt/datetime/sequence/dt_sequence.hpp"
#include"simplydt/duration/unit/dur_unit_def.hpp"
#include"simplydt/datetime/time/unit/dt_hour.hpp"
#include"simplydt/datetime/time/unit/dt_minute.hpp"
#include"simplydt/datetime/time/unit/dt_second.hpp"
#include"simplydt/datetime/time/unit/dt_millisecond.hpp"


/* Time duration ( dd:HH:MM:SS:MS ) */
class Duration : public DatetimeSequence<ArbDay, Hour, Minute, Second, Millisecond> {

public:
    /* Datetime time unit */
    using TimeUnit = DatetimeSequence<ArbDay, Hour, Minute, Second, Millisecond>::TimeUnit;
    /* Datetime type */
    using DatetimeType = DatetimeSequence<ArbDay, Hour, Minute, Second, Millisecond>::DatetimeType;
    /* Duration direction sign */
    using Sign = Interval<uint16_t>::Trans;

    /* Duration layout */
    enum Layout {
        SIGN_D_H_M_S_MS,// ( +/- dd:HH:MM:SS:MS ) [ Example: +124:08:30:00:00 ]
        D_H_M_S_MS,// ( dd:HH:MM:SS:MS ) [ Example: 124:08:30:00:00 ]
        SIGN_D_H_M_S,// ( +/- dd:HH:MM:SS ) [ Example: -124:08:30:00 ]
        D_H_M_S,// ( dd:HH:MM:SS ) [ Example: 124:08:30:00 ]
        SIGN_D_H_M,// ( +/- dd:HH:MM ) [ Example: +124:08:30 ]
        D_H_M,// ( dd:HH:MM ) [ Example: 124:08:30 ]
        SIGN_D_H,// ( +/- dd:HH ) [ Example: +124:08 ]
        D_H,// ( dd:HH ) [ Example: 124:08 ]
    };

    Duration(uint16_t days, uint16_t hour, uint16_t minute, uint16_t second, uint16_t ms) noexcept;

    Duration(uint16_t days, uint16_t hour, uint16_t minute, uint16_t second) noexcept;

    Duration(uint16_t days, uint16_t hour, uint16_t minute) noexcept;

    Duration(uint16_t days, uint16_t hour) noexcept;

    Duration(uint16_t days) noexcept;

    Duration() noexcept;

    Duration(const Duration& duration) noexcept;

    Duration(Duration&& duration) noexcept;

    ~Duration() noexcept = default;

    friend std::ostream& operator<<(std::ostream& os, const Duration& duration) noexcept;

    Duration& operator=(const Duration& duration) noexcept;

    Duration& operator=(Duration&& duration) noexcept;

    bool operator==(const Duration& duration) noexcept;

    bool operator<(const Duration& duration) noexcept;

    bool operator>(const Duration& duration) noexcept;

    bool operator<=(const Duration& duration) noexcept;

    bool operator>=(const Duration& duration) noexcept;

    /* Returns duration elapsed days */
    uint16_t days() const noexcept;

    /* Returns duration hours */
    uint16_t hour() const noexcept;

    /* Returns duration minutes */
    uint16_t minute() const noexcept;

    /* Returns duration seconds */
    uint16_t second() const noexcept;

    /* Returns duration milliseconds */
    uint16_t millisecond() const noexcept;

    /* Returns duration direction sign */
    Sign sign() const noexcept;

    /* Returns duration direction sign character literal */
    char signChar() const noexcept;

    /* Returns duration string with provided format */
    std::string durationStr(Layout layout) const noexcept;

    /* Returns duration string */
    std::string durationStr() const noexcept;

    /* Returns arbitrary day in duration */
    ArbDay& getDays() const noexcept;

    /* Returns hour in duration */
    Hour& getHour() const noexcept;

    /* Returns minute in duration */
    Minute& getMinute() const noexcept;

    /* Returns second in duration */
    Second& getSecond() const noexcept;

    /* Returns millisecond in duration */
    Millisecond& getMillisecond() const noexcept;

    /* Returns true if provided duration is longer than this one */
    bool isShorterThan(const Duration& duration) const noexcept;

    /* Returns true if provided duration is shorter than this one */
    bool isLongerThan(const Duration& duration) const noexcept;

    /* Returns elapsed duration compressed into provided unit  */
    size_t convertedTo(TimeUnit unit) const noexcept;

    /* Returns absolute total number of seconds from this duration until provided duration */
    size_t secondsUntil(const Duration& duration) const noexcept;

    /* Returns absolute total number of milliseconds from this duration until provided duration */
    size_t millisecondsUntil(const Duration& duration) const noexcept;

    /* Returns duration from this to provided duration */
    Duration until(const Duration& duration) const noexcept;


private:
    Sign m_directionSign;

};



#endif // SIMPLYDTLIB_L_DATETIME_DURATION_SEQUENCE_OBJ_H_
