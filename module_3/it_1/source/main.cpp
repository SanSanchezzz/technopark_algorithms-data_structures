#include <iostream>

#include "matrix_graph.hpp"
#include "list_graph.hpp"
#include "arc_graph.hpp"
#include "set_graph.hpp"

int main() {
    MatrixGraph sg(5);

    sg.addEdge(0, 1);
    sg.addEdge(0, 4);
    sg.addEdge(0, 3);
    sg.addEdge(1, 2);
    sg.addEdge(2, 3);
    sg.addEdge(3, 4);
    sg.addEdge(4, 0);
    sg.addEdge(4, 1);


    ListGraph lg(sg);
    MatrixGraph mg(lg);
    ArcGraph ag(mg);

    for (size_t i = 0; i < lg.verticesCount(); i++) {
        for (size_t v : ag.getNextVertices(i)) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Hello, world!" << std::endl;

    return 0;
}
