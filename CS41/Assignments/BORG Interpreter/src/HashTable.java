/**
 * 
 * @author Mike Zrimsek
 * @version 04.28.2015
 *
 */

public class HashTable
{
	private int DEFAULT_SIZE = 128;
	private HashEntry[] entries;
	
	public HashTable()
	{
		entries = new HashEntry[DEFAULT_SIZE];
	}
	
	public void put(String key, Integer value)
	{
		int hash = hash(key); //get hashed key value
		HashEntry entry = entries[hash]; //get entry at value
		if(entry == null) //if no entry at value
		{
			entries[hash] = new HashEntry(key, value); //put new data here
		}
		else //if there is an entry
		{
			while(entry.getNext() != null && entry.getKey() != key) //try and find the right entry
			{
				entry = entry.getNext();
			}
			if(entry.getKey() == key) //entry found
			{
				entry.setValue(value); //update the data
			}
			else //no entry found
			{
				entry.setNext(new HashEntry(key, value)); //put new data in the next entry in the list
			}
		}
	}
	
	public Integer get(String key)
	{
		int hash = hash(key); //get hashed key value
		HashEntry entry = entries[hash]; //get the entry at the value
		if(entry == null) //if there's no entry
		{
			return null;
		}
		else //if there is an entry
		{
			while(entry != null && entry.getKey() != key) //try and find the right entry
			{
				entry = entry.getNext();
			}
			if(entry == null) //if entry cannot be found
			{
				return null;
			}
			else //if entry is found
			{
				return entry.getValue();
			}
		}
	}
	
	private int hash(String key)
	{
		int hash = 0;
		char[] characters = key.toCharArray();
		for(int i = 0; i < characters.length; i++)
		{
			hash += Character.getNumericValue(characters[i]) * (i+1);
		}
		return hash % DEFAULT_SIZE;
	}
}
