/**
 * 
 * @author Mike Zrimsek
 * @version 02.17.2015
 *
 */

import java.util.Scanner;

public class Tester
{
	public static void main(String[] args)
	{
		Scanner sc = new Scanner(System.in);
		Tester t = new Tester();
		
		System.out.print("How many numbers? ");
		int[] nums = new int[sc.nextInt()];
		
		for (int i = 0; i < nums.length; i++)
		{
			System.out.print("Enter number: ");
			nums[i] = sc.nextInt();
		}
		
		System.out.print("\nUnsorted: ");
		t.print(nums);
		
		t.sort(nums);
		
		System.out.print("\nSorted: ");
		t.print(nums);
		
		System.out.print("\nEnter value to find: ");
		
		int index = t.binarySearch(nums, sc.nextInt(), 0, nums.length-1);
		
		if(index != -1)
			System.out.println("Value found at index: " + index);
		else
			System.out.println("Value not found in array.");
		
		sc.close();
	}
	
	// assumes sorted array
	private int binarySearch(int[] n, int val, int min, int max)
	{
		if (max < min)
			return -1;
		else
		{
			int mid = min + ((max - min) / 2);
			if (n[mid] > val) // search lower half
				return binarySearch(n, val, min, mid - 1);
			else if (n[mid] < val) // search upper half
				return binarySearch(n, val, mid + 1, max);
			else return mid;
		}
	}
	
	private void sort(int[] n)
	{
		for (int i = 0; i < n.length; i++)
		{
			for (int j = 0; j < n.length - 1; j++)
			{
				if (n[j] > n[j + 1])
				{
					int temp = n[j];
					n[j] = n[j + 1];
					n[j + 1] = temp;
				}
			}
		}
	}
	
	private void print(int[] n)
	{
		for (int x : n)
			System.out.print(x + " ");
	}
	
}
