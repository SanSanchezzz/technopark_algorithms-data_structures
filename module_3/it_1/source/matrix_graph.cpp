#include "matrix_graph.hpp"

MatrixGraph::MatrixGraph(size_t size)
    : count_vertices(size), vertices(size) {
    for (size_t i = 0; i < size; i++) {
        vertices[i].assign(size, false);
    }
}

MatrixGraph::MatrixGraph(const IGraph& graph) : MatrixGraph(graph.verticesCount()) {
    for (size_t i = 0; i < count_vertices; i++) {
        vertices[i].assign(count_vertices, false);
    }

    for (size_t i = 0; i < count_vertices; i++) {
        for (size_t v : graph.getNextVertices(i)) {
            this->addEdge(i, v);
        }
    }
}

size_t MatrixGraph::verticesCount(void) const {
    return count_vertices;
}

void MatrixGraph::addEdge(size_t from, size_t to) {
    vertices[from][to] = true;
}

std::vector<size_t> MatrixGraph::getNextVertices(size_t vertex) const {
    std::vector<size_t> result;

    for (size_t i = 0; i < count_vertices; i++) {
        if (vertices[vertex][i]) {
            result.push_back(i);
        }
    }

    return result;
}

std::vector<size_t> MatrixGraph::getPrevVertices(size_t vertex) const {
    std::vector<size_t> result;

    for (size_t i = 0; i < count_vertices; i++) {
        if (vertices[vertex][i]) {
            result.push_back(i);
        }
    }

    return result;
}

