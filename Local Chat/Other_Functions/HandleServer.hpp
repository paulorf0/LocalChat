#include <iostream>
#include <regex>

#include "../ClientSocket/ClientSocket.hpp"
#include "../ServerSocket/ServerSocket.hpp"
// #include "UtilsFunction.hpp"

ClassServerSocket *ServerSocket = nullptr;
ClassClientSocket *ClientSocket = nullptr;

void CreateConnectionServer(const char *IP_HOST)
{
    try
    {
        ServerSocket = new ClassServerSocket(IP_HOST);
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error(e.what());
    }
}

bool CreateSocketClient()
{
    if (ServerSocket != nullptr)
    {
        std::cout << "Voce esta hosteando um chat no momento. Reinicie o programa.";
        return false;
    }

    ClientSocket = new ClassClientSocket();
    return true;
}

bool CreateServerSocketInIp(const char *IP_HOST)
{
    try
    {
        int iResult = 0;

        if (ServerSocket != nullptr)
        {
            delete ServerSocket;
            ServerSocket = nullptr;
        }

        try
        {
            CreateConnectionServer(IP_HOST);
        }
        catch (std::exception &e)
        {
            std::cout << e.what();
        }

        system("cls");
        std::cout << "A host foi criada com sucesso!" << std::endl;
        std::cout << std::endl
                  << "---------------------" << std::endl
                  << std::endl;

        return true;
    }
    catch (const std::exception &e)
    {
        std::cout << e.what();
        return false;
    }
    return false;
}
