#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;


// ===================== AUXILLARY FUNCTIONS =======================

vector <int> createSortedVec(int size) {
    vector <int> vec(size);
    for (int i = 0; i < size; ++i) {
        vec[i] = i;
    }
    return vec;
}

vector <int> createAlmostSortedVec(int size) {
    vector <int> vec(size);
    for (int i = 0; i < size; i++) {
        vec[i] = i;
    }
    for (int i = 0; i < size/10; i++) {
        int index1 = rand() % size;
        int index2 = rand() % size;
        swap(vec[index1], vec[index2]);
    }
    return vec;
}

vector <int> createReverseSortedVec(int size) {
    vector <int> vec(size);
    int j = size;
    for (int i = 0; i < size; i++) {
        vec[i] = size;
        j--;
    }
    return vec;
}

vector <int> createRandomVec(int size) {
    vector <int> vec(size);
    for (int i = 0; i < size; ++i) {
        vec[i] = rand() % 1000;
    }
    return vec;
}

int findMin(vector <int> vec, int i) {
    int minElem = vec[i];
    int minIndex = i;
    for (int l = i + 1; l < vec.size(); l++) {
        if (vec[l] < minElem) {
            minElem = vec[l];
            minIndex = l;
        }
    }
    return minIndex;
}

void VecFill(vector <int> &vec) {
    unsigned int i = 0;
    while (i != vec.size()) {
        vec[i] = rand() % 1000;
        i++;
    }
}

void VecShow(vector <int> vec) {
    unsigned int i = 0;
    while (i != vec.size()) {
        cout << vec[i] << '\n';
        i++;
    }
}

vector <int> merge(vector <int> vec1, vector <int> vec2) {
    int i = 0, j = 0, k = 0;
    vector <int> vecResult;
    vecResult.resize(vec1.size() + vec2.size());
    while (i < vec1.size() and j < vec2.size()) {
        if (vec1[i] < vec2[j]) {
            vecResult[k] = vec1[i];
            i++;
        }
        else {
            vecResult[k] = vec2[j];
            j++;
        }
        k++;
    }
    while (i < vec1.size()) {
        vecResult[k] = vec1[i];
        i++;
        k++;
    }
    while (j < vec2.size()) {
        vecResult[k] = vec2[j];
        j++;
        k++;
    }
    return vecResult;
}

vector <int> uniteVector_forQS(vector<int> vec1, vector<int> vec2) {
    for (int element : vec2) {
        vec1.push_back(element);
    }
    return vec1;
}

void heapify(vector <int>& vec, int vecSize, int i)
{
    int root = i;//Ставим наибольший элемент последним
    int left = 2 * i + 1; // левый
    int right = 2 * i + 2; // правый
    if (left < vecSize and vec[left] > vec[root])
    {
        root = left;
    }
    if (right < vecSize and vec[right] > vec[root])
    {
        root = right;
    }
    if (root != i)
    {
        swap(vec[i], vec[root]);
        heapify(vec, vecSize, root);
    }
}

// ===================== SORTING FUNCTIONS =========================

vector <int> selectionSort(vector<int> vec) {
    int n = vec.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (vec[j] < vec[minIndex]) {
                minIndex = j;
            }
        }
        swap(vec[i], vec[minIndex]);
    }
    return vec;
}

vector <int> insertionSort(vector <int> vec) {
    for (int i = 1; i < vec.size(); i++) {
        for (int j = i; j > 0; j--) {
            if (vec[j] < vec[j - 1])
                swap(vec[j - 1], vec[j]);
            else
                break;
        }
    }
    return vec;
}

vector <int> bubbleSort(vector<int> vec) {
    for (int i = 0; i < vec.size() - 1; ++i) {
        for (int j = 0; j < vec.size() - i - 1; ++j) {
            if (vec[j] > vec[j + 1]) {
                swap(vec[j], vec[j + 1]);
            }
        }
    }
    return vec;
}

