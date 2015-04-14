/**
 * 
 * @author Mike Zrimsek
 * @version 04.14.2015
 */

import java.util.Scanner;

public class Tester
{
	public static void main(String[] args)
	{
		Scanner sc = new Scanner(System.in);
		System.out.print("How many vertices? ");
		int numVertices = sc.nextInt();
		
		Graph graph = new Graph(numVertices);
		
		for(int i = 0; i < numVertices; i++)
		{
			System.out.print("Label for vertex " + i + ": ");
			graph.setVertexLabel(i, sc.next());
		}
		
		String ans = "Y";
		do
		{
			System.out.println("Let's add an edge.");
			System.out.print("Vertex one label: ");
			String from = sc.next();
			
			System.out.print("Vertex two label: ");
			String to = sc.next();
			
			graph.addEdge(from, to);
			
			System.out.print("Would you like to add another? (Y/N) ");
			ans = sc.next();
		} while(ans.equalsIgnoreCase("Y"));
		
		sc.close();
		
		System.out.println(graph);
	}
}
