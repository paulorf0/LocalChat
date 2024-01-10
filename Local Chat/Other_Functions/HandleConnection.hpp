#include <iostream>

#include "UtilsFunction.hpp"

void ServerEnterChat()
{
    if (ServerSocket == nullptr)
    {
        std::cout << "Nao esta sendo hosteado nenhum chat.";
        return;
    }
}