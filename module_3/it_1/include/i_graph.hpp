#ifndef I_GRAPH_HPP
#define I_GRAPH_HPP

#include <iostream>
#include <vector>

struct IGraph {
    virtual ~IGraph() {}

    virtual void addEdge(size_t from, size_t to) = 0;

    virtual size_t verticesCount(void) const = 0;

    virtual std::vector<size_t> getNextVertices(size_t vertex) const = 0;
    virtual std::vector<size_t> getPrevVertices(size_t vertex) const = 0;
};

#endif // I_GRAPH_HPP
