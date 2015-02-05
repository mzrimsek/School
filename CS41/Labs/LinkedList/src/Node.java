/**
 * @author Mike Zrimsek
 * @version 02.05.2015
 * 
 *          Nodes are comparable 
 *          Nodes contain data that is comparable
 */

public class Node<T extends Comparable<T>> implements Comparable<Node<T>>
{
	private Node<T> prev;
	private Node<T> next;
	private T data;
	
	public Node(T data)
	{
		next = null;
		this.data = data;
	}
	
	public Node(T data, Node<T> next)
	{
		this.data = data;
		this.next = next;
	}
	
	public Node<T> getPrev()
	{
		return prev;
	}
	
	public void setPrev(Node<T> prev)
	{
		this.prev = prev;
	}
	
	public Node<T> getNext()
	{
		return next;
	}
	
	public void setNext(Node<T> next)
	{
		this.next = next;
	}
	
	public T getData()
	{
		return data;
	}
	
	public void setData(T data)
	{
		this.data = data;
	}
	
	public String toString()
	{
		return data.toString();
	}
	
	@Override
	public int compareTo(Node<T> that)
	{
		return this.data.compareTo(that.data);
	}
}
