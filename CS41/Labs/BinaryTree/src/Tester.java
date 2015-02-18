/**
 * 
 * @author Mike Zrimsek
 * @version 02.17.2015
 *
 */

import java.util.Scanner;

public class Tester
{
	public static void main(String[] args)
	{
		Scanner sc = new Scanner(System.in);
		BinaryTree<Integer> tree = new BinaryTree<Integer>();
		
		tree.add(5);
		System.out.println(tree);
		tree.add(4);
		System.out.println(tree);
		tree.add(3);
		System.out.println(tree);
		tree.add(6);
		System.out.println(tree);
		tree.add(2);
		System.out.println(tree);
		tree.add(20);
		System.out.println(tree);
		tree.add(79);
		System.out.println(tree);
		tree.add(7);
		System.out.println(tree);
		System.out.println("Size: " + tree.size());
		
		sc.close();
	}
}
