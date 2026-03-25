# Analiza Experimentală a Algoritmilor de Sortare

Acest proiect reprezintă studiul performanței a 5 algoritmi de sortare fundamentali, comparând rezultatele teoretice ($O(n^2)$ vs $O(n \log n)$) cu datele obținute experimental pe diverse tipuri de structuri de date.

## 🚀 Metode Implementate
*   **Bubble Sort** ($O(n^2)$)
*   **Selection Sort** ($O(n^2)$)
*   **Insertion Sort** ($O(n^2)$)
*   **Merge Sort** ($O(n \log n)$)
*   **Quick Sort** ($O(n \log n)$)

## 📊 Rezultate Cheie (N=10.000)

| Algoritm | Random | Sorted | Reverse | Nearly Sorted |
| :--- | :--- | :--- | :--- | :--- |
| **Bubble Sort** | 437.39 ms | 171.79 ms | 486.94 ms | 228.99 ms |
| **Insertion Sort** | 107.54 ms | **0.049 ms** | 219.34 ms | 26.36 ms |
| **Quick Sort** | **1.16 ms** | **0.27 ms** | **0.31 ms** | **0.46 ms** |
| **Merge Sort** | 3.95 ms | 3.29 ms | 3.27 ms | 3.55 ms |

## 🧠 Concluzii și Anomalii Hardware
*   **Aproape Sortat:** Insertion Sort este extrem de eficient pe date aproape sortate, depășind chiar și Quick Sort la dimensiuni mici.
*   **Overhead Merge Sort:** Merge Sort este mai lent decât Quick Sort din cauza alocărilor dinamice de memorie (heap allocation), deși ambele au aceeași complexitate teoretică.
*   **L1/L2 Cache:** Quick Sort profită de localitatea referinței (date in-place), ceea ce îl face campionul performanței practice.

## 📂 Structura Proiectului
*   [main.cpp](main.cpp): Codul sursă complet în C++.
*   [Documentatie.pdf](Documentatie.pdf): Raportul detaliat generat în LaTeX.

---
**Autor:** Costin Anica  
