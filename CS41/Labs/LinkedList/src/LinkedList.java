/**
 * @author Mike Zrimsek
 * @version 01.27.2015
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
	
	// add to end of list
	public void add(T data)
	{
		if (head == null)
			addFirst(data);
		else
		{
			Node<T> current = head;
			// navigate to end of list
			while (current.getNext() != null)
				current = current.getNext();
			current.setNext(new Node<T>(data));
			size++;
		}
	}
	
	// add to position in list
	public void add(T data, int n)
	{
		if (n - 1 > size)
			System.out.println("Invalid index");
		else if (head == null || n == 0) // empty list or add to first
			addFirst(data);
		else
		{
			Node<T> current = head;
			for (int i = 0; i < size && current != null; i++)
			{
				if (i == n - 1) // found where we are inserting to
				{
					Node<T> next = current.getNext();
					Node<T> temp = new Node<T>(data);
					current.setNext(temp);
					temp.setNext(next);
					size++;
					return;
				}
				current = current.getNext();
			}
		}
	}
	
	// get Node at index
	public Node<T> get(int n)
	{
		if (n - 1 > size)
		{
			System.out.println("Invalid index");
			return null;
		} else if (size == 0)
			return null;
		else if (size == 1)
			return head;
		else
		{
			Node<T> current = head;
			for (int i = 0; i < size && current != null; i++)
			{
				if (i == n)
					return current;
				current = current.getNext();
			}
			System.out.println("Node not found at index."); // ??
			return null;
		}
	}
	
	// remove at position
	public void remove(int n)
	{
		// should be similar to add at position
	}
	
	// add to end of list
	public void addFirst(T data)
	{
		head = new Node<T>(data, head);
		size++;
	}
	
	public Node<T> getFirst()
	{
		return head;
	}
	
	public boolean empty()
	{
		return size == 0;
	}
	
	public int size()
	{
		return size;
	}
	
	public void print()
	{
		System.out.print("\n[ ");
		Node<T> current = head;
		for (int i = 0; i < size && current != null; i++)
		{
			System.out.print(current.getData() + " ");
			current = current.getNext();
		}
		System.out.println("]");
	}
}
