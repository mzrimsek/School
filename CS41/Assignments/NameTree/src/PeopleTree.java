/**
 * 
 * @author Mike Zrimsek
 * @version 03.15.2015
 *
 */

import java.util.InputMismatchException;
import java.util.Scanner;

public class PeopleTree
{
	public static void main(String[] args)
	{
		BinaryTree<Person> people = new BinaryTree<Person>();
		
		Scanner sc = new Scanner(System.in);
		for(int i = 0; i < 15; i++)
		{
			System.out.print("Enter name: ");
			String name = sc.nextLine();
			Double weight = -1.0;
			do
			{
				try
				{
					System.out.print("Enter weight: ");
					weight = sc.nextDouble();
				}
				catch(InputMismatchException ime)
				{
					weight = -1.0;
					sc.nextLine();
				}
				if(weight < 0)
					System.out.println("Please enter a valid weight.");
			} while(weight < 0);
			people.insert(new Person(name, weight));
			sc.nextLine();
		}
		
		System.out.println("Height: " + people.height());
		System.out.println("Leaves: " + people.leaves());
		
		people.inorderTraversal();
		people.preorderTraversal();
		people.postorderTraversal();
		
		System.out.print("Enter name to search for: ");
		String search = sc.nextLine();
		
		// comparing Person objects compares on the name and is not case sensitive
		Person searchedPerson = people.find(new Person(search));
		if(searchedPerson != null)
			System.out.println("Weight for " + searchedPerson.getName() + " is " + searchedPerson.getWeight() + ".");
		else
			System.out.println("Not found in tree.");
		
		System.out.println("First person alphabetically: " + getFirstAlphabetically(people.getRoot()));
		System.out.println("Lowest weight: " + getLowestWeight(people.getRoot()));
		
		sc.close();
	}
	
	public static Person getFirstAlphabetically(TreeNode<Person> root)
	{
		if(root.getLeft() == null)
			return root.getData();
		else
			return getFirstAlphabetically(root.getLeft());
	}
	
	public static Double getLowestWeight(TreeNode<Person> root)
	{
		Double lowest = root.getData().getWeight();
		
		TreeNode<Person> head = root;
		
		while(root.getLeft() != null)
		{
			Double leftVal = root.getLeft().getData().getWeight();
			lowest = Math.min(lowest, leftVal);
			root = root.getLeft();
		}
		
		root = head;
		
		while(root.getRight() != null)
		{
			Double rightVal = root.getRight().getData().getWeight();
			lowest = Math.min(lowest, rightVal);
			root = root.getRight();
		}
		
		return lowest;
	}
}