class ClassClientSocket
{
public:
    ClassClientSocket()
    {
    }

    void ClientConnectToServer(const char *IP, std::string ClientUsername)
    {
        struct sockaddr_in service = SetClientData(IP);

        iResult = connect(ConnectSocket, (SOCKADDR *)&service, sizeof(service));
        if (iResult == SOCKET_ERROR)
        {
            iResult = closesocket(ConnectSocket);
            if (iResult == SOCKET_ERROR)
            {
                throw std::runtime_error("Erro em fechar o scoket apos falha.");
            }
            WSACleanup();

            throw std::runtime_error("Erro em conectar ao servidor");
        }

        RecvUsername();

        clientUsername = ClientUsername;

        const char *username = (const char *)&clientUsername;
        do
        {
            iResult = send(ConnectSocket, username, strlen(username), 0);
        } while (iResult != 0);
    }

protected:
    void InitWSA()
    {

        iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (iResult != 0)
        {
            throw std::runtime_error("Falha em inicializar WSAStartup");
        }
    }

    void CreateClientSocket()
    {
        ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (ConnectSocket == INVALID_SOCKET)
        {
            WSACleanup();
            throw std::runtime_error("Houve um erro ao criar o socket.");
        }
    }

private:
    WSADATA wsaData;
    SOCKET ConnectSocket;
    std::string serverUsername;
    std::string clientUsername;
    int iResult = 0;
    const int PORT = 444;

    void RecvUsername()
    {
        char buffer[1024];

        iResult = recv(ConnectSocket, buffer, sizeof(buffer), 0);

        if (iResult > 0)
        {
            serverUsername = std::string(buffer, iResult);
        }
        else if (iResult == 0)
        {
            throw std::runtime_error("Conexao fechada pelo outro lado.");
        }
        else
        {
            serverUsername = "default";
        }
    }

    sockaddr_in SetClientData(const char *IP)
    {
        struct sockaddr_in ClientData;

        try
        {
            ClientData.sin_family = AF_INET;
            ClientData.sin_addr.s_addr = inet_addr(IP);
            ClientData.sin_port = htons(PORT);
        }
        catch (const std::exception &e)
        {
            throw std::runtime_error("Erro ao configurar os dados para conectar ao servidor!");
        }

        return ClientData;
    }
};