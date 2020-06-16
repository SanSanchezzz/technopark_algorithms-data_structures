#include "set_graph.hpp"

SetGraph::SetGraph(size_t size) : vertices(size) {
}

SetGraph::SetGraph(const IGraph& graph) : vertices(graph.verticesCount()) {
    for (size_t i = 0; i < vertices.size(); i++) {
        for (size_t v : graph.getNextVertices(i)) {
            this->addEdge(i, v);
        }
    }
}

void SetGraph::addEdge(size_t from, size_t to) {
    vertices[from].insert(to);
}

size_t SetGraph::verticesCount(void) const {
    return vertices.size();
}

std::vector<size_t> SetGraph::getNextVertices(size_t vertex) const {
    std::vector<size_t> result;

    for (size_t v : vertices[vertex]) {
        result.push_back(v);
    }

    return result;
}

std::vector<size_t> SetGraph::getPrevVertices(size_t vertex) const {
    std::vector<size_t> result;

    for (size_t i = 0; i < vertices.size(); i++) {
        if (vertices[i].count(vertex) > 0) {
            result.push_back(i);
        }
    }

    return result;
}
