/**
 * 
 * @author Mike Zrimsek
 * @version 03.16.2015
 *
 */

public class BinaryTree<T extends Comparable<T>>
{
	protected TreeNode<T> head;
	protected int size;
	
	public BinaryTree()
	{
		head = null;
		size = 0;
	}
	
	// recursively find height of tree
	public int height()
	{
		return height(head) - 1;
	}
	
	// height helper
	private int height(TreeNode<T> root)
	{
		if (root == null)
			return 0;
		else return 1 + Math.max(height(root.getLeft()),
				height(root.getRight()));
	}
	
	// gets number of leaves on tree
	public int leaves()
	{
		return leaves(head);
	}
	
	// leaves helper
	// leaves are defined as nodes that have no children
	private int leaves(TreeNode<T> root)
	{
		if (root == null) 
			return 0;
		else if(root.getLeft() == null && root.getRight() == null)
			return 1;
		else
			return leaves(root.getLeft()) + leaves(root.getRight());
	}
	
	// returns the root of the tree
	public TreeNode<T> getRoot()
	{
		return head;
	}
	
	// returns null if can't find matching data
	// returns matching data if found
	public T find(T data)
	{
		return find(head, data);
	}
	
	// returns if data exists in tree
	public boolean exists(T data)
	{
		return find(data) != null;
	}
	
	// find helper
	private T find(TreeNode<T> root, T data)
	{
		if(root == null)
			return null;
		
		TreeNode<T> other = new TreeNode<T>(data);
		if(other.compareTo(root) == 0)
			return root.getData();
		else if(other.compareTo(root) < 0)
			return find(root.getLeft(), data);
		else
			return find(root.getRight(), data);
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
	public void inorderTraversal(boolean display)
	{
		if(display) System.out.print("Inorder (LVR): ");
		printInorder(head);
		System.out.println();
	}
	
	private void printInorder(TreeNode<T> root)
	{
		if (root == null) // empty tree
			return;
		
		printInorder(root.getLeft());
		System.out.print(root.getData() + " ");
		printInorder(root.getRight());
	}
	
	// print contents of tree postorder (LRV)
	public void postorderTraversal(boolean display)
	{
		if(display) System.out.print("Postorder (LRV): ");
		printPostorder(head);
		System.out.println();
	}
	
	private void printPostorder(TreeNode<T> root)
	{
		if (root == null) // empty tree
			return;
		
		printPostorder(root.getLeft());
		printPostorder(root.getRight());
		System.out.print(root.getData() + " ");
	}
	
	// print contents of tree preorder (VLR)
	public void preorderTraversal(boolean display)
	{
		if(display) System.out.print("Preorder (VLR): ");
		printPreorder(head);
		System.out.println();
	}
	
	private void printPreorder(TreeNode<T> root)
	{
		if (root == null) // empty tree
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
