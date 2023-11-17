#include <iostream>
#include <iomanip>
#include <stack>
using namespace std;
#define MAX 100
bool flag = false;
const int MAX_VERTICES = 100;

struct Edge {
    int src;
    int dest;
    int wt;
};
class PQueue{
public:
//экземпляр элемента очереди с приоритетом
    struct node {
        int data; //значение элемента
        node* next; //указатель на следующий элемент
    };

    node* head;
    node* tail; //начало, конец
    int length = 0;

//добавление элемента(неприоритетное)
    void insert(int data) {
        node* q = new node;
        if (length == 0){
            head = q;
        } else{
            tail->next = q;
        }
        q->data = data;
        q->next = NULL;
        tail = q;
        length++;
    }

//удаление элемента(приоритетное)
    int Delete(int shortest[]) {
        //пустая очередь
        if (!head) {
            std::cerr << "queue is empty\n";
            exit(1);
        }

        //поиск элемента, с минимальным значением shortest
        int min_shortest = shortest[head->data];
        int min_key = head->data;
        node* curr = head->next;
        node* prev = head;

        while (curr) {
            if (shortest[curr->data] < min_shortest) {
                min_shortest = shortest[curr->data];
                min_key = curr->data;
            }

            curr = curr->next;
        }

        if (head->data == min_key) {
            curr = head->next;
            delete head;
            head = curr;
        } else {
            prev = head;
            curr = head->next;
            while (curr) {
                if (curr->data == min_key) {
                    prev->next = curr->next;
                    delete curr;
                    break;
                }

                prev = curr;
                curr = curr->next;
            }
        }

        length--;
        return min_key;
    }

//Проверка на пустоту
    bool empty(){
        return !head;
    }
};


void addEdge(
        Edge* edgeArray,
        int& ne,
        int src,
        int dest,
        int wt
);

// Функция проверки на отрицательный вес
void checking(
        Edge* e,
        int edges
);

// Функция вычесления кратчайшего пути между двух вершин, у которых имеется ребро (u v)
void relaxDijkstra(
        Edge* edges,
        int u,
        int v,
        int* shortest,
        int* pred
);


// Функция поиска кратчайшего пути для вершин графа
void dijkstra(
        int** matrix,
        int vertex,
        int* shortest,
        int* pred
);

void floydWarshall(
        int** matrix,
        int** shortest,
        int** path,
        int vertices
);

void bellmanFord(
        int vertexes,
        Edge* e,
        int edges,
        int* shortest,
        int* pred
);

void primMST(
        int** graph,
        int V,
        int start
);

int** edgesToMatrix(
        Edge* edges,
        int edgeCount,
        int vertexCount
);

// Функция для нахождения корня множества (родителя) элемента v
int findSet(
        int parent[],
        int v
);

// Функция для объединения двух множеств, в которых находятся элементы x и y
void unionSets(
        int parent[],
        int x,
        int y
);

// Функция для нахождения минимального остовного дерева с использованием алгоритма Краскала
void kruskalMST(
        int n,
        int** g
);

// Функция вывода матрицы смежности
void printMatrix(
        int** matrix,
        int vertexes
);

void inicializeShortest(
        int* shortest,
        int vertexes,
        int start
);

void inicializePred(
        int* pred,
        int vertexes
);

void mirrored(
        int** matrix,
        int vertexts
);

void inicializeGraph(
        Edge* edgeArray,
        int& vertexes,
        int& edges
);

void printFloydWarshallResult(
        int vertexes,
        int** floydShortest,
        int** path
);

