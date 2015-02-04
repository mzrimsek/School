/**
 * 
 * @author Mike Zrimsek
 * @version 02.03.2015
 *
 */

public class Tester
{
	
	public static void main(String[] args)
	{
		
		
	}
	
	class Queue
	{
		final int MAX_SIZE = 10;
		int count;
		int[] nums;
		int frontIndex;
		int backIndex;
		
		public Queue()
		{
			nums = new int[MAX_SIZE];
			count = 0;
			frontIndex = -1;
			backIndex = -1;
		}
	}
}
