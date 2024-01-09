#include <iostream>
#include <pthread.h>
#include <regex>

#include "../ServerSocket/CreateListenSocket.hpp"
#include "./UtilsFunction.hpp"

CreateServerSocket *ClassServerSocket;

void* CreateConnectionServer(void* arg) {
    
    const char* IP_HOST = (const char*) arg;
    try {
        ClassServerSocket = new CreateServerSocket(IP_HOST);
    }catch(const std::exception& e) {
        throw std::runtime_error(e.what());
    }
    
    return nullptr;
}

bool CreateSocketInIp(const char* IP_HOST) {
    try {
        pthread_t ServerSocketThread;
        int iResult = 0;
    
        pthread_create(&ServerSocketThread, NULL, CreateConnectionServer, (void *)IP_HOST);
        pthread_join(ServerSocketThread, NULL);
        
        system("cls");
        std::cout << "A host foi criada com sucesso!\n";
        std::cout << "\n---------------------\n\n";
        
        return true;
    }catch(const std::exception& e) {
        std::cout << e.what();
        return false;
    }
    return false;
}

