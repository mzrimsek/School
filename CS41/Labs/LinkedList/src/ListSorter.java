/**
 * 
 * @author Mike Zrimsek
 * @version 02.09.2015
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
	
	public ListSorter(LinkedList<T> list)
	{
		this.list = list;
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
				temp = mergeSort(0, list.size() - 1);
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
		}
		
		return sortedList;
	}
	
	private LinkedList<T> selectionSort()
	{
		LinkedList<T> sortedList = list;
		
		for (int i = 0; i < sortedList.size(); i++)
		{
			int small = i;
			for (int j = i + 1; j < sortedList.size(); j++)
			{
				Node<T> comp = sortedList.getNode(j);
				Node<T> temp = sortedList.getNode(small);
				if (temp.compareTo(comp) < 0)
				{
					small = j;
					temp = sortedList.getNode(small);
				}
				swap(temp, comp);
			}
		}
		
		return sortedList;
	}
	
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
		}
		
		return sortedList;
	}
	
	private LinkedList<T> mergeSort(int start, int end)
	{
		LinkedList<T> sortedList = list;
		
		if(end-start <= 0)
			return null;
		int mid = (start+end)/2;
		mergeSort(start, mid);
		mergeSort(mid+1, end);
		merge(start, mid, mid+1, end);
		
		return sortedList;
	}
	
	private void merge(int start1, int end1, int start2, int end2)
	{
		LinkedList<T> temp = new LinkedList<T>();
		
		while (start1 <= end1 && start2 <= end2)
		{
			T first = list.get(start1);
			T second = list.get(start2);
			if(first.compareTo(second) <= 0)
			{
				temp.add(first);
				start1++;
			}
			else
			{
				temp.add(second);
				start2++;
			}
		}
		
		while(start1 <= end1)
		{
			temp.add(list.get(start1));
			start1++;
		}
		
		while(start2 <= end2)
		{
			temp.add(list.get(start2));
			start2++;
		}
		
		for(int i = 0; i < temp.size(); i++)
		{
			list.set(temp.get(i), start1+i);
		}
	}
	
	private LinkedList<T> quickSort()
	{
		LinkedList<T> sortedList = list;
		
		return sortedList;
	}
	
	private void swap(Node<T> one, Node<T> two)
	{
		T data;
		data = one.getData();
		one.setData(two.getData());
		two.setData(data);
	}
}
