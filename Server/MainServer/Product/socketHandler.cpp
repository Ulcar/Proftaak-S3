#include "socketHandler.h"

#define SOCKET_SIZE 20

Database* SocketHandler::database;

void SocketHandler::RunSocketHandler(Database* tempdatabase)
{
    database = tempdatabase;
    int masterFd;
    int maxFd;

    Setup(&masterFd);

    DebugLogger::Record("Sockets started", "socketHandler");

    while (true)
    {        
//is dit echt nodig?     
        fd_set readFds;
        FD_ZERO(&readFds);
        FD_SET(masterFd, &readFds);
        maxFd = masterFd;

        std::vector<Client*> tempClients = database->GetClients();
        for(Client* client : tempClients)              
        {
            if(client->GetSocket() == nullptr)
            {
                continue;
            }

            int sd = client->GetSocket()->getSocketFd();
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
            Errorlogger::Record("error from calling socket", "socketHandler");
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

        tempClients = database->GetClients();
        for(Client* tempClient : tempClients)
        {
            Socket* tempsocket = tempClient->GetSocket();

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
                    tempClient->SetSocket(nullptr);
                    tempsocket = nullptr;
                    DebugLogger::Record("Removed socket of " + tempClient->GetMacAdress(), "socketHandler");
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
        Errorlogger::Record("Can't create socket", "socketHandler");
        return;
    }

    struct sockaddr_in sa;
    memset(&sa, 0, sizeof sa);
    sa.sin_family = AF_INET;
    sa.sin_port = Protocol::GetPort();
    sa.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(*socketFd, (struct sockaddr*)&sa, sizeof sa) < 0)
    {
       Errorlogger::Record("bind failed", "socketHandler");
        close(*socketFd);
        exit(EXIT_FAILURE);
    }
    
    if (listen(*socketFd, SOCKET_SIZE) < 0)
    {
        Errorlogger::Record("listen failed", "socketHandler");
        close(*socketFd);
        exit(EXIT_FAILURE);
    }
}

Client* SocketHandler::CreateNewClient(char typeChar, std::string macAdress)
{
    Type type;
    try
    {
        if(typeChar == '\0')
        {
            type = Type::ControlPanel;
        }
        else
        {
            type = Type(typeChar);
        }
    }
    catch(...)
    {
        return nullptr;
    }

    std::vector<Client*> tempClients = database->GetClients();
    for(Client* client : tempClients)
    {
        if(client->GetMacAdress() == macAdress)
        {
            return client;
        }
    }
    DebugLogger::Record("Created new Client: " + type, "socketHandler");
            
    if(type == Type::ControlPanel)
    {
        Client* client = new Client(macAdress, type);
        return client;
    }
    else
    {
        Client* client = new Machine(macAdress, type);
        return client;
    }
}


void SocketHandler::ConnectClient(int socketFd)
{
    int connectFd = accept(socketFd, NULL, NULL);
    if (connectFd < 0)
    {
        Errorlogger::Record("Accept failed", "socketHandler");
        close(socketFd);
        exit(EXIT_FAILURE);
    }
    
    Socket* socket = new Socket(connectFd);
    DebugLogger::Record("New socket connected: " + connectFd, "socketHandler");

    if(!socket->Read())
    {
        DebugLogger::Record("Removed socket: " + connectFd, "socketHandler");
        delete socket;
        return;
    }

    std::vector<std::string> message = Protocol::FromClient(socket->ReadLastMessage());
    
    if((message.size() == 2) || (message.size() == 3))
    {
        if(message.at(0) == "0")
        {
            Client* client;

            if(message.size() == 2)
            {
                client = CreateNewClient('\0', message.at(1));
            }
            else
            {
                client = CreateNewClient(message.at(1).at(0), message.at(2));
            }

            if(client == nullptr)
            {
                delete socket;
                return;
            }

            socket->NewSendMessage(Protocol::ToClient(CODE_CONNECT, 0));
            socket->TrySend();
            client->SetSocket(socket);
            database->AddClient(client);

            std::string fu = "Added Client with type: " + client->GetType();
            fu += "with id: " + client->GetMacAdress();
            DebugLogger::Record(fu, "socketHandler");
            return;
        }
    }    
}

bool SocketHandler::ReadClient(Socket* socket)
{
    if(!socket->Read())
    {
       return false;
    }
    return true;
}