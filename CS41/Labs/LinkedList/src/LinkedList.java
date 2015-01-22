/**
 * @author Mike Zrimsek
 * @version 01.22.2015
 */

public class LinkedList
{
	private Node head;
	private int size;
	
	public LinkedList()
	{
		head = null;
		size = 0;
	}
	
	//add to end of list
	public void add(Object data)
	{
		if(head == null)
			addFirst(data);
		else
		{
			Node current = head;
			//navigate to end of list
			while(current.getNext() != null)
				current = current.getNext();
			current.setNext(new Node(data));
		}
		size++;
	}
	
	//add to end of list
	public void addFirst(Object data)
	{
		head = new Node(data, head);
		size++;
	}
	
	public Node getFirst()
	{
		return head;
	}
	
	public int getSize()
	{
		return size;
	}
}
