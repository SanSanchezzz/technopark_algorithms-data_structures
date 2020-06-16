#include <iostream>
#include <limits.h>
#include <unordered_set>
#include <vector>
#include <queue>
#include <set>

using TmpEdge = std::pair<int, int>;
struct Edge {
    size_t from;
    size_t to;
    size_t weight;

    Edge(size_t from, size_t to, size_t weight)
        : from(from), to(to), weight(weight) {}
};

class ArcGraph {
public:
    explicit ArcGraph(size_t size);

    void addEdge(size_t from, size_t to, size_t weight);

    size_t verticesCount(void) const;

    std::vector<TmpEdge> getNextVertices(size_t vertex) const;
    //std::vector<size_t> getPrevVertices(size_t vertex) const;

private:
    size_t count_vertices;
    std::vector<Edge> vertices;
};


size_t shortestPath(const ArcGraph& graph, size_t from, size_t to);

int main() {
    size_t count_vertices;
    size_t count_edges;

    std::cin >> count_vertices >> count_edges;
    ArcGraph graph(count_vertices);

    int from, to, weight;
    for (size_t i = 0; i < count_edges; i++) {
        std::cin >> from >> to >> weight;
        graph.addEdge(from, to, weight);
    }

    std::cin >> from >> to;
    std::cout << shortestPath(graph, from, to) << std::endl;

    return 0;
}

bool relax(size_t u, TmpEdge v, std::vector<int>& weight, std::vector<int>& parents, std::set<std::pair<size_t,size_t>> q) {
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

size_t shortestPath(const ArcGraph& graph, size_t from, size_t to) {
    std::vector<int> parents(graph.verticesCount(), -1);
    std::vector<int> weight(graph.verticesCount(), INT_MAX);
    std::set<std::pair<size_t,size_t>> q;
    std::cout << "result = ";
    q.emplace(std::make_pair(from, 0));
    weight[from] = 0;
    while (!q.empty()) {
        int v = (q.begin())->second;
        q.erase(q.begin());

        std::vector<TmpEdge> next_vertices = graph.getNextVertices(v);
        for (TmpEdge child : next_vertices) {
            if (weight[child.first] > weight[v] + child.second) {
                if (weight[child.first] != INT_MAX) {
                    q.erase(std::make_pair(child.first, weight[child.first]));
                }
                weight[child.first] = weight[v] + child.second;
                q.emplace(std::make_pair(child.first, weight[child.first]));
            }
        }
    }
/*    while (!q.empty()) {*/
        //int v = (q.begin())->first;
        //q.erase(q.begin());

        //std::vector<TmpEdge> next_vertices = graph.getNextVertices(v);
        //for (TmpEdge child : next_vertices) {
            //if (weight[child.first] == INT_MAX) {
                //weight[child.first] = weight[v] + child.second;
                //parents[child.first] = v;
                //q.emplace(std::make_pair(child.first, weight[child.first]));
            //}
            //else if (relax(v, child, weight, parents, q)) {
                //q.emplace(std::make_pair(child.first, weight[child.first]));
            //}
        //}
    //}

    return weight[to];
}

ArcGraph::ArcGraph(size_t size) : count_vertices(size) {
}

void ArcGraph::addEdge(size_t from, size_t to, size_t weight) {
    vertices.push_back(Edge(from, to, weight));
}

size_t ArcGraph::verticesCount(void) const {
    return count_vertices;
}

std::vector<TmpEdge> ArcGraph::getNextVertices(size_t vertex) const {
    std::vector<TmpEdge> result;

    for (size_t i = 0; i < vertices.size(); i++) {
        if (vertices[i].from == vertex) {
            result.push_back(std::make_pair(vertices[i].to, vertices[i].weight));
        }
        else if (vertices[i].to == vertex) {
            result.push_back(std::make_pair(vertices[i].from, vertices[i].weight));
        }
    }

    return result;
}

//std::vector<size_t> ArcGraph::getPrevVertices(size_t vertex) const {
    //std::vector<size_t> result;

    //for (size_t i = 0; i < vertices.size(); i++) {
        //if (vertices[i].second == vertex) {
            //result.push_back(vertices[i].first);
        //}
    //}

    //return result;
/*}*/
