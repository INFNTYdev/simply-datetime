
/*!
* @file string_util.hpp
*
* @brief
* String utilities document.
*
* @details
* Utilities for datetime related strings.
*/



#ifndef SIMPLYDT_L_SIMPLYDT_DATETIME_STRING_UTIL_H_
#define SIMPLYDT_L_SIMPLYDT_DATETIME_STRING_UTIL_H_



#include<string>


namespace SimplyDt {

    /*!
    * @namespace SimplyDt::String
    *
    * @brief
    * Datetime string utilities namespace.
    */
    namespace String {

        /*!
        * @brief
        * Returns provided integer as a double
        * digit string.
        */
        template <typename UINT_T>
        std::string toDoubleDigitStr(const UINT_T& integer) noexcept
        {
            if (integer <= (UINT_T)99)
                return std::to_string(integer);

            UINT_T multi{ 10 };

            do {

                multi *= (UINT_T)10;

            } while ((integer / multi) % (UINT_T)10 != (UINT_T)0);

            return std::to_string(integer % multi);
        }

    }

}



#endif // SIMPLYDT_L_SIMPLYDT_DATETIME_STRING_UTIL_H_
