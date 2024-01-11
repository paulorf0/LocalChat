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
    std::string username = GetUsername();
    std::string clientUsername;

    if (ServerSocket->clientSocketAccepted != INVALID_SOCKET)
    {
        std::cout << "O cliente ja esta conectado..." << std::endl;
        std::cout << "Entrando no chat..." << std::endl;
        // Lógica para conexão no chat...
        return;
    }
    else
    {
        std::cout << "Esperando a conexao do cliente...";
        clientconnected = ServerSocket->AcceptConnection();
        // De alguma maneira, quando o cliente for conectado, tenho que enviar o username que foi digitado.
        // A lógica para enviar o server username para o cliente deve ser implementado aqui quando for aceitado.
    }

    if (!clientconnected)
    {
        std::cout << "Erro na conexão do cliente.";
        return;
    }

    EnterChat(username, clientUsername);
}

void ClientEnterChat()
{
    // A lógica de enviar o nickname para o servidor deve ser implementada aqui.
}

void EnterChat(std::string ServerUsername, std::string ClientUsername)
{
    bool connectInChat = true;

    std::cout << "Chat de conversas. Se desejar sair da conversa, apenas digite !exit/" << std::endl;
    std::cout << "O seu username é: " << ServerUsername << std::endl;
    std::cout << "O username do outro é: " << ClientUsername << std::endl;

    while (connectInChat)
    {
        // Creio que deve ter que usar thread para poder fazer duas tarefas ao mesmo tempo.
        // Receber mensagem constantemente e poder enviar mensagem constantemente.
        // Essa parte da lógica deve ser pensado cuidadosamente.
        // Deve ser implementado tanto na parte cliente quanto na parte do servidor.
        // Deve ser algo bem pensado, para que essa função possa ser reaproveitada para cliente e servidor.
    }
}