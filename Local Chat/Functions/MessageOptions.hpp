#include <iostream>
#include <vector>

const std::vector<std::string> options_game = {"Iniciar conexao com o chat.", "Ser o host do chat.", "Sair do programa."};

bool CharIsNumber(char c) { return c > 48 && c < 57 ? true : false; }

void ShowOptions()
{
    std::size_t size_optionsGame = options_game.size();

    for (int i = 0; i < size_optionsGame; i++)
    {
        std::cout << i + 1 << '.' << options_game[i] << '\n';
    }

    std::cout << "Esperando resposta...\n";
}

int GetInputToOption()
{
    std::size_t responsePlayer_size;
    std::string responsePlayer;
    bool anyError = false;

    do
    {
        anyError = false;
        std::cin >> responsePlayer;

        system("cls");

        responsePlayer_size = responsePlayer.length();

        if (responsePlayer_size > 1)
        {
            std::cout << "A resposta deve ser apenas o numero da opcao!\n";
            anyError = true;
            continue;
        }

        if (!CharIsNumber(responsePlayer[0]))
        {
            std::cout << "Deve ser um numero.\n";
            anyError = true;
            continue;
        }

    } while (responsePlayer_size > 1 || anyError);

    return responsePlayer[0] - '0';
}