vector <int> mergeSort(vector <int> vec) {
    if (vec.size() == 1) {
        return vec;
    }
    else {
        vector <int> vecFirstHalf, vecSecondHalf;
        for (int i = 0; i < vec.size(); i++) {
            if (i < vec.size() / 2)
                vecFirstHalf.push_back(vec[i]);
            else
                vecSecondHalf.push_back(vec[i]);
        }
        return merge(mergeSort(vecFirstHalf), mergeSort(vecSecondHalf));
    }
}

vector <int> quickSort(vector<int> vec) {
    if (vec.size() == 0) {
        return vec;
    }
    else {
        int pivot = vec[vec.size() / 2]; // опорный элемент
        vector<int> vecLessThanPivot; // элементы меньше опорного
        vector<int> vecPivot; // элементы равные опорному
        vector<int> vecBiggerThanPivot; // элементы больше опорного
        for (int i = 0; i < vec.size(); i++) {
            if (vec[i] < pivot) {
                vecLessThanPivot.push_back(vec[i]);
            }
            else if (vec[i] == pivot) {
                vecPivot.push_back(vec[i]);
            }
            else {
                vecBiggerThanPivot.push_back(vec[i]);
            }
        }
        return uniteVector_forQS(uniteVector_forQS(quickSort(vecLessThanPivot), vecPivot), quickSort(vecBiggerThanPivot));
    }
}

vector <int> heapSort(vector <int> vec)//heap sort
{
    for (int i = vec.size() / 2 - 1; i >= 0; i--)
        heapify(vec, vec.size(), i);

    for (int i = vec.size() - 1; i >= 0; i--)
    {
        swap(vec[0], vec[i]);

        heapify(vec, i, 0);
    }
    return vec;
}

vector <int> shellSort(vector<int> vec) {
    int n = vec.size();

    // Начинаем с большого шага и уменьшаем его
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // Сортировка вставками для элементов, разделенных шагом gap
        for (int i = gap; i < vec.size(); ++i) {
            int temp = vec[i]; // текущий элемент
            int j;

            // Сдвигаем элементы, которые больше текущего, на шаг gap вправо
            for (j = i; j >= gap && vec[j - gap] > temp; j -= gap) {
                vec[j] = vec[j - gap]; // Сдвиг
            }

            // Вставляем текущий элемент на правильное место
            vec[j] = temp;
        }
    }
    return vec;
}

vector <int> shellSortHibbard(vector<int> vec) {
    vector<int> gaps;

    // Генерируем последовательность Хиббарда: 2^k - 1
    for (int k = 1; (1 << k) - 1 < vec.size(); ++k) {
        gaps.push_back((1 << k) - 1); // 1 << k - это 2^k
    }
    reverse(gaps.begin(), gaps.end()); // Начинаем с больших промежутков

    // Сортировка с использованием промежутков Хиббарда
    for (int gap : gaps) {
        for (int i = gap; i < vec.size(); ++i) {
            int temp = vec[i];
            int j;
            for (j = i; j >= gap && vec[j - gap] > temp; j -= gap) {
                vec[j] = vec[j - gap];
            }
            vec[j] = temp;
        }
    }
    return vec;
}

vector <int> shellSortPratt(vector <int> vec, int len, vector <int>& gaps)
{
    int element, i, j;
    int gap;
    for (int gaps_size = gaps.size() - 1; gaps_size >= 0; gaps_size--)
    {
        gap = gaps[gaps_size];
        for (i = gap; i < len; i++)
        {
            element = vec[i];
            for (j = i; j >= gap and vec[j - gap] > element; j -= gap)
            {
                vec[j] = vec[j - gap];
            }
            vec[j] = element;
        }
    }
    return vec;
}

// ==================== OUTPUT FUNCTIONS ======================

