/**
 * @author Mike Zrimsek
 * @version 01.27.2015
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
			list.add(n, 0);
//			list.add(n);
		}
		
		System.out.print("\n[ ");
		for(int i = 0; i < list.size(); i++)
		{
			System.out.print(list.get(i) + " ");
		}
		System.out.println("]");
		sc.close();
	}
}