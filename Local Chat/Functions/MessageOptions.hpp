#include <iostream>
#include <vector>

const std::vector<std::string> options_game = {"Iniciar conexao com o chat.", "Ser o host do chat.", "Sair do programa."};

bool CharIsNumber(char c) { return c > 48 && c < 57 ? true : false; }

void CleanBuffer() {std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');}

void ShowOptions()
{
    std::size_t size_optionsGame = options_game.size();

    for (int i = 0; i < size_optionsGame; i++)
    {
        std::cout << i + 1 << '.' << options_game[i] << std::endl;
    }

    std::cout << "Esperando resposta..." << std::endl;
}

int GetInputToOption()
{
    std::size_t responsePlayer_size;
    char responsePlayer;
    bool anyError = false;

    do
    {
        anyError = false;
        responsePlayer = getchar();

        system("cls");

        
        if (!CharIsNumber(responsePlayer))
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