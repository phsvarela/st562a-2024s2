#include "utils.h"
#include <cstdio>
#include <iostream>
#include <limits>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <string>
#include <dirent.h>
#include <cstring>
#include <vector>
#include <sstream>

using namespace std;

/* UTILS */

// verifica se a opcao escolhida é um número valido com uma faixa definida
int Utils::validaInputOperacao12()
{
    int escolha;
    while (1)
    {
        cin >> escolha;
        if (!cin.fail() && (escolha == 1 || escolha == 2))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return escolha;
        }
        else
        {
            cout << "Entrada invalida. Digite um numero valido!" << endl
                 << "Escolha uma opcao: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
    }
}

// verifica se a opcao escolhida é um número valido com uma faixa definida
int Utils::validaInputOperacao01()
{
    int escolha;
    while (1)
    {
        cin >> escolha;
        if (!cin.fail() && (escolha == 1 || escolha == 0))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return escolha;
        }
        else
        {
            cout << "Entrada invalida. Digite um numero valido!" << endl
                 << "Escolha uma opcao: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
    }
}

// verifica se a opcao escolhida é um número valido com uma faixa definida
int Utils::validaInputOperacao0123456()
{
    int escolha;
    while (1)
    {
        cin >> escolha;
        if (!cin.fail() && (escolha == 1 || escolha == 2 || escolha == 3 || escolha == 4 || escolha == 5 || escolha == 6 || escolha == 0))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return escolha;
        }
        else
        {
            cout << "Entrada invalida. Digite um numero valido!" << endl
                 << "Escolha uma opcao: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
    }
}

// verifica se a opcao escolhida é um número valido com uma faixa definida
int Utils::validaInputOperacao012345()
{
    int escolha;
    while (1)
    {
        cin >> escolha;
        if (!cin.fail() && (escolha == 1 || escolha == 2 || escolha == 3 || escolha == 4 || escolha == 5 || escolha == 0))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return escolha;
        }
        else
        {
            cout << "Entrada invalida. Digite um numero valido!" << endl
                 << "Escolha uma opcao: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
    }
}

// verifica se o nome do arquivo é válido e não tem contem caracterés especiais
string Utils::validaInputFileName()
{
    string name;
    while (1)
    {
        cin >> name;
        if (name.empty() || (name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") != string::npos))
        {
            cout << "Entrada invalida. Digite um nome valido" << endl
                 << "Caracteres aceitos: [a/z][A/Z][0-9]" << endl
                 << "Digite o nome do arquivo .txt a ser criado: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        else
        {
            return name;
        }
    }
}

// verifica se a opcao escolhida é um char valido com uma faixa definida
char Utils::validaConfirmacao()
{
    char confirmacao;
    while (1)
    {
        cin >> confirmacao;
        if (!cin.fail() && (confirmacao == 's' || confirmacao == 'n'))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return confirmacao;
        }
        else
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << endl
                 << "Comando invalido! Digite um comando valido. [s/n]" << endl;
            continue;
        }
    }
}

// verifica se a opcao escolhida é um número valido
int Utils::validaInputNumero()
{
    int escolha;
    while (1)
    {
        cin >> escolha;
        if (!cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return escolha;
        }
        else
        {
            cout << "Entrada invalida. Digite um numero valido!" << endl
                 << "Escolha uma opcao: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
    }
}
