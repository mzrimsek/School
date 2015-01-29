/**
 * @author Mike Zrimsek
 * @version 01.28.2015
 */

public class LinkedStack<T> extends LinkedList<T> 
{
	public LinkedStack()
	{
		super();
	}
	
	//add element to top of stack
	public void push(T data)
	{
		add(data);
	}
	
	//look at element data on top of stack
	public T peek()
	{
		return get(size()-1);
	}
	
	//get element data on top of stack
	public T pop()
	{
		remove(size()-1);
		return peek();
	}
}
