import java.io.*;
import java.util.*;

// === 自作 PriorityQueue (前回と同じ) ===
class MinPriorityQueue<T> {
    private final List<T> heap = new ArrayList<>();
    private final Comparator<T> comparator;

    public MinPriorityQueue(Comparator<T> comparator) {
        this.comparator = comparator;
    }

    public void add(T item) {
        heap.add(item);
        heapifyUp(heap.size() - 1);
    }

    public T extractMin() {
        if (heap.isEmpty()) return null;
        T min = heap.get(0);
        T last = heap.remove(heap.size() - 1);
        if (!heap.isEmpty()) {
            heap.set(0, last);
            heapifyDown(0);
        }
        return min;
    }

    public boolean isEmpty() {
        return heap.isEmpty();
    }

    private void heapifyUp(int idx) {
        while (idx > 0) {
            int parent = (idx - 1) / 2;
            if (comparator.compare(heap.get(idx), heap.get(parent)) >= 0) break;
            swap(idx, parent);
            idx = parent;
        }
    }

    private void heapifyDown(int idx) {
        int size = heap.size();
        while (true) {
            int smallest = idx;
            int left = 2 * idx + 1;
            int right = 2 * idx + 2;

            if (left < size && comparator.compare(heap.get(left), heap.get(smallest)) < 0) {
                smallest = left;
            }
            if (right < size && comparator.compare(heap.get(right), heap.get(smallest)) < 0) {
                smallest = right;
            }
            if (smallest == idx) break;
            swap(idx, smallest);
            idx = smallest;
        }
    }

    private void swap(int i, int j) {
        T tmp = heap.get(i);
        heap.set(i, heap.get(j));
        heap.set(j, tmp);
    }
}

// === Edge, Graph ===
class Edge {
    int to;
    long weight;

    public Edge(int to, long weight) {
        this.to = to;
        this.weight = weight;
    }
}

class WeightedGraph {
    private final int V;
    private final List<List<Edge>> adj;

    public WeightedGraph(int V) {
        this.V = V;
        adj = new ArrayList<>();
        for (int i = 0; i < V; i++) {
            adj.add(new ArrayList<>());
        }
    }

    public void addEdge(int from, int to, long weight) {
        adj.get(from).add(new Edge(to, weight));
        // 無向グラフにする場合:
        // adj.get(to).add(new Edge(from, weight));
    }

    public List<Edge> getNeighbors(int v) {
        return adj.get(v);
    }

    public int getNumVertices() {
        return V;
    }
}

// === Dijkstra ===
class Dijkstra {
    private final WeightedGraph graph;
    private long[] dist;
    private int[] prev;

    public Dijkstra(WeightedGraph graph) {
        this.graph = graph;
    }

    public void shortestPaths(int source) {
        int V = graph.getNumVertices();
        dist = new long[V];
        prev = new int[V];
        Arrays.fill(dist, Long.MAX_VALUE);
        Arrays.fill(prev, -1);
        dist[source] = 0;

        class Node {
            int vertex;
            long distance;

            Node(int vertex, long distance) {
                this.vertex = vertex;
                this.distance = distance;
            }
        }

        MinPriorityQueue<Node> pq = new MinPriorityQueue<>(
            Comparator.comparingLong(node -> node.distance)
        );
        pq.add(new Node(source, 0));

        while (!pq.isEmpty()) {
            Node node = pq.extractMin();
            int u = node.vertex;

            for (Edge edge : graph.getNeighbors(u)) {
                int v = edge.to;
                long weight = edge.weight;

                if (dist[u] != Long.MAX_VALUE && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    prev[v] = u;
                    pq.add(new Node(v, dist[v]));
                }
            }
        }
    }

    public long getDistance(int target) {
        return dist[target];
    }

    public List<Integer> getPath(int target) {
        List<Integer> path = new ArrayList<>();
        if (dist[target] == Long.MAX_VALUE) return path; // 到達不可
        for (int at = target; at != -1; at = prev[at]) {
            path.add(at);
        }
        Collections.reverse(path);
        return path;
    }
}

// === メイン ===
public class Main {
    public static void main(String[] args) throws IOException {
        if (args.length != 3) {
            System.err.println("Usage: java Main <filename> <source> <target>");
            System.exit(1);
        }

        String filename = args[0];
        int source = Integer.parseInt(args[1]);
        int target = Integer.parseInt(args[2]);

        WeightedGraph graph = readGraphFromFile(filename);

        Dijkstra dijkstra = new Dijkstra(graph);
        dijkstra.shortestPaths(source);

        List<Integer> path = dijkstra.getPath(target);
        if (path.isEmpty()) {
            System.out.println("No path");
        } else {
            for (int v : path) {
                System.out.print(v + " ");
            }
            System.out.println();
            System.out.println(dijkstra.getDistance(target));
        }
    }

    private static WeightedGraph readGraphFromFile(String filename) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader(filename));
        int V = Integer.parseInt(br.readLine().trim());
        WeightedGraph graph = new WeightedGraph(V);

        String line;
        while ((line = br.readLine()) != null) {
            String[] parts = line.trim().split("\\s+");
            if (parts.length != 3) continue;
            int from = Integer.parseInt(parts[0]);
            int to = Integer.parseInt(parts[1]);
            long weight = Long.parseLong(parts[2]);
            graph.addEdge(from, to, weight);
        }

        br.close();
        return graph;
    }
}

