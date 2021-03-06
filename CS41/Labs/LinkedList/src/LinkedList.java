/**
 * @author Mike Zrimsek
 * @version 02.09.2015
 * 
 *          Doubly Linked Linked List List type must be comparable
 */

public class LinkedList<T extends Comparable<T>>
{
	private Node<T> head;
	private Node<T> tail;
	private int size;
	
	public LinkedList()
	{
		head = null;
		tail = null;
		size = 0;
	}
	
	// creates a LinkedList of a set size
	// all data is null by default
	public LinkedList(int size)
	{
		for (int i = 0; i < size; i++)
		{
			this.add(null);
		}
	}
	
	// add to end of list
	// returns true if added at index successfully
	public boolean add(T data)
	{
		return add(data, size);
	}
	
	// add to position in list
	// returns true if added at index successfully
	public boolean add(T data, int n)
	{
		if (!isValidIndex(n))
			return false;
		else if (empty()) // assign head to new node
		{
			head = new Node<T>(data);
			tail = head;
		}
		else if (n == 0) // add to front of non empty list
		{
			if (head.getNext() == null) // if list is size 1
				tail = head; // tail is old head
			Node<T> temp = new Node<T>(data, head); // new node before head
			head.setPrev(temp); // set head to reference new front node
			head = temp; // reassign head
		}
		else if (n == size)
		{
			Node<T> temp = new Node<T>(data); // new node after tail
			tail.setNext(temp); // set tail to reference new end node
			temp.setPrev(tail); // set new end to reference old tail
			tail = temp; // set tail to new end node
		}
		else
		{
			Node<T> current = getNode(n); // get current position node
			Node<T> prev = current.getPrev(); // get previous node to current
												// node
			Node<T> temp = new Node<T>(data, current); // new node to be added
														// before current
			
			prev.setNext(temp); // set previous next to new node
			temp.setPrev(prev); // set new node previous to previous
			current.setPrev(temp); // set current previous to temp
		}
		size++;
		return true;
	}
	
	// sets Node data at index
	// returns true if index set successfully
	public boolean set(T data, int n)
	{
		if (!isValidIndex(n) || empty())
			return false;
		else getNode(n).setData(data);
		return true;
	}
	
	// add to sorted position in list
	// assumes list is sorted when adding
	public boolean insert(T data)
	{
		Node<T> temp = new Node<T>(data);
		// if empty or greater than last node
		if (empty() || temp.compareTo(head) < 0) // if less than first node
			return add(data, 0); // add to front
		else if (temp.compareTo(tail) > 0)
			return add(data); // add to end
		else
		// find position in list where data should be inserted
		{
			int pos = 0;
			for (int i = 0; i < size; i++)
				if (temp.compareTo(getNode(i)) >= 0) pos++;
			return add(data, pos);
		}
	}
	
	// remove at position
	// returns true if index removed successfully
	public boolean remove(int n)
	{
		if (!isValidIndex(n) || empty())
			return false;
		else if (n == 0) // remove from front
		{
			head = head.getNext(); // set head to next node
			head.setPrev(null); // set previous to null - end of list
		}
		else if (n == size - 1) // remove from last index
		{
			tail = tail.getPrev(); // set prev to last node
			tail.setNext(null); // set next to null - end of list
		}
		else
		{
			Node<T> current = getNode(n);
			Node<T> prev = current.getPrev();
			Node<T> next = current.getNext();
			
			current = null;
			prev.setNext(next);
			next.setPrev(prev);
		}
		size--;
		return true;
	}
	
	// get Node data at position
	public T get(int n)
	{
		if (!isValidIndex(n)) return null;
		return getNode(n).getData();
	}
	
	// get node at position
	protected Node<T> getNode(int n)
	{
		if (n == 0) // get first node
			return head;
		else if (n == size - 1) // get last node
			return tail;
		else
		{
			Node<T> current = head; // traverse from end of list
			for (int i = 0; i < size && current != null; i++)
			{
				if (i == n) break;
				current = current.getNext();
			}
			return current;
		}
	}
	
	// check if index being passed in is valid
	// must be less than list size and cannot be negative
	private boolean isValidIndex(int n)
	{
		return n < size || n >= 0;
	}
	
	// check if list is empty
	public boolean empty()
	{
		return size == 0 && head == null && tail == null;
	}
	
	// return size of list
	public int size()
	{
		return size;
	}
	
	protected LinkedList<T> reverseList()
	{
		LinkedList<T> reversedList = new LinkedList<T>();
		
		Node<T> current = tail;
		for (int i = 0; i < size && current != null; i++)
		{
			reversedList.add(current.getData());
			current = current.getPrev();
		}
		
		return reversedList;
	}
	
	// return reversed contents of list
	public String reverse()
	{
		return reverseList().toString();
	}
	
	// return contents of list
	public String toString()
	{
		String output = "[ ";
		Node<T> current = head;
		for (int i = 0; i < size && current != null; i++)
		{
			output += current.getData() + ", ";
			current = current.getNext();
		}
		return output.substring(0, output.lastIndexOf(',')) + " ]";
	}
}
