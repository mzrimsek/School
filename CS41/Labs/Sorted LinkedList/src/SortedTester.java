/**
 * @author Mike Zrimsek
 * @version 01.28.2015
 */

import java.util.Scanner;

//using LinkedList Lab classes

public class SortedTester
{
	public static void main(String[] args)
	{
		Scanner sc = new Scanner(System.in);
		LinkedList<Integer> list = new LinkedList<Integer>();
		
		Integer n = 0;
		while (n != -1)
		{
			System.out.print("Enter number: ");
			n = sc.nextInt();
			if (n == -1) break;
			list.insert(n);
			
			System.out.println(list);
		}
		//System.out.println(list);
		
		sc.close();
	}
}
