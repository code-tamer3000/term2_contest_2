#include "Graph.hpp"
 
#include <vector>
 
class ArcGraph : public IGraph {
 public:
  explicit ArcGraph(size_t vertices_count);
  explicit ArcGraph(const IGraph* other);
  
  void AddEdge(size_t from, size_t to) override;
 
  size_t VerticesCount() const override;
 
  std::vector<size_t> FindAllAdjacentIn(size_t vertex) const override;
  std::vector<size_t> FindAllAdjacentOut(size_t vertex) const override;
 
 private:
 size_t size = 0;
  struct Arc {
    size_t from = 0;
    size_t to = 0;
    Arc(size_t from_, size_t to_);
    Arc() = default;
  };
  std::vector<Arc> edges;
};
