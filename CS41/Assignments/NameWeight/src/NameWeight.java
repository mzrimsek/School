/**
 * 
 * @author Mike Zrimsek
 * @version 02.05.2015
 *
 */

public class NameWeight
{
	private LinkedList<NameEntry> names; // list sorted by name
	private LinkedList<WeightEntry> weights; // list sorted by weight
	
	public NameWeight()
	{
		names = new LinkedList<NameEntry>();
		weights = new LinkedList<WeightEntry>();
	}
	
	public void add(String name, Double weight)
	{
		NameEntry nameE = new NameEntry(name);
		WeightEntry weightE = new WeightEntry(weight);
		weightE.setNamePointer(nameE);
		nameE.setWeightPointer(weightE);
		
		names.insert(nameE);
		weights.insert(weightE);
	}
	
	// true for ascending
	// false for descending
	public void printByName(boolean ascending)
	{
		if (empty())
		{
			System.out.println("Nothing to print.");
			return;
		}
		if(ascending)System.out.println(names);
		else System.out.println(names.reverse());
	}
	
	// true for ascending
	// false for descending
	public void printByWeight(boolean ascending)
	{
		if (empty())
		{
			System.out.println("Nothing to print.");
			return;
		}
		if(ascending)System.out.println(weights);
		else System.out.println(weights.reverse());
	}
	
	public boolean empty()
	{
		return names.size() == 0 || weights.size() == 0;
	}
}
