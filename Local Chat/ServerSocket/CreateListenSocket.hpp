

#define DEFAULT_PORT 444 
#define NUMBER_CONNECTIONS 1

class CreateServerSocket {
public:
    CreateServerSocket(const char* IP_HOST) { 
        
        InitSocketWSA();
        struct sockaddr_in serverData;
        
        try {
            serverData = SetServerData(IP_HOST);
        }
        catch(const std::exception& e) {
            throw std::runtime_error(e.what());
        }
        
        serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

        if(serverSocket == INVALID_SOCKET) {
            WSACleanup();
            throw std::runtime_error("Houve um erro ao criar o socket.");
        }

        iResult = bind(serverSocket, (SOCKADDR *)& serverData, sizeof(serverData));
        if( iResult != 0 ) {
            closesocket(serverSocket);
            WSACleanup();
            throw std::runtime_error("Houve um erro ao atribuir dados ao socket.");
        }

        iResult = listen(serverSocket, NUMBER_CONNECTIONS);
        if(iResult == SOCKET_ERROR) {
            closesocket(serverSocket);
            WSACleanup();
            throw std::runtime_error("Erro ao atribuir escuta no socket.");
        }
    }

    void InformationsAboutSocket() {
        if(serverSocket == INVALID_SOCKET) throw std::runtime_error("O servidor não foi criado.");
        
        struct sockaddr_in addrServer;
        int addrServer_len = sizeof(addrServer);

        if(getsockname(serverSocket, reinterpret_cast<struct sockaddr*>(&addrServer), &addrServer_len) == 0) {
            std::cout << "Endereço IP do servidor: " << inet_ntoa(addrServer.sin_addr) << std::endl;
            std::cout << "Porta do servidor: " << ntohs(addrServer.sin_port) << std::endl;
        }else {
            throw std::runtime_error("Erro ao obter informações do servidor.");
        }

        struct sockaddr_in addrClient;
        int addrClient_len = sizeof(addrClient);

        if(getpeername(clientSocketAccepted, reinterpret_cast<struct sockaddr*>(&addrClient), &addrClient_len) == 0) {
            std::cout << "------------------------------------";
            std::cout << "Endereço IP do cliente: " << inet_ntoa(addrClient.sin_addr) << std::endl;
            std::cout << "Porta do cliente: " << ntohs(addrClient.sin_port) << std::endl;
        }else {
            std::cout << "-----------------------------------";
            throw std::runtime_error("Erro ao obter informacoes do cliente.");
        }
    }

    void AcceptConnection() {
        clientSocketAccepted = accept(serverSocket, NULL, NULL);
        if(clientSocketAccepted == INVALID_SOCKET) {
            closesocket(serverSocket);
            WSACleanup();
            throw std::runtime_error("Erro ao aceitar conexão do cliente.");
        }
    }

    void CloseConnectionWithClient() {
        if(closesocket(clientSocketAccepted) != 0) {
            throw std::runtime_error("Erro ao fechar conexão com cliente.");
        }
    }

    ~CreateServerSocket() {
        closesocket(serverSocket);
        closesocket(clientSocketAccepted);
        WSACleanup();
    }

private:
    WSADATA wsaData;
    SOCKET serverSocket = INVALID_SOCKET;
    SOCKET clientSocketAccepted;
    int iResult = 0;
    
    void InitSocketWSA() {
        
        iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if(iResult != 0) {
            throw std::runtime_error("Falha em inicializar WSAStartup");
        }

    }


    sockaddr_in SetServerData(const char* IP) {
        struct sockaddr_in serverData;

        try {
            serverData.sin_family = AF_INET;
            serverData.sin_addr.s_addr = inet_addr(IP);
            serverData.sin_port = htons(DEFAULT_PORT); 
            }
        catch(const std::exception& e) {
            throw std::runtime_error("Erro ao configurar os dados do servidor!");
        }

        return serverData;
    }
};
