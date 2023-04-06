#include "Graph.hpp"
 
#include <vector>
 
class MatrixGraph : public IGraph {
 public:
  explicit MatrixGraph(size_t vertices_count);
  explicit MatrixGraph(const IGraph* other);
 
  void AddEdge(size_t from, size_t to) override;
 
  size_t VerticesCount() const override;
 
  std::vector<size_t> FindAllAdjacentIn(size_t vertex) const override;
  std::vector<size_t> FindAllAdjacentOut(size_t vertex) const override;
 
 private:
  std::vector<std::vector<bool>> matrix;
};
 