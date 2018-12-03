#include "socketHandler.h"

#define SOCKET_SIZE 20

Database* SocketHandler::database;

void SocketHandler::RunSocketHandler(Database* tempdatabase)
{
    database = tempdatabase;
    int masterFd;
    int maxFd;

    Setup(&masterFd);

    std::cout << "  Socket started\n";

    while (true)
    {        
//is dit echt nodig?     
        fd_set readFds;
        FD_ZERO(&readFds);
        FD_SET(masterFd, &readFds);
        maxFd = masterFd;

        std::vector<Machine*> tempMachines = database->GetMachines();
        for(Machine* machine : tempMachines)              
        {
                int sd = machine->GetSocket()->getSocketFd();
                 //if valid socket descriptor then add to read list
            if(sd > 0)
            {
                FD_SET(sd,&readFds);
            }
                
            //highest file descriptor number, need it for the select function
            if(sd > maxFd)
            {
                maxFd = sd;
            }
        }

        struct timeval timeout;
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;

        int nrSockets = select(maxFd + 1, &readFds, NULL, NULL, &timeout);


        if (nrSockets < 0) // error situation
        {
            perror("error from calling socket");
        }
        else if (nrSockets == 0) // timeout
        {
            //nothing
        }
//to hier
                
        if (FD_ISSET(masterFd, &readFds))
        {
            ConnectClient(masterFd);
        }

        tempMachines = database->GetMachines();
        for(Machine* tempmachine : tempMachines)
        {
            Socket* tempsocket = tempmachine->GetSocket();

            if(tempsocket == nullptr)
            {
                continue;
            }

            //Try Sending a message
            tempsocket->TrySend();

            //Try Reading a message
            if (FD_ISSET(tempsocket->getSocketFd(), &readFds))
            {
                if(!ReadClient(tempsocket))
                { 
                    tempmachine->SetSocket(nullptr);
                    tempsocket = nullptr;
                }
            }
        }

        std::vector<ControlPanel*> tempControlPanels = database->GetControlPanels();
        for(ControlPanel* tempcontrolpanel : tempControlPanels)
        {
            Socket* tempsocket = tempcontrolpanel->GetSocket();

            tempsocket->TrySend();

            if (FD_ISSET(tempsocket->getSocketFd(), &readFds))
            {
                if(!ReadClient(tempsocket))
                { 
                    tempcontrolpanel->SetSocket(nullptr);
                    tempsocket = nullptr;
                }
            }
        }
    }
}

void SocketHandler::Setup(int *socketFd)
{
    *socketFd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (*socketFd < 0)
    {
        perror("cannot create socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in sa;
    memset(&sa, 0, sizeof sa);
    sa.sin_family = AF_INET;
    sa.sin_port = Protocol::GetPort();
    //sa.sin_port = htons(Protocol::GetPort());
    sa.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(*socketFd, (struct sockaddr*)&sa, sizeof sa) < 0)
    {
        perror("bind failed");
        close(*socketFd);
        exit(EXIT_FAILURE);
    }
    
    if (listen(*socketFd, SOCKET_SIZE) < 0)
    {
        perror("listen failed");
        close(*socketFd);
        exit(EXIT_FAILURE);
    }
}

Machine* SocketHandler::CreateNewMachine(char type, std::string macAdress)
{
    std::vector<Machine*> tempMachines = database->GetMachines();
    for(Machine* machine : tempMachines)
    {
        if(machine->GetMacAdress() == macAdress)
        {
            return machine;
        }
    }

    Machine* machine;

    switch(type)
    {
    case '0':
        machine = new Wasmachine(macAdress);
        break;
    case '1':
        machine = new Wasmachine(macAdress);
        break;
    case '2':
        machine = new Wasmachine(macAdress);
        break;
    case '3':
        machine = new Wasmachine(macAdress);
        break;
    default:
        machine = nullptr;
    }
    return machine;
}


void SocketHandler::ConnectClient(int socketFd)
{
    int connectFd = accept(socketFd, NULL, NULL);
    if (connectFd < 0)
    {
        perror("accept failed");
        close(socketFd);
        exit(EXIT_FAILURE);
    }
    
    Socket* socket = new Socket(connectFd);
    std::cout << "Socket " << connectFd << " connected\n";

    if(!socket->Read())
    {
        delete socket;
        return;
    }

    std::vector<std::string> message = Protocol::FromClient(socket->ReadLastMessage());
    
    if(message.size() == 3)
    {
        if(message.at(0) == "0")
        {
            Machine* machine = CreateNewMachine(message.at(1).at(0), message.at(2));
            if(machine == nullptr)
            {
                delete socket;
                return;
            }

            socket->NewSendMessage(Protocol::ToClient(CODE_CONNECT, 0));
            socket->TrySend();
            machine->SetSocket(socket);
            database->AddMachine(machine);
            return;
        }
    }    
    else if(message.size() == 2)
    {
        if(message.at(0) == "0")
        {
            ControlPanel* controlpanel = new ControlPanel(message.at(1));
            socket->NewSendMessage(Protocol::ToClient(CODE_CONNECT, 0));
            socket->TrySend();
            controlpanel->SetSocket(socket);
            database->AddControlPanel(controlpanel);
            return;
        }
    }
}

bool SocketHandler::ReadClient(Socket* socket)
{
    std::cout << "Client '" << socket->getSocketFd() << "' || ";
    if(!socket->Read())
    {
       return false;
    }
    return true;
}