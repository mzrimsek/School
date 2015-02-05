/**
 * 
 * @author Mike Zrimsek
 * @version 02.05.2015
 *
 */

public class WeightEntry implements Comparable<WeightEntry>
{
	private Double weight;
	private NameEntry namePointer;
	
	public WeightEntry(Double weight)
	{
		this.setWeight(weight);
		namePointer = null;
	}

	public Double getWeight()
	{
		return weight;
	}

	public void setWeight(Double weight)
	{
		this.weight = weight;
	}
	
	public NameEntry getNamePointer()
	{
		return namePointer;
	}

	public void setNamePointer(NameEntry namePointer)
	{
		this.namePointer = namePointer;
	}
	
	public String toString()
	{
		return namePointer.getName() + " - " + weight;
	}

	@Override
	public int compareTo(WeightEntry that)
	{
		return this.weight.compareTo(that.weight);
	}
}
