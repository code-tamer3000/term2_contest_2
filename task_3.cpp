/*
Дан ориентированный граф. Определите, какое минимальное число ребер необходимо добавить, чтобы граф стал сильносвязным. В графе возможны петли.

Формат ввода
В первой строке указывается число вершин графа V (макс. 50000), во второй – число ребер E (макс. 200000), в последующих – E пар вершин, задающих ребра.

Формат вывода
Минимальное число ребер k.
*/

#include <iostream> 
#include <memory> 
#include <stack> 
#include <unordered_set> 
#include <vector>
 
class SetGraph {
 public:
  explicit SetGraph(size_t vertices_count);
 
  void AddEdge(size_t from, size_t to);
 
  size_t VerticesCount() const;
 
  std::vector<size_t> FindAllAdjacentIn(size_t vertex) const;
  std::vector<size_t> FindAllAdjacentOut(size_t vertex) const;
 
 private:
  std::vector<std::unordered_set<size_t>> in_edges_;
};

SetGraph::SetGraph(size_t vertices_count) : in_edges_(vertices_count) {
}

void SetGraph::AddEdge(size_t from, size_t to) {
  in_edges_[to].insert(from);
}
 
size_t SetGraph::VerticesCount() const {
  return in_edges_.size();
}
 
std::vector<size_t> SetGraph::FindAllAdjacentIn(size_t vertex) const {
  std::vector<size_t> in(in_edges_[vertex].begin(), in_edges_[vertex].end());
  return in;
}
std::vector<size_t> SetGraph::FindAllAdjacentOut(size_t vertex) const {
  std::vector<size_t> out; 
  for (size_t i = 0; i < in_edges_.size(); i++) {
    if (in_edges_[i].find(vertex) != in_edges_[i].end()) out.push_back(i);
  }
  return out;
}

std::vector<size_t> DefaultDFS(const SetGraph& graph) {
  std::vector<size_t> to_go;
  std::vector<bool> visited(graph.VerticesCount());
  for (size_t s = 0; s < graph.VerticesCount(); ++s) {
    if (!visited[s]) {
      std::stack<size_t> DFSStack;
      DFSStack.push(s);
      visited[s] = true;
      while (!DFSStack.empty()) {
        size_t u = DFSStack.top(); 
        bool already_proccesed = true;
        for (size_t v : graph.FindAllAdjacentOut(u)) {
          if (!visited[v]) {
            visited[v] = true;
            DFSStack.push(v);
            already_proccesed = false;
          }
        }
        if (already_proccesed) {
          to_go.push_back(u);
          DFSStack.pop();
        }
      }
    }
  }
  return to_go;
}

std::unique_ptr<SetGraph> Condense(const SetGraph& graph) {
  std::vector<size_t> to_go = DefaultDFS(graph);
  std::vector<bool> visited(graph.VerticesCount());
  size_t current_component = 0;
  std::vector<size_t> component(graph.VerticesCount());
  for (int i = to_go.size() - 1; i >= 0; --i) {
    if (!visited[to_go[i]]) {
      std::stack<size_t> DFSStack;
      DFSStack.push(to_go[i]);
      visited[to_go[i]] = true;
      while (!DFSStack.empty()) {
        size_t u = DFSStack.top(); 
        bool already_proccesed = true;
        component[u] = current_component;
        for (size_t v : graph.FindAllAdjacentIn(u)) {
          if (!visited[v]) {
            visited[v] = true;
            DFSStack.push(v);
            already_proccesed = false;
          }
        }
        if (already_proccesed) {
          DFSStack.pop();
        }
      }
      ++current_component;
    }
  }
  
  std::unique_ptr<SetGraph> condense = std::make_unique<SetGraph>(current_component);
  for (size_t u = 0; u < graph.VerticesCount(); ++u) {
    for (size_t v : graph.FindAllAdjacentOut(u)) {
      if (component[u] != component[v]) {
        condense->AddEdge(component[u], component[v]);
      }
    }
  }
 
  return condense;
}

size_t NumbeOfAdgesToMakeGraphStronglyConnected(const SetGraph& condense) {
    if (condense.VerticesCount() < 2) return 0;
    int number_of_sinks = 0;
    int number_of_isolated = 0;
    int number_of_sources = 0;
    for (size_t i = 0; i < condense.VerticesCount(); i++) {
        size_t in = condense.FindAllAdjacentIn(i).size();
        size_t out = condense.FindAllAdjacentOut(i).size();
        if (in == 0 && out == 0) number_of_isolated++;
        else if (in == 0 && out != 0) number_of_sources++;
        else if (out == 0 && in != 0) number_of_sinks++;
    }
    return std::max(number_of_isolated + number_of_sources, number_of_isolated + number_of_sinks);
}

SetGraph MakeGraph() {
    int n = 0;
    int m = 0;
    std::cin >> n >> m;
    SetGraph graph(n);
    for (size_t i = 0; i < m; i++) {
        int from = 0;
        int to = 0;
        std::cin >> from >> to;
        graph.AddEdge(from - 1, to - 1);
    }
    return graph;
}

int main() {
  auto graph = MakeGraph();
  auto condense = Condense(graph);
  std::cout << NumbeOfAdgesToMakeGraphStronglyConnected(*condense) << '\n';
  return 0;
}
