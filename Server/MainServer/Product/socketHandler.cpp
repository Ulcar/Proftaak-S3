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

Client* SocketHandler::CreateNewClient(char typeChar, std::string macAdress)
{
    //nog op letten bij unreeele waardes
    Type type;
    if(typeChar == 'x')
    {
        type = Type::ControlPanel;
    }
    else
    {
        type = Type(typeChar);
    }

    std::vector<Client*> tempClients = database->GetClients();
    for(Client* client : tempClients)
    {
        if(client->GetMacAdress() == macAdress)
        {
            return client;
        }
    }

    if(type == Type::ControlPanel)
    {
        return new Client(macAdress, type);
    }
    else
    {
        return new Machine(macAdress, type);
    }
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
    
    if((message.size() == 2) || (message.size() == 3))
    {
        if(message.at(0) == "0")
        {
            Client* client;

            if(message.size() == 2)
            {
                client = CreateNewClient('x', message.at(1));
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