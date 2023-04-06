#include "Graph.hpp"
 
#include <vector>
 
class ListGraph : public IGraph {
 public:
  explicit ListGraph(size_t vertices_count);
  explicit ListGraph(const IGraph* other);
 
  void AddEdge(size_t from, size_t to) override;
 
  size_t VerticesCount() const override;
 
  std::vector<size_t> FindAllAdjacentIn(size_t vertex) const override;
  std::vector<size_t> FindAllAdjacentOut(size_t vertex) const override;
 
 private:
  std::vector<std::vector<size_t>> in_edges_;
  std::vector<std::vector<size_t>> out_edges_;
};
