/**
 * @author Mike Zrimsek
 * @version 01.22.2015
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
			list.addFirst(n);
//			list.add(n);
		}
		
		System.out.print("\n[ ");
		Node current = list.getFirst();
		for(int i = 0; i < list.getSize() && current != null; i++)
		{
			System.out.print(current.getData() + " ");
			current = current.getNext();
		}
		System.out.println("]");
		sc.close();
	}
}