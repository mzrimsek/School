/**
 * @author mzrimsek
 * @version 01.28.2015
 */

import java.util.Scanner;

public class Tester
{
	public static void main(String[] args)
	{
		Scanner sc = new Scanner(System.in);
		LinkedStack<Integer> stack = new LinkedStack<Integer>();
		
		Integer n = 0;
		
		while(n != -1)
		{
			System.out.print("Enter number: ");
			n = sc.nextInt();
			if(n == -1) break;
			stack.push(n);
			System.out.println(stack);
		}
		
		System.out.println("Peek: " + stack.peek());
		System.out.println(stack);
		System.out.println("Pop: " + stack.pop());
		System.out.println(stack);
		
		sc.close();
	}
}
