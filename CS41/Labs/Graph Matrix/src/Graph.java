/**
 * 
 * @author Mike Zrimsek
 * @version 04.14.2015
 *
 */
public class Graph
{
	private int numVertices;
	private String[] labels;
	private int[][] matrix;
	
	public Graph(int numVertices)
	{
		this.numVertices = numVertices;
		labels = new String[numVertices];
		matrix = new int[numVertices][numVertices];
	}
	
	public void setVertexLabel(int vertex, String label)
	{
		labels[vertex] = label;
	}
	
	private int getVertexIndex(String label)
	{
		for(int i = 0; i < labels.length; i++)
			if(labels[i].equals(label)) return i;
		
		return -1;
	}
	
	public void addEdge(String from, String to)
	{
		int v1 = getVertexIndex(from);
		int v2 = getVertexIndex(to);
		
		if(v1 == -1 || v2 == -1)
		{
			System.out.println("One or more invalid vertex.");
			return;
		}
		addEdge(v1, v2);
	}
	
	private void addEdge(int from, int to)
	{
		if(edgeExists(from, to))
		{
			System.out.println("Edge already exists!");
			return;
		}
		matrix[from][to] = 1;
	}
	
	private boolean edgeExists(int from, int to)
	{
		return matrix[from][to] == 1;
	}
	
	public String toString()
	{
		String output = "Edges:\n";
		for(int i = 0; i < numVertices; i++)
		{
			for(int j = 0; j < numVertices; j++)
			{
				if(matrix[i][j] == 1)
				{
					output +=  labels[i] + " to " + labels[j] + "\n";
				}
			}
		}
		return output;
	}
}
