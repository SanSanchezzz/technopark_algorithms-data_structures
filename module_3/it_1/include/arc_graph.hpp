#ifndef ARC_GRAPH_HPP
#define ARC_GRAPH_HPP

#include "i_graph.hpp"

class ArcGraph : public IGraph {
public:
    explicit ArcGraph(size_t size);
    explicit ArcGraph(const IGraph&);

    void addEdge(size_t from, size_t to) override;

    size_t verticesCount(void) const override;

    std::vector<size_t> getNextVertices(size_t vertex) const override;
    std::vector<size_t> getPrevVertices(size_t vertex) const override;

private:
    size_t count_vertices;
    std::vector<std::pair<size_t, size_t>> vertices;
};

#endif // ARC_GRAPH_HPP
