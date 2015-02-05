/**
 * 
 * @author Mike Zrimsek
 * @version 02.04.2015
 *
 */

public abstract class Entry
{
	protected int entryNum;
	
	public Entry(int entryNum)
	{
		this.entryNum = entryNum;
	}

	public int getEntryNum()
	{
		return entryNum;
	}

	public void setEntryNum(int entryNum)
	{
		this.entryNum = entryNum;
	} 
	
	abstract int hashcode();
}
