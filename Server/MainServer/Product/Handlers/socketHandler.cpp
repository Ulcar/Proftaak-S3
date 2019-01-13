#include "socketHandler.h"

#define SOCKET_SIZE 20

Database* SocketHandler::database;

void SocketHandler::RunSocketHandler(Database* tempdatabase)
{
    database = tempdatabase;
    int masterFd;
    int maxFd;

    Setup(&masterFd);

    Logger::Record(false, "Sockets started", "socketHandler");

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

            int sd = client->GetSocket()->GetSocketFd();
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
            Logger::Record(true, "error from calling socket", "socketHandler");
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

            if((tempsocket == nullptr) || (!tempClient->IsEnabled()))
            {
                continue;
            }

            //Try Sending a message
            tempsocket->TrySend();

            //Try Reading a message
            if (FD_ISSET(tempsocket->GetSocketFd(), &readFds))
            {
                if(!ReadClient(tempsocket))
                { 
                    tempClient->SetSocket(nullptr);
                    tempsocket = nullptr;
                    Logger::Record(false, "Removed socket of " + tempClient->GetMacAdress(), "socketHandler");
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
        Logger::Record(true, "Can't create socket", "socketHandler");
        return;
    }

    struct sockaddr_in sa;
    memset(&sa, 0, sizeof sa);
    sa.sin_family = AF_INET;
    sa.sin_port = Translator::GetPort();
    sa.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(*socketFd, (struct sockaddr*)&sa, sizeof sa) < 0)
    {
        Logger::Record(true, "Port already in use", "socketHandler");
        close(*socketFd);
        exit(EXIT_FAILURE);
    }
    
    if (listen(*socketFd, SOCKET_SIZE) < 0)
    {
        Logger::Record(true, "listen failed", "socketHandler");
        close(*socketFd);
        exit(EXIT_FAILURE);
    }
}

Client* SocketHandler::CreateNewClient(char typeChar, std::string macAdress)
{
    Type type;

    if(typeChar == '\0')
    {
        type = Type::ControlPanel;
    }
    else
    {
        int typeInt = typeChar - '0';
        if((typeInt >= 0) && (typeInt <= 4))
        {
            type = Type(typeInt);
        }
        else
        {
            Logger::Record(true, "Not a valid type: " + std::to_string(typeChar), "SocketHandler - CreateSocket");
            return nullptr;
        }
    }

    std::vector<Client*> tempClients = database->GetClients();
    for(Client* client : tempClients)
    {
        if(client->GetMacAdress() == macAdress)
        {
            return client;
        }
    }
    Logger::Record(false, "Created new Client: " + type, "socketHandler");
            
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
        Logger::Record(true, "Accept failed", "socketHandler");
        close(socketFd);
        exit(EXIT_FAILURE);
    }
    
    Socket* socket = new Socket(connectFd);
    Logger::Record(false, "New socket connected: " + connectFd, "socketHandler");

    if(!socket->Read())
    {
        Logger::Record(false, "Removed socket: " + connectFd, "socketHandler");
        delete socket;
        return;
    }
    std::string encodedMessage = socket->ReadLastMessage();
    std::vector<std::vector<std::string>> message = Translator::FromMachine(encodedMessage);
    
    if(message.size() != 0)
    {
        if((message.at(0).size() == 3) && (message.at(0).at(0) == "0"))
        {
            Client* client;
            std::vector<std::string> temp = {std::to_string(0)};

            //client
            client = CreateNewClient(message.at(0).at(1).at(0), message.at(0).at(2));
            socket->NewSendMessage(Translator::ToMachine(M_CODE_CONNECT, 0));

            if(client == nullptr)
            {
                delete socket;
                return;
            }

        //    socket->TrySend();
            client->SetSocket(socket);
            database->AddClient(client);

            Logger::Record(false, "Added Client with type: " + std::to_string(client->GetType()) + "with id: " + client->GetMacAdress(), "socketHandler");
            return;
        }        
    }

    message = Translator::FromControlPanel(encodedMessage);

    if(message.size() != 0)
    {
        if((message.at(0).size() == 2) && (message.at(0).at(0) == "0"))
        {
            Client* client;
            std::vector<std::string> temp = {std::to_string(0)};

            //ControlPanel
            client = CreateNewClient('\0', message.at(0).at(1));
            socket->NewSendMessage(Translator::ToControlPanel(CP_CODE_CONNECT, temp));

            if(client == nullptr)
            {
                delete socket;
                return;
            }

        //    socket->TrySend();
            client->SetSocket(socket);
            database->AddClient(client);

            Logger::Record(false, "Added ControlPanel with id: " + client->GetMacAdress(), "socketHandler");
            return;
        }
    }
    std::cout << "This is not a machine";
}

bool SocketHandler::ReadClient(Socket* socket)
{
    if(!socket->Read())
    {
       return false;
    }
    return true;
}