/**
 * @author Mike Zrimsek
 * @version 01.29.2015
 */

public class LinkedStack<T> extends LinkedList<T>
{
	public LinkedStack()
	{
		super();
	}
	
	// add element to top of stack
	// returns true if data added successfully
	public boolean push(T data)
	{
		return add(data);
	}
	
	// look at element data on top of stack
	public T peek()
	{
		return get(size() - 1);
	}
	
	// get element data on top of stack
	public T pop()
	{
		T data = peek();
		remove(size() - 1);
		return data;
	}
}