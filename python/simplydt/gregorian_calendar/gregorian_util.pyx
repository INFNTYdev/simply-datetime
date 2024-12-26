
from . cimport gregorian_util


def is_valid_year(year: int) -> bool:
    # Check integer range here...
    return gregorian_util.isValidYear(<uint16_t>year)
