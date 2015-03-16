/**
 * 
 * @author Mike Zrimsek
 * @version 03.15.2015
 *
 */

public class Person implements Comparable<Person>
{
	private String name;
	private Double weight;
	
	public Person(String name, Double weight)
	{
		this.name = name;
		this.weight = weight;
	}
	
	public Person(String name)
	{
		this.name = name;
		weight = null;
	}
	
	public String toString() { return name; }
	
	public String toFullString() { return name + " - " + weight; }
	
	@Override
	public int compareTo(Person that)
	{
		return this.getName().toLowerCase().compareTo(that.getName().toLowerCase());
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
	
	
}
