
#include<iostream>
#include"meta/info.h"
#include"meta/version.h"


int main(int argc, char* argv[])
{
    //
    std::cout << "\nFunctioning properly."
        << "\nTitle: " << TEMPLATEMetadata::OFFICIAL_NAME
        << "\nShort name: " << TEMPLATEMetadata::SHORT_NAME
        << "\nPublisher: " << TEMPLATEMetadata::PUBLISHER << '\n'
        << std::endl;

    return 0;
}
