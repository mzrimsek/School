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
			if (list.empty())
				list.add(n);
			else if (list.size() == 1)
			{
				if (n > list.get(0))
					list.add(n);
				else list.add(n, 0);
			}
			else
			{
				for (int i = 0; i < list.size(); i++)
				{
					// insert to sorted position
					// check if n > list.get(i)
					// insertion sort!?!?
				}
			}
			
			System.out.println(list);
		}
		System.out.println(list);
		
		sc.close();
	}
}
