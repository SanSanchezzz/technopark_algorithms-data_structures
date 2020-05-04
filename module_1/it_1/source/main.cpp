/*В круг выстроено N человек, пронумерованных числами от 1 до N.
 * Будем исключать каждого k-ого до тех пор,
 * пока не уцелеет только один человек.*/

//Например, если N=10, k=3, то сначала умрет 3-й,
//потом 6-й, затем 9-й, затем 2-й, затем 7-й,
//потом 1-й, потом 8-й, за ним - 5-й, и потом 10-й.
//Таким образом, уцелеет 4-й.

//Необходимо определить номер уцелевшего.

//N, k ≤ 10000.

#include <iostream>

int counting(bool *membership, const int memberQty, int step);

int main() {
    int memberQty;
    int counterStep;
    int surviving;
    bool* membership;

    std::cin >> memberQty;
    std::cin >> counterStep;

    membership = new bool[memberQty];

    surviving = counting(membership, memberQty, counterStep);
    std::cout << surviving + 1 << std::endl;

    delete[] membership;

    return 0;
}
int counting(bool *membership, int memberQty, int step) {
    for (int i = 0; i < memberQty; i++) {
        membership[i] = true;
    }

    step--;
    step = step % memberQty;

    int survivingQty = memberQty;
    int counter = 0;
    int idx = 0;

    while (survivingQty != 1) {
        if (idx == memberQty) {
            idx = 0;
        }

        if (membership[idx] == false) {
            idx++;
            continue;
        }

        if (counter == step) {
            membership[idx] = false;
            survivingQty--;
            counter = 0;
            idx++;
        }
        else {
            counter++;
            idx++;
        }
    }

    for (int i = 0; i < memberQty; i++) {
        if (membership[i] == true) {
            return i;
        }
    }

    return -1;
}
