/**
 * @author Mike Zrimsek
 * @version 01.29.2015
 */

import java.util.Scanner;

public class ReversePolish
{
	public static void main(String[] args)
	{
		Scanner sc = new Scanner(System.in);
		
		System.out.print("Enter polish notation expression: ");
		
		ReversePolishCalculator rpc = new ReversePolishCalculator(sc.nextLine());
		if(rpc.calculate()) System.out.println("Result: " + rpc);
		
		sc.close();
	}
}
