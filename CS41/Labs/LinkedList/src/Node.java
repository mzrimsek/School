/**
 * @author Mike Zrimsek
 * @version 01.22.2015
 */

public class Node
{
	private Node next;
	private Object data;
	
	public Node(Object data)
	{
		next = null;
		this.data = data;
	}
	
	public Node(Object data, Node next)
	{
		this.data = data;
		this.next = next;
	}
	
	public Node getNext()
	{
		return next;
	}
	
	public void setNext(Node next)
	{
		this.next = next;
	}

	public Object getData()
	{
		return data;
	}

	public void setData(Object data)
	{
		this.data = data;
	}
}
