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
		LinkedList list = new LinkedList();
		
		int n = 0;
		
		while(n != -1)
		{
			System.out.print("Enter number to add to list: ");
			n = sc.nextInt();
			if(n == -1) break;
			list.add(n);
		}
		list.reverse();
		
		System.out.print("\n[ ");
		System.out.print(list);
		System.out.println("]");
		sc.close();
	}
}