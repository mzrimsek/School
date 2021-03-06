/**
 * 
 * @author Mike Zrimsek
 * @version 02.10.2015
 *
 *          Takes a LinkedList and returns a sorted version of that list based
 *          on the chosen sort.
 */

public final class ListSorter<T extends Comparable<T>>
{
	public static final int BUBBLE_SORT = 0;
	public static final int SELECTION_SORT = 1;
	public static final int INSERTION_SORT = 2;
	public static final int MERGE_SORT = 3;
	public static final int QUICK_SORT = 4;
	
	private LinkedList<T> list;
	private boolean print;
	
	public ListSorter(LinkedList<T> list, boolean print)
	{
		this.list = list;
		this.print = print;
	}
	
	public LinkedList<T> sort(int type)
	{
		if (list.size() == 0) return null;
		LinkedList<T> temp = new LinkedList<T>();
		switch (type)
		{
			case BUBBLE_SORT:
				temp = bubbleSort();
				break;
			case SELECTION_SORT:
				temp = selectionSort();
				break;
			case INSERTION_SORT:
				temp = insertionSort();
				break;
			case MERGE_SORT:
				temp = mergeSort();
				break;
			case QUICK_SORT:
				temp = quickSort();
				break;
		}
		
		return temp;
	}
	
	public LinkedList<T> reverseSort(int type)
	{
		return sort(type).reverseList();
	}
	
	// Iterate through list and swap if value is smaller than following value
	private LinkedList<T> bubbleSort()
	{
		LinkedList<T> sortedList = list;
		
		for (int i = 0; i < sortedList.size(); i++)
		{
			Node<T> temp = sortedList.getNode(i);
			for (int j = i; j < sortedList.size(); j++)
			{
				Node<T> comp = sortedList.getNode(j);
				if (temp.compareTo(comp) > 0) swap(temp, comp);
			}
			if (print) System.out.println(sortedList);
		}
		
		return sortedList;
	}
	
	// Iterate through list, find smallest value, and move it to next front
	// position of the list
	private LinkedList<T> selectionSort()
	{
		LinkedList<T> sortedList = list;
		
		for (int i = 0; i < sortedList.size(); i++)
		{
			int small = i;
			Node<T> smallVal = sortedList.getNode(small);
			for (int j = i + 1; j < sortedList.size(); j++)
			{
				Node<T> comp = sortedList.getNode(j);
				smallVal = sortedList.getNode(small);
				if (comp.compareTo(smallVal) < 0) small = j;
			}
			
			swap(smallVal, sortedList.getNode(i));
			if (print) System.out.println(sortedList);
		}
		
		return sortedList;
	}
	
	// Iterate through the list and swap if current value is less than the
	// previous value of the list.
	private LinkedList<T> insertionSort()
	{
		LinkedList<T> sortedList = list;
		
		for (int i = 0; i < sortedList.size(); i++)
		{
			for (int j = i; j > 0; j--)
			{
				Node<T> cur = sortedList.getNode(j);
				Node<T> prev = cur.getPrev();
				
				if (cur.compareTo(prev) < 0) swap(cur, prev);
			}
			
			if (print) System.out.println(sortedList);
		}
		
		return sortedList;
	}
	
	private LinkedList<T> mergeSort()
	{
		LinkedList<T> sortedList = list;
		LinkedList<T> temp = new LinkedList<T>(sortedList.size());
		
		mergeSort(sortedList, temp, 0, list.size() - 1);
		
		return sortedList;
	}
	
	private void mergeSort(LinkedList<T> list, LinkedList<T> temp, int left,
			int right)
	{
		if (left < right)
		{
			int mid = (left + right) / 2;
			mergeSort(list, temp, left, mid);
			mergeSort(list, temp, mid + 1, right);
			merge(list, temp, left, mid + 1, right);
			if (print) System.out.println(list);
		}
	}
	
	private void merge(LinkedList<T> list, LinkedList<T> temp, int left,
			int right, int rightend)
	{
		int leftend = right - 1;
		int index = left;
		
		while (left <= leftend && right <= rightend)
		{
			T leftData = list.get(left);
			T rightData = list.get(right);
			if (leftData.compareTo(rightData) <= 0)
			{
				temp.set(leftData, index++);
				left++;
			}
			else
			{
				temp.set(rightData, index++);
				right++;
			}
		}
		
		while (left <= leftend)
			// merge left side
			temp.set(list.get(left++), index++);
		
		while (right <= rightend)
			// merge right side
			temp.set(list.get(right++), index++);
		
		for (int i = 0; i < index; i++)
			// copy back from temp
			list.set(temp.get(i), i);
	}
	
	private LinkedList<T> quickSort()
	{
		LinkedList<T> sortedList = list;
		
		quickSort(sortedList, 0, sortedList.size() - 1);
		
		return sortedList;
	}
	
	private void quickSort(LinkedList<T> list, int low, int high)
	{
		int x = partition(list, low, high);
		if (low < x - 1) quickSort(list, low, x - 1);
		if (high > x) quickSort(list, x, high);
	}
	
	private int partition(LinkedList<T> list, int low, int high)
	{
		T pivot = list.get(low);
		if (print) System.out.println("Pivot: " + pivot);
		
		while (low <= high)
		{
			while (list.get(low).compareTo(pivot) < 0)
				low++;
			while (list.get(high).compareTo(pivot) > 0)
				high--;
			if (low <= high) swap(list.getNode(low++), list.getNode(high--));
			if (print) System.out.println(list);
		}
		
		return low;
	}
	
	// swaps data in two different nodes
	private void swap(Node<T> one, Node<T> two)
	{
		T data;
		data = one.getData();
		one.setData(two.getData());
		two.setData(data);
	}
}
