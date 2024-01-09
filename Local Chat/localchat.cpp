#ifndef UNICODE
#define UNICODE
#endif

#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>


// Need to link with Ws2_32.lib
#pragma comment(lib, "ws2_32.lib")

#include "Other_Functions//HandleServer.hpp"
#include "Other_Functions//MessageOptions.hpp"

void ManagePlayerChoice(int choice);

bool leave = false;

int main() {
    while (1) {
        system("cls");
        ShowOptions();

        int choice = GetInputToOption();
        ManagePlayerChoice(choice);

        if (leave) return 1;
    }
    return 1;
}


void ManagePlayerChoice(int choice) {
    std::string getIP;
    const char *IP_HOST;
    bool SocketCreated = false;

    switch (choice) {
        case 1:
            std::cout << "Testando a opcao de conectar";
            GoNext();
            break;
        case 2:
            getIP = GetInputIp();
            if (getIP == ".") break;

            IP_HOST = getIP.c_str();
            SocketCreated = CreateSocketInIp(IP_HOST);

            GoNext();
            break;
        case 3:
            ShowDataServerClient();
            GoNext();
            break;
        case 4:
            leave = true;
            DeleteServerSocket();
            break;
        default:
            system("cls");
            std::cout << "Nenhuma opcao valida digitada.";
            GoNext();
            break;
    }

}

