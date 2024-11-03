#include "src/file/file_utils.h"
#include "src/utils/utils.h"
#include "src/tree/tree.h"
#include <sstream>
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

using namespace std;

/* CAMADA PRINCIPAL */

int main()
{
    cout << "**********************************************************" << endl
         << "Bem-vindo ao programa gerenciador de arquvidos de texto!" << endl
         << "Esse programa criara uma estrutura hierarquica(arvore) simples." << endl
         << "**********************************************************" << endl
         << endl;

    Tree *arvore = new Tree();

    while (1)
    {
        int escolha = -1;
        cout << endl
             << "Operacoes possiveis:" << endl
             << "1. Inserir." << endl
             << "2. Deletar." << endl
             << "3. Editar." << endl
             << "4. Listar diretorio atual." << endl
             << "5. Acessar subdiretorio." << endl
             << "6. Voltar ao diretorio pai." << endl
             << "0. Encerrar." << endl
             << "Escolha uma opcao: " << endl;
        escolha = Utils::validaInputOperacao0123456();

        switch (escolha)
        {
        case 1:
            cout << endl
                 << "Opcao selecionada: Inserir." << endl;
            arvore->addFile();
            break;

        case 2:
            cout << endl
                 << "Opcao selecionada: Deletar." << endl;
            arvore->deleteFile();
            break;

        case 3:
            cout << endl
                 << "Opcao selecionada: Editar." << endl;
            arvore->selectAndEditFile();
            break;
        case 4:
            cout << endl
                 << "Opcao selecionada: Listar diretorio atual." << endl;
            arvore->listDirectory();
            break;
        case 5:
            cout << endl
                 << "Opcao selecionada: Acessar subdiretorio." << endl;
            arvore->enterDirectory();
            break;
        case 6:
            cout << endl
                 << "Opcao selecionada: Voltar ao diretorio pai." << endl;
            arvore->goBack();
            break;
        default:
            cout << endl
                 << "O programa sera encerrado." << endl;
            arvore->~Tree();
            return 0;
        }
    }

    return 0;
}