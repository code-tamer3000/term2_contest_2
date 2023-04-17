/*
Найти в связном графе остовное дерево минимального веса.

Формат ввода
Первая строка входного файла содержит два натуральных числа n и m — количество вершин и ребер графа соответственно (1 ≤ n ≤ 20000, 0 ≤ m ≤ 100000).
Следующие m строк содержат описание ребер по одному на строке. Ребро номер i описывается тремя натуральными числами bi, ei и wi — номера концов ребра и его вес соответственно (1 ≤ bi, ei ≤ n, 0 ≤ wi ≤ 100000).
Граф является связным.

Формат вывода
Выведите единственное целое число - вес минимального остовного дерева.
*/

#include <iostream>
#include <vector>
#include <queue>


struct WeightedVertex {
  int weight = 0; 
  int vertex = 0;
  WeightedVertex(int weight_, int from_or_to_) : weight(weight_) , vertex(from_or_to_) {}
};

class ListGraph {
 public:
  explicit ListGraph(int  vertices_count);
 
  void AddEdge(int from, int to, int weight);
 
  int VerticesCount() const;
 
  std::vector<WeightedVertex> FindAllAdjacentIn(int vertex) const;
  std::vector<WeightedVertex> FindAllAdjacentOut(int vertex) const;
 
 private:
  std::vector<std::vector<WeightedVertex>> in_edges_;
  std::vector<std::vector<WeightedVertex>> out_edges_;
};

ListGraph::ListGraph(int vertices_count) : in_edges_(vertices_count), out_edges_(vertices_count) {
}

void ListGraph::AddEdge(int from, int to, int weight) {
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

int prim(ListGraph& graph, std::vector<bool>& visited, int start) {
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    pq.push({0, start}); 
    int min_cost = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        int w = pq.top().first;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true; 
        min_cost += w; 

        for (auto v : graph.FindAllAdjacentOut(u)) { 
            if (!visited[v.vertex]) { 
                pq.push({v.weight, v.vertex}); 
            }
        }
    }

    return min_cost;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    ListGraph graph(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        graph.AddEdge(u - 1, v - 1, w); 
        graph.AddEdge(v - 1, u - 1, w);
    }
    std::vector<bool> visited(n);
    int start = 0; 
    int min_cost = prim(graph, visited, start); 

    std::cout << min_cost << '\n';

    return 0;
}
