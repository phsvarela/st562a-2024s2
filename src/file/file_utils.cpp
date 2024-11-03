#include "file_utils.h"
#include "../utils/utils.h"
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
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

// funcao responsavel por criar arquivos e editar caso já exista
bool FileUtils::criarArquivoNoDisco(const fs::path &path)
{
    try
    {
        ofstream arquivo(path); // abre o arquivo
        arquivo.close();        // fecha o arquivo aberto
        cout << endl
             << "Arquivo criado com sucesso!" << endl;
        return true;
    }
    catch (const std::exception &e)
    {
        cout << endl
             << "Erro: Nao foi possivel criar o arquivo!" << endl;
        return false;
    }
}

bool FileUtils::criarPastaNoDisco(const fs::path &path)
{
    try
    {
        fs::create_directory(path); // cria diretorio
        cout << endl
             << "Diretorio criado com sucesso!" << endl;
        return true;
    }
    catch (const std::exception &e)
    {
        cout << endl
             << "Erro: Nao foi possivel criar o diretorio!" << endl;
        return false;
    }
}

// funcao resposavel por excluir arquivo
bool FileUtils::excluirArquivo(const fs::path &path)
{
    try
    {
        fs::remove(path); // remove o arquivo atual
        cout << endl
             << "Arquivo removido com sucesso!" << endl;
        return true;
    }
    catch (const std::exception &e)
    {
        cout << endl
             << "Erro: Nao foi possivel remover o arquivo com nome " << path << endl;
        return false;
    }
}

bool FileUtils::renameFile(const fs::path &oldPath, const fs::path &newPath)
{
    try
    {
        fs::rename(oldPath, newPath); // renomeia o arquivo usando o caminho antigo e o caminho novo
        cout << endl
             << "Recurso renomeado com sucesso." << endl;
        return true;
    }
    catch (const std::exception &e)
    {
        cout << endl
             << "Erro: Nao foi possivel renomear o recurso!" << endl;
        return false;
    }
}

// Insere um novo texto, gerando um novo id incremental
void FileUtils::inserirTexto(const fs::path &path, const string &text)
{
    try
    {
        fstream arquivo(path, ios::in | ios::out | ios::app); // abre o arquivo em modo de leitura, gravação e concatenacao
        arquivo.clear();                                      // limpa estado IOF
        arquivo.seekg(0, ios::beg);                           // aponta para o inicio do arquivo em modo leitura

        int numeroLinhas = 0;
        string linha;

        while (getline(arquivo, linha))
        {
            stringstream ss(linha); // pega o primeiro numero
            ss >> numeroLinhas;
        }

        int novoId = numeroLinhas + 1; // cria novo id como a quantidade de linhas + 1

        arquivo.clear();
        arquivo.seekp(0, ios::end); // aponta para o inicio do arquivo em modo gravacao

        arquivo << novoId << " - " << text << endl; // insere texto no formato "ID - Texto"
        cout << "Nova linha inserida no arquvio com ID " << novoId << endl;
        arquivo.close();
    }
    catch (const std::exception &e)
    {
        cout << endl
             << "Erro: Nao foi possivel inserir a linha no arquivo." << endl;
    }
}

// Busca linha que sera removida e remove exclusivamente ela, mantendo o restante do arquivo
void FileUtils::removerTexto(const fs::path &path, int &index)
{
    try
    {
        fstream arquivo(path, ios::in | ios::out | ios::app); // abre o arquivo em modo de leitura, gravação e concatenacao
        arquivo.clear();                                      // limpa estado IOF
        arquivo.seekg(0, ios::beg);                           // aponta para o inicio do arquivo em modo leitura

        vector<string> linhas;
        string linha;
        bool encontrou = false;

        // para cada linha do arquivo
        while (getline(arquivo, linha))
        {
            // busca o primeiro numero (id)
            stringstream ss(linha);
            int id;
            ss >> id;

            if (id != index)
            {
                // se nao for o id inserido, insere linha no vector
                linhas.push_back(linha);
            }
            else
            {
                // se for, nao adiciona no vector
                encontrou = true;
            }
        }

        arquivo.clear(); // limpa estado EOF
        if (!encontrou)
        {
            // se nao encontrou, sai da funcao
            cout << endl
                 << "ID " << index << " nao encontrado no arquivo." << endl;
            return;
        }
        else
        {
            // se encontrou, reescreve o arquivo sem a linha selecionada
            // fecha o arquivo e abre em modo truncado (limpa o conteudo)
            arquivo.close();
            arquivo.open(path, ios::out | ios::trunc);

            // reabre o arquivo para leitura, gravação e concatenação
            arquivo.close();
            arquivo.open(path, ios::in | ios::out | ios::app);

            // reescreve as linhas anteriores sem a linha apagada
            for (const auto &linhaArmazenada : linhas)
            {
                arquivo << linhaArmazenada << endl;
            }

            arquivo.close();
            cout << endl
                 << "Linha com ID " << index << " foi removida com sucesso" << endl;
        }
    }
    catch (const std::exception &e)
    {
        cout << endl
             << "Erro: Nao foi possivel remover a linha." << endl;
    }
}

// Imprime cada linha do arquivo
void FileUtils::imprimirTexto(const fs::path &path)
{
    try
    {
        fstream arquivo(path, ios::in); // abre o arquivo em modo de leitura
        arquivo.seekg(0, ios::beg);     // aponta para o inicio do arquivo em modo leitura
        string linha;

        cout << endl
             << "Conteudo do arquivo:" << endl;

        // imprime cada linha do arquivo
        while (getline(arquivo, linha))
        {
            cout << linha << endl;
        }

        arquivo.close();
    }
    catch (const std::exception &e)
    {
        cout << endl
             << "Erro: Nao foi possivel imprimir o conteudo do arquivo." << endl;
    }
}

// Apaga o conteudo do arquivo
void FileUtils::apagarConteudoArquivo(const fs::path &path)
{
    try
    {
        // abre o arquivo truncado (sem conteudo)
        fstream arquivo(path, ios::out | ios::trunc);
        arquivo.close();

        cout << endl
             << "Conteudo do arquivo apagado com sucesso" << endl;
    }
    catch (const std::exception &e)
    {
        cout << endl
             << "Erro: Nao foi possivel apagar o conteudo do arquivo." << endl;
    }
}
