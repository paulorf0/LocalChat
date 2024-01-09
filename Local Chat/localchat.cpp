#ifndef UNICODE
#define UNICODE
#endif

#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <stdio.h>


// Need to link with Ws2_32.lib
#pragma comment(lib, "ws2_32.lib")

#include "Functions/HandleServer.hpp"
#include "Functions/MessageOptions.hpp"

void ManagePlayerChoise(int choise);

int main()
{
    ShowOptions();

    int choise = GetInputToOption();
    ManagePlayerChoise(choise);

    return 1;
}



void ManagePlayerChoise(int choise) {
    std::string getIP;
    const char* IP_HOST;

    switch(choise) {
        case 1:
            std::cout << "Testando a opcao de conectar";
            // ConnectToPlayer();
            break;
        case 2:
            getIP = GetInputIp();
            if(getIP == ".") break;

            IP_HOST = getIP.c_str();
            if(CreateSocketInIp(IP_HOST)) {
                
            }
            break;
        case 3:
            exit;
            break;
        default:
            system("cls");
            std::cout << "Nenhuma opcao valida digitada.";
            break;
    }

}