int main() {
    // Локализация
    setlocale(LC_ALL, "Russian");
    Edge* edge = new Edge[10];

    int vertexes = 4;
    int edges = 0;
    int** matrix;
    int start = 0; // Начальная вершина
    int* shortest = new int[vertexes];
    int* pred = new int[vertexes];

    inicializeShortest(shortest, vertexes, start);
    inicializePred(pred, vertexes);
    inicializeGraph(edge, vertexes, edges);

    matrix = edgesToMatrix(edge, edges, vertexes);

    /*=================================================================================*/
    cout << "АЛГОРИТМ БЕЛЛМАНА-ФОРДА:\n";
    printMatrix(matrix, vertexes);
    bellmanFord(vertexes, edge,edges, shortest, pred);
    for (int v = 0; v < vertexes; v++) {
        std::cout << "Кратчайший путь до вершины " << v << " = " << shortest[v] << " (предшествующая вершина: " << pred[v] << ")\n";
    }

    cout << "\n=======================================================================\n";
    cout << "АЛГОРИТМ ДЕЙКСТРЫ:\n";
    inicializeShortest(shortest, vertexes, start);
    inicializePred(pred, vertexes);
    printMatrix(matrix, vertexes);
    checking(edge, edges); // Функция проверки на отрицательный вес

    if (!flag) {
        dijkstra(matrix, vertexes, shortest, pred);
        // Вывод кратчайших путей и их длин
        cout << '\n';
        for (int v = 0; v < vertexes; v++) {
            std::cout << "Кратчайший путь до вершины " << v << " = " << shortest[v] << " (предшествующая вершина: " << pred[v] << ")\n";
        }
    }
    else {
        cout << "Алгоритм Дейкстры не работает на графах с отрицательными весами!";
    }

    cout << "\n=======================================================================\n";
    cout << "АЛГОРИТМ ФЛОЙДА УОРШЕЛА\n";
    int** floydShortest = new int* [vertexes];
    int** path = new int* [vertexes];
    for (int i = 0; i < vertexes; ++i) {
        floydShortest[i] = new int[vertexes];
        path[i] = new int[vertexes];
    }
    floydWarshall(matrix, floydShortest, path, vertexes);
    printFloydWarshallResult(vertexes, floydShortest, path);


    cout << "\n=======================================================================\n";
    cout << "АЛГОРИТМ ПРИМА\n";
    mirrored(matrix, vertexes);
    printMatrix(matrix, vertexes);
    primMST(matrix, vertexes, start);

    cout << "\n=======================================================================\n";
    cout << "АЛГОРИТМ  КРУСКАЛЛА\n";
    kruskalMST(vertexes, matrix);
    // Освобождение памяти (для обычный шортест и пред не сделал еще)
    for (int i = 0; i < vertexes; ++i) {
        delete[] matrix[i];
        delete[] floydShortest[i];
        delete[] path[i];
    }
    delete[] matrix;
    delete[] floydShortest;
    delete[] path;
}

void inicializeGraph(
        Edge* edgeArray,
        int& vertexes,
        int& edges
) {
    /*addEdge(edgeArray, edges, 0, 1, 6);
    addEdge(edgeArray, edges, 0, 2, 8);
    addEdge(edgeArray, edges, 0, 3, 18);
    addEdge(edgeArray, edges, 1, 4, 11);
    addEdge(edgeArray, edges, 2, 3, 9);
    addEdge(edgeArray, edges, 4, 5, 5);
    addEdge(edgeArray, edges, 5, 3, 4);
    addEdge(edgeArray, edges, 5, 2, 7);*/
    addEdge(edgeArray, edges, 0, 1, 3);
    addEdge(edgeArray, edges, 0, 2, 8);
    addEdge(edgeArray, edges, 1, 3, 1);
    addEdge(edgeArray, edges, 2, 1, 4);
    addEdge(edgeArray, edges, 3, 0, 2);
    addEdge(edgeArray, edges, 3, 2, 5);
}

void addEdge(
        Edge* edgeArray,
        int& ne,
        int src,
        int dest,
        int wt
) {
    edgeArray[ne].src = src;
    edgeArray[ne].dest = dest;
    edgeArray[ne].wt = wt;
    ne++;
}

int** edgesToMatrix(
        Edge* edges,
        int edgeCount,
        int vertexCount
) {
    // Выделение памяти для матрицы смежности
    int** matrix = new int* [vertexCount];
    for (int i = 0; i < vertexCount; i++) {
        matrix[i] = new int[vertexCount];
        // Инициализация матрицы нулями
        for (int j = 0; j < vertexCount; j++) {
            matrix[i][j] = 999;
            matrix[i][i] = 0;
        }
    }

    // Заполнение матрицы смежности значениями из массива рёбер
    for (int i = 0; i < edgeCount; i++) {
        matrix[edges[i].src][edges[i].dest] = edges[i].wt;
    }

    return matrix;
}

void inicializeShortest(
        int* shortest,
        int vertexes,
        int start
) {
    for (int i = 0; i < vertexes; i++) {
        shortest[i] = INT_MAX;
    }
    shortest[start] = 0; // Я сделяль! Я прохрамист!
}

void inicializePred(
        int* pred,
        int vertexes
) {
    for (int i = 0; i < vertexes; i++) {
        pred[i] = -1;

    }
}

