/**
 * @author Mike Zrimsek
 * @version 01.20.2014
 */

import java.util.Scanner;

public class Tester {

	public static void main(String[] args)
	{
		Tester t = new Tester();
		Scanner sc = new Scanner(System.in);
		
		int[] nums = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
		
		System.out.print("Enter number to search for: ");
		int pos = t.search(nums, sc.nextInt());
		if(pos != -1)
			System.out.println("Number found at: " + pos);
		else
			System.out.println("Number not found in array.");
		
		sc.close();
	}
	
	private int search(int[] nums, int n)
	{
		for(int i = 0; i < nums.length; i++)
			if(nums[i] == n) return i;
		return -1;
			
	}
}
