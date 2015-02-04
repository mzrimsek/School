/**
 * 
 * @author Mike Zrimsek
 * @version 02.03.2015
 *
 */

public class Person
{
	private String name;
	private Double weight;
	private int sortBy;
	
	static final int SORT_BY_NAME = 0;
	static final int SORT_BY_WEIGHT = 1;
	
	public Person(String name, Double weight)
	{
		this.name = name;
		this.weight = weight;
		sortBy = SORT_BY_NAME;
	}
	
	public Person(String name, Double weight, int sortBy)
	{
		this.name = name;
		this.weight = weight;
		this.sortBy = sortBy;
	}
	
	public String getName()
	{
		return name;
	}
	
	public void setName(String name)
	{
		this.name = name;
	}
	
	public Double getWeight()
	{
		return weight;
	}
	
	public void setWeight(Double weight)
	{
		this.weight = weight;
	}
	
	public String toString()
	{
		return name + " - " + weight;
	}
	
	public int hashcode()
	{
		if(sortBy == SORT_BY_NAME)
			return name.hashCode();
		else
			return weight.hashCode();
	}
	
}
