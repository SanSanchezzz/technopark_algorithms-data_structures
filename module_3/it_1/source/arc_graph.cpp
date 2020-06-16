#include "arc_graph.hpp"

ArcGraph::ArcGraph(size_t size) : count_vertices(size) {
}

ArcGraph::ArcGraph(const IGraph& graph) : count_vertices(graph.verticesCount()) {
    for (size_t i = 0; i < count_vertices; i++) {
        for (size_t v : graph.getNextVertices(i)) {
            this->addEdge(i, v);
        }
    }
}

void ArcGraph::addEdge(size_t from, size_t to) {
    vertices.push_back(std::make_pair(from, to));
}

size_t ArcGraph::verticesCount(void) const {
    return count_vertices;
}

std::vector<size_t> ArcGraph::getNextVertices(size_t vertex) const {
    std::vector<size_t> result;

    for (size_t i = 0; i < vertices.size(); i++) {
        if (vertices[i].first == vertex) {
            result.push_back(vertices[i].second);
        }
    }

    return result;
}

std::vector<size_t> ArcGraph::getPrevVertices(size_t vertex) const {
    std::vector<size_t> result;

    for (size_t i = 0; i < vertices.size(); i++) {
        if (vertices[i].second == vertex) {
            result.push_back(vertices[i].first);
        }
    }

    return result;
}
