/*
Дан невзвешенный неориентированный граф. Найдите цикл минимальной длины.

Формат ввода
В первой строке вводятся два натуральных числа N и M, не превосходящих 10000. Далее идут M строк по 2 числа (от 0 до N-1) - индексы вершин между которыми есть ребро.

Формат вывода
Требуется вывести одно целое число равное длине минимального цикла. Если цикла нет, то вывести -1.
*/

#include "graph_implementation/ListGraph.hpp"
#include <iostream> 
#include <vector> 
#include <queue>

ListGraph make_graph() {
    int m = 0;
    int n = 0;
    std::cin >> n >> m;
    ListGraph graph(n);
    for (int i = 0; i < m; i++) {
        int v1 = 0;
        int v2 = 0;
        std::cin >> v1 >> v2;
        graph.AddEdge(v1, v2);
        graph.AddEdge(v2, v1);
    }
    return graph;
}

int BFS(ListGraph& graph, int start) {
  std::vector<char> color(graph.VerticesCount(), 0);
  std::vector<std::pair<int, int>> path(graph.VerticesCount(), {0, 0});
  std::queue<int> to_go;
  int st =-1;
  int end = -1;
  to_go.push(start);
  to_go.push(-1);
  color[start] = 1;
  int level = 1;
  while (!to_go.empty() && st == -1) {
    int u = to_go.front(); to_go.pop();
    if (u == -1) {
      if (!to_go.empty()) to_go.push(-1);
      level++;
      continue;
    }
    for (int v : graph.FindAllAdjacentOut(u)) {
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
    int cycle_lenght = 0;
    if (path[st].second != path[end].second) {
      cycle_lenght += 2;
      st = path[st].first;
    } else cycle_lenght++;
    while(st != end) {
      cycle_lenght += 2;
      st = path[st].first;
      end = path[end].first;
    }
    return cycle_lenght;
  }
}

int find_min_cycle(ListGraph& graph) {
  int ans = -1;
  for (int i = 0; i < graph.VerticesCount(); i++) {
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
