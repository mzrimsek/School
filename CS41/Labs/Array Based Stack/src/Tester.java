/**
 * 
 * @author Mike Zrimsek
 * @version 01.29.2015
 *
 */

public class Tester
{
	public static void main(String[] args)
	{
		Stack s = new Stack();
		System.out.println("Value: " + s.pop());
		s.push(10);
		s.push(20);
		s.push(30);
		s.push(40);
		s.push(50);
		System.out.println(s);
		
		System.out.println(s.pop());
		System.out.println(s.pop());
		System.out.println(s.pop());
		System.out.println(s);
		
		s.push(60);
		s.push(70);
		s.push(80);
		s.push(90);
		s.push(100);
		s.push(110);
		s.push(120);
		s.push(130);
		s.push(140);
		System.out.println(s);
	}
}

class Stack
{
	private final int MAX_SIZE = 10;
	private int[] nums;
	private int count;
	
	public Stack()
	{
		nums = new int[MAX_SIZE];
		count = 0;
	}
	
	public void push(int data)
	{
		if (count == MAX_SIZE)
		{
			System.out.println("Stack at full capacity");
			return;
		}
		nums[count] = data;
		count++;
	}
	
	public int pop()
	{
		if (empty())
		{
			System.out.println("Empty stack");
			return Integer.MIN_VALUE;
		}
		else
		{
			count--;
			int n = nums[count];
			nums[count] = 0;
			return n;
		}
	}
	
	public String toString()
	{
		String output = "[ ";
		for (int x : nums)
			output += x + ", ";
		return output.substring(0, output.lastIndexOf(',')) + "]";
	}
	
	public boolean empty()
	{
		return count == 0;
	}
}
