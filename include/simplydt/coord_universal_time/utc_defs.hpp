
/*!
* @file utc_defs.hpp
*
* @brief
* Coordinated Universal Time definitions document.
*
* @details
* Constant definitions for Coordinated Universal Time
* related entities.
*/



#ifndef SIMPLYDT_L_SIMPLYDT_UTC_DEFS_H_
#define SIMPLYDT_L_SIMPLYDT_UTC_DEFS_H_



#include<cstdint>
#include<array>


namespace SimplyDt {

    /*!
    * @namespace SimplyDt::CoordUniversalTime
    *
    * @brief
    * Coordinated Universal Time system namespace.
    */
    namespace CoordUniversalTime {

        /*!
        * @brief
        * Coordinated Universal Time presentation formats.
        */
        enum TimeFormat {
            MILITARY,    ///< Military format (24-hour)
            STANDARD     ///< Standard format (12-hour)
        };

        /*!
        * @brief
        * Coordinated Universal Time layouts.
        */
        enum TimeLayout {
            H_M_S,      ///< HH:MM:SS [ Example: 08:30:57 ]
            H_M_S_P,    ///< HH:MM:SS P [ Example: 08:30:57 AM ]
            H_M,        ///< HH:MM [ Example: 08:30 ]
            H_M_P       ///< HH:MM P [ Example: 08:30 AM ]
        };

        /*!
        * @brief
        * Standard Coordinated Universal Time. (UTC)
        */
        struct Time {
            uint8_t hour;      ///< Time hour
            uint8_t minute;    ///< Time minute
            uint8_t second;    ///< Time second
        };

        /*!
        * @brief
        * Coordinated Universal Time periods in
        * time-of-day.
        */
        const std::array<const char*, 2> Phases{
            "AM",    ///< Ante meridiem (before midday)
            "PM"     ///< Post meridiem (after midday)
        };

    }

}



#endif // SIMPLYDT_L_SIMPLYDT_UTC_DEFS_H_
