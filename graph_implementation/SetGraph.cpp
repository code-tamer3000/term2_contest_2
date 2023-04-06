 #include "SetGraph.hpp"
 
SetGraph::SetGraph(size_t vertices_count) : in_edges_(vertices_count) {
}
 
SetGraph::SetGraph(const IGraph* other) : in_edges_(other->VerticesCount()) {
  for (size_t i = 0; i < in_edges_.size(); ++i) {
    std::vector<size_t> tmp = other->FindAllAdjacentIn(i);
    for (size_t j : tmp) {
        in_edges_[i].insert(j);
    }
  }
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
