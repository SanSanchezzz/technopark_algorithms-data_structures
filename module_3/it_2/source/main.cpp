#include <iostream>
#include <limits.h>
#include <vector>
#include <queue>

class ListGraph {
public:
    explicit ListGraph(size_t size);

    virtual ~ListGraph() {}

    void addEdge(size_t from, size_t to);

    size_t verticesCount(void) const;

    std::vector<size_t> getNextVertices(size_t vertex) const;
    std::vector<size_t> getPrevVertices(size_t vertex) const;

private:
    std::vector<std::vector<size_t>> vertices;
};

size_t differentPaths(const ListGraph& graph, size_t from, size_t to);

int main() {
    size_t count_vertices;
    size_t count_edges;

    std::cin >> count_vertices >> count_edges;
    ListGraph graph(count_vertices);

    size_t from, to;
    for (size_t i = 0; i < count_edges; i++) {
        std::cin >> from >> to;
        graph.addEdge(from, to);
    }

    std::cin >> from >> to;
    std::cout << differentPaths(graph, from, to) << std::endl;

    return 0;
}

size_t differentPaths(const ListGraph& graph, size_t from, size_t to) {
    std::vector<size_t> paths_count(graph.verticesCount(), 0);
    std::vector<size_t> weight(graph.verticesCount(), 0);
    std::queue<size_t> q;

    q.push(from);
    paths_count[from] = 1;

    while (!q.empty()) {
        size_t v = q.front();
        q.pop();

        std::vector<size_t> next_vertices = graph.getNextVertices(v);
        for (size_t child : next_vertices) {
            if (paths_count[child] == 0) {
                paths_count[child] = paths_count[v];
                weight[child] = weight[v] + 1;
                q.push(child);
            }
            else if (weight[child] == (weight[v] + 1)) {
                paths_count[child] += paths_count[v];
            }
        }
    }

    return paths_count[to];
}

ListGraph::ListGraph(size_t size) : vertices(size) {
}

void ListGraph::addEdge(size_t from, size_t to) {
    vertices[from].push_back(to);
    vertices[to].push_back(from);
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
