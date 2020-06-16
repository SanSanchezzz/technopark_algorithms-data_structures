#ifndef MATRIX_GRAPH_HPP
#define MATRIX_GRAPH_HPP

#include "i_graph.hpp"

class MatrixGraph : public IGraph {
public:
    explicit MatrixGraph(size_t size);
    explicit MatrixGraph(const IGraph&);

    void addEdge(size_t from, size_t to) override;

    size_t verticesCount(void) const override;

    std::vector<size_t> getNextVertices(size_t vertex) const override;
    std::vector<size_t> getPrevVertices(size_t vertex) const override;

private:
    size_t count_vertices;
    std::vector<std::vector<bool>> vertices;
};

#endif // MATRIX_GRAPH_HPP
