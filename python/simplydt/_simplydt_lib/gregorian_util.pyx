
from .core cimport *


"""
SimplyDt::GregorianCalendar::Util
"""


def is_valid_year(year: int) -> bool:
    """ Validate provided year. """
    # Check integer range here...
    return isValidYear(<uint16_t>year)
