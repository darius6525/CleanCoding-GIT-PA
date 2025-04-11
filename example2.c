#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Graph {
    int vertex_count;
    Node** adjacency_lists;
    int* visited;
} Graph;


Node* create_node(int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

Graph* create_graph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->vertex_count = vertices;

    graph->adjacency_lists = (Node**)malloc(vertices * sizeof(Node*));
    graph->visited = (int*)malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

void reset_visited(Graph* graph) {
    for (int i = 0; i < graph->vertex_count; i++) {
        graph->visited[i] = 0;
    }
}


void add_edge(Graph* graph, int src, int dest) {
    Node* new_node = create_node(dest);
    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

    new_node = create_node(src);
    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}

void insert_edges(Graph* graph, int edge_count) {
    int src, dest;
    printf("adauga %d muchii (de la 0 la %d)\n", edge_count, graph->vertex_count - 1);
    for (int i = 0; i < edge_count; i++) {
        scanf("%d %d", &src, &dest);
        if (src >= 0 && src < graph->vertex_count && dest >= 0 && dest < graph->vertex_count) {
            add_edge(graph, src, dest);
        }
        else {
            printf("Muchie invalida: %d %d\n", src, dest);
            i--; 
        }
    }
}

void dfs(Graph* graph, int vertex) {
    Node* temp = graph->adjacency_lists[vertex];
    graph->visited[vertex] = 1;
    printf("%d->", vertex);

    while (temp != NULL) {
        int connected_vertex = temp->data;
        if (!graph->visited[connected_vertex]) {
            dfs(graph, connected_vertex);
        }
        temp = temp->next;
    }
}

int is_empty(Node* queue) {
    return queue == NULL;
}

void enqueue(Node** queue, int data) {
    Node* new_node = create_node(data);
    if (is_empty(*queue)) {
        *queue = new_node;
    }
    else {
        Node* temp = *queue;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

int dequeue(Node** queue) {
    if (*queue == NULL) return -1;
    int data = (*queue)->data;
    Node* temp = *queue;
    *queue = (*queue)->next;
    free(temp);
    return data;
}

void bfs(Graph* graph, int start) {
    Node* queue = NULL;
    graph->visited[start] = 1;
    enqueue(&queue, start);

    while (!is_empty(queue)) {
        int current = dequeue(&queue);
        printf("%d ", current);

        Node* temp = graph->adjacency_lists[current];
        while (temp != NULL) {
            int adj_vertex = temp->data;
            if (!graph->visited[adj_vertex]) {
                graph->visited[adj_vertex] = 1;
                enqueue(&queue, adj_vertex);
            }
            temp = temp->next;
        }
    }
}

int main() {
    int nr_of_vertices;
    int nr_of_edges;
    int starting_vertex;

    printf("cate noduri are graful? ");
    scanf("%d", &nr_of_vertices);

    printf("cate muchii are graful? ");
    scanf("%d", &nr_of_edges);

    Graph* graph = create_graph(nr_of_vertices);
    insert_edges(graph, nr_of_edges);

    printf("de unde plecam in DFS? ");
    scanf("%d", &starting_vertex);
    printf("parcurgere cu DFS: ");
    dfs(graph, starting_vertex);

    reset_visited(graph);
    printf("\n");

    printf("de unde plecam in BFS? ");
    scanf("%d", &starting_vertex);
    printf("parcurgere cu BFS: ");
    bfs(graph, starting_vertex);

    printf("\n");

    return 0;
}
