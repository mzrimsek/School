/**
 * 
 * @author Mike Zrimsek
 * @version 02.04.2015
 *
 */

public class NameWeight
{
	private LinkedList<NameEntry> names; // list sorted by name
	private LinkedList<WeightEntry> weights; // list sorted by weight
	private int entryNum; // track sequence of entries to lists
	
	public NameWeight()
	{
		names = new LinkedList<NameEntry>();
		weights = new LinkedList<WeightEntry>();
		entryNum = 1;
	}
	
	public void add(String name, Double weight)
	{
		names.insert(new NameEntry(name, entryNum));
		weights.insert(new WeightEntry(weight, entryNum));
		entryNum++;
	}
	
	// true for ascending
	// false for descending
	public void printByName(boolean ascending)
	{
		if (entryNum == 0) // no entries - empty lists
			System.out.println("Nothing to print.");
		else if (ascending)
			for (int i = 0; i < entryNum; i++)
				System.out.println(getNameWeightPair(names.get(i)));
		else for (int i = entryNum - 1; i >= 0; i--)
			System.out.println(getNameWeightPair(names.get(i)));
	}
	
	// true for ascending
	// false for descending
	public void printByWeight(boolean ascending)
	{
		if (entryNum == 0) // no entries - empty lists
			System.out.println("Nothing to print.");
		else if (ascending)
			for (int i = 0; i < entryNum; i++)
				System.out.println(getNameWeightPair(weights.get(i)));
		else for (int i = entryNum - 1; i >= 0; i--)
			System.out.println(getNameWeightPair(weights.get(i)));
	}
	
	private String getNameWeightPair(Entry e)
	{
		String name = "";
		Double weight = new Double(0);
		
		if (e instanceof NameEntry) // search from NameEntry
		{
			name = ((NameEntry) e).getName(); // name is this entry's name
			for (int j = 0; j < entryNum; j++) // find the corresponding
												// WeightEntry
			{
				WeightEntry cur = weights.get(j);
				if (cur.getEntryNum() == e.getEntryNum()) // found corresponding
															// entry
				{
					weight = cur.getWeight();
					break;
				}
			}
		}
		else
		{
			weight = ((WeightEntry) e).getWeight(); // name is this entry's name
			for (int j = 0; j < entryNum; j++) // find the corresponding
												// WeightEntry
			{
				NameEntry cur = names.get(j);
				if (cur.getEntryNum() == e.getEntryNum()) // found corresponding
															// entry
				{
					name = cur.getName();
					break;
				}
			}
		}
		
		return name + " - " + weight;
	}
	
	public String toString()
	{
		return names + "\n" + weights;
	}
}
