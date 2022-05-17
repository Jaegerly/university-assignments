
/**
 * class MyGraph. Will use Matrix to represent a simple weighted directed graph. There is no loop at vertex.
 * No more than one edge from vertex i to another vertex j. The vertices are numbered as 1, 2, ..., n
 * The graph with n vertices is reprented by an (n+1) by (n+1) matrix with row 0 and column 0 unused.
 * If there is an edge from vertex i to vertex j (i != j), then entry on row i column j of the matrix will 
 * be 1. If there is no edge between vertex i to vertex j (i != j), then the entry on row i column j of the 
 * matrix will be Integer.MAX_VALUE
 * 
 * @author Johan Jaeger
 * @version April 20, 2022
 */
import java.util.*;
public class MyGraph
{
    private int[][] graph;
    private int numberOfVertices;
    
    /**
     * create a graph with given number of vertices with no edges
     * @param numberOfVertices number of vertices of the graph
     */
    public MyGraph(int numberOfVertices){
        this.numberOfVertices = numberOfVertices;
        graph = new int[numberOfVertices+1][numberOfVertices+1];
    }
    
    /**
     * create a graph with given matrix representation
     * @param graph The matrix representation on the given graph. Assume column 0 and row 0 are not used
     */
    public MyGraph(int [][] graph){
        this.graph = graph;
        // change any 0 to infinity if the 0 is not on diagonal
        for(int i = 1; i < graph.length; i++){
            for(int j = 1; j < graph.length; j++){
                if(i == j) graph[i][j] = 0;
                else if(i != j && graph[i][j] == 0)
                    graph[i][j] = Integer.MAX_VALUE;
            }
        }
        numberOfVertices = graph.length - 1; 
    }
    
    /**
     * return a String that represent the vertices in order if the BFS algorithm is used to traversal the graph
     * starting from the given vertex. If the startVertex not exists, return an error message
     * @param startVertex The vertex where the traversal starts
     * @return A String that describes the vertices visited in order
     */
    public String bfs(int startVertex){
        if (startVertex > (graph.length - 1))
            return "vertex does not exist in graph.";
        
        /* string to return. */
        String traversal = "";
        
        /* frontier queue. */
        Queue<Integer> frontier = new LinkedList<> ();

        /* each index after position 0 corresponds to vertex. a value of 0 means vertex is not present. */
        int [] discovered = new int[numberOfVertices + 1];

        /* manage starting vertex. */
        frontier.add(startVertex);
        discovered[startVertex] = 1;

        while (!frontier.isEmpty()) { /* algorithm stops when frontier is empty. */
            int currentVertex = frontier.remove(); /* remove vertex from queue. */
            traversal = traversal + currentVertex + ' '; /* add vertex to string. */

            for (int i = 1; i < graph.length; ++i) { /* add adjacent vertices to queue that haven't yet been visited. */
                int edge = graph[currentVertex][i];
                if (edge < Integer.MAX_VALUE && discovered[i] == 0) {
                    frontier.add(i);
                    discovered[i] = 1;
                }
            }
        }

        return traversal; /* return string. */
    }
    
    /**
     * return a String that represents the vertices in order if the DFS algorithm is used to traversal the graph
     * starting from the given vertex. If the startVertex not exist, return an error message
     * @param startVertex The vertex where the traversal starts
     * @return An ArrayList of Integer that represents the vertices visited in order
     */
    public String dfs(int startVertex){
        if (startVertex > (graph.length - 1))
            return "vertex does not exist in graph.";
        
        /* string to return. */
        String traversal = "";

        /* stack construct for algorithm. */
        Stack<Integer> stack = new Stack<> ();

        /* each index after position 0 corresponds to vertex. a value of 0 means vertex is not present. */
        int [] visited = new int[numberOfVertices + 1];

        stack.push(startVertex);

        while (!stack.isEmpty()) { /* algorithm stops when stack is empty. */
            int currentVertex = stack.pop(); /* pop vertex from stack. */

            if (visited[currentVertex] == 0) { /* if vertex has not been visited. */
                traversal = traversal + currentVertex + ' '; /* concatenate vertex with string. */
                visited[currentVertex] = 1; /* mark vertex as visited. */

                for (int i = numberOfVertices; i > 0; --i) { /* push adjacent vertices to stack. */
                    int edge = graph[currentVertex][i];
                    if (edge < Integer.MAX_VALUE)
                        stack.push(i);
                }
            }
        }

        return traversal; /* return string. */
    }
}