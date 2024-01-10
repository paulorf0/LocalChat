class ClassClientSocket
{
public:
    ClassClientSocket(const char *IP, int SERVER_PORT = 444)
    {
    }

private:
    int PORT = 444;

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