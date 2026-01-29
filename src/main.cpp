// part a
#include <iostream>
using namespace std;

const int MAXV = 100;
const int MAXDEG = 100;

int V, M;
bool isDirected;

int adj[MAXV][MAXDEG + 1];
int edgeCount;

void initGraph(int n, bool directed) {
    V = n;
    isDirected = directed;
    edgeCount = 0;
    for (int i = 0; i < V; i++) {
        adj[i][0] = 0;
    }
}

bool addNeighbor(int u, int v) {
    if (adj[u][0] >= MAXDEG) return false;
    adj[u][0]++;
    adj[u][adj[u][0]] = v;
    return true;
}

bool edgeExists(int u, int v) {
    for (int i = 1; i <= adj[u][0]; i++) {
        if (adj[u][i] == v) return true;
    }
    return false;
}

void addEdge(int u, int v) {
    if (!edgeExists(u, v)) addNeighbor(u, v);
    if (!isDirected && !edgeExists(v, u)) addNeighbor(v, u);
    edgeCount++;
}

void sortNeighbors() {
    for (int u = 0; u < V; u++) {
        int cnt = adj[u][0];
        for (int i = 1; i <= cnt; i++) {
            for (int j = i + 1; j <= cnt; j++) {
                if (adj[u][i] > adj[u][j]) {
                    int t = adj[u][i];
                    adj[u][i] = adj[u][j];
                    adj[u][j] = t;
                }
            }
        }
    }
}

//part b
void bfs(int start, int order[], int &orderLen, int dist[], int parent[]) {
    int visited[MAXV] = {0};
    int q[MAXV];
    int head = 0, tail = 0;

    for (int i = 0; i < V; i++) {
        dist[i] = -1;
        parent[i] = -1;
    }

    visited[start] = 1;
    dist[start] = 0;
    q[tail++] = start;
    orderLen = 0;

    while (head < tail) {
        int u = q[head++];
        order[orderLen++] = u;

        for (int i = 1; i <= adj[u][0]; i++) {
            int v = adj[u][i];
            if (!visited[v]) {
                visited[v] = 1;
                dist[v] = dist[u] + 1;
                parent[v] = u;
                q[tail++] = v;
            }
        }
    }
}

void shortestPath(int s, int t, int parent[], int dist[]) {
    if (dist[t] == -1) {
        cout << "No path\n";
        return;
    }

    int path[MAXV];
    int len = 0;
    int cur = t;

    while (cur != -1) {
        path[len++] = cur;
        cur = parent[cur];
    }

    for (int i = len - 1; i >= 0; i--) {
        cout << path[i];
        if (i) cout << "-";
    }
    cout << "\n";
}
//part c 
void dfsRecUtil(int u, int visited[], int order[], int &len) {
    visited[u] = 1;
    order[len++] = u;

    for (int i = 1; i <= adj[u][0]; i++) {
        int v = adj[u][i];
        if (!visited[v]) dfsRecUtil(v, visited, order, len);
    }
}

void dfsRecursive(int start, int order[], int &len) {
    int visited[MAXV] = {0};
    len = 0;
    dfsRecUtil(start, visited, order, len);
}

void dfsIterative(int start, int order[], int &len) {
    int visited[MAXV] = {0};
    int stack[MAXV];
    int top = 0;
    len = 0;

    stack[top++] = start;

    while (top) {
        int u = stack[--top];
        if (visited[u]) continue;

        visited[u] = 1;
        order[len++] = u;

        for (int i = adj[u][0]; i >= 1; i--) {
            int v = adj[u][i];
            if (!visited[v]) stack[top++] = v;
        }
    }
}

bool dfsCycle(int u, int parent, int visited[]) {
    visited[u] = 1;
    for (int i = 1; i <= adj[u][0]; i++) {
        int v = adj[u][i];
        if (!visited[v]) {
            if (dfsCycle(v, u, visited)) return true;
        } else if (v != parent) {
            return true;
        }
    }
    return false;
}

void connectedComponents() {
    int visited[MAXV] = {0};
    int comp = 0;

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            comp++;
            cout << "Component " << comp << ": ";
            int stack[MAXV], top = 0;
            stack[top++] = i;

            while (top) {
                int u = stack[--top];
                if (visited[u]) continue;
                visited[u] = 1;
                cout << u << " ";

                for (int j = adj[u][0]; j >= 1; j--) {
                    int v = adj[u][j];
                    if (!visited[v]) stack[top++] = v;
                }
            }
            cout << "\n";
        }
    }
}
//part d
int main() {
    int directed;
    cin >> V >> M >> directed;
    initGraph(V, directed);

    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        addEdge(u, v);
    }

    sortNeighbors();

    int S, T;
    cin >> S >> T;

    int bfsOrder[MAXV], bfsLen;
    int dist[MAXV], parent[MAXV];
    bfs(S, bfsOrder, bfsLen, dist, parent);

    cout << "BFS: ";
    for (int i = 0; i < bfsLen; i++) cout << bfsOrder[i] << " ";
    cout << "\n";

    cout << "Shortest path: ";
    shortestPath(S, T, parent, dist);

    int dfsR[MAXV], dfsRLen;
    dfsRecursive(S, dfsR, dfsRLen);
    cout << "DFS recursive: ";
    for (int i = 0; i < dfsRLen; i++) cout << dfsR[i] << " ";
    cout << "\n";

    int dfsI[MAXV], dfsILen;
    dfsIterative(S, dfsI, dfsILen);
    cout << "DFS iterative: ";
    for (int i = 0; i < dfsILen; i++) cout << dfsI[i] << " ";
    cout << "\n";

    if (!isDirected) {
        connectedComponents();
        int visited[MAXV] = {0};
        cout << "Cycle: " << (dfsCycle(0, -1, visited) ? "YES" : "NO") << "\n";
    }

    return 0;
}
