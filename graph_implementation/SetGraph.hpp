#include "Graph.hpp"

#include <unordered_set> 
#include <vector>
 
class SetGraph : public IGraph {
 public:
  explicit SetGraph(size_t vertices_count);
  explicit SetGraph(const IGraph* other);
 
  void AddEdge(size_t from, size_t to) override;
 
  size_t VerticesCount() const override;
 
  std::vector<size_t> FindAllAdjacentIn(size_t vertex) const override;
  std::vector<size_t> FindAllAdjacentOut(size_t vertex) const override;
 
 private:
  std::vector<std::unordered_set<size_t>> in_edges_;
};
