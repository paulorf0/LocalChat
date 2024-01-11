#include <iostream>

#include "UtilsFunction.hpp"

void EnterChat(std::string ServerUsername, std::string ClientUsername);

void ServerEnterChat()
{
    if (ServerSocket == nullptr)
    {
        std::cout << "Nao esta sendo hosteado nenhum chat.";
        return;
    }

    bool clientconnected = false;
    std::string serverUsername = GetUsername();
    std::string clientUsername;

    if (ServerSocket->clientSocketAccepted != INVALID_SOCKET)
    {
        std::cout << "O cliente ja esta conectado..." << std::endl;
        std::cout << "Entrando no chat..." << std::endl;
        // Lógica para conexão no chat caso o cliente já esteja no chat...
        return;
    }
    else
    {
        std::cout << "Esperando a conexao do cliente...";
        clientconnected = ServerSocket->AcceptConnection(serverUsername);
    }

    if (!clientconnected)
    {
        std::cout << "Erro na conexão do cliente.";
        return;
    }

    EnterChat(serverUsername, clientUsername);
}

void ClientEnterChat(std::string ServerIP)
{
    // A lógica de enviar o nickname para o servidor deve ser implementada aqui.
    ClientSocket->ClientConnectToServer((const char *)&ServerIP, clientUsername);
    // Deve terminar a lógica.
}

void EnterChat(std::string ServerUsername, std::string ClientUsername)
{
    bool connectInChat = true;

    // Esse clientUsername ou serverusername deve ser capturado da classe de quem entrou no chat, para deixar generico!!!!!
    // Retire esses argumentos. Capture do socket de quem entrou no chat.
    // Uma verificação de por qual entrada foi colocada para entrar no chat resolveria.
    std::cout << "Chat de conversas. Se desejar sair da conversa, apenas digite !exit/" << std::endl;
    std::cout << "O seu username é: " << ServerUsername << std::endl;
    std::cout << "O username do outro é: " << ClientUsername << std::endl;

    while (connectInChat)
    {
        std::string message;
    }
}

void HandlerChat()
{
    // Será uma função que ficara trocando entre enviar mensagem e receber a mensagem.
}