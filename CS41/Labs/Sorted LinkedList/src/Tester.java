/**
 * @author mzrimsek
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
			System.out.print("Enter number: ");
			n = sc.nextInt();
		}
		
		sc.close();
	}
}
