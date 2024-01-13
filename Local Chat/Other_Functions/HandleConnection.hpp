#include <iostream>

#include "UtilsFunction.hpp"

void EnterChat(int ServerOrClient);

void ServerEnterChat()
{
    if (ServerSocket == nullptr)
    {
        std::cout << "Nao esta sendo hosteado nenhum chat.";
        return;
    }

    bool clientconnected = false;
    std::string serverUsername = GetUsername();

    if (ServerSocket->ClientConnected)
    {
        std::cout << "O cliente ja esta conectado..." << std::endl;
        std::cout << "Entrando no chat..." << std::endl;
        // Lógica para conexão no chat caso o cliente já esteja no chat...
        return;
    }
    else
    {
        std::cout << "Esperando a conexao do cliente...";
        clientconnected = ServerSocket->StabilizeConn(serverUsername);
    }

    if (!clientconnected)
    {
        std::cout << "Erro na conexão do cliente.";
        return;
    }

    EnterChat(1);
}

void ClientEnterChat(std::string ServerIP)
{
    // A lógica de enviar o nickname para o servidor deve ser implementada aqui.
    std::string clientUsername = GetUsername();
    try
    {
        ClientSocket->ClientConnectToServer((const char *)&ServerIP, clientUsername);
    }
    catch (std::exception &e)
    {
        std::cout << "Houve um erro na tentativa de conectar ao servidor";
        return;
    }
    EnterChat(2);
}

void EnterChat(int ServerOrClient)
{
    bool connectInChat = true;

    if (ServerOrClient == 1)
    {
    }
    else
    {
    }
    std::cout << "Chat de conversas. Se desejar sair da conversa, apenas digite !exit/" << std::endl;
    std::cout << "O seu username é: " << std::endl;
    std::cout << "O username do outro é: " << std::endl;

    while (connectInChat)
    {
        std::string message;
    }
}

void HandlerChat()
{
    // Será uma função que ficara trocando entre enviar mensagem e receber a mensagem.
}