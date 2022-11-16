#ifndef REGISTRO
#define REGISTRO

#include <string>

using namespace std;

class Registro {
    public:
        char nome[20];
        char telefone[14];
        char endereco[30];
        Registro();
        Registro(uint8_t* bytes);
        Registro(string nome, string telefone, string endereco);
        uint8_t* returnReg();
        void printReg();
};

#endif REGISTRO