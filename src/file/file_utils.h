#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <string>
#include <fstream>
#include <vector>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

// classe para biblioteca de manipulacao de arquivos
class FileUtils
{
public:
    // prototipo das funcoes
    static bool criarArquivoNoDisco(const fs::path &path);
    static bool criarPastaNoDisco(const fs::path &path);
    static bool excluirArquivo(const fs::path &path);
    static bool renameFile(const fs::path &oldPath, const fs::path &newPath);
    static void inserirTexto(const fs::path &path, const string &text);
    static void removerTexto(const fs::path &path, int &index);
    static void imprimirTexto(const fs::path &path);
    static void apagarConteudoArquivo(const fs::path &path);
};

#endif // FILE_UTILS_H