#ifndef _BANCO_
#define _BANCO_

#include "registro.hpp"
#include "serial.hpp"
#include "memoria.hpp"
#include <vector>

class Banco {
    private:
        Memoria memoria_i2c;
    public:
        Banco();
        void reset();
        vector<Registro> allRegs();
        void addReg(Registro reg);
        void removeReg(uint8_t add);
        Registro* getRegistro(uint8_t add);
        uint8_t getIndReg(char* nome, bool opt);
        void deletaPosi(uint8_t index);
        void reorganiza(uint8_t pos_excluida);
        void getTam();
};

#endif