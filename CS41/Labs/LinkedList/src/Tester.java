/**
 * @author Mike Zrimsek
 * @version 02.10.2015
 */

import java.util.Scanner;

public class Tester
{
	public static void main(String[] args)
	{
		Scanner sc = new Scanner(System.in);
		LinkedList list = new LinkedList();
		
		// int n = 0;
		// while(n != -1)
		// {
		// System.out.print("Enter number to add to list: ");
		// n = sc.nextInt();
		// if(n == -1) break;
		// list.add(n, 0);
		// // list.add(n);
		// }
		
		// System.out.print("\n[ ");
		// for(int i = 0; i < list.size(); i++)
		// {
		// System.out.print(list.get(i) + " ");
		// }
		// System.out.println("]");
		
		list.add(1);
		System.out.println(list);
		list.add(8);
		System.out.println(list);
		list.add(2);
		System.out.println(list);
		list.add(7);
		System.out.println(list);
		list.add(3);
		System.out.println(list);
		list.add(6);
		System.out.println(list);
		list.add(4);
		System.out.println(list);
		list.add(5);
		System.out.println(list);
		
		LinkedList test = list.reverseList();
		System.out.println(test);
		ListSorter ls = new ListSorter(test, true);
		
//		System.out.println("Bubble Sort");
//		ls.sort(ListSorter.BUBBLE_SORT);
//		
//		System.out.println("Selection Sort");
//		ls.sort(ListSorter.SELECTION_SORT);
////		
//		System.out.println("Insertion Sort");
//		ls.sort(ListSorter.INSERTION_SORT);
////		
//		System.out.println("Merge Sort");
//		ls.sort(ListSorter.MERGE_SORT);
////		
		System.out.println("Quick Sort");
		ls.sort(ListSorter.QUICK_SORT);
		
		sc.close();
	}
}