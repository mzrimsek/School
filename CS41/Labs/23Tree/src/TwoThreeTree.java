/**
 * 
 * @author Mike Zrimsek
 * @version 03.17.2015
 *
 */

public class TwoThreeTree<T extends Comparable<T>>
{
	TwoThreeNode<T> root;
	Integer size;
	
	public TwoThreeTree()
	{
		root = null;
		size = 0;
	}
}
