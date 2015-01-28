/**
 * @author Mike Zrimsek
 * @version 01.27.2015
 */

import java.util.Scanner;

//using LinkedList Lab classes

public class SortedTester
{
	public static void main(String[] args)
	{
		Scanner sc = new Scanner(System.in);
		LinkedList<Integer> list = new LinkedList<Integer>();
		
		int n = 0;
		while (n != -1)
		{
			System.out.print("Enter number: ");
			n = sc.nextInt();
			if(n == -1) break;
			
		}
		list.print();
		
		sc.close();
	}
}
