/**
 * @author Mike Zrimsek
 * @version 01.21.2015
 */

public class LinkedList
{
	private Node head;
	private int size;
	
	public LinkedList()
	{
		head = new Node(null);
		size = 0;
	}
	
	public void add(Object data)
	{
		Node temp = new Node(data);
		Node current = head;
		
		//navigate to end of list
		while(current.getNext() != null)
			current = current.getNext();
		
		current.setNext(temp);
		size++;
	}
	
	public int getSize()
	{
		return size;
	}
	
	public void reverse()
	{
		Node current = head;
		Node reversed = null;
		
		while(current != null)
		{
			Node next = current.getNext();
			current.setNext(reversed);
			reversed = current;
			current = next;
		}
		
		head = reversed;
	}
	
	public String toString()
	{
		String output = "";
		Node n = head.getNext();
		while(n != null)
		{
			output += n.getData() + " ";
			n = n.getNext();
		}
		return output;
	}
}
