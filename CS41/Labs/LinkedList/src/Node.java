/**
 * @author Mike Zrimsek
 * @version 02.03.2015
 */

public class Node<T>
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
	
	public int compareTo(Node<T> that)
	{
		return this.data.hashCode() - that.getData().hashCode();
	}
}
