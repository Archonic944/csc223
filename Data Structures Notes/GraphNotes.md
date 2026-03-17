# Graph Notes

## Introduction

A graph is an abstract data structure that implements the mathematical concept of graphs. It is a collection of vertices (nodes) and edges that connect them. Graphs are a generalization of trees; while trees have strict parent-child hierarchies, graphs allow for any kind of complex relationship.

## Basic Definitions

**Graph G**: Defined as an ordered set $(V, E)$, where $V(G)$ represents the set of vertices and $E(G)$ represents the set of edges.

**Undirected Graph**: A graph where edges do not have a direction. If an edge exists between A and B, it can be traversed in both directions.
```text
A --- B
|     |
D --- C
```

**Directed Graph (Digraph)**: A graph where every edge has a direction. Edges are represented as ordered pairs $(u, v)$, where the edge initiates at $u$ (initial node) and terminates at $v$ (terminal node).
```text
A --> B
^     |
|     v
D <-- C
```

## Graph Terminology

**Adjacent nodes (Neighbors)**: For an edge $e = (u, v)$, nodes $u$ and $v$ are end-points and are said to be adjacent or neighbors.

**Degree**: The total number of edges containing a node $u$. If $deg(u) = 0$, the node is known as an **isolated node**.

**Regular Graph**: A graph where every vertex has the same degree (e.g., a 2-regular graph where every node has degree 2).
```text
  A --- B
  |     |
  D --- C
```

**Path**: A sequence of nodes $(v_0, v_1, ..., v_n)$ where each $v_{i-1}$ is adjacent to $v_i$.
- **Length**: The number of edges in the path ($n$).
- **Closed path**: A path where the first and last nodes are the same ($v_0 = v_n$).
- **Simple path**: A path where all nodes are distinct (except possibly $v_0 = v_n$).

**Cycle**: A path where the first and last vertices are the same. A simple cycle has no repeated edges or vertices (other than the start/end).

**Connected Graph**: A graph where a path exists between any two vertices $(u, v)$.
- **Tree**: A connected graph with no cycles.

**Complete Graph**: A graph where every node is connected to every other node. It has $n(n-1)/2$ edges.

**Clique**: A subset of vertices where every two distinct vertices are adjacent.

**Weighted Graph (Labelled Graph)**: A graph where edges are assigned values (weights/costs/lengths).
```text
A --(4)-- B
|         |
(2)      (7)
|         |
D --(3)-- E
```

**Loop**: An edge that connects a node to itself $(u, u)$.
```text
  ____
 /    \
 \_u__/
```

**Multiple Edges (Parallel Edges)**: Distinct edges that connect the same two end-points.
```text
   __e1__
  /      \
 u        v
  \__e2__/
```

**Multi-graph**: A graph that contains multiple edges and/or loops.

**Size**: The total number of edges in the graph.

## Directed Graph Specifics

**In-degree**: The number of edges terminating at node $u$.

**Out-degree**: The number of edges originating at node $u$.

**Isolated vertex**: A vertex with degree zero; it is not an end-point of any edge.

**Pendant vertex (Leaf vertex)**: A vertex with degree one.

**Cut vertex**: A vertex which, when deleted, would disconnect the remaining graph.

**Successor/Predecessor**: In a directed edge $(u, v)$, $u$ is the predecessor (origin/initial point) and $v$ is the successor (destination/terminal point).

**Source**: A node $u$ with a positive out-degree but a zero in-degree.
```text
[Source] --> B
         --> C
```

**Sink**: A node $u$ with a positive in-degree but a zero out-degree.
```text
A --> [Sink]
B -->
```

**Reachability**: Node $v$ is reachable from $u$ if a directed path exists from $u$ to $v$.

**Connectivity Levels**:
1. **Strongly Connected**: A path exists between every pair of nodes in both directions ($u \to v$ and $v \to u$).
```text
A <--> B
^      ^
|      |
v <--> C
```
2. **Unilaterally Connected**: A path exists between any pair of nodes $u, v$ such that there is a path from $u \to v$ or $v \to u$, but not both.
3. **Weakly Connected**: The graph is connected only if the directions of the edges are ignored.

**Simple Directed Graph**: A directed graph with no parallel edges (it may contain cycles, but no more than one loop per node).

## Transitive Closure

The transitive closure of a directed graph $G = (V, E)$ is a graph $G^* = (V, E^*)$ where an edge $(v, w)$ exists in $E^*$ if and only if there is a path from $v$ to $w$ in $G$.

```text
Graph G:        Transitive Closure G*:
A --> B --> C   A --> B --> C
                |           ^
                \___________/
```

- **Purpose**: While a binary relation indicates only direct connectivity (A to B, B to C), the transitive closure allows for answering reachability questions (e.g., "Is node E reachable from node A in one or more hops?") in **O(1)** time once the closure is constructed. The algorithm to compute it typically has a complexity of **O(n³)**.
- **Storage**: Usually stored as a matrix $T$, where $T[i][j] = 1$ if node $j$ is reachable from node $i$ in one or more hops, and $0$ otherwise.
- **Applications**:
    - Reachability analysis in transition networks.
    - Construction of parsing automata in compilers.
    - Evaluating recursive database queries.
