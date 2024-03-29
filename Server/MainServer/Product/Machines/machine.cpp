#include "machine.h"

Machine::Machine(std::string macAdress, Type type)
    : Client(macAdress, type)
{
    ReplyCount = 0;
    usedPower = 0;
    usedWater = 0;
    inProgress = false;
    requestingInProgress = false;
}

Machine::~Machine()
{
    
}

void Machine::Send(M_Code code, int value)
{
    if(socket == nullptr)
    {
        return;
    }
    socket->NewSendMessage(Translator::ToMachine(code, value));
}


int Machine::GetUsedPower()
{
    return usedPower;
}

void Machine::SetUsedPower(int setPower)
{
    usedPower = setPower;
}

int Machine::GetUsedWater()
{
    return usedWater;
}

void Machine::SetUsedWater(int setWater)
{
    usedWater = setWater;
}

Program Machine::GetProgram()
{
    return currentProgram;
}

void Machine::SetProgram(Program SetProgram)
{
    currentProgram = SetProgram;
}

bool Machine::IsInProgress()
{
    return inProgress;
}

void Machine::SetInProgress(bool inProgress)
{
    this->inProgress = inProgress;
}

bool Machine::IsRequestingInProgress()
{
    return requestingInProgress;
}

void Machine::SetRequestingInProgress(bool requestingInProgress)
{
    this->requestingInProgress = requestingInProgress;
}
void Machine::AddToReplyCount()
{
    ReplyCount += 1;
}

int Machine::GetReplyCount()
{
    return ReplyCount;
}

void Machine::ResetReplyCount()
{
    ReplyCount = 0;
}

void Machine::SetSocket(Socket* tempSocket)
{
    if(socket != nullptr)
    {
        delete socket;
    }
    socket = tempSocket;
    ResetReplyCount();
}