/**
 * 
 * @author Mike Zrimsek
 * @version 02.04.2015
 *
 */

public class NameEntry extends Entry
{
	private String name;
	
	public NameEntry(String name, int entryNum)
	{
		super(entryNum);
		this.setName(name);
	}
	
	public String getName()
	{
		return name;
	}
	
	public void setName(String name)
	{
		this.name = name;
	}

	@Override
	int hashcode()
	{
		return name.hashCode();
	}
	
	public String toString()
	{
		return name + ":" + entryNum;
	}
}