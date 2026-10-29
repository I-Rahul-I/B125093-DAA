// Question 2 :
// [Multi-Source BFS for Radius-Constrained Voronoi Cell Partitioning] You are given:
// ◦ An unweighted, undirected graph G = (V,E).
// ◦ A set of K designated hub vertices H = {h1,h2,...,hK} ⊆ V , indexed from 1 to K.
// ◦ An integer radius threshold R ≥ 0.
// Let dist(u,v) denote the shortest path distance (minimum number of edges) between
// vertices u and v in G.
// For every vertex v ∈ V , assign an ownership label owner[v] ∈ {1,2,...,K}∪{−1}
// according to the following rules:
// 1.	Distance Metric: Find the distance from v to each service hub: di = dist(v,hi)for
// all i ∈ {1,...,K}. Let dmin(v) = min1≤i≤K di.
// 2.	Reachability Threshold (R): If dmin(v) > R, vertex v lies outside the service 
// coverage area. Set owner[v] = −1.
// 3.	Closest Hub Assignment: If dmin(v) ≤ R, assign v to the hub hi that minimizes di.
// 4.	Deterministic Tie-Breaking: If multiple hubs achieve the exact same minimum
// distance
// dmin(v), choose the hub with the smallest numerical index i.
// Objective: Output the array owner[︁1...|V |]︁ containing the assigned hub index 
// (or −1 if unassigned) and the corresponding shortest distance to that hub for every
// vertex. By choosing the proper input representation, write a program in C to validate
// your algorithm and derive the complexity analysis of your algorithm.


// CODE---
#include <stdio.h>
#include <stdlib.h>
#define MAXV 100005
#define MAXE 400005
typedef struct {
    int to;
    int next;
} Edge;
Edge edges[MAXE];
int head[MAXV];
int edgeCount = 0;
int dist[MAXV];
int owner[MAXV];
int visited[MAXV];
int queue[MAXV];
void addEdge(int u, int v) {
    edges[edgeCount].to = v;
    edges[edgeCount].next = head[u];
    head[u] = edgeCount++;
    edges[edgeCount].to = u;
    edges[edgeCount].next = head[v];
    head[v] = edgeCount++;
}
void multiSourceBFS(int n, int K, int hubs[], int R) {
    int front = 0, rear = 0;
    for (int i = 1; i <= n; i++) {
        dist[i] = -1;
        owner[i] = -1;
        visited[i] = 0;
    }
    // Insert hubs in increasing hub-index order.
    for (int i = 1; i <= K; i++) {
        int h = hubs[i];
        visited[h] = 1;
        dist[h] = 0;
        owner[h] = i;
        queue[rear++] = h;
    }
    while (front < rear) {
        int u = queue[front++];
        // Do not expand beyond the radius.
        if (dist[u] >= R)
            continue;
        for (int e = head[u]; e != -1; e = edges[e].next) {
            int v = edges[e].to;
            if (!visited[v]) {
                visited[v] = 1;
                dist[v] = dist[u] + 1;
                owner[v] = owner[u];
                queue[rear++] = v;
            }
        }
    }
}
int main(void) {
    int n, m, K, R;
    int hubs[MAXV];
    printf("Enter vertices, edges, number of hubs and radius:\n");
    scanf("%d %d %d %d", &n, &m, &K, &R);
    for (int i = 1; i <= n; i++) head[i] = -1;
    int isHub[MAXV] = {0};
    printf("Enter the hub vertices in index order:\n");
    for (int i = 1; i <= K; i++) {
        scanf("%d", &hubs[i]);
        isHub[hubs[i]] = 1;
    }
    printf("Enter the undirected edges (u v):\n");
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v);
    }
    multiSourceBFS(n, K, hubs, R);
    printf("\nVertex\tOwner\tDistance\n");
    for (int v = 1; v <= n; v++) printf("%d\t%d\t%d\n", v, owner[v], dist[v]);
    return 0;
}
//Complexity Analysis
//Time complexity O(V+E)
//Space complexity O(V+E)