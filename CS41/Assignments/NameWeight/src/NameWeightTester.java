/**
 * 
 * @author Mike Zrimsek
 * @version 02.05.2015
 *
 */

import java.util.Scanner;

public class NameWeightTester
{
	public static void main(String[] args)
	{
		Scanner sc = new Scanner(System.in);
		
		NameWeight nw = new NameWeight();
		for(int i = 0; i < 15; i++)
		{
			System.out.print("Enter name: ");
			String name = sc.nextLine();
			System.out.print("Enter weight: ");
			Double weight = sc.nextDouble();
			nw.add(name, weight);
			sc.nextLine();
		}
		System.out.println("By Name Ascending");
		nw.printByName(true);
		System.out.println("By Name Descending");
		nw.printByName(false);
		System.out.println("By Weight Ascending");
		nw.printByWeight(true);
		System.out.println("By Weight Descending");
		nw.printByWeight(false);
		sc.close();
	}
}
