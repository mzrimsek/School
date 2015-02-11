/**
 * 
 * @author Mike Zrimsek
 * @version 02.10.2015
 *
 */

public class Tester
{
	public static void main(String[] args)
	{
		LinkedQueue queue = new LinkedQueue();
		
		queue.enqueue(1);
		System.out.println(queue);
		queue.enqueue(2);
		System.out.println(queue);
		queue.enqueue(3);
		System.out.println(queue);
		queue.enqueue(4);
		System.out.println(queue);
		System.out.println("Dequeue: " + queue.dequeue());
		System.out.println(queue);
	}
}
