#include "interface.h"
#include "enums.h"


Interface::Interface(std::string macAdress)
    : macAdress(macAdress)
{
    error = Error::None;
}

Interface::~Interface()
{

}

void Interface::Send()
{

}

void Interface::Read()
{

}

int Interface::Ping()
{
    return 0;
}
