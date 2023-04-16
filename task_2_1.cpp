/*
Дан невзвешенный неориентированный граф. Найдите цикл минимальной длины.

Формат ввода
В первой строке вводятся два натуральных числа N и M, не превосходящих 10000. Далее идут M строк по 2 числа (от 0 до N-1) - индексы вершин между которыми есть ребро.

Формат вывода
Требуется вывести одно целое число равное длине минимального цикла. Если цикла нет, то вывести -1.
*/

#include <iostream> 
#include <vector> 
#include <queue>

class ListGraph {
 public:
  explicit ListGraph(size_t vertices_count);
 
  void AddEdge(size_t from, size_t to);
 
  size_t VerticesCount() const;
 
  std::vector<size_t> FindAllAdjacentIn(size_t vertex) const;
  std::vector<size_t> FindAllAdjacentOut(size_t vertex) const;
 
 private:
  std::vector<std::vector<size_t>> in_edges_;
  std::vector<std::vector<size_t>> out_edges_;
};

ListGraph::ListGraph(size_t vertices_count) : in_edges_(vertices_count), out_edges_(vertices_count) {
}

void ListGraph::AddEdge(size_t from, size_t to) {
  in_edges_[to].push_back(from);
  out_edges_[from].push_back(to);
}
 
size_t ListGraph::VerticesCount() const {
  return in_edges_.size();
}
 
std::vector<size_t> ListGraph::FindAllAdjacentIn(size_t vertex) const {
  return in_edges_[vertex];
}
std::vector<size_t> ListGraph::FindAllAdjacentOut(size_t vertex) const {
  return out_edges_[vertex];
}

ListGraph make_graph() {
    size_t m = 0;
    size_t n = 0;
    std::cin >> n >> m;
    ListGraph graph(n);
    for (size_t i = 0; i < m; i++) {
        size_t v1 = 0;
        size_t v2 = 0;
        std::cin >> v1 >> v2;
        graph.AddEdge(v1, v2);
        graph.AddEdge(v2, v1);
    }
    return graph;
}

size_t BFS(const ListGraph& graph, size_t start) {
  std::vector<char> color(graph.VerticesCount());
  std::vector<std::pair<size_t, size_t>> path(graph.VerticesCount());
  std::queue<size_t > to_go;
  size_t st =-1;
  size_t end = -1;
  to_go.push(start);
  to_go.push(-1);
  color[start] = 1;
  size_t  level = 1;
  while (!to_go.empty() && st == -1) {
    size_t  u = to_go.front(); to_go.pop();
    if (u == -1) {
      if (!to_go.empty()) to_go.push(-1);
      level++;
      continue;
    }
    for (size_t v : graph.FindAllAdjacentOut(u)) {
      if (color[v] == 0) {
        to_go.push(v);
        color[v] = 1;
        path[v] = std::make_pair(u, level);
      } else if (color[v] == 1 && v != u) {
        st = v;
        end = u;
      }
    }
    color[u] = 2;
  }
  if (st == -1) return -1;
  else {
    size_t cycle_length = 0;
    if (path[st].second != path[end].second) {
      cycle_length += 2;
      st = path[st].first;
    } else cycle_length++;
    while(st != end) {
      cycle_length += 2;
      st = path[st].first;
      end = path[end].first;
    }
    return cycle_length;
  }
}

int find_min_cycle(const ListGraph& graph) {
  int ans = -1;
  for (size_t i = 0; i < graph.VerticesCount(); i++) {
    int cycle = BFS(graph, i);
    if (cycle != -1) (ans != -1) ? ans = std::min(ans, cycle) : ans = cycle;
  }
  return ans;
}

int main() {
    ListGraph graph = make_graph();
    std::cout << find_min_cycle(graph) << '\n';
    return 0;
}