void printFloydWarshallResult(
        int vertexes,
        int** floydShortest,
        int** path
) {
    cout << "Кротчайшие веса между каждыми парами вершин:\n";
    for (int i = 0; i < vertexes; ++i) {
        for (int j = 0; j < vertexes; ++j) {
            cout << floydShortest[i][j] << "\t";
        }
        cout << "\n";
    }

    cout << "\nМатрица путей:\n";
    for (int i = 0; i < vertexes; ++i) {
        for (int j = 0; j < vertexes; ++j) {
            cout << path[i][j] << "\t";
        }
        cout << "\n";
    }
}

// Функция Relax - обновление кратчайших путей для пары вершин (u, v)
void relaxDijkstra(
        Edge* edges,
        int u,
        int v,
        int* shortest,
        int* pred
) {
    //shortest[edges[v].dest]
    if (shortest[u] != INT_MAX && shortest[u] + edges[v].wt < shortest[edges[v].dest]) {
        shortest[edges[v].dest] = shortest[u] + edges[v].wt; // Если новый путь короче, обновляем shortest
        pred[edges[v].dest] = u; // Обновляем предшествующую вершину для v
    }
}
void relaxBellman(
        Edge* edges,
        int j,
        int* shortest,
        int* pred
) {
    int u = edges[j].src; // u - начало ребра (откуда)
    int v = edges[j].dest; // v - конец ребра (куда)
    int weight = edges[j].wt; // weight - вес ребра
    if (shortest[u] != INT_MAX && shortest[u] + weight < shortest[v]) { // По хорошему засунуть в функцию relax,
        // реализовать вывод на каждой итерации я не смогла((((
        shortest[v] = shortest[u] + weight;
        pred[v] = u;
    }
}
void relax(
        int**matrix,
        int*pred,
        int*shortest,
        int u,
        int v
){
    if (shortest[u] != INT_MAX && shortest[u] + matrix[u][v] < shortest[v]) {
        shortest[v] = shortest[u] + matrix[u][v];
        pred[v] = u;
    }
}

void checking(
        Edge* e,
        int edges
) {
    for (int i = 0; i < edges; i++) {
        if (e[i].wt < 0) {
            flag = true;
            return;
        }
    }
}

void bellmanFord(
        int vertexes, //Количество вершин
        Edge* e, //Массив ребер
        int edges, // Количество ребер
        int* shortest, // Массив кратчайших путей до вершины
        int* pred // Массив, хранящий значение вершины на пути в вершину
) {
    for (int i = 0; i < vertexes - 1; i++) { // Цикл, чтобы алгоритм был не бесконечен
        for (int j = 0; j < edges; j++) { // Цикл по j от 0 до 5 (по номеру ребер)
            relaxBellman(e,j, shortest, pred);
        }
    }
    cout << endl;
}




// Функция Dijkstra для поиска кратчайших путей из начальной вершины start
void dijkstra(
        int** matrix,
        int vertex,
        int* shortest,
        int* pred
) {
    PQueue pqueue;
    for (int i = 0; i < vertex; i++) { // Добавление всех вершин в очередь с приоритетом
        pqueue.insert(i);
    }

    while (!pqueue.empty()) { // Пока очередь не пуста
        int u = pqueue.Delete(shortest); // Записываем в u элемент с наименьшим значением shortest[u]
        // и удаляем его из очереди

        for (int v = 0; v < vertex; v++) { // Проходим по всем вершинам
            if (matrix[u][v] > 0) { // Если существует ребро
                relax(matrix,pred, shortest,u,v); // Релаксация ребра
            }
        }
        for (int v = 0; v < vertex; v++) {
            std::cout << "(" << shortest[v] << ") ";
        }
        cout << endl;

    }

}

void floydWarshall(
        int** matrix,
        int** shortest,
        int** path,
        int vertices
) {
    printMatrix(matrix, vertices);

    // Инициализация массива shortest и path
    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            shortest[i][j] = matrix[i][j];
            if (matrix[i][j] != 999 && i != j) {
                path[i][j] = i;
            }
            else {
                path[i][j] = -1; // -1 означает отсутствие пути
            }
        }
    }
    printFloydWarshallResult(vertices, shortest, path);

    // Выполнение алгоритма Флойда-Уоршелла
    for (int k = 0; k < vertices; ++k) {
        for (int i = 0; i < vertices; ++i) {
            for (int j = 0; j < vertices; ++j) {
                if (shortest[i][k] + shortest[k][j] < shortest[i][j]) {
                    shortest[i][j] = shortest[i][k] + shortest[k][j];
                    path[i][j] = k;
                }
            }
        }
        printFloydWarshallResult(vertices, shortest, path);
    }
}

