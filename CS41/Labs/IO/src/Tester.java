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
		
		System.out.print("Enter sentence: ");
		String[] input = sc.nextLine().split(" ");
		
		for(String s : input)
		{
			if(t.isNumber(s))
				System.out.println(Double.parseDouble(s)*2);
			else
				System.out.println(s);
		}
		sc.close();
	}
	
	//Doesn't account for if the number is followed by punctuation
	private boolean isNumber(String str)
	{
		try{
			Double.parseDouble(str);
		}
		catch(Exception e)
		{
			return false;
		}
		return true;
	}
}
