#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <string>
#include <random>

using namespace std;
using namespace std::chrono;
string getMemoryUsage(string alg, long n) {
    if (alg == "BUBBLE" || alg == "SELECT" || alg == "INSERT")
        return "O(1) (~k bytes)"; // Sortare in-place
    if (alg == "QUICK")
        return "O(log N) (~" + to_string(sizeof(int) * 32) + " bytes stack)";
    if (alg == "MERGE")
        return "O(N) (~" + to_string(n * sizeof(int)) + " bytes)"; // Are nevoie de vector auxiliar
    return "0";
}
// --- ALGORITMI ---
void BUBBLE_SORT(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1]) swap(arr[j], arr[j + 1]);
}

void SELECTION_SORT(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx]) min_idx = j;
        swap(arr[min_idx], arr[i]);
    }
}

void INSERTION_SORT(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i], j = i - 1;
        while (j >= 0 && arr[j] > key) { arr[j + 1] = arr[j]; j--; }
        arr[j + 1] = key;
    }
}

void MERGE(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void MERGE_SORT(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        MERGE_SORT(arr, l, m); MERGE_SORT(arr, m + 1, r);
        MERGE(arr, l, m, r);
    }
}

void QUICK_SORT(vector<int>& arr, int left, int right) {
    int i = left, j = right;
    int pivot = arr[left + (right - left) / 2];
    while (i <= j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i <= j) { swap(arr[i], arr[j]); i++; j--; }
    }
    if (left < j) QUICK_SORT(arr, left, j);
    if (i < right) QUICK_SORT(arr, i, right);
}

// --- GENERARE DATE ---
vector<int> generateData(int size, string type) {
    vector<int> arr(size);
    if (type == "sorted") for (int i = 0; i < size; i++) arr[i] = i;
    else if (type == "reverse") for (int i = 0; i < size; i++) arr[i] = size - i;
    else if (type == "flat") for (int i = 0; i < size; i++) arr[i] = rand() % 10;
    else if (type == "nearly") {
        for (int i = 0; i < size; i++) arr[i] = i;
        for (int k = 0; k < size/10; k++) swap(arr[rand()%size], arr[rand()%size]);
    }
    else for (int i = 0; i < size; i++) arr[i] = rand() % 1000000;
    return arr;
}

// --- ENGINE TESTARE ---
void runAll(const vector<int>& base, int n, int reps = 1) {
    auto test = [&](string name, void (*f)(vector<int>&)) {
        auto s = high_resolution_clock::now();
        for(int i = 0; i < reps; i++) {
            vector<int> d = base;
            f(d);
        }
        auto e = high_resolution_clock::now();
        double total = duration<double>(e - s).count();
        if (reps > 1) cout << name << " : " << total << " s" << endl;
        else cout << name << ": " << fixed << setprecision(4) << total * 1000 << " ms" << endl;
    };

    test("BUBBLE", BUBBLE_SORT);
    test("SELECT", SELECTION_SORT);
    test("INSERT", INSERTION_SORT);
    test("MERGE", [](vector<int>& v){ if(!v.empty()) MERGE_SORT(v, 0, v.size()-1); });
    test("QUICK", [](vector<int>& v){ if(!v.empty()) QUICK_SORT(v, 0, v.size()-1); });
}

int main() {
    srand(time(0));

    // FAZA 1: LISTE MICI (10, 20, 50, 100) - 1.000.000 repetari
    int repsSmall = 1000000;
    vector<int> smallSizes = {10, 20, 50, 100};
    for (int n : smallSizes) {
        cout << "\n--- FAZA 1: N = " << n << " (" << repsSmall << " repetari) ---" << endl;
        runAll(generateData(n, "random"), n, repsSmall);
    }

    // FAZA 2: CRESTERE DIN 100 IN 100 (100 -> 1000)
    cout << "\n--- FAZA 2: CRESTERE DIN 100 IN 100 ---" << endl;
    for (int n = 200; n <= 1000; n += 200) {
        cout << "\nN = " << n << endl;
        runAll(generateData(n, "random"), n);
    }

    // FAZA 3: CRESTERE DIN 1000 IN 1000 (1000 -> 10.000)
    cout << "\n--- FAZA 3: CRESTERE DIN 1000 IN 1000 ---" << endl;
    for (int n = 2000; n <= 10000; n += 2000) {
        cout << "\nN = " << n << endl;
        runAll(generateData(n, "random"), n);
    }
    long sizes[] = {10, 100, 1000, 10000};
    string algos[] = {"BUBBLE", "SELECT", "INSERT", "MERGE", "QUICK"};
    cout<<endl;
    cout << "--- ANALIZA MEMORIEI AUXILIARE ---" << endl;
    for (long n : sizes) {
        cout << "N = " << n << endl;
        for (string a : algos) {
            cout << a << ": " << getMemoryUsage(a, n) << endl;
        }
        cout << "-----------------" << endl;
    }

    return 0;
}
