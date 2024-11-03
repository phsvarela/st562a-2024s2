#ifndef UTILS_H
#define UTILS_H

#include <string>

using namespace std;

// classe para biblioteca de utilidades para validacao de inputs
class Utils
{
public:
    // prototipo das funcoes
    static int validaInputOperacao12();
    static int validaInputOperacao01();
    static int validaInputOperacao0123456();
    static int validaInputOperacao012345();
    static string validaInputFileName();
    static char validaConfirmacao();
    static int validaInputNumero();
};

#endif // UTILS_H