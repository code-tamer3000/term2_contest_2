/*
Необходимо написать торгового советника для поиска арбитража.
Арбитраж - это торговля по цепочке различных валют в надежде заработать на небольших различиях в коэффициентах. Например, есть следующие курсы валют:
GBP/USD: 0.67
RUB/GBP: 78.66
USD/RUB: 0.02
Имея 1$ и совершив цикл USD->GBP->RUB->USD, получим 1.054$. Таким образом заработав 5.4

Формат ввода
Первая строка содержит число N – количество возможных валют (определяет размер таблицы котировок).
Далее следует построчное представление таблицы. Диагональные элементы (i, i) пропущены (подразумевается, что курс валюты к себе же 1.0).
В элементе таблицы (i, j) содержится обменный курс i->j.
Если обмен в данном направлении не производится, то -1.
Формат вывода
Выведите YES, если арбитраж есть, и NO, иначе.
*/

#include <iostream>
#include <vector>
#include <float.h>

double bellman_ford(std::vector<std::vector<double>>& matrix, int start) {
    std::vector<double> distances(matrix.size(), DBL_MIN); 
    distances[start] = 1; 
    bool not_processed = true;
    for (int i = 0; i < matrix.size() - 1 && not_processed; i++) {
        not_processed = false;
        for (int u = 0; u < matrix.size(); u++) {
            for (int v = 0; v < matrix.size(); v++) {
                if (matrix[u][v] > 0) { 
                    if (distances[u] != DBL_MIN && distances[v] < distances[u] * matrix[u][v]) {
                        distances[v] = distances[u] * matrix[u][v];
                        not_processed = true;
                    }
                }
            }
        }
    }
    return distances[start]; 
}

bool arbitrage(std::vector<std::vector<double>>& matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        double tmp = bellman_ford(matrix, i);
        if (tmp > 1) return true;
    }
    return false;
}

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<std::vector<double>> matrix(n, std::vector<double>(n, 0.));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) std::cin.ignore();
            else std::cin >> matrix[i][j];
        }
    }    
    std::cout << ((arbitrage(matrix)) ? "YES" : "NO") << '\n';
    return 0;
}
