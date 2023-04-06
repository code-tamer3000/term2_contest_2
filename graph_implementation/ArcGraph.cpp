#include <iostream>
#include "ArcGraph.hpp"
 
ArcGraph::ArcGraph(size_t vertices_count) : size(vertices_count) {
}

ArcGraph::Arc::Arc(size_t from_, size_t to_) : from(from_) , to(to_) {}

ArcGraph::ArcGraph(const IGraph* other) : size(other->VerticesCount()) {
  for (size_t i = 0; i < size; ++i) {
    std::vector<size_t> in_tmp = other->FindAllAdjacentIn(i);
    std::vector<size_t> out_tmp = other->FindAllAdjacentOut(i);
    for (size_t j : in_tmp) {
        edges.push_back(Arc(j, i));
    }
    for (size_t j : out_tmp) {
        edges.push_back(Arc(i, j));
    }
  }
}
 
void ArcGraph::AddEdge(size_t from, size_t to) {
  edges.push_back(Arc(from, to));
}
 
size_t ArcGraph::VerticesCount() const {
  return size;
}
 
std::vector<size_t> ArcGraph::FindAllAdjacentIn(size_t vertex) const {
  std::vector<size_t> in; 
  for (auto i : edges) {
    if (i.to == vertex) in.push_back(i.from);
  };
  return in;
}
std::vector<size_t> ArcGraph::FindAllAdjacentOut(size_t vertex) const {
  std::vector<size_t> out; 
  for (auto i : edges) {
    if (i.from == vertex) out.push_back(i.to);
  };
  return out;
}
