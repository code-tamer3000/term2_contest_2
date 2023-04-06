#include <iostream>
#include <vector>
#include <algorithm>
 
#include "ListGraph.hpp"
#include "MatrixGraph.hpp"
#include "SetGraph.hpp"
#include "ArcGraph.hpp"

void fill_graph_edges(IGraph& graph) {
  for (size_t i = 0; i < graph.VerticesCount(); i++) {
    for (size_t j = 0; j < graph.VerticesCount(); j++) {
      size_t chance = rand() % 4;
      if (chance == 3) {
        if (i != j) {
          graph.AddEdge(i , j);
        }
      }
    }
  }
}

size_t get_middle_value(std::vector<size_t>& nums) {
  size_t sum = 0;
  for (size_t i : nums) sum += i;
  return (sum / nums.size());
}

void get_statistic(IGraph& graph) {
  std::vector<size_t> vertex_degree(graph.VerticesCount());
  for (size_t i = 0; i < vertex_degree.size(); i++) {
    vertex_degree[i] = graph.FindAllAdjacentIn(i).size() + graph.FindAllAdjacentOut(i).size();
  }
  std::cout << "min: " << *std::min_element(vertex_degree.begin(), vertex_degree.end()) << ' ';
  std::cout << "average: " << get_middle_value(vertex_degree) << ' ';
  std::cout << "max: " << *std::max_element(vertex_degree.begin(), vertex_degree.end()) << '\n';
}
 
int main() {
  unsigned int seed = time(nullptr);
	srand(seed);

  ListGraph list(1000);
  fill_graph_edges(list);

  MatrixGraph matrix(1000);
  fill_graph_edges(matrix);

  SetGraph set(1000);
  fill_graph_edges(set);

  ArcGraph arc(1000);
  fill_graph_edges(arc);
  
  MatrixGraph from_list_to_matrix(&list);
  SetGraph from_list_to_set(&list);
  ArcGraph from_list_to_arc(&list);

  ListGraph from_matrix_to_list(&matrix);
  SetGraph from_matrix_to_set(&matrix);
  ArcGraph from_matrix_to_arc(&matrix);

  ListGraph from_set_to_list(&set);
  MatrixGraph from_set_to_matrix(&set);
  ArcGraph from_set_to_arc(&set);

  ListGraph from_arc_to_list(&arc);
  MatrixGraph from_arc_to_matrix(&arc);
  SetGraph from_arc_to_set(&arc);
  
  std::cout << "list graph statistic: " << '\n';
  get_statistic(list);
  std::cout << "set graph statistic: " << '\n';
  get_statistic(set);
  std::cout << "matrix graph statistic: " << '\n';
  get_statistic(matrix);
  std::cout << "arc graph statistic: " << '\n';
  get_statistic(arc);

  return 0;
}
