/**
 * @author Mike Zrimsek
 * @version 02.03.2015
 *
 */

import java.util.Scanner;

public class NameWeight
{
	public static void main(String[] args)
	{
		Scanner sc = new Scanner(System.in);
		LinkedList<Person> people = new LinkedList<Person>();
		people.insert(new Person("Joe", Double.valueOf(200), Person.SORT_BY_WEIGHT));
		people.insert(new Person("Adam", Double.valueOf(210), Person.SORT_BY_WEIGHT));
		people.insert(new Person("Mike", Double.valueOf(220), Person.SORT_BY_WEIGHT));
		System.out.println(people);
		
	}
	
}
