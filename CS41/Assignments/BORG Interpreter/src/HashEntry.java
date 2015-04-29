/**
 * 
 * @author Mike Zrimsek
 * @version 04.28.2015
 * 
 * A LinkedHashEntry class for use in a HashTable
 *
 */
public class HashEntry
{
	String key;
	Integer value;
	HashEntry next;
	
	public HashEntry(String key, Integer value)
	{
		this.key = key;
		this.value = value;
		next = null;
	}
	
	public String getKey()
	{
		return key;
	}
	
	public void setKey(String key)
	{
		this.key = key;
	}
	
	public Integer getValue()
	{
		return value;
	}
	
	public void setValue(Integer value)
	{
		this.value = value;
	}
	
	public HashEntry getNext()
	{
		return next;
	}
	
	public void setNext(HashEntry next)
	{
		this.next = next;
	}
}