void chooseSort(vector <int> vec, int sortType) {
    switch (sortType) {
    case 1:
        vec = selectionSort(vec);
        break;
    case 2:
        vec = insertionSort(vec);
        break;
    case 3:
        vec = bubbleSort(vec);
        break;
    case 4:
        vec = mergeSort(vec);
        break;
    case 5:
        vec = quickSort(vec);
        break;
    case 6:
        vec = heapSort(vec);
        break;
    case 7:
        vec = shellSort(vec);
        break;
    case 8:
        vec = shellSortHibbard(vec);
        break;
    case 9:
        vector<int> gaps;
        for (int i = 1; i <= vec.size(); i *= 2)
        {
            for (int j = i; j <= vec.size(); j *= 3)
            {
                gaps.push_back(j);
            }
        }
        vec = shellSortPratt(vec, vec.size(), gaps);
        break;
    }
}

string chooseFile(int sortType) {
    switch (sortType) {
    case 1:
        return "sel.txt";
    case 2:
        return "ins.txt";
    case 3:
        return "bub.txt";
    case 4:
        return "mer.txt";
    case 5:
        return "qui.txt";
    case 6:
        return "hea.txt";
    case 7:
        return "she.txt";
    case 8:
        return "hib.txt";
    case 9:
        return "pra.txt";
    }
}

void menu() {
    vector <string> sortNames{ "Selection sort", "Insertion sort", "Bubble sort", "Merge sort","Quick sort","Heap sort","Shell sort","Shell-Hibbard sort","Shell-Pratt sort" };
    vector <int> vec;
    cout << "What sorting method do you want to see in action?\n";
    for (int i = 0; i < sortNames.size(); i++) {
        cout << i + 1 << " - " << sortNames[i] << '\n';
    }
    int sortType;
    cin >> sortType;
    
    const int startSize = 10000;
    const int endSize = 110000;
    const int step = 10000;

    ofstream outFile(chooseFile(sortType));

    outFile << "sorted\n";
    for (int i = startSize; i <= endSize; i+=step) {
        vec = createSortedVec(i);
        auto startTime = chrono::high_resolution_clock::now();
        chooseSort(vec, sortType);
        auto endTime = chrono::high_resolution_clock::now();
        chrono::duration<double> sortTime = endTime - startTime;
        cout << sortNames[sortType - 1] << ", sorted: " << fixed << setprecision(6) << sortTime.count() << '\n';
        outFile << sortNames[sortType - 1] << ',' << "sorted," << i << ',' << sortTime.count() << '\n';
    }
    outFile << "almost sorted\n";
    for (int i = startSize; i <= endSize; i += step) {
        vec = createAlmostSortedVec(i);
        auto startTime = chrono::high_resolution_clock::now();
        chooseSort(vec, sortType);
        auto endTime = chrono::high_resolution_clock::now();
        chrono::duration<double> sortTime = endTime - startTime;
        cout << sortNames[sortType - 1] << ", almost sorted: " << fixed << setprecision(6) << sortTime.count() << '\n';
        outFile << sortNames[sortType - 1] << ',' << "almost_sorted," << i << ',' << sortTime.count() << '\n';
    }
    outFile << "reverse sorted\n";
    for (int i = startSize; i <= endSize; i += step) {
        vec = createReverseSortedVec(i);
        auto startTime = chrono::high_resolution_clock::now();
        chooseSort(vec, sortType);
        auto endTime = chrono::high_resolution_clock::now();
        chrono::duration<double> sortTime = endTime - startTime;
        cout << sortNames[sortType - 1] << ", reverse sorted: " << fixed << setprecision(6) << sortTime.count() << '\n';
        outFile << sortNames[sortType - 1] << ',' << "reverse_sorted," << i << ',' << sortTime.count() << '\n';
    }
    outFile << "random\n";
    for (int i = startSize; i <= endSize; i += step) {
        vec = createRandomVec(i);
        auto startTime = chrono::high_resolution_clock::now();
        chooseSort(vec, sortType);
        auto endTime = chrono::high_resolution_clock::now();
        chrono::duration<double> sortTime = endTime - startTime;
        cout << sortNames[sortType - 1] << ", random: " << fixed << setprecision(6) << sortTime.count() << '\n';
        outFile << sortNames[sortType - 1] << ',' << "random," << i << ',' << sortTime.count() << '\n';
    }

    outFile.close();
}

int main()
{
    menu();

}
