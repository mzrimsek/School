/**
 * @author Mike Zrimsek
 * @version 02.03.2015
 */

import java.util.Scanner;

public class Tester
{
	public static void main(String[] args)
	{
		Scanner sc = new Scanner(System.in);
		
		System.out.print("Enter size of array: ");
		int size = sc.nextInt();
		
		int count = 0;
		int[] nums = new int[size];
		while (count < size)
		{
			System.out.print("Enter number: ");
			int n = sc.nextInt();
			if (n == -1) break;
			nums[count] = n;
			count++;
			if (count == size) //going to add out of index
			{
				int[] temp = new int[size+1];
				for (int i = 0; i < size; i++)
					temp[i] = nums[i];
				nums = temp; //resized array
				size++;
			}
		}
		
		System.out.print("\n[ ");
		for (int i = 0; i < size; i++)
			if(!(i == size-1 && nums[i] == 0))
				System.out.print(nums[i] + " ");
		System.out.println(" ]");
		sc.close();
	}
}
