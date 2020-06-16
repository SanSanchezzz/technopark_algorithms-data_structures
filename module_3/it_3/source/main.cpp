#include <iostream>
#include <limits.h>
#include <vector>
#include <queue>
#include <set>

using Edge = std::pair<int, int>;

class ListGraph {
public:
    explicit ListGraph(size_t size);

    ~ListGraph() {}

    void addEdge(size_t from, size_t to, size_t weight);

    size_t verticesCount(void) const;

    std::vector<Edge> getNextVertices(size_t vertex) const;
    //std::vector<Edge> getPrevVertices(size_t vertex) const;

private:
    size_t size;
    std::vector<std::vector<Edge>> vertices;
};

size_t shortestPath(const ListGraph& graph, size_t from, size_t to);

int main() {
    size_t count_vertices;
    size_t count_edges;

    std::cin >> count_vertices >> count_edges;
    ListGraph graph(count_vertices);

    int from, to, weight;
    for (size_t i = 0; i < count_edges; i++) {
        std::cin >> from >> to >> weight;
        graph.addEdge(from, to, weight);
    }

    std::cin >> from >> to;
    std::cout << shortestPath(graph, from, to) << std::endl;

    return 0;
}

bool relax(size_t u, Edge v, std::vector<int>& weight, std::vector<int>& parents, std::set<std::pair<size_t,size_t>> q) {
    if (weight[v.first] > weight[u] + v.second) {
        q.erase(std::make_pair(v.first, weight[v.first]));
        weight[v.first] = weight[u] + v.second;
        parents[v.first] = u;
        return true;
    }
    else {
        return false;
    }
}

size_t shortestPath(const ListGraph& graph, size_t from, size_t to) {
    std::vector<int> parents(graph.verticesCount(), -1);
    std::vector<int> weight(graph.verticesCount(), INT_MAX);
    std::set<std::pair<size_t,size_t>> q;

    q.emplace(std::make_pair(from, 0));
    weight[from] = 0;

    while (!q.empty()) {
        int v = (q.begin())->second;
        q.erase(q.begin());

        std::vector<Edge> next_vertices = graph.getNextVertices(v);
        for (Edge child : next_vertices) {
            if (weight[child.first] > weight[v] + child.second) {
                if (weight[child.first] != INT_MAX) {
                    q.erase(std::make_pair(child.first, weight[child.first]));
                }
                weight[child.first] = weight[v] + child.second;
                q.emplace(std::make_pair(child.first, weight[child.first]));
            }
        }
    }

    return weight[to];
}

ListGraph::ListGraph(size_t size) : vertices(size) {
}

//ListGraph::~ListGraph() {
    //delete[] vertices;
//}

void ListGraph::addEdge(size_t from, size_t to, size_t weight) {
    vertices[from].push_back(std::make_pair(to, weight));
    vertices[to].push_back(std::make_pair(from, weight));
}

size_t ListGraph::verticesCount(void) const {
    return size;
}

std::vector<Edge> ListGraph::getNextVertices(size_t vertex) const {
    std::vector<Edge> result;

    result.resize(vertices[vertex].size());
    std::copy(vertices[vertex].begin(), vertices[vertex].end(), result.begin());

    return result;
}
