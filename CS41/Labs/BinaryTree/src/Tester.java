/**
 * 
 * @author Mike Zrimsek
 * @version 03.16.2015
 *
 */

import java.util.Scanner;

public class Tester
{
	public static void main(String[] args)
	{
		Scanner sc = new Scanner(System.in);
		BinaryTree<Integer> tree = new BinaryTree<Integer>();
		
		tree.insert(5);
		System.out.println(tree);
		tree.insert(4);
		System.out.println(tree);
		tree.insert(3);
		System.out.println(tree);
		tree.insert(6);
		System.out.println(tree);
		tree.insert(2);
		System.out.println(tree);
		tree.insert(20);
		System.out.println(tree);
		tree.insert(79);
		System.out.println(tree);
		tree.insert(7);
		System.out.println(tree);
		System.out.println("Size: " + tree.size());
		
		tree.inorderTraversal(true);
		tree.postorderTraversal(true);
		tree.preorderTraversal(true);
		
		System.out.println("Height: " + tree.height());
		System.out.println("Leaves: " + tree.leaves());
		
		Integer num = 5;
		System.out.println(num + " is in this tree: " + tree.exists(num));
		sc.close();
	}
}
