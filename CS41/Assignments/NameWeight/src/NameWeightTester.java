/**
 * 
 * @author Mike Zrimsek
 * @version 02.05.2015
 *
 */

import java.util.InputMismatchException;
import java.util.Scanner;

public class NameWeightTester
{
	public static void main(String[] args)
	{
		Scanner sc = new Scanner(System.in);
		
		NameWeight nw = new NameWeight();
		for (int i = 0; i < 15; i++)
		{
			String name;
			Double weight;
			try
			{
				System.out.print("Enter name: ");
				name = sc.nextLine();
				System.out.print("Enter weight: ");
				weight = sc.nextDouble();
			}
			catch (InputMismatchException ime)
			{
				System.out.println("Invalid input!");
				sc.close();
				return;
			}
			
			nw.add(name, weight);
			sc.nextLine();
		}
		
		System.out.println("By Name Ascending");
		nw.printByName(true);
		System.out.println("\nBy Name Descending");
		nw.printByName(false);
		System.out.println("\nBy Weight Ascending");
		nw.printByWeight(true);
		System.out.println("\nBy Weight Descending");
		nw.printByWeight(false);
		
		sc.close();
	}
}
