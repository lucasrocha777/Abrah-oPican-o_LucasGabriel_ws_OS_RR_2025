#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include <chrono>
#include <mutex>
#include <queue>

std::mutex cout_mutex; // Para sincronizar saídas no console

void search_file(const std::string& filename, const std::vector<std::string>& keywords) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cerr << "Erro ao abrir o arquivo: " << filename << "\n";
        return;
    }

    std::string line;
    int line_number = 0;
    while (std::getline(file, line)) {
        ++line_number;
        for (const auto& keyword : keywords) {
            if (line.find(keyword) != std::string::npos) {
                std::lock_guard<std::mutex> lock(cout_mutex);
                std::cout << filename << " [Line " << line_number << "] (" << keyword << "): " << line << "\n";
            }
        }
    }
    file.close();
}

void worker_thread(std::queue<std::string>& files, const std::vector<std::string>& keywords, std::mutex& queue_mutex) {
    while (true) {
        std::string filename;
        {
            std::lock_guard<std::mutex> lock(queue_mutex);
            if (files.empty()) {
                return;
            }
            filename = files.front();
            files.pop();
        }
        search_file(filename, keywords);
    }
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    std::string directory = "./files"; // Diretório onde os arquivos .txt estão
    std::vector<std::string> keywords = {"example", "test"}; // Múltiplas palavras-chave
    std::queue<std::string> files;
    std::mutex queue_mutex;
    std::vector<std::thread> threads;

    // Verifica se o diretório existe
    if (!std::filesystem::exists(directory)) {
        std::cerr << "Diretório não encontrado: " << directory << "\n";
        return 1;
    }

    // Coleta os arquivos .txt
    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        if (entry.path().extension() == ".txt") {
            files.push(entry.path().string());
        }
    }

    // Determina o número de threads com base no hardware
    unsigned int num_threads = std::thread::hardware_concurrency();
    if (num_threads == 0) num_threads = 4; // Fallback caso hardware_concurrency não funcione
    std::cout << "Usando " << num_threads << " threads\n";

    // Cria as threads
    for (unsigned int i = 0; i < num_threads; ++i) {
        threads.emplace_back(worker_thread, std::ref(files), std::ref(keywords), std::ref(queue_mutex));
    }

    // Aguarda todas as threads terminarem
    for (auto& t : threads) {
        t.join();
    }

    // Calcula e exibe o tempo total de execução
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "\nTempo total de execução: " << duration.count() << " ms\n";

    return 0;
}
