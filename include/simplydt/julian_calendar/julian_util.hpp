
/*!
* @file julian_util.hpp
*
* @brief
* Julian calendar utilities document.
*
* @details
* Utilities for Julian calendar related functionality.
*/



#ifndef SIMPLYDT_L_SIMPLYDT_JULIAN_UTIL_H_
#define SIMPLYDT_L_SIMPLYDT_JULIAN_UTIL_H_



#include<cstdint>
#include"simplydt/julian_calendar/julian_defs.hpp"
#include"simplydt/gregorian_calendar/gregorian_defs.hpp"


namespace SimplyDt {

    namespace JulianCalendar {

        /*!
        * @namespace SimplyDt::JulianCalendar::Util
        *
        * @brief
        * Roman Julian calendar utilities namespace.
        */
        namespace Util {

            //

            /*!
            * @brief
            * Convert Gregorian date to Julian Day Number.
            */
            void dateToJdn(const SimplyDt::GregorianCalendar::Date& date, SimplyDt::JulianCalendar::JDN& jdn) noexcept;

        }

    }

}



#endif // SIMPLYDT_L_SIMPLYDT_JULIAN_UTIL_H_
