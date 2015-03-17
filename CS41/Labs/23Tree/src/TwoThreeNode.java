/**
 * 
 * @author Mike Zrimsek
 * @version 03.17.2015
 */

public class TwoThreeNode<T extends Comparable<T>> extends TreeNode<T>
{
	T rightData;
	TwoThreeNode<T> middleChild;
	
	public TwoThreeNode(T data)
	{
		super(data);
		rightData = null;
		middleChild = null;
	}
	
	public TwoThreeNode(T left, T right)
	{
		super(left);
		rightData = right;
		middleChild = null;
	}
	
	public TwoThreeNode(T data, TwoThreeNode<T> parent)
	{
		super(data, parent);
	}
	
	public T getLeftData()
	{
		return super.getData();
	}
	
	public void setLeftData(T data)
	{
		super.setData(data);
	}
	
	public T getRightData()
	{
		return rightData;
	}
	
	public void setRightData(T data)
	{
		rightData = data;
	}
	
	public TwoThreeNode<T> getMiddle()
	{
		return middleChild;
	}
}
