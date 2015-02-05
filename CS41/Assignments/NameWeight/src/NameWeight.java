/**
 * 
 * @author Mike Zrimsek
 * @version 02.05.2015
 *
 */

public class NameWeight
{
	private LinkedList<Entry<String>> names; // list sorted by name
	private LinkedList<Entry<Double>> weights; // list sorted by weight
	
	public NameWeight()
	{
		names = new LinkedList<Entry<String>>();
		weights = new LinkedList<Entry<Double>>();
	}
	
	public void add(String name, Double weight)
	{
		Entry<String> nameE = new Entry<String>(name);
		Entry<Double> weightE = new Entry<Double>(weight);
		weightE.setPointer(nameE);
		nameE.setPointer(weightE);
		
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
