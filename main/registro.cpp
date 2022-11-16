#include "registro.hpp"

Registro::Registro(){
    int i;
    for (i = 0; i < 20; i++) this->nome[i] = '\0';
    for (i = 0; i < 14; i++) this->telefone[i] = '\0';
    for (i = 0; i < 40; i++) this->endereco[i] = '\0';
}

Registro::Registro(uint8_t *bytes){
    int i;
    for (i = 0; i < 20; i++) this->nome[i] = bytes[i];
    for (i = 0; i < 14; i++) this->telefone[i] = bytes[i + 20];
    for (i = 0; i < 30; i++) this->endereco[i] = bytes[i + 34];
}

Registro::Registro(string nome, string num, string endereco){
    int i;
    for (i = 0; i < 20; i++) this->nome[i] = nome[i];
    for (i = 0; i < 14; i++) this->telefone[i] = num[i];
    for (i = 0; i < 40; i++) this->endereco[i] = endereco[i];
}

uint8_t *Registro::returnReg(){
    uint8_t *reg = new uint8_t[64];
    for (int i = 0; i < 20; i++) reg[i] = this->nome[i];
    for (int i = 0; i < 14; i++) reg[i + 20] = this->telefone[i];
    for (int i = 0; i < 30; i++) reg[i + 34] = this->endereco[i];
    return reg;
}

void Registro::printReg(){printf("Nome: %s\nTelefone: %s\nEndereco: %s\n", this->nome,this->telefone,this->endereco);}
