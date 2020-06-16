#include "list_graph.hpp"

ListGraph::ListGraph(size_t size) : vertices(size) {
}

ListGraph::ListGraph(const IGraph& graph)
    : vertices(graph.verticesCount()) {
    for (size_t i = 0; i < vertices.size(); i++) {
        for (size_t v : graph.getNextVertices(i)) {
            this->addEdge(i, v);
        }
    }
}
void ListGraph::addEdge(size_t from, size_t to) {
    vertices[from].push_back(to);
}

size_t ListGraph::verticesCount(void) const {
    return vertices.size();
}

std::vector<size_t> ListGraph::getNextVertices(size_t vertex) const {
    return vertices[vertex];
}

std::vector<size_t> ListGraph::getPrevVertices(size_t vertex) const {
    std::vector<size_t> result;

    for (size_t i = 0; i < vertices.size(); i++) {
        for (size_t v : vertices[i]) {
            if (v == vertex) {
                result.push_back(i);
            }
        }
    }

    return result;
}

