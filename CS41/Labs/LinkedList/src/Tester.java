/**
 * @author Mike Zrimsek
 * @version 02.05.2015
 */

import java.util.Scanner;

public class Tester
{
	public static void main(String[] args)
	{
		Scanner sc = new Scanner(System.in);
		LinkedList list = new LinkedList();
		
//		int n = 0;
//		while(n != -1)
//		{
//			System.out.print("Enter number to add to list: ");
//			n = sc.nextInt();
//			if(n == -1) break;
//			list.add(n, 0);
////			list.add(n);
//		}
		
//		System.out.print("\n[ ");
//		for(int i = 0; i < list.size(); i++)
//		{
//			System.out.print(list.get(i) + " ");
//		}
//		System.out.println("]");
		
		list.insert("A");
		System.out.println(list);
		list.insert("Z");
		System.out.println(list);
		//list.set(3, 0);
		//System.out.println(list);
		list.insert("B");
		System.out.println(list);
		list.insert("Y");
		System.out.println(list);
		list.insert("C");
		System.out.println(list);
		list.insert("X");
		System.out.println(list);
		list.insert("D");
		System.out.println(list);
		list.insert("W");
		System.out.println(list);
		// A B C D W X Y Z
		//System.out.println(list.reverse());
		sc.close();
	}
}