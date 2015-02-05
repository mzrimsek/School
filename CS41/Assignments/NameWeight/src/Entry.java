/**
 * 
 * @author Mike Zrimsek
 * @version 02.05.2015
 *
 */

public class Entry<T extends Comparable<T>> implements Comparable<Entry<T>>
{
	T data;
	Entry<?> pointer;
	
	public Entry(T data)
	{
		this.data = data;
		pointer = null;
	}
	
	public T getData()
	{
		return data;
	}
	
	public void setData(T data)
	{
		this.data = data;
	}
	
	public Entry<?> getPointer()
	{
		return pointer;
	}
	
	public void setPointer(Entry<?> pointer)
	{
		this.pointer = pointer;
	}
	
	public String toString()
	{
		return data + " - " + pointer.data;
	}
	
	@Override
	public int compareTo(Entry<T> that)
	{
		return this.data.compareTo(that.data);
	}
	
}
