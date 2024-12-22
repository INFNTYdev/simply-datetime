
/*!
* @file utc_util.hpp
*
* @brief
* Coordinated Universal Time utilities document.
*
* @details
* Utilities for Coordinated Universal Time related
* functionality.
*/



#ifndef SIMPLYDT_L_SIMPLYDT_COORD_UNIVERSAL_TIME_UTIL_H_
#define SIMPLYDT_L_SIMPLYDT_COORD_UNIVERSAL_TIME_UTIL_H_



#include<cstdint>
#include"simplydt/coord_universal_time/utc_defs.hpp"
#include"simplydt/gregorian_calendar/gregorian_defs.hpp"
#include"simplydt/julian_calendar/julian_defs.hpp"


namespace SimplyDt {

    namespace CoordUniversalTime {

        /*!
        * @namespace SimplyDt::CoordUniversalTime::Util
        *
        * @brief
        * Standard time system utilities namespace.
        */
        namespace Util {

            /*!
            * @brief
            * Validate provided hour.
            * 
            * @return
            * True if provided hour is within valid
            * range
            */
            inline bool isValidHour(const uint8_t& hour) noexcept;

            /*!
            * @brief
            * Validate provided minute.
            *
            * @return
            * True if provided minute is within valid
            * range
            */
            inline bool isValidMinute(const uint8_t& minute) noexcept;

            /*!
            * @brief
            * Validate provided second.
            *
            * @return
            * True if provided second is within valid
            * range
            */
            inline bool isValidSecond(const uint8_t& second) noexcept;

            /*!
            * @brief
            * Evaluate if provided time conforms to
            * 24-hour Coordinated Universal Time rules.
            *
            * @return
            * True if provided time is valid
            */
            inline bool isValidTime(const uint8_t& hour, const uint8_t& minute, const uint8_t& second) noexcept;

            /*!
            * @brief
            * Convert Julian Day Number to Coordinated
            * Universal Time.
            */
            void jdnToUtc(const SimplyDt::JulianCalendar::JDN& jdn, SimplyDt::CoordUniversalTime::Time& time) noexcept;

        }

    }

}



#endif // SIMPLYDT_L_SIMPLYDT_COORD_UNIVERSAL_TIME_UTIL_H_
