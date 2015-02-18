/**
 * 
 * @author Mike Zrimsek
 * @version 02.17.2015
 *
 */

public class BinaryTree<T extends Comparable<T>>
{
	private TreeNode<T> head;
	private int size;
	
	public BinaryTree()
	{
		head = null;
		size = 0;
	}
	
	public void add(T data)
	{
		TreeNode<T> temp = new TreeNode<T>(data);
		if (empty())
			head = temp;
		else
		{
			TreeNode<T> current = head;
			TreeNode<T> parent;
			
			while (true)
			{
				parent = current;
				if (temp.compareTo(parent) < 0) // go left
				{
					current = parent.getLeft();
					if (current == null) // no left node
					{
						parent.setLeft(temp);
						break;
					}
				}
				else
				// go right
				{
					current = parent.getRight();
					if (current == null) // no right node
					{
						parent.setRight(temp);
						break;
					}
				}
			}
		}
		size++;
	}
	
	public String toString()
	{
		String output = "[ " + print(head);
		return output.substring(0, output.lastIndexOf(',')) + " ]";
	}
	
	private String print(TreeNode<T> node)
	{
		String output = "";
		if(node != null)
		{
			output += node.getData() + ", ";
			output += print(node.getLeft());
			output += print(node.getRight());
		}
		return output;
	}
	
	public int size()
	{
		return size;
	}
	
	public boolean empty()
	{
		return size == 0 && head == null;
	}
}
