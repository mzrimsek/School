/**
 * 
 * @author Mike Zrimsek
 * @version 02.10.2015
 *
 */
public class LinkedQueue<T extends Comparable<T>> extends LinkedList<T>
{
	public LinkedQueue()
	{
		super();
	}
	
	//gets the top element in the queue
	public T dequeue()
	{
		T data = get(size() - 1);
		remove(size() - 1);
		return data;
	}
	
	//adds data to the end of the queue
	public boolean enqueue(T data)
	{
		return add(data, 0);
	}
	
	public T peek()
	{
		return get(size() - 1);
	}
}
