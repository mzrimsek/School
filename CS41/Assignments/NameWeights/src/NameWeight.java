/**
 * 
 * @author Mike Zrimsek
 * @version 02.04.2015
 *
 */

public class NameWeight 
{
	private String name;
	private Double weight;
	
	public NameWeight(String name, Double weight)
	{
		this.name = name;
		this.weight = weight;
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
