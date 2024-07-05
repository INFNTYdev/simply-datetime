
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
    //


private:
    //

};



#endif // SIMPLYDTLIB_L_DATETIME_DURATION_SEQUENCE_OBJ_H_
