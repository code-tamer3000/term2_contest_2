 
#include "ListGraph.hpp"
 
ListGraph::ListGraph(size_t vertices_count) : in_edges_(vertices_count), out_edges_(vertices_count) {
}
 
ListGraph::ListGraph(const IGraph* other) : in_edges_(other->VerticesCount()), out_edges_(other->VerticesCount()) {
  for (size_t i = 0; i < in_edges_.size(); ++i) {
    in_edges_[i] = other->FindAllAdjacentIn(i);
    out_edges_[i] = other->FindAllAdjacentOut(i);
  }
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
