/**
 * 
 * @author Mike Zrimsek
 * @version 02.17.2015
 *
 */

public class TreeNode<T extends Comparable<T>> extends Node<T>
{
	private TreeNode<T> parent;
	
	public TreeNode(T data)
	{
		super(data);
	}
	
	public TreeNode(T data, TreeNode<T> parent)
	{
		super(data);
		this.parent = parent;
	}
	
	public TreeNode<T> getLeft()
	{
		return (TreeNode<T>) super.getPrev();
	}
	
	public void setLeft(TreeNode<T> node)
	{
		super.setPrev(node);
	}
	
	public TreeNode<T> getRight()
	{
		return (TreeNode<T>) super.getNext();
	}
	
	public void setRight(TreeNode<T> node)
	{
		super.setNext(node);
	}
	
	public TreeNode<T> getParent()
	{
		return parent;
	}
	
	public void setParent(TreeNode<T> node)
	{
		parent = node;
	}
}
