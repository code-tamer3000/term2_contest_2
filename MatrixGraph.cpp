#include "MatrixGraph.hpp"
 
MatrixGraph::MatrixGraph(size_t vertices_count) : matrix(std::vector<std::vector<bool>> (vertices_count, std::vector<bool> (vertices_count, false))) {}
 
MatrixGraph::MatrixGraph(const IGraph* other) : matrix(std::vector<std::vector<bool>> (other->VerticesCount(), std::vector<bool> (other->VerticesCount(), false))) {
  for (size_t i = 0; i < matrix.size(); ++i) {
    std::vector<size_t> in_tmp = other->FindAllAdjacentIn(i);
    std::vector<size_t> out_tmp = other->FindAllAdjacentOut(i);
    for (size_t j : in_tmp) {
        matrix[j][i] = true;
    }
    for (size_t j : out_tmp) {
        matrix[i][j] = true;
    }
  }
}
 
void MatrixGraph::AddEdge(size_t from, size_t to) {
  matrix[from][to] = true;
}
 
size_t MatrixGraph::VerticesCount() const {
  return matrix.size();
}
 
std::vector<size_t> MatrixGraph::FindAllAdjacentIn(size_t vertex) const {
  std::vector<size_t> in;
  for (size_t i = 0; i < matrix.size(); i++) {
    if (matrix[i][vertex]) in.push_back(i);
  }
  return in;
}
std::vector<size_t> MatrixGraph::FindAllAdjacentOut(size_t vertex) const {
  std::vector<size_t> out;
  for (size_t i = 0; i < matrix.size(); i++) {
    if (matrix[vertex][i]) out.push_back(i);
  }
  return out;
}
