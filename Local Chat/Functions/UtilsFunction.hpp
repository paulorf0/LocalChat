#include <iostream>
#include <regex>

bool isValidIPv4(const std::string& ip) {
    const std::regex ipv4Regex("^\\b(?:\\d{1,3}\\.){3}\\d{1,3}\\b");
    return std::regex_match(ip, ipv4Regex);
}

std::string GetInputIp() {
    while(1) {
        std::cout << "Digite o IP para hostear (Geralmente o ip do radmin): \n";
        std::string IP;
        std::cin >> IP;

        if(isValidIPv4(IP)) {
            return IP;
        }

        if(IP == "exit") return ".";
        
        system("cls");
        std::cout << "Ip invalido, reescreva de maneira correta. Caso o erro persista, escreva \"exit\" para sair\n";
    }

    return ".";
}