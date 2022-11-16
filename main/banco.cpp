#include <stdio.h>
#include "banco.hpp"

Banco::Banco(){
    this->memoria_i2c = Memoria();
    this->reset();
}

vector<Registro> Banco::allRegs(){
    vector<Registro> regs;
    uint8_t header[64];
    this->memoria_i2c.le(0, header, 64);
    uint16_t qtd = header[0] << 8 | header[1];
    uint16_t tamMax = header[2] << 8 | header[3];
    for (int i = 0; i < qtd; i++){
        uint8_t reg[64];
        this->memoria_i2c.le((i+1) * 64, reg, 64);
        regs.push_back(Registro(reg));
    }
    return regs;
}
 
void Banco::reset(){
    this->memoria_i2c.init(0);
    uint8_t header[64];
    header[0] = 0;
    header[1] = 0;
    header[2] = 1023 >> 8;
    header[3] = 1023;
    this->memoria_i2c.escreve(0, header, 64);
}

void Banco::addReg(Registro reg){
    uint8_t header[64];
    this->memoria_i2c.le(0, header, 64);
    uint16_t qtd = header[0] << 8 | header[1];
    uint16_t qtdMax = header[2] << 8 | header[3];
    if (qtd < qtdMax){
        this->memoria_i2c.escreve(((qtd + 1)) * 64, reg.returnReg(), 64);
        qtd++;
        header[0] = qtd >> 8;
        header[1] = qtd;
        this->memoria_i2c.escreve(0, header, 64);
    }
}

void Banco::removeReg(uint8_t index){
    uint8_t header[64];
    this->memoria_i2c.le(0, header, 64);
    uint16_t qtd = header[0] << 8 | header[1];
    uint16_t qtdMax = header[2] << 8 | header[3];
    if(qtd>0){
        qtd--;
        header[0] = qtd >> 8;
        header[1] = qtd;
        this->memoria_i2c.escreve(0, header, 64);
        this->deletaPosi(index);
        this->reorganiza(index);
    }
}

Registro* Banco::getRegistro(uint8_t index){
    uint8_t header[64];
    this->memoria_i2c.le(0, header, 64);
    Registro *reg;
    uint8_t data[64];
    memoria_i2c.le(index*64, data, 64);
    reg = new Registro(data);
    return reg;
}

uint8_t Banco::getIndReg(char* nome, bool opt){
    uint8_t header[64];
    this->memoria_i2c.le(0, header, 64);
    uint16_t qtd = header[0] << 8 | header[1];
    for(int i = 1; i <= qtd; i++){
        uint8_t regTemp[64];
        memoria_i2c.le(i*64, regTemp, 64);
        bool flag = true;
        if(opt){
            for(int j = 0; j < 20; j++){
                if(nome[j] == 0 || nome[j] == '\n') break;
                if(regTemp[j] != nome[j]){
                    flag = false;
                    break;
                }
            }
        }
        else{
            for(int j = 20; j < 34; j++){
                if(telefone[j-20] == 0 || telefone[j-20] == '\n') break;
                if(read_data[j] != telefone[j-20]){
                    flag = false;
                    break;
                }   
            }
        }
        if(flag) return i;
    }
    return 0;
}

void Banco::deletaPosi(uint8_t index){
    uint8_t nulo[64];
    for (int i = 0; i < 64; i++) nulo[i] = 0;
    this->memoria_i2c.escreve(index * 64, nulo, 64);
}

void Banco::reoganiza(uint8_t index){
    uint8_t header[64];
    this->memoria_i2c.le(0, header, 64);
    uint16_t qtd = header[0] << 8 | header[1];
    uint16_t qtdMax = header[2] << 8 | header[3];
    uint8_t ultimo[64];
    this->memoria_i2c.le((qtd+1) * 64, ultimo, 64);
    this->memoria_i2c.escreve(index * 64, ultimo, 64);
    this->deletaPosi(qtd+1);
}

void Banco::getTam(){
    uint8_t header[64];
    memoria_i2c.le(0, (uint8_t *)header, 4);
    printf("Registros na agenda: %d\n", (header[0]<<8)+ header[1]);
}