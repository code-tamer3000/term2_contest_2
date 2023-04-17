/*
Требуется отыскать самый короткий маршрут между городами. Из города может выходить дорога, которая возвращается в этот же город.

Требуемое время работы O((N + M)log N), где N – количество городов, M – известных дорог между ними.
N ≤ 10000, M ≤ 250000.
Длина каждой дороги ≤ 10000.

Формат ввода
Первая строка содержит число N – количество городов.

Вторая строка содержит число M - количество дорог.

Каждая следующая строка содержит описание дороги (откуда, куда, время в пути). Все указанные дороги двусторонние. Между любыми двумя городами может быть больше одной дороги.

Последняя строка содержит маршрут (откуда и куда нужно доехать).

Формат вывода
Вывести длину самого короткого маршрута.
*/

#include <iostream> 
#include <vector> 
#include <limits.h>
#include <set>

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

struct PriorityQueue {
 public:
  void Push(int v, int distance);
  int Pop();
  void DecreaseKey(int v, int old_distance, int distance);
  bool Empty() {return distances_and_vertices.empty();} 
 
 private:
  std::set<std::pair<int, int>> distances_and_vertices;
};
 
void PriorityQueue::Push(int v, int distance) {
  distances_and_vertices.insert({distance, v});
}

int PriorityQueue::Pop() {
  auto it = distances_and_vertices.begin();
  int result = it->second;
  distances_and_vertices.erase(it);
  return result;
}

void PriorityQueue::DecreaseKey(int v, int old_distance, int distance) {
  distances_and_vertices.erase({old_distance, v});
  distances_and_vertices.insert({distance, v});
}

int Dijkstra(ListGraph& graph, int start, int finish) {
  std::vector<int> distances(graph.VerticesCount(), INT_MAX);
  distances[start] = 0;
  PriorityQueue q;
  q.Push(start, 0);
  while (!q.Empty()) {
    int u = q.Pop();
    for (auto v : graph.FindAllAdjacentOut(u)) {
      if (distances[v.vertex] == INT_MAX) q.Push(v.vertex, distances[v.vertex]);
      if (distances[v.vertex] > distances[u] + v.weight) {
        q.DecreaseKey(v.vertex, distances[v.vertex], distances[u] + v.weight);
        distances[v.vertex] = distances[u] + v.weight;
      }
    }
  }
  return distances[finish];
}

ListGraph MakeGraph() {
    int n = 0;
    int m = 0;
    std::cin >> n >> m;
    ListGraph graph(n);
    for (size_t i = 0; i < m; i++) {
        int from = 0;
        int to = 0;
        int weight = 0;
        std::cin >> from >> to >> weight;
        graph.AddEdge(from, to, weight);
        graph.AddEdge(to, from, weight);
    }
    return graph;
}

int main() {
  ListGraph graph = MakeGraph();
  int start = 0; 
  int finish = 0; 
  std::cin >> start >> finish;
  std::cout << Dijkstra(graph, start, finish) << '\n';
}
