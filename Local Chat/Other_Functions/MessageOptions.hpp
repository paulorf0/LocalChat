#include <iostream>
#include <vector>

const std::vector <std::string> optionsMessage = {"Iniciar conexao com o chat.", "Ser o host do chat.",
                                                  "Dados do cliente/servidor.", "Sair do programa."};
const std::vector <std::string> extraoptionsMessage = {"Capturar dados do cliente.", "Capturar dados do servidor."};

bool CharIsNumber(char c) { return c > 48 && c < 57 ? true : false; }

void ShowOptions() {
    std::size_t sizeOptionsMessage = optionsMessage.size();

    for (int i = 0; i < sizeOptionsMessage; i++) {
        std::cout << i + 1 << ". " << optionsMessage[i] << std::endl;
    }

    std::cout << "Esperando resposta..." << std::endl;
}


int GetInputToOption() {
    char responsePlayer;
    bool anyError = false;

    do {
        anyError = false;
        responsePlayer = getchar();

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        system("cls");


        if (responsePlayer == '\n' || responsePlayer == EOF) {
            anyError = true;
            ShowOptions();
        }
        if (!CharIsNumber(responsePlayer) && responsePlayer != '\n' && responsePlayer != EOF) {
            std::cout << "Deve ser um numero." << std::endl;
            std::cout << "-----------------" << std::endl;
            ShowOptions();
            anyError = true;
            continue;
        }

    } while (anyError);

    return responsePlayer - '0';
}


void ShowDataServerClient() {
    std::size_t sizeOptionsMessage = extraoptionsMessage.size();

    for (int i = 0; i < sizeOptionsMessage; i++) {
        std::cout << i + 1 << ". " << extraoptionsMessage[i] << std::endl;
    }

    std::cout << "Esperando resposta..." << std::endl;

    int choice = GetInputToOption();

    if (choice == 1) {
        if (ClassClientSocket == nullptr) {
            std::cout << "O cliente ainda nao iniciou conexao." << std::endl;
            return;
        }

        ClassServerSocket->InformationsAboutClientSocket();
        return;
    } else if (choice == 2) {
        if (ClassServerSocket == nullptr) {
            std::cout << "O servidor ainda nao foi criado." << std::endl;
            return;
        }

        ClassServerSocket->InformationsAboutServerSocket();
        return;
    } else {
        std::cout << "Nenhum item valido." << std::endl;
    }
}

void DeleteServerSocket() {
    ClassServerSocket->~CreateServerSocket();
}

bool GoNext() {
    char go;
    std::cout << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    go = std::getchar();
}
