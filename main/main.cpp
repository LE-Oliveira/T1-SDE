#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "banco.hpp"
#include <inttypes.h>

extern "C" void app_main();
void menu(){
    printf("\n\t\t\t MENU");
    printf("\n[1] - Lista todos os registros");
    printf("\n[2] - Pesquisa registro por nome");
    printf("\n[3] - Pesquisa registro por telefone");
    printf("\n[4] - Insere registro");
    printf("\n[5] - Remove registro baseado no telefone");
    printf("\n[6] - Mostra a quantidade de registros atualmente armazenados");
    printf("\n[7] - Inicializa o banco de dados (todas as informações armazenadas serão perdidas)");
}

Banco banco = Banco();
void lista(){
    vector<Registro> regs = banco.allRegs();
    printf("Registros:\n");
    for (int i = 0; i < regs.size(); i++) regs.at(i).printReg();
}

void pesquisa(bool opt){
    int aux;
    if(opt){
        printf("Pesquisar registro baseado no nome\n");
        printf("Nome: \n");    
        aux = 20
    }
    else{
        printf("Pesquisar registro baseado no telefone\n");
        printf("Telefone: \n");    
        aux = 14;
    }
    char var[aux];
    serial.readString((uint8_t *)var, aux);
    uint8_t indice = banco.getIndReg(var, opt);
    if(indice != 0){
        Registro *reg = banco.getRegistro(indice);
        reg->printReg();
    }
    else printf("Registro nao encontrado\n");
}

void insereRegistro(){
    printf("Insere Registro");
    char nome[20];
    char telefone[14];
    char endereco[40];
    printf("Nome: \n");
    serial.readString((uint8_t *)nome, 20);
    printf("%s\n", nome);
    printf("Telefone: \n");
    serial.readString((uint8_t *)telefone, 14);
    printf("%s\n", telefone);
    printf("Endereco: \n");
    serial.readString((uint8_t *)endereco, 40);
    printf("%s\n", endereco);
    Registro reg = Registro(nome, telefone, endereco);
    banco.addReg(reg);
}

void removeTelefone(){
    printf("Remove registro\n");
    char tel[14];
    printf("Telefone: \n");
    serial.readString((uint8_t *)tel, 14);
    banco.removeReg(banco.getIndReg(tel, false));
}

void initBanco(){
    printf("Inicializacao do banco de dados. Dados anteriores serao removidos\n");
    banco.reset();
}

void app_main(){
    serial.begin(9600);
    while(1){
        menu();
        char opt = serial.readChar();
        printf("Opcao: %c\n", opt);
        switch(opt){
            case 1:
                lista();
                break;
            case 2:
                pesquisa(true);
                break;
            case 3:
                pesquisa(false);
                break;
            case 4:
                insereRegistro();
                break;
            case 5:
                removeTelefone());
                break;
            case 6:
                banco.getTam();;
                break;
            case 7:
                initBanco());
                break;
            default:
                printf("Opcao invalida, selecione outro valor\n");
        }
    }
    
}