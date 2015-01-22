/**
 * @author Mike Zrimsek
 * @version 01.22.2015
 */

public class Tester
{
	public static void main(String[] args)
	{
		int[] nums = {9, 8, 7, 6, 5, 4, 3, 2, 1};
		System.out.print("Unsorted: [ ");
		for(int x : nums)
			System.out.print(x + " ");
		System.out.print("]");
		for(int i = 0; i < nums.length; i++)
		{
			for(int j = 0; j < nums.length-1; j++)
			{
				if(nums[j] > nums[j+1])
				{
					int temp = nums[j];
					nums[j] = nums[j+1];
					nums[j+1] = temp;
				}
			}
		}
		System.out.print("\nSorted: [ ");
		for(int x : nums)
			System.out.print(x + " ");
		System.out.print("]");
	}
}
