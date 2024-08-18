#include <iostream> 
#include <algorithm>
#include <random>
#include <iomanip>
#include <chrono>
#include <time.h>

void swap(int* xp, int* yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubbleSort(int v[], int n) {

    for (int i = 0; i < n; i++)
        for (int j = 1; j < n - i; j++)
            if (v[j] < v[j - 1])
                std::swap(v[j], v[j - 1]);

}

void shellSort(int v[], int n) {

    for (int k = n / 2; k > 0; k /= 2) {
        for (int i = k; i < n; i++) {
            int temp = v[i];
            int j;
            for (j = i; j >= k && v[j - k] > temp; j -= k) {
                v[j] = v[j - k];
            }
            v[j] = temp;
        }
    }
}

void selectionSort(int v[], int l, int n) {

    for (int i = l; i < n; i++) {
        int Min = i;
        for (int j = i + 1; j <= n; j++) {
            if (v[j] < v[Min])
                Min = j;
        }
        if (v[Min] < v[i]) swap(&v[i], &v[Min]);
    }
}

void insertionSort(int v[], int l, int n) {

    for (int i = l + 1; i <= n; i++) {
        int aux = v[i];
        int j = i - 1;
        while ((j >= 0) && (aux < v[j])) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = aux;
    }
}

void partition(int* v, int esq, int dir, int* i, int* j) {
    int x;
    *i = esq; *j = dir;
    x = v[(*i + *j) / 2];
    do
    {
        while (x > v[*i]) {
            (*i)++;
        }
        while (x < v[*j]) {
            (*j)--;
        }
        if (*i <= *j) {
            swap(&v[*i], &v[*j]);
            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);

}

void quickSort(int* v, int esq, int dir) {
    int i, j;
    partition(v, esq, dir, &i, &j);
    if (esq < j) quickSort(v, esq, j);
    if (i < dir) quickSort(v, i, dir);
}

void merge(int v[], int const e, int const m, int const d) {

    int const aux1 = m - e + 1;
    int const aux2 = d - m;

    auto* vete = new int[aux1], * vetd = new int[aux2];

    for (auto i = 0; i < aux1; i++)
        vete[i] = v[e + i];

    for (auto j = 0; j < aux2; j++)
        vetd[j] = v[m + 1 + j];

    auto aux1_i = 0, aux2_i = 0;
    int vetM_i = e;

    while (aux1_i < aux1 && aux2_i < aux2) {

        if (vete[aux1_i] <= vetd[aux2_i]) {

            v[vetM_i] = vete[aux1_i];
            aux1_i++;
        }
        else {
            v[vetM_i] = vetd[aux2_i];
            aux2_i++;
        }
        vetM_i++;
    }

    while (aux1_i < aux1) {

        v[vetM_i] = vete[aux1_i];
        aux1_i++;
        vetM_i++;
    }

    while (aux2_i < aux2) {

        v[vetM_i] = vetd[aux2_i];
        aux2_i++;
        vetM_i++;
    }
    delete[] vete;
    delete[] vetd;
}

void mergeSort(int v[], int const e, int const d)
{
    if (e >= d)
        return;

    int m = e + (d - e) / 2;
    mergeSort(v, e, m);
    mergeSort(v, m + 1, d);
    merge(v, e, m, d);
}

void countingSort(int v[], int n) {

    int* saida = new int[n];
    int* cont = new int[n];
    int max = v[0];

    for (int i = 1; i < n; i++)
        if (v[i] > max)
            max = v[i];

    for (int i = 0; i <= max; ++i)
        cont[i] = 0;

    for (int i = 0; i < n; i++)
        cont[v[i]]++;

    for (int i = 1; i <= max; i++)
        cont[i] += cont[i - 1];


    for (int i = n - 1; i >= 0; i--) {
        saida[cont[v[i]] - 1] = v[i];
        cont[v[i]]--;
    }

    for (int i = 0; i < n; i++)
        v[i] = saida[i];
}

struct Node {
    int info;
    struct Node* prox;
};

#define NBUCKET 6 
#define INTERVAL 10

int bucketIndex(int i) {
    return i / INTERVAL;
}

struct Node* InsertionSort(struct Node* lista) {

    struct Node* k, * elemLista;

    if (lista == 0 || lista->prox == 0)
        return lista;

    elemLista = lista;
    k = lista->prox;
    elemLista->prox = 0;
    while (k != 0) {
        struct Node* ptr;
        if (elemLista->info > k->info) {
            struct Node* aux;
            aux = k;
            k = k->prox;
            aux->prox = elemLista;
            elemLista = aux;
            continue;
        }

        for (ptr = elemLista; ptr->prox != 0; ptr = ptr->prox)
            if (ptr->prox->info > k->info)
                break;

        if (ptr->prox != 0) {
            struct Node* aux;
            aux = k;
            k = k->prox;
            aux->prox = ptr->prox;
            ptr->prox = aux;
            continue;
        }
        else {
            ptr->prox = k;
            k = k->prox;
            ptr->prox->prox = 0;
            continue;
        }
    }
    return elemLista;
}

void bucketSort(int v[], int n) {
    int i, j;
    struct Node** buckets;

    buckets = (struct Node**)malloc(sizeof(struct Node*) * NBUCKET);

    for (i = 0; i < NBUCKET; i++)
        buckets[i] = NULL;

    for (i = 0; i < n; i++) {
        struct Node* atual;
        int pos = bucketIndex(v[i]);
        atual = (struct Node*)malloc(sizeof(struct Node));
        atual->info = v[i];
        atual->prox = buckets[pos];
        buckets[pos] = atual;
    }

    for (i = 0; i < NBUCKET; i++)
        buckets[i] = InsertionSort(buckets[i]);

    for (j = 0, i = 0; i < NBUCKET; i++) {

        struct Node* elem;
        elem = buckets[i];
        while (elem) {
            v[j++] = elem->info;
            elem = elem->prox;
        }
    }

    for (i = 0; i < NBUCKET; i++) {
        struct Node* node;
        node = buckets[i];
        while (node) {
            struct Node* aux;
            aux = node;
            node = node->prox;
            free(aux);
        }
    }
    free(buckets);
    return;
}

int getMax(int v[], int n) {
    int max = v[0];
    for (int i = 1; i < n; i++)
        if (v[i] > max)
            max = v[i];
    return max;
}

void countingSort_Radix(int v[], int n, int place) {
    const int max = 10;
    int* output = new int[n];
    int count[max];

    for (int i = 0; i < max; ++i)
        count[i] = 0;

    for (int i = 0; i < n; i++)
        count[(v[i] / place) % 10]++;

    for (int i = 1; i < max; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        output[count[(v[i] / place) % 10] - 1] = v[i];
        count[(v[i] / place) % 10]--;
    }

    for (int i = 0; i < n; i++)
        v[i] = output[i];
}

void radixSort(int v[], int size) {

    int max = getMax(v, size);

    for (int place = 1; max / place > 0; place *= 10)
        countingSort_Radix(v, size, place);
}

void preenche_ord(int v[], int tam) {

    for (int i = 0; i < tam; i++)
        v[i] = i + 1;
}

void preenche_Iord(int v[], int tam) {

    for (int i = 0; i < tam; i++) {
        v[i] = tam - i;
    }
}

void embaralha(int v[], int tam) {

    for (int i = 0; i < tam; i++) {
        int r = rand() % tam;  // generate a random position
        int temp = v[i]; v[i] = v[r]; v[r] = temp;
    }
}

void printarray(int v[], int tam)
{
    for (int i = 0; i < tam; i++)
        std::cout << v[i] << ' ';

    std::cout << std::endl;
}

int main(int argc, char** argv) {

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    int vet100[100] = { 0 };
    int vet150[150] = { 0 };
    int vet200[200] = { 0 };
    int vet250[250] = { 0 };
    int vet300[300] = { 0 };
    double tempos[5][9][3] = { 0 };

    auto comeco = std::chrono::high_resolution_clock::now();
    auto fim = std::chrono::high_resolution_clock::now();
    auto duracao = std::chrono::duration_cast<std::chrono::microseconds>(comeco - fim).count();

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 3; k++) {
                switch (k) {

                case 0:
                    //ordenado
                    preenche_ord((i == 0 ? vet100 : i == 1 ? vet150 : i == 2 ? vet200 : i == 3 ? vet250 : vet300), (i == 0 ? 100 : i == 1 ? 150 : i == 2 ? 200 : i == 3 ? 250 : 300));

                    switch (j) {
                    case 0:
                        //bubble sort

                        comeco = std::chrono::high_resolution_clock::now();
                        bubbleSort((i == 0 ? vet100 : i == 1 ? vet150 : i == 2 ? vet200 : i == 3 ? vet250 : vet300), (i == 0 ? 100 : i == 1 ? 150 : i == 2 ? 200 : i == 3 ? 250 : 300));
                        fim = std::chrono::high_resolution_clock::now();
                        duracao = std::chrono::duration_cast<std::chrono::microseconds>(fim - comeco).count();
                        tempos[i][j][k] = duracao;
                        duracao = 0;

                        break;

                    case 1:
                        //shell sort

                        comeco = std::chrono::high_resolution_clock::now();
                        shellSort((i == 0 ? vet100 : i == 1 ? vet150 : i == 2 ? vet200 : i == 3 ? vet250 : vet300), (i == 0 ? 100 : i == 1 ? 150 : i == 2 ? 200 : i == 3 ? 250 : 300));
                        fim = std::chrono::high_resolution_clock::now();
                        duracao = std::chrono::duration_cast<std::chrono::microseconds>(fim - comeco).count();
                        tempos[i][j][k] = duracao;
                        duracao = 0;

                        break;

                    case 2:
                        //selection sort

                        comeco = std::chrono::high_resolution_clock::now();
                        selectionSort((i == 0 ? vet100 : i == 1 ? vet150 : i == 2 ? vet200 : i == 3 ? vet250 : vet300), 0, (i == 0 ? 99 : i == 1 ? 149 : i == 2 ? 199 : i == 3 ? 249 : 299));
                        fim = std::chrono::high_resolution_clock::now();
                        duracao = std::chrono::duration_cast<std::chrono::microseconds>(fim - comeco).count();
                        tempos[i][j][k] = duracao;
                        duracao = 0;

                        break;

                    case 3:
                        //insertion sort

                        comeco = std::chrono::high_resolution_clock::now();
                        insertionSort((i == 0 ? vet100 : i == 1 ? vet150 : i == 2 ? vet200 : i == 3 ? vet250 : vet300), 0, (i == 0 ? 99 : i == 1 ? 149 : i == 2 ? 199 : i == 3 ? 249 : 299));
                        fim = std::chrono::high_resolution_clock::now();
                        duracao = std::chrono::duration_cast<std::chrono::microseconds>(fim - comeco).count();
                        tempos[i][j][k] = duracao;
                        duracao = 0;

                        break;

                    case 4:
                        //quick sort

                        comeco = std::chrono::high_resolution_clock::now();
                        quickSort((i == 0 ? vet100 : i == 1 ? vet150 : i == 2 ? vet200 : i == 3 ? vet250 : vet300), 0, (i == 0 ? 99 : i == 1 ? 149 : i == 2 ? 199 : i == 3 ? 249 : 299));
                        fim = std::chrono::high_resolution_clock::now();
                        duracao = std::chrono::duration_cast<std::chrono::microseconds>(fim - comeco).count();
                        tempos[i][j][k] = duracao;
                        duracao = 0;

                        break;

                    case 5:
                        //merge sort

                        comeco = std::chrono::high_resolution_clock::now();
                        mergeSort((i == 0 ? vet100 : i == 1 ? vet150 : i == 2 ? vet200 : i == 3 ? vet250 : vet300), 0, (i == 0 ? 99 : i == 1 ? 149 : i == 2 ? 199 : i == 3 ? 249 : 299));
                        fim = std::chrono::high_resolution_clock::now();
                        duracao = std::chrono::duration_cast<std::chrono::microseconds>(fim - comeco).count();
                        tempos[i][j][k] = duracao;
                        duracao = 0;

                        break;

                    case 6:
                        //counting sort

                        comeco = std::chrono::high_resolution_clock::now();
                        countingSort((i == 0 ? vet100 : i == 1 ? vet150 : i == 2 ? vet200 : i == 3 ? vet250 : vet300), (i == 0 ? 100 : i == 1 ? 150 : i == 2 ? 200 : i == 3 ? 250 : 300));
                        fim = std::chrono::high_resolution_clock::now();
                        duracao = std::chrono::duration_cast<std::chrono::microseconds>(fim - comeco).count();
                        tempos[i][j][k] = duracao;
                        duracao = 0;

                        break;

                    case 7:
                        //bucket sort

                        comeco = std::chrono::high_resolution_clock::now();
                        bucketSort((i == 0 ? vet100 : i == 1 ? vet150 : i == 2 ? vet200 : i == 3 ? vet250 : vet300), (i == 0 ? 100 : i == 1 ? 150 : i == 2 ? 200 : i == 3 ? 250 : 300));
                        fim = std::chrono::high_resolution_clock::now();
                        duracao = std::chrono::duration_cast<std::chrono::microseconds>(fim - comeco).count();
                        tempos[i][j][k] = duracao;
                        duracao = 0;

                        break;

                    case 8:
                        //radix sort

                        comeco = std::chrono::high_resolution_clock::now();
                        radixSort((i == 0 ? vet100 : i == 1 ? vet150 : i == 2 ? vet200 : i == 3 ? vet250 : vet300), (i == 0 ? 100 : i == 1 ? 150 : i == 2 ? 200 : i == 3 ? 250 : 300));
                        fim = std::chrono::high_resolution_clock::now();
                        duracao = std::chrono::duration_cast<std::chrono::microseconds>(fim - comeco).count();
                        tempos[i][j][k] = duracao;
                        duracao = 0;

                        break;
                    }

                    break;
                case 1:
                    // I ordenado
                    preenche_Iord((i == 0 ? vet100 : i == 1 ? vet150 : i == 2 ? vet200 : i == 3 ? vet250 : vet300), (i == 0 ? 100 : i == 1 ? 150 : i == 2 ? 200 : i == 3 ? 250 : 300));

                    switch (j) {
                    case 0:
                        //bubble sort

                        comeco = std::chrono::high_resolution_clock::now();
                        bubbleSort((i == 0 ? vet100 : i == 1 ? vet150 : i == 2 ? vet200 : i == 3 ? vet250 : vet300), (i == 0 ? 100 : i == 1 ? 150 : i == 2 ? 200 : i == 3 ? 250 : 300));
                        fim = std::chrono::high_resolution_clock::now();
                        duracao = std::chrono::duration_cast<std::chrono::microseconds>(fim - comeco).count();
                        tempos[i][j][k] = duracao;
                        duracao = 0;

                        break;

                    case 1:
                        //shell sort

                        comeco = std::chrono::high_resolution_clock::now();
                        shellSort((i == 0 ? vet100 : i == 1 ? vet150 : i == 2 ? vet200 : i == 3 ? vet250 : vet300), (i == 0 ? 100 : i == 1 ? 150 : i == 2 ? 200 : i == 3 ? 250 : 300));
                        fim = std::chrono::high_resolution_clock::now();
                        duracao = std::chrono::duration_cast<std::chrono::microseconds>(fim - comeco).count();
                        tempos[i][j][k] = duracao;
                        duracao = 0;

                        break;

                    case 2:
                        //selection sort

                        comeco = std::chrono::high_resolution_clock::now();
                        selectionSort((i == 0 ? vet100 : i == 1 ? vet150 : i == 2 ? vet200 : i == 3 ? vet250 : vet300), 0, (i == 0 ? 99 : i == 1 ? 149 : i == 2 ? 199 : i == 3 ? 249 : 299));
                        fim = std::chrono::high_resolution_clock::now();
                        duracao = std::chrono::duration_cast<std::chrono::microseconds>(fim - comeco).count();
                        tempos[i][j][k] = duracao;
                        duracao = 0;

                        break;

                    case 3:
                        //insertion sort

                        comeco = std::chrono::high_resolution_clock::now();
                        insertionSort((i == 0 ? vet100 : i == 1 ? vet150 : i == 2 ? vet200 : i == 3 ? vet250 : vet300), 0, (i == 0 ? 99 : i == 1 ? 149 : i == 2 ? 199 : i == 3 ? 249 : 299));
                        fim = std::chrono::high_resolution_clock::now();
                        duracao = std::chrono::duration_cast<std::chrono::microseconds>(fim - comeco).count();
                        tempos[i][j][k] = duracao;
                        duracao = 0;

                        break;

                    case 4:
                        //quick sort

                        comeco = std::chrono::high_resolution_clock::now();
                        quickSort((i == 0 ? vet100 : i == 1 ? vet150 : i == 2 ? vet200 : i == 3 ? vet250 : vet300), 0, (i == 0 ? 99 : i == 1 ? 149 : i == 2 ? 199 : i == 3 ? 249 : 299));
                        fim = std::chrono::high_resolution_clock::now();
                        duracao = std::chrono::duration_cast<std::chrono::microseconds>(fim - comeco).count();
                        tempos[i][j][k] = duracao;
                        duracao = 0;

                        break;

                    case 5:
                        //merge sort

                        comeco = std::chrono::high_resolution_clock::now();
                        mergeSort((i == 0 ? vet100 : i == 1 ? vet150 : i == 2 ? vet200 : i == 3 ? vet250 : vet300), 0, (i == 0 ? 99 : i == 1 ? 149 : i == 2 ? 199 : i == 3 ? 249 : 299));
                        fim = std::chrono::high_resolution_clock::now();
                        duracao = std::chrono::duration_cast<std::chrono::microseconds>(fim - comeco).count();
                        tempos[i][j][k] = duracao;
                        duracao = 0;

                        break;

                    case 6:
                        //counting sort

                        comeco = std::chrono::high_resolution_clock::now();
                        countingSort((i == 0 ? vet100 : i == 1 ? vet150 : i == 2 ? vet200 : i == 3 ? vet250 : vet300), (i == 0 ? 100 : i == 1 ? 150 : i == 2 ? 200 : i == 3 ? 250 : 300));
                        fim = std::chrono::high_resolution_clock::now();
                        duracao = std::chrono::duration_cast<std::chrono::microseconds>(fim - comeco).count();
                        tempos[i][j][k] = duracao;
                        duracao = 0;

                        break;

                    case 7:
                        //bucket sort

                        comeco = std::chrono::high_resolution_clock::now();
                        bucketSort((i == 0 ? vet100 : i == 1 ? vet150 : i == 2 ? vet200 : i == 3 ? vet250 : vet300), (i == 0 ? 100 : i == 1 ? 150 : i == 2 ? 200 : i == 3 ? 250 : 300));
                        fim = std::chrono::high_resolution_clock::now();
                        duracao = std::chrono::duration_cast<std::chrono::microseconds>(fim - comeco).count();
                        tempos[i][j][k] = duracao;
                        duracao = 0;

                        break;

                    case 8:
                        //radix sort

                        comeco = std::chrono::high_resolution_clock::now();
                        radixSort((i == 0 ? vet100 : i == 1 ? vet150 : i == 2 ? vet200 : i == 3 ? vet250 : vet300), (i == 0 ? 100 : i == 1 ? 150 : i == 2 ? 200 : i == 3 ? 250 : 300));
                        fim = std::chrono::high_resolution_clock::now();
                        duracao = std::chrono::duration_cast<std::chrono::microseconds>(fim - comeco).count();
                        tempos[i][j][k] = duracao;
                        duracao = 0;

                        break;
                    }

                    break;

                    break;

                case 2:
                    // aleatorio
                    preenche_ord((i == 0 ? vet100 : i == 1 ? vet150 : i == 2 ? vet200 : i == 3 ? vet250 : vet300), (i == 0 ? 100 : i == 1 ? 150 : i == 2 ? 200 : i == 3 ? 250 : 300));
                    embaralha((i == 0 ? vet100 : i == 1 ? vet150 : i == 2 ? vet200 : i == 3 ? vet250 : vet300), (i == 0 ? 100 : i == 1 ? 150 : i == 2 ? 200 : i == 3 ? 250 : 300));

                    switch (j) {
                    case 0:
                        //bubble sort

                        comeco = std::chrono::high_resolution_clock::now();
                        bubbleSort((i == 0 ? vet100 : i == 1 ? vet150 : i == 2 ? vet200 : i == 3 ? vet250 : vet300), (i == 0 ? 100 : i == 1 ? 150 : i == 2 ? 200 : i == 3 ? 250 : 300));
                        fim = std::chrono::high_resolution_clock::now();
                        duracao = std::chrono::duration_cast<std::chrono::microseconds>(fim - comeco).count();
                        tempos[i][j][k] = duracao;
                        duracao = 0;

                        break;

                    case 1:
                        //shell sort

                        comeco = std::chrono::high_resolution_clock::now();
                        shellSort((i == 0 ? vet100 : i == 1 ? vet150 : i == 2 ? vet200 : i == 3 ? vet250 : vet300), (i == 0 ? 100 : i == 1 ? 150 : i == 2 ? 200 : i == 3 ? 250 : 300));
                        fim = std::chrono::high_resolution_clock::now();
                        duracao = std::chrono::duration_cast<std::chrono::microseconds>(fim - comeco).count();
                        tempos[i][j][k] = duracao;
                        duracao = 0;

                        break;

                    case 2:
                        //selection sort

                        comeco = std::chrono::high_resolution_clock::now();
                        selectionSort((i == 0 ? vet100 : i == 1 ? vet150 : i == 2 ? vet200 : i == 3 ? vet250 : vet300), 0, (i == 0 ? 99 : i == 1 ? 149 : i == 2 ? 199 : i == 3 ? 249 : 299));
                        fim = std::chrono::high_resolution_clock::now();
                        duracao = std::chrono::duration_cast<std::chrono::microseconds>(fim - comeco).count();
                        tempos[i][j][k] = duracao;
                        duracao = 0;

                        break;

                    case 3:
                        //insertion sort

                        comeco = std::chrono::high_resolution_clock::now();
                        insertionSort((i == 0 ? vet100 : i == 1 ? vet150 : i == 2 ? vet200 : i == 3 ? vet250 : vet300), 0, (i == 0 ? 99 : i == 1 ? 149 : i == 2 ? 199 : i == 3 ? 249 : 299));
                        fim = std::chrono::high_resolution_clock::now();
                        duracao = std::chrono::duration_cast<std::chrono::microseconds>(fim - comeco).count();
                        tempos[i][j][k] = duracao;
                        duracao = 0;

                        break;

                    case 4:
                        //quick sort

                        comeco = std::chrono::high_resolution_clock::now();
                        quickSort((i == 0 ? vet100 : i == 1 ? vet150 : i == 2 ? vet200 : i == 3 ? vet250 : vet300), 0, (i == 0 ? 99 : i == 1 ? 149 : i == 2 ? 199 : i == 3 ? 249 : 299));
                        fim = std::chrono::high_resolution_clock::now();
                        duracao = std::chrono::duration_cast<std::chrono::microseconds>(fim - comeco).count();
                        tempos[i][j][k] = duracao;
                        duracao = 0;

                        break;

                    case 5:
                        //merge sort

                        comeco = std::chrono::high_resolution_clock::now();
                        mergeSort((i == 0 ? vet100 : i == 1 ? vet150 : i == 2 ? vet200 : i == 3 ? vet250 : vet300), 0, (i == 0 ? 99 : i == 1 ? 149 : i == 2 ? 199 : i == 3 ? 249 : 299));
                        fim = std::chrono::high_resolution_clock::now();
                        duracao = std::chrono::duration_cast<std::chrono::microseconds>(fim - comeco).count();
                        tempos[i][j][k] = duracao;
                        duracao = 0;

                        break;

                    case 6:
                        //counting sort

                        comeco = std::chrono::high_resolution_clock::now();
                        countingSort((i == 0 ? vet100 : i == 1 ? vet150 : i == 2 ? vet200 : i == 3 ? vet250 : vet300), (i == 0 ? 100 : i == 1 ? 150 : i == 2 ? 200 : i == 3 ? 250 : 300));
                        fim = std::chrono::high_resolution_clock::now();
                        duracao = std::chrono::duration_cast<std::chrono::microseconds>(fim - comeco).count();
                        tempos[i][j][k] = duracao;
                        duracao = 0;

                        break;

                    case 7:
                        //bucket sort

                        comeco = std::chrono::high_resolution_clock::now();
                        bucketSort((i == 0 ? vet100 : i == 1 ? vet150 : i == 2 ? vet200 : i == 3 ? vet250 : vet300), (i == 0 ? 100 : i == 1 ? 150 : i == 2 ? 200 : i == 3 ? 250 : 300));
                        fim = std::chrono::high_resolution_clock::now();
                        duracao = std::chrono::duration_cast<std::chrono::microseconds>(fim - comeco).count();
                        tempos[i][j][k] = duracao;
                        duracao = 0;

                        break;

                    case 8:
                        //radix sort

                        comeco = std::chrono::high_resolution_clock::now();
                        radixSort((i == 0 ? vet100 : i == 1 ? vet150 : i == 2 ? vet200 : i == 3 ? vet250 : vet300), (i == 0 ? 100 : i == 1 ? 150 : i == 2 ? 200 : i == 3 ? 250 : 300));
                        fim = std::chrono::high_resolution_clock::now();
                        duracao = std::chrono::duration_cast<std::chrono::microseconds>(fim - comeco).count();
                        std::cout << duracao << std::endl;
                        tempos[i][j][k] = duracao;
                        duracao = 0;

                        break;
                    }

                    break;

                    break;
                }
            }
        }
    }

    for (int j = 0; j < 9; j++) {

        std::cout << "Algoritimo: " << (j == 0 ? "bubble sort" : j == 1 ? "shell sort" : j == 2 ? "selection sort" : j == 3 ? "insertion sort" : j == 4 ? "quick sort" : j == 5 ? "merge sort" : j == 6 ? "counting sort" : j == 7 ? "bucket sort" : "radix sort") << std::endl;

        for (int i = 0; i < 5; i++) {

            std::cout << "Vetor tam: " << (i == 0 ? "100" : i == 1 ? "150" : i == 2 ? "200" : i == 3 ? "250" : "300") << std::endl;

            for (int k = 0; k < 3; k++) {

                std::cout << "Estado inicial: " << (k == 0 ? "ordenado" : k == 1 ? "inversamente ordenado" : "aleatorio") << std::endl;
                std::cout << "Tempo: " << tempos[i][j][k] << std::endl;
            }
        }
        std::cout << std::endl;
    }

    exit(0);
}
