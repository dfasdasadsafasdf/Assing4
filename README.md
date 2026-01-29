# Assignment 4 — Graph, BFS and DFS


## Description
This project implements a graph data structure and basic graph traversal algorithms.
The graph is represented using an adjacency list. Breadth-First Search (BFS) and
Depth-First Search (DFS) are implemented according to the assignment requirements.

## Implemented features
- Graph ADT (directed and undirected)
- Adjacency list representation
- Breadth-First Search (BFS)
- Depth-First Search (DFS)
- Shortest path in unweighted graph using BFS
- Connected components
- Cycle detection

## Input format
The program reads input from standard input.

- First line: number of vertices, number of edges, graph type (0 – undirected, 1 – directed)
- Next lines: edges (u v)
- Last line: start and target vertices

Example input is provided in `tests/test1.txt`.

## Build
```bash
g++ -std=c++17 src/main.cpp -o graph

## Run
./graph < tests/test1.txt

