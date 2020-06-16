#ifndef LIST_GRAPH_HPP
#define LIST_GRAPH_HPP

#include "i_graph.hpp"

class ListGraph : public IGraph {
public:
    explicit ListGraph(size_t size);
    explicit ListGraph(const IGraph&);

    void addEdge(size_t from, size_t to) override;

    size_t verticesCount(void) const override;

    std::vector<size_t> getNextVertices(size_t vertex) const override;
    std::vector<size_t> getPrevVertices(size_t vertex) const override;

private:
    std::vector<std::vector<size_t>> vertices;
};

#endif // LIST_GRAPH_HPP
