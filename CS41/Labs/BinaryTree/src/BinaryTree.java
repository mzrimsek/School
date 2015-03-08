/**
 * 
 * @author Mike Zrimsek
 * @version 03.08.2015
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
	
	// recursive add method
	public boolean insert(T data)
	{
		TreeNode<T> temp = new TreeNode<T>(data);
		
		if (head == null)
		{
			head = temp;
			size++;
			return true;
		}
		
		return insert(head, temp);
	}
	
	// recursive insert helper
	private boolean insert(TreeNode<T> root, TreeNode<T> temp)
	{
		if (root.compareTo(temp) > 0)
		{
			if (root.getLeft() == null)
			{
				root.setLeft(temp);
				size++;
				return true;
			}
			else return insert(root.getLeft(), temp);
		}
		else
		{
			if (root.getRight() == null)
			{
				root.setRight(temp);
				size++;
				return true;
			}
			else return insert(root.getRight(), temp);
		}
	}
	
	// iterative add method
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
	
	// print contents of tree inorder (LVR)
	public void inorderTraversal()
	{
		System.out.print("Inorder (LVR): ");
		printInorder(head);
		System.out.println();
	}
	
	private void printInorder(TreeNode<T> root)
	{
		if(root == null) // empty tree
			return;
		
		printInorder(root.getLeft());
		System.out.print(root.getData() + " ");
		printInorder(root.getRight());
	}
	
	// print contents of tree postorder (LRV)
	public void postorderTraversal()
	{
		System.out.print("Postorder (LRV): ");
		printPostorder(head);
		System.out.println();
	}
	
	private void printPostorder(TreeNode<T> root)
	{
		if(root == null) // empty tree
			return;
		
		printPostorder(root.getLeft());
		printPostorder(root.getRight());
		System.out.print(root.getData() + " ");
	}
	
	// print contents of tree preorder (VLR)
	public void preorderTraversal()
	{
		System.out.print("Preorder (VLR): ");
		printPreorder(head);
		System.out.println();
	}
	
	private void printPreorder(TreeNode<T> root)
	{
		if(root == null) // empty tree
			return;
		
		System.out.print(root.getData() + " ");
		printPreorder(root.getLeft());
		printPreorder(root.getRight());
	}
	
	public String toString()
	{
		String output = "[ " + print(head);
		return output.substring(0, output.lastIndexOf(',')) + " ]";
	}
	
	private String print(TreeNode<T> node)
	{
		String output = "";
		if (node != null)
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
