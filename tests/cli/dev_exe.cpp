
#include<iostream>
#include"meta/info.h"
#include"meta/version.h"


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
    
    return 0;
}
