/**
 * @author Mike Zrimsek
 * @version 01.28.2015
 */

import java.util.Scanner;

public class ReversePolish
{
	public static void main(String[] args)
	{
		Scanner sc = new Scanner(System.in);
		
		System.out.print("Enter polish formula: ");
		System.out.println(new ReversePolishCalculator(sc.nextLine()));
		
		sc.close();
	}
}
