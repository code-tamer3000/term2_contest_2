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

struct WeightedVertex {
    double weight = 0; 
    int vertex = 0;
    WeightedVertex(double weight_, int from_or_to_) : weight(weight_) , vertex(from_or_to_) {}
};

class ListGraph {
 public:
    explicit ListGraph(int vertices_count);
 
    void AddEdge(int from, int to, double weight);
 
    int VerticesCount() const;
 
    std::vector<WeightedVertex> FindAllAdjacentIn(int vertex) const;
    std::vector<WeightedVertex> FindAllAdjacentOut(int vertex) const;
 
 private:
    std::vector<std::vector<WeightedVertex>> in_edges_;
    std::vector<std::vector<WeightedVertex>> out_edges_;
};

ListGraph::ListGraph(int vertices_count) : in_edges_(vertices_count), out_edges_(vertices_count) {
}

void ListGraph::AddEdge(int from, int to, double weight) {
    in_edges_[to].push_back(WeightedVertex(weight, from));
    out_edges_[from].push_back(WeightedVertex(weight, to));
}
 
int ListGraph::VerticesCount() const {
    return in_edges_.size();
}
 
std::vector<WeightedVertex> ListGraph::FindAllAdjacentIn(int vertex) const {
    return in_edges_[vertex];
}
std::vector<WeightedVertex> ListGraph::FindAllAdjacentOut(int vertex) const {
    return out_edges_[vertex];
}


double bellman_ford(ListGraph& graph, int start) {
    std::vector<double> distances(graph.VerticesCount(), DBL_MIN); 
    distances[start] = 1; 
    bool not_processed = true;
    for (int i = 0; i < graph.VerticesCount() - 1 && not_processed; i++) {
        not_processed = false;
        for (int u = 0; u < graph.VerticesCount(); u++) {
            for (auto v : graph.FindAllAdjacentOut(u)) {
                if (v.weight > 0) { 
                    if (distances[u] != DBL_MIN && distances[v.vertex] < distances[u] * v.weight) {
                        distances[v.vertex] = distances[u] * v.weight;
                        not_processed = true;
                    }
                }
            }
        }
    }
    return distances[start]; 
}

bool arbitrage(ListGraph& graph) {
    for (int i = 0; i < graph.VerticesCount(); i++) {
        double tmp = bellman_ford(graph, i);
        if (tmp > 1) return true;
    }
    return false;
}

int main() {
    int n = 0;
    std::cin >> n;
    ListGraph graph(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) std::cin.ignore();
            else {
                double tmp = 0;
                std::cin >> tmp;
                graph.AddEdge(i, j, tmp);
            }
        }
    }    
    std::cout << ((arbitrage(graph)) ? "YES" : "NO") << '\n';
    return 0;
}
