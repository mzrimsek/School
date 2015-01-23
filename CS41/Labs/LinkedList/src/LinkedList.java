/**
 * @author Mike Zrimsek
 * @version 01.22.2015
 */

public class LinkedList<T>
{
	private Node<T> head;
	private int size;
	
	public LinkedList()
	{
		head = null;
		size = 0;
	}
	
	//add to end of list
	public void add(T data)
	{
		if(head == null)
			addFirst(data);
		else
		{
			Node<T> current = head;
			//navigate to end of list
			while(current.getNext() != null)
				current = current.getNext();
			current.setNext(new Node<T>(data));
		}
		size++;
	}
	
	//add to sorted position in list
	public void insert(T data)
	{
		Node<T> current = head;
		Node<T> temp = new Node<T>(data);
		if(current == null)
			add(data);
		else
		{
			while(current.getNext() != null)
			{
				//new data is bigger
				if(current.compareTo(temp) > 0)
				{
					Node<T> next = current.getNext();
					current.setNext(temp);
					temp.setNext(next);
				}
				//new data is smaller
				else if(current.compareTo(temp) < 0)
				{
					
					temp.setNext(current);
					
				}
				current = current.getNext();
			}
		}
	}
	
	//add to end of list
	public void addFirst(T data)
	{
		head = new Node<T>(data, head);
		size++;
	}
	
	public Node<T> getFirst()
	{
		return head;
	}
	
	public int getSize()
	{
		return size;
	}
	
	public void print()
	{
		System.out.print("\n[ ");
		Node<T> current = head;
		for(int i = 0; i < size && current != null; i++)
		{
			System.out.print(current.getData() + " ");
			current = current.getNext();
		}
		System.out.println("]");
	}
}
