/**
 * 
 * @author Mike Zrimsek
 * @ version 03.16.2015
 *
 */

public class BinarySearchTree<T extends Comparable<T>> extends BinaryTree<T>
{
	// same insert as BinaryTree, but only unique values
	public boolean insert(T data)
	{
		if(!exists(data))
		{
			return super.insert(data);
		}
		
		return false;
	}
	
	public void print()
	{
		super.inorderTraversal(false);
	}
}
