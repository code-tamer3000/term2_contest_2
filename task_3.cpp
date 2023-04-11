/*
Дан ориентированный граф. Определите, какое минимальное число ребер необходимо добавить, чтобы граф стал сильносвязным. В графе возможны петли.

Формат ввода
В первой строке указывается число вершин графа V (макс. 50000), во второй – число ребер E (макс. 200000), в последующих – E пар вершин, задающих ребра.

Формат вывода
Минимальное число ребер k.
*/

#include <iostream> 
#include <memory> 
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

void DFSReverseRecursive(size_t u, const SetGraph& graph, std::vector<bool>& visited, std::vector<size_t>& to_go) {
  visited[u] = true;
  for (size_t v : graph.FindAllAdjacentIn(u)) {
    if (!visited[v]) DFSReverseRecursive(v, graph, visited, to_go);
  }
  to_go.push_back(u);
}
 
std::vector<size_t> DFSReverse(const SetGraph& graph) {
  std::vector<size_t> to_go;
  std::vector<bool> visited(graph.VerticesCount());
  for (size_t s = 0; s < graph.VerticesCount(); ++s) {
    if (!visited[s]) DFSReverseRecursive(s, graph, visited, to_go);
  }
  return to_go;
}

void DFSCondense(size_t u, const SetGraph& graph, std::vector<bool>& visited, std::vector<size_t>& component, size_t current_component) {
  visited[u] = true;
  component[u] = current_component;
  for (int v : graph.FindAllAdjacentOut(u)) {
    if (!visited[v])
      DFSCondense(v, graph, visited, component, current_component);
  }
}

std::unique_ptr<SetGraph> Condense(const SetGraph& graph) {
  std::vector<size_t> to_go = DFSReverse(graph);
  std::vector<bool> visited(graph.VerticesCount());
  size_t current_component = 0;
  std::vector<size_t> component(graph.VerticesCount());
  for (int i = to_go.size() - 1; i >= 0; --i) {
    if (!visited[to_go[i]]) {
      DFSCondense(to_go[i], graph, visited, component, current_component);
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
    int number_of_stocks = 0;
    int number_of_isolated = 0;
    int number_of_sourses = 0;
    for (size_t i = 0; i < condense.VerticesCount(); i++) {
        size_t in = condense.FindAllAdjacentIn(i).size();
        size_t out = condense.FindAllAdjacentOut(i).size();
        if (in == 0 && out == 0) number_of_isolated++;
        else if (in == 0 && out != 0) number_of_sourses++;
        else if (out == 0 && in != 0) number_of_stocks++;
    }
    return std::max(number_of_isolated + number_of_sourses, number_of_isolated + number_of_stocks);
}

std::unique_ptr<SetGraph> MakeGraph() {
    int n = 0;
    int m = 0;
    std::cin >> n >> m;
    std::unique_ptr<SetGraph> graph = std::make_unique<SetGraph>(n);
    for (size_t i = 0; i < m; i++) {
        int from = 0;
        int to = 0;
        std::cin >> from >> to;
        graph->AddEdge(from - 1, to - 1);
    }
    return graph;
}

int main() {
  auto graph = MakeGraph();
  auto condense = Condense(*graph);
  std::cout << NumbeOfAdgesToMakeGraphStronglyConnected(*condense) << '\n';
  return 0;
}
