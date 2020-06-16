#ifndef SET_GRAPH_HPP
#define SET_GRAPH_HPP

#include "i_graph.hpp"

#include <unordered_set>

class SetGraph : public IGraph {
public:
    explicit SetGraph(size_t size);
    explicit SetGraph(const IGraph& graph);

    void addEdge(size_t from, size_t to) override;

    size_t verticesCount(void) const override;

    std::vector<size_t> getNextVertices(size_t vertex) const override;
    std::vector<size_t> getPrevVertices(size_t vertex) const override;

private:
    std::vector<std::unordered_set<size_t>> vertices;

};


#endif // SET_GRAPH_HPP
