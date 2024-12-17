
/*!
* @file gregorian_defs.hpp
*
* @brief
* Gregorian calendar definitions document.
*
* @details
* Constant definitions for Gregorian calendar related
* entities.
*/



#ifndef SIMPLYDT_L_SIMPLYDT_GREGORIAN_DEFS_H_
#define SIMPLYDT_L_SIMPLYDT_GREGORIAN_DEFS_H_



#include<cstdint>
#include<array>


namespace SimplyDt
{

    /*!
    * @namespace SimplyDt::GregorianCalendar
    *
    * @brief
    * Standard civil calendar system namespace.
    */
    namespace GregorianCalendar
    {

        /*!
        * @brief
        * Gregorian date presentation formats.
        */
        enum DateFormat {
            RECORD,     ///< Record format (01-01-1970)
            STANDARD    ///< Standard format (01/01/1970)
        };

        /*!
        * @brief
        * Gregorian date presentation layouts.
        */
        enum DateLayout {
            M_D_YYYY,    ///< mm/dd/YYYY [ Example: 01-29-1970 ]
		    M_D_YY,      ///< mm/dd/YY [ Example: 01-29-70 ]
		    M_YYYY,      ///< mm/YYYY [ Example: 01-1970 ]
		    M_YY,        ///< mm/YY [ Example: 01-70 ]
		    M_D,         ///< mm/dd [ Example: 01-29 ]
		    YYYY_M_D,    ///< YYYY/mm/dd [ Example: 1970-01-29 ]
		    YY_M_D,      ///< YY/mm/dd [ Example: 70-01-29 ]
		    YYYY_D_M,    ///< YYYY/dd/mm [ Example: 1970-29-01 ]
		    YY_D_M,      ///< YY/dd/mm [ Example: 70-29-01 ]
		    YYYY_M,      ///< YYYY/mm [ Example: 1970-01 ]
		    YY_M,        ///< YY/mm [ Example: 70-01 ]
		    D_M,         ///< dd/mm [ Example: 29-01 ]
        };

        /*!
        * @brief
        * Gregorian calendar date.
        */
        struct Date
        {
            const uint16_t year;    ///< Date year
            const uint8_t month;    ///< Date month
            const uint8_t day;      ///< Date day
        };

        /*!
        * @brief
        * Gregorian calendar days of week.
        */
        const std::array<const char*, 7> DaysOfWeek{
            "Sunday",
            "Monday",
            "Tuesday",
            "Wednesday",
            "Thursday",
            "Friday",
            "Saturday"
        };

        /*!
        * @brief
        * Gregorian calendar months.
        */
        const std::array<const char*, 12> Months{
            "January",
            "February",
            "March",
            "April",
            "May",
            "June",
            "July",
            "August",
            "September",
            "October",
            "November",
            "December"
        };

    }

}



#endif // SIMPLYDT_L_SIMPLYDT_GREGORIAN_DEFS_H_
