/**
 * 
 * @author Mike Zrimsek
 * @version 02.17.2015
 *
 */

public class Tester
{
	
	public static void main(String[] args)
	{
		Queue q = new Queue();
		System.out.println(q.dequeue());
		q.enqueue(10);
		q.enqueue(20);
		q.enqueue(30);
		q.enqueue(40);
		q.enqueue(50);
		q.enqueue(60);
		q.enqueue(70);
		q.enqueue(80);
		q.enqueue(90);
		q.enqueue(100);
		System.out.println(q);
		
		System.out.println(q.dequeue());
		System.out.println(q);
		System.out.println(q.dequeue());
		System.out.println(q);
		System.out.println(q.dequeue());
		System.out.println(q);
		
		q.enqueue(110);
		q.enqueue(120);
		q.enqueue(130);
		q.enqueue(140);
		
		System.out.println(q);
	}
}

class Queue
{
	final int MAX_SIZE = 10;
	int count;
	int[] nums;
	int frontIndex;
	int backIndex;
	
	public Queue()
	{
		nums = new int[MAX_SIZE];
		count = 0;
		frontIndex = -1;
		backIndex = -1;
	}
	
	public void enqueue(int data)
	{
		if (count == MAX_SIZE)
		{
			System.out.println("Queue at full capacity");
			return;
		}
		nums[count] = data;
		count++;
	}
	
	public int dequeue()
	{
		if (empty())
		{
			System.out.println("Empty queue");
			return Integer.MIN_VALUE;
		}
		else
		{
			int n = nums[10-count];
			count--;
			nums = shift(nums);
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
	
	private int[] shift(int[] n)
	{
		int[] temp = new int[n.length];
		for(int i = 1; i < n.length; i++)
			temp[i-1] = n[i];
		return temp;
	}
}
