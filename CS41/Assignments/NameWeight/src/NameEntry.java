/**
 * 
 * @author Mike Zrimsek
 * @version 02.05.2015
 *
 */

public class NameEntry implements Comparable<NameEntry>
{
	private String name;
	private WeightEntry weightPointer;
	
	public NameEntry(String name)
	{
		this.setName(name);
		weightPointer = null;
	}
	
	public String getName()
	{
		return name;
	}
	
	public void setName(String name)
	{
		this.name = name;
	}
	
	public WeightEntry getWeightPointer()
	{
		return weightPointer;
	}
	
	public void setWeightPointer(WeightEntry weightPointer)
	{
		this.weightPointer = weightPointer;
	}
	
	public String toString()
	{
		return name + " - " + weightPointer.getWeight();
	}

	@Override
	public int compareTo(NameEntry that)
	{
		return this.name.compareTo(that.name);
	}
}