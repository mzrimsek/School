/**
 * @author Mike Zrimsek
 * @version 01.20.2015
 */

import java.util.Scanner;

public class Tester {

	public static void main(String[] args)
	{
		Tester t = new Tester();
		Scanner sc = new Scanner(System.in);
		
		System.out.print("Enter number: ");
		int n = sc.nextInt();
		
		System.out.println("Summation: " + t.sumI(n));
	}
	
	public int sumR(int n)
	{
		if(n < 1)
			return 0;
		else return sumR(n-1) + n;
	}
	
	public int sumI(int n)
	{
		int sum = 0;
		while(n > 0)
		{
			sum += n;
			n--;
		}
		return sum;
	}
}
