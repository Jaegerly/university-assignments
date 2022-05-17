/**
 * class CSCI463ProjFive. It is an interactive test class for MyGraph
 * 
 * @author Hongbiao Zeng
 * @version Dec 11, 2015
 */
import java.util.Scanner;

public class CSCI463ProjFive
{
   public static void main(String args[]){
        int numberOfVertices;
        String result;
        int [][] graphRep;
        int startVertex;
        int choice;
        Scanner input = new Scanner(System.in);
        MyGraph graph = null;
       
        do{
            menu();
            System.out.print("Enter your choice: ");
            choice = input.nextInt();
            switch(choice){
            case 1:
                System.out.println("Enter an graph.");
                System.out.print("First enter the number of vertices: ");
                numberOfVertices = input.nextInt();
                graphRep = new int[numberOfVertices+1][numberOfVertices+1];
                System.out.println("Enter the matrx reprentation of the graph.");
                System.out.println("If no edge between two vertices, enter 0");
                for(int i = 1; i<= numberOfVertices; i++){
                    for(int j = 1; j <= numberOfVertices; j++){
                        graphRep[i][j] = input.nextInt();
                    }
                }
                graph = new MyGraph(graphRep);
                break;
            case 2: 
                System.out.print("Enter the start vertex: ");
                startVertex = input.nextInt();
                result = graph.bfs(startVertex);
                if(result == null)
                    System.out.println("No such a start vertex");   
                else
                    System.out.println("The result for BFS is: " + result);
                break;
            case 3:
                System.out.print("Enter the start vertex: ");
                startVertex = input.nextInt();
                result = graph.dfs(startVertex);
                if(result == null)
                    System.out.println("No such a start vertex");   
                else
                    System.out.println("The result for DFS is: " + result);
                break;
            case 4:
                System.out.println("Make sure you run enough test before you turn it in");
                break;
            default:
                System.out.println("Wrong option. Please choose from menu");
                break;
            }
        }while(choice != 4);
        
    }
    
    private static void menu(){
        System.out.println("*********************************");
        System.out.println("*              MENU             *");
        System.out.println("* 1. Enter a graph              *");
        System.out.println("* 2. Breadth First Search       *");
        System.out.println("* 3. Depth First Search         *");
        System.out.println("* 4. Quit                       *");
        System.out.println("********************************");
    }
}