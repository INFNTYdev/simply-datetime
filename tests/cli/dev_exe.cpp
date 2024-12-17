
#include<iostream>
#include"simplydt/common/string/string_util.hpp"


int main(int argc, char* argv[])
{
    //
    std::cout << "\nWorking properly." << std::endl;

    unsigned long int testYear{ 2024 };

    std::string demo{ SimplyDt::String::toDoubleDigitStr(testYear) };
    
    return 0;
}
