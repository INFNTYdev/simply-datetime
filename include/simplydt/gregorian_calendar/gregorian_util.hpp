
/*!
* @file gregorian_util.hpp
*
* @brief
* Gregorian calendar utilities document.
*
* @details
* Utilities for Gregorian calendar related functionality.
*/



#ifndef SIMPLYDT_L_SIMPLYDT_GREGORIAN_DEFS_H_
#define SIMPLYDT_L_SIMPLYDT_GREGORIAN_DEFS_H_



#include<cstdint>
#include"simplydt/gregorian_calendar/gregorian_defs.hpp"


namespace SimplyDt {

    namespace GregorianCalendar {

        /*!
        * @namespace SimplyDt::GregorianCalendar::Util
        *
        * @brief
        * Standard civil calendar utilities namespace.
        */
        namespace Util {

            /*!
            * @brief
            * Evaluate if provided year is a leap year.
            * 
            * @return
            * True if provided year is a leap year
            */
            bool isLeapYear(const uint16_t& year) noexcept;

            /*!
            * @brief
            * Determine total number of days in specified month.
            * 
            * @return
            * Total number of days in provided year-month
            * time frame.
            */
            uint8_t getMonthTotalDays(const uint16_t& year, const uint8_t& month) noexcept;

            /*!
            * @brief
            * Determine total number of days in specified year.
            * 
            * @return
            * Total number of days in provided year time frame.
            */
            uint16_t getYearTotalDays(const uint16_t& year) noexcept;

            /*!
            * @brief
            * Determine month index of specified month.
            * 
            * @return
            * Month index of provided month
            */
            uint8_t getMonthIndex(const uint8_t& month) noexcept;

            /*!
            * @brief
            * Determine month name of specified month.
            * 
            * @return
            * Month literal of provided month
            */
            const char* getMonth(const uint8_t& month) noexcept;

            /*!
            * @brief
            * Determine day-of-week index of specified date.
            * 
            * @return
            * Day-of-week index of provided date
            */
            uint8_t getDayOfWeekIndex(const uint16_t& year, const uint8_t& month, const uint8_t& day) noexcept;

            /*!
            * @brief
            * Determine day-of-week of specified date.
            * 
            * @return
            * Day-of-week literal of provided date
            */
            const char* getDayOfWeek(const uint16_t& year, const uint8_t& month, const uint8_t& day) noexcept;

        }

    }

}



#endif // SIMPLYDT_L_SIMPLYDT_GREGORIAN_DEFS_H_
