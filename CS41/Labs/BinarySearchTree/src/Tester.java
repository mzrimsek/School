/**
 * 
 * @author Mike Zrimsek
 * @version 03.16.2015
 *
 */

public class Tester
{
	public static void main(String[] args)
	{
		BinarySearchTree<String> words = new BinarySearchTree<String>();
		
		words.insert("Apple");
		words.insert("Strudel");
		words.insert("Apple");
		words.insert("Pie");
		words.insert("Bananas");
		words.insert("Creame");
		words.insert("Key-lime");
		
		words.print();
		
		BinarySearchTree<Integer> numbers = new BinarySearchTree<Integer>();
		
		numbers.insert(10);
		numbers.insert(4);
		numbers.insert(34);
		numbers.insert(12);
		numbers.insert(52);
		numbers.insert(86);
		numbers.insert(1);
		numbers.insert(8);
		numbers.insert(4);
		numbers.insert(52);
		numbers.insert(54);
		
		numbers.print();
	}
}
