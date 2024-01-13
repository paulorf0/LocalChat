#ifndef UNICODE
#define UNICODE
#endif

#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>

#pragma comment(lib, "ws2_32.lib")

class BaseSocket
{
protected:
    // ID = 1 -> Server ... ID = 2 -> Client;

    static std::string serverUsername;
    static std::string clientUsername;
    static int port;
    static int const NUMBER_CONNECTIONS;

    WSADATA wsaData;
    SOCKET MySocket = INVALID_SOCKET;
    SOCKET OtherSocket = INVALID_SOCKET;
    struct sockaddr_in service;
    int iResult = 0;
    int ID_SOCKET = 0;

public:
    // virtual void CloseConnectionWithClient() = 0;

    void InitSocketWSA()
    {

        iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (iResult != 0)
        {
            throw std::runtime_error("Falha em inicializar WSAStartup");
        }
    }

    void CreateSocket()
    {
        MySocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (MySocket == INVALID_SOCKET)
        {
            WSACleanup();
            throw std::runtime_error("Houve um erro ao criar o socket.");
        }
        ViewDatas();
    }

    void SetDataService(const char *IP)
    {
        try
        {
            service.sin_family = AF_INET;
            service.sin_addr.s_addr = inet_addr(IP);
            service.sin_port = htons(port);
        }
        catch (const std::exception &e)
        {
            throw std::runtime_error("Erro ao configurar os dados do servidor!");
        }
    }

    void BindServiceInSocket()
    {
        iResult = bind(MySocket, (SOCKADDR *)&service, sizeof(service));
        if (iResult != 0)
        {
            closesocket(MySocket);
            WSACleanup();
            throw std::runtime_error("Houve um erro ao atribuir dados ao socket.");
        }
    }

    void RecvUsername()
    {
        char buffer[1024];
        if (ID_SOCKET == 1)
        {
            iResult = recv(OtherSocket, buffer, sizeof(buffer), 0);
        }
        else if (ID_SOCKET == 2)
        {
            iResult = recv(MySocket, buffer, sizeof(buffer), 0);
        }

        if (iResult > 0)
        {
            if (ID_SOCKET == 1)
            {
                SetNames(std::string(buffer, iResult), "client_default");
            }
            else if (ID_SOCKET == 2)
            {
                SetNames("server_default", std::string(buffer, iResult));
            }
        }
        else if (iResult == 0)
        {
            throw std::runtime_error("Conexao fechada pelo outro lado.");
        }
    }

    void SetSocketID(int id)
    {
        ID_SOCKET = id;
    }

    void SetNames(std::string server, std::string client)
    {
        serverUsername = server;
        clientUsername = client;
    }

    void ViewDatas()
    {
        std::cout << ID_SOCKET << std::endl;
        std::cout << port << std::endl;
    }
};

int BaseSocket::port = 5086;
int const BaseSocket::NUMBER_CONNECTIONS = 1;
std::string BaseSocket::clientUsername = "client_default";
std::string BaseSocket::serverUsername = "server_default";

class ClassServerSocket : public BaseSocket
{
public:
    bool ClientConnected = false;

    ClassServerSocket(const char *IP_HOST)
    {
        try
        {
            InitSocketWSA();

            CreateSocket();

            SetDataService(IP_HOST);

            BindServiceInSocket();

            OpenToListenSocket();
        }
        catch (const std::exception &e)
        {
            throw std::runtime_error(e.what());
        }

        SetSocketID(1);
    }

    ~ClassServerSocket()
    {
        closesocket(MySocket);
        closesocket(OtherSocket);
        WSACleanup();
    }

    bool AcceptConn()
    {
        OtherSocket = accept(MySocket, NULL, NULL);
        if (OtherSocket == INVALID_SOCKET)
        {
            return true;
        }
        return false;
    }

    bool StabilizeConn(std::string ServerUsername)
    {
        const char *username = ServerUsername.c_str();

        if (AcceptConn())
            return false;

        ClientConnected = true;

        do
        {
            iResult = send(OtherSocket, username, strlen(username), 0);
        } while (iResult != 0);

        try
        {
            RecvUsername();
            std::cout << "username do cliente: " << clientUsername;
        }
        catch (const std::exception &e)
        {
            return false;
        }

        return true;
    }

private:
    void OpenToListenSocket()
    {
        iResult = listen(MySocket, NUMBER_CONNECTIONS);
        if (iResult == SOCKET_ERROR)
        {
            closesocket(MySocket);
            WSACleanup();
            throw std::runtime_error("Erro ao atribuir escuta no socket.");
        }
    }
};

class ClassClientSocket : public BaseSocket
{
public:
    ClassClientSocket()
    {
        try
        {
            InitSocketWSA();

            CreateSocket();
        }
        catch (const std::exception &e)
        {
            throw std::runtime_error(e.what());
        }

        SetSocketID(2);
    }

    void ClientConnectToServer(const char *IP, std::string ClientUsername)
    {
        try
        {
            SetDataService(IP);

            ConnServer();

            RecvUsername();
            std::cout << "username do servidor: " << serverUsername;
            const char *username = (const char *)&ClientUsername;
            do
            {
                iResult = send(MySocket, username, strlen(username), 0);
            } while (iResult != 0);
        }
        catch (const std::exception &e)
        {
            throw std::runtime_error("Erro");
        }
    }

    void ConnServer()
    {

        do
        {
            iResult = connect(MySocket, (SOCKADDR *)&service, sizeof(service));
            std::cout << GetLastError();

        } while (iResult != 0);
        if (iResult == SOCKET_ERROR)
        {
            iResult = closesocket(MySocket);
            if (iResult == SOCKET_ERROR)
            {
                throw std::runtime_error("Erro em fechar o socket apos falha.");
            }
            WSACleanup();

            throw std::runtime_error("Erro em conectar ao servidor");
        }
    }
};