#pragma once
 
#include <vector>
 
struct IGraph {
  virtual ~IGraph() = default;
 
  virtual void AddEdge(size_t from, size_t to) = 0;
 
  virtual size_t VerticesCount() const = 0;
 
  virtual std::vector<size_t> FindAllAdjacentIn(size_t vertex) const = 0;
  virtual std::vector<size_t> FindAllAdjacentOut(size_t vertex) const = 0;
};
