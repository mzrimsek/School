/**
 * @author Mike Zrimsek
 * @version 01.28.2015
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
		add(data, size);
	}
	
	// add to position in list
	public void add(T data, int n)
	{
		if (!isValidIndex(n))
			return;
		else if (empty() || n == 0) 
			head = new Node<T>(data, head);
		else
		{
			Node<T> prev = getNode(n - 1);
			Node<T> current = prev.getNext();
			Node<T> temp = new Node<T>(data);
			
			prev.setNext(temp);
			temp.setNext(current);
		}
		size++;
	}
	
	public void set(T data, int n)
	{
		if (!isValidIndex(n) || empty())
			return;
		else
			getNode(n).setData(data);
	}
	
	//add to sorted position in list
	public void insert(T data)
	{
		Node<T> temp = new Node<T>(data);
		if (empty() || temp.compareTo(getNode(size-1)) > 0)
			add(data);
		else if (temp.compareTo(head) < 0)
			add(data, 0);
		else
		{
			int pos = 0;
			for (int i = pos; i < size; i++)
				if (temp.compareTo(getNode(i)) >= 0) pos = i;
			add(data, pos + 1);
		}
	}
	
	// remove at position
	public void remove(int n)
	{
		if (!isValidIndex(n) || empty())
			return;
		else if (n == 0)
			head = head.getNext();
		else
		{
			Node<T> prev = getNode(n - 1);
			Node<T> current = prev.getNext();
			Node<T> next = current.getNext();
			
			prev.setNext(next);
			current = null;
		}
		size--;
	}
	
	// get Node data at position
	public T get(int n)
	{
		if (!isValidIndex(n)) return null;
		return getNode(n).getData();
	}
	
	// get node at position
	private Node<T> getNode(int n)
	{
		Node<T> current = head;
		for (int i = 0; i < size && current != null; i++)
		{
			if (i == n) break;
			current = current.getNext();
		}
		return current;
	}
	
	// check if index being passed in is valid
	// must be less than list size and cannot be negative
	private boolean isValidIndex(int n)
	{
		boolean val = n < size || n >= 0;
		if (val == false) System.out.println("Invalid index");
		return val;
	}
	
	// check if list is empty
	public boolean empty()
	{
		return size == 0 && head == null;
	}
	
	// return size of list
	public int size()
	{
		return size;
	}
	
	// return contents of list
	public String toString()
	{
		String output = "[ ";
		for (int i = 0; i < size; i++)
			output += get(i) + " ";
		return output + "]";
	}
}
