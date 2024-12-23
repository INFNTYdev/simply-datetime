
#include<iostream>
#include"simplydt/meta/info.h"
#include"simplydt/meta/version.h"

#include"simplydt/gregorian_calendar/gregorian_util.hpp"


void ProjectInfoOut() noexcept
{
    std::cout << '\n'
		<< "\n\t" << SIMPLYDTMetadata::PUBLISHER << "\n"
		<< "\n\t[ " << SIMPLYDTMetadata::OFFICIAL_NAME << " ]"
		<< "\n\tDeveloper executable"
		<< "\n\tRelease: " << SIMPLYDTMetadata::VERSION_MAJOR
		<< " Version: " << SIMPLYDTMetadata::VERSION_MINOR
		<< " Patch: " << SIMPLYDTMetadata::VERSION_PATCH
		<< " Tweak: " << SIMPLYDTMetadata::VERSION_TWEAK
		<< "\n\t-> (dev_exe.exe)\n"
		<< "\n\tC++ 20"
		<< "\n\n" << std::endl;
}


int main(int argc, char* argv[])
{
	ProjectInfoOut();

	// DO NOT DELETE ABOVE


    //\\//
	SimplyDt::GregorianCalendar::Date someDate{};
	SimplyDt::JulianCalendar::JDN someJDN{ 2'440'587.5 };

	SimplyDt::GregorianCalendar::Util::jdnToDate(someJDN, someDate);
    
    return 0;
}
