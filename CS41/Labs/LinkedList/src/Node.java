/**
 * @author Mike Zrimsek
 * @version 01.21.2015
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
	
	public Node(Node next, Object data)
	{
		this.next = next;
		this.data = data;
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
