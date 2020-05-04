#include <iostream>

int BinarySearch (int* array, int left, int right);
int FindDelimiter (int* array, int size);

int main() {
    int size, result;
    int* array;

    //std::cout << "Enter the size of the array: ";
    std::cin >> size;

    array = new int[size];

    for (int i = 0; i < size; i++) {
        //std::cout << "Enter " << i << " array element: ";
        std::cin >> array[i];
    }

    result = FindDelimiter(array, size);

    delete[] array;

    //std::cout << "Delimiter = " << array[result] <<", index delimiter = " << result << std::endl;
    std::cout << result << std::endl;

    return 0;
}

int FindDelimiter(int* array, int size) {
    int delimiter = -1;
    int approxDel = 1;

    while (approxDel < size) {
        if (array[approxDel - 1] < array[approxDel]) {
            approxDel *= 2;
        }
        else {
            delimiter = BinarySearch(array, approxDel / 2, approxDel);
            break;
        }
    }
    if (delimiter == -1) {
        delimiter = BinarySearch(array, approxDel / 2 , size);
    }

    return delimiter;
}

int BinarySearch (int* array, int left, int right) {
    int first = left;
    int last = right;
    int middle;

    while ((first + 1) < last) {
        middle = (first + last) / 2;

        if (array[middle - 1] > array[middle]) {
            last = middle;
        }
        else {
            first = middle;
        }
    }

    return first;
}
