/**
 * @author Mike Zrimsek
 * @version 01.21.2015
 */

import java.util.Scanner;

public class Tester 
{
	public static void main(String[] args)
	{
		Scanner sc = new Scanner(System.in);
		
		System.out.print("Enter size of array: ");
		int[] nums = new int[sc.nextInt()];
		
		for(int i = 0; i < nums.length; i++)
		{
			System.out.print("Enter number: ");
			int n = sc.nextInt();
			if(n == -1) break;
			nums[i] = n;
		}
		
		System.out.print("\n[ ");
		for(int x : nums)
			System.out.print(x + " ");
		System.out.println(" ]");
		sc.close();
	}
}
