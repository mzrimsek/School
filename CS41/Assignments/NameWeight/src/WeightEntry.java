/**
 * 
 * @author Mike Zrimsek
 * @version 02.04.2015
 *
 */

public class WeightEntry extends Entry
{
	private Double weight;
	
	public WeightEntry(Double weight, int entryNum)
	{
		super(entryNum);
		this.setWeight(weight);
	}

	public Double getWeight()
	{
		return weight;
	}

	public void setWeight(Double weight)
	{
		this.weight = weight;
	}
	
	@Override
	public int hashcode()
	{
		return weight.hashCode();
	}
	
	public String toString()
	{
		return weight + ":" + entryNum;
	}
}
