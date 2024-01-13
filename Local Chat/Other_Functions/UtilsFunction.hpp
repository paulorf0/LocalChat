#include <iostream>
#include <vector>
#include <regex>

const std::vector<std::string> optionsMessage = {"Iniciar conexao com o chat.", "Ser o host do chat.", "Entrar no chat.", "Sair do programa."};

void ShowOptions()
{
    std::size_t sizeOptionsMessage = optionsMessage.size();

    for (int i = 0; i < sizeOptionsMessage; i++)
    {
        std::cout << i + 1 << ". " << optionsMessage[i] << std::endl;
    }

    std::cout << "Esperando resposta..." << std::endl;
}

bool CharIsNumber(char c) { return c > 48 && c < 57 ? true : false; }

bool isValidIPv4(const std::string &ip)
{
    const std::regex ipv4Regex("^\\b(?:\\d{1,3}\\.){3}\\d{1,3}\\b");
    return std::regex_match(ip, ipv4Regex);
}

std::string GetInputIp()
{
    while (1)
    {
        std::cout << "Digite o IP (Geralmente o ip do radmin): " << std::endl;
        std::string IP;
        std::getline(std::cin, IP);

        if (isValidIPv4(IP))
        {
            return IP;
        }

        if (IP == "exit")
            return ".";

        system("cls");
        std::cout << "Ip invalido, reescreva de maneira correta. Caso o erro persista, escreva \"exit\" para sair"
                  << std::endl;
    }

    return ".";
}

int GetInputToOption()
{
    char responsePlayer;
    bool anyError = false;

    do
    {
        anyError = false;
        responsePlayer = getchar();

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        system("cls");

        if (responsePlayer == '\n' || responsePlayer == EOF)
        {
            anyError = true;
            ShowOptions();
        }
        if (!CharIsNumber(responsePlayer) && responsePlayer != '\n' && responsePlayer != EOF)
        {
            std::cout << "Deve ser um numero." << std::endl;
            std::cout << "-----------------" << std::endl;
            ShowOptions();
            anyError = true;
            continue;
        }

    } while (anyError);

    return responsePlayer - '0';
}

std::string GetUsername()
{
    std::string username;

    std::cout << "Digite o username que deseja: " << std::endl;

    std::getline(std::cin, username);

    return username;
}

void DeleteServerSocket()
{
    ServerSocket->~ClassServerSocket();
}

bool GoNext()
{
    char go;
    // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << std::endl;

    go = std::getchar();
}