void printMatrix(
        int** matrix,
        int vertexes
) {
    // Вывод заголовка
    std::cout << "Матрица смежности:\n\t";
    for (int i = 0; i < vertexes; i++) {
        std::cout << std::setw(3) << i << ' ';
    }
    std::cout << std::endl << std::endl;

    // Вывод матрицы
    for (int row = 0; row < vertexes; row++) {
        std::cout << row << '\t';
        for (int column = 0; column < vertexes; column++) {
            std::cout << std::setw(3) << matrix[row][column] << ' ';
        }
        std::cout << std::endl;
    }
}
// Функция mirrored принимает матрицу и количество вершин, зеркально копирует значения
// из верхнего треугольника матрицы в нижний треугольник.
void mirrored(int** matrix, int vertices) {
    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            if (matrix[i][j] != 999) {
                matrix[j][i] = matrix[i][j]; // Зеркальное копирование
            }
        }
    }
}


// Функция primMST реализует алгоритм Прима для поиска минимального остовного дерева во взвешенном графе.
// Принимает матрицу графа и количество вершин.
void primMST(
        int** graph,
        int V,
        int start
) {
    int shortest[MAX];
    bool inMST[MAX];

    // Инициализация ключей и флагов для каждой вершины.
    for (int i = 0; i < V; ++i) {
        shortest[i] = INT_MAX;
        inMST[i] = false;
    }

    shortest[start] = 0;


    inMST[start] = true;
    int minW = INT_MAX;
    int step;
    for (int count = 0; count < V; ++count) {
        int flag = false;
        for (int i = 0; i < V; ++i) {
            if (graph[start][i] != 0 &&
                graph[start][i] != 999 &&
                graph[start][i] < minW && !inMST[i]) { // Ребро есть, вес меньше и мы не были в этой вершине
                minW = graph[start][i];
                step = i;
                flag = true;
            }
        }
        if (!flag)
            break;
        cout << "Ребро из " << start << " в " << step << " весом " << minW << endl;
        start = step;
        inMST[step] = true;
        minW = INT_MAX;
    }
}


// Функция findSet реализует операцию FindSet для структуры данных "disjoint-set" (несвязанные множества).
// Если вершина v не имеет родителя (принадлежит корневому элементу), возвращает саму вершину v.
// В противном случае рекурсивно вызывает findSet для родителя вершины v.
int findSet(int parent[], int v) {
    if (parent[v] == -1)
        return v;
    return findSet(parent, parent[v]);
}

// Функция unionSets реализует операцию Union для структуры данных "disjoint-set".
// Находит корневые элементы множеств, к которым принадлежат вершины x и y (rootX и rootY).
// Затем устанавливает корень множества x в качестве родителя корня множества y.
// Это соединяет два множества в одно, объединяя их корневые элементы.
void unionSets(int parent[], int x, int y) {
    int rootX = findSet(parent, x);
    int rootY = findSet(parent, y);
    parent[rootX] = rootY;
}

// Функция customSort сортирует массив рёбер по их весу.
void customSort(Edge arr[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (arr[j].wt > arr[j + 1].wt) {
                // Обмен элементов, если они стоят в неправильном порядке.
                Edge temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Функция kruskalMST реализует алгоритм Крускала для поиска минимального остовного дерева во взвешенном графе.
void kruskalMST(
        int n,
        int** g
) {
    Edge edges[MAX * MAX];
    int edgeCount = 0;

    // Заполнение массива рёбер.
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (g[i][j] != 999) {
                edges[edgeCount].src = i;
                edges[edgeCount].dest = j;
                edges[edgeCount].wt = g[i][j];
                ++edgeCount;
            }
        }
    }

    // Сортировка массива рёбер.
    customSort(edges, edgeCount);

    int parent[MAX];
    fill(parent, parent + n, -1);

    // Вывод рёбер минимального остовного дерева.
    cout << "Минимальное остовное дерево (ребро, вес):" << endl;
    for (int i = 0; i < edgeCount; ++i) {
        int str = edges[i].src;
        int dest = edges[i].dest;
        int wt = edges[i].wt;

        int rootStr = findSet(parent, str);
        int rootDest = findSet(parent, dest);

        if (rootStr != rootDest) {
            cout << "(" << str << ", " << dest << ") " << wt << endl;
            unionSets(parent, rootStr, rootDest);
        }
    }
}
