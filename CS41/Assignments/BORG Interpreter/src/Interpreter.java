import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

/**
 * 
 * @author Mike Zrimsek
 * @version 04.28.2015
 *
 */

public class Interpreter
{	
	public static void main(String[] args)
	{
		HashTable table = new HashTable();
		File input = new File("borg.txt");
		
		try(BufferedReader reader = new BufferedReader(new FileReader(input)))
		{
			//System.out.println("DEBUG: Starting interpreter");
			int scope = 0;
			HashTable variables = new HashTable(); //keep track of variable scopes
			
			//System.out.println("DEBUG: Reading line");
			String line = reader.readLine();
			
			while(line != null)
			{
				String[] lineItems = filter(line);
				//System.out.println("DEBUG: Deciding how to proceed");
				if(lineItems[0].equals("COM")) //comment
				{
					System.out.println("DEBUG: Comment");
					//break;
				}
				else if(lineItems[0].equals("START")) //start block
				{
					System.out.println("DEBUG: Block start");
					scope++;
				}
				else if(lineItems[0].equals("FINISH")) //end block
				{
					System.out.println("DEBUG: Block end");
					scope*=2;
				}
				else if(lineItems[0].equals("VAR")) //variable declaration
				{
					System.out.println("DEBUG: Variable declaration");
					table.put(lineItems[1], Integer.valueOf(lineItems[3]));
					variables.put(lineItems[1], scope);
				}
				else if(lineItems[0].equals("PRINT")) //print
				{
					System.out.println("DEBUG: Printing");
					String variable = lineItems[1];
					System.out.println(table.get(variable));
					if(table.get(variable) != null) //if variable exists
					{
						if(variables.get(variable) != scope && scope != 0) //not in current scope - 0 means global scope
						{
							System.out.println("DEBUG: Variable not in scope");
							System.out.println(variable + " IS UNDEFINED");
						}
						else
						{
							System.out.println("DEBUG: Variable in scope");
							Integer value = table.get(variable);
							if(lineItems.length > 2) //has an operation
							{
								doOperation(lineItems[2], value, Integer.valueOf(lineItems[3]));
								table.put(variable, value);
							}
							System.out.println(variable + " IS " + value);
						}
					}
				}
				//System.out.println("DEBUG: Reading line");
				line = reader.readLine();
			}
		}
		catch(IOException ioe)
		{
			ioe.printStackTrace();
		}
	}
	
	private static void doOperation(String operator, Integer value, Integer operationVal)
	{
		System.out.println("DEBUG: Deciding operation to execute");
		switch(operator) //switch on operator
		{
			case("++"):
			{
				System.out.println("DEBUG: Increment");
				value++;
				break;
			}
			case("--"):
			{
				System.out.println("DEBUG: Decrement");
				value--;
				break;
			}
			case("+"):
			{
				System.out.println("DEBUG: Addition");
				value += operationVal;
			}
			case("-"):
			{
				System.out.println("DEBUG: Subtraction");
				value -= operationVal;
			}
			case("*"):
			{
				System.out.println("DEBUG: Muliplication");
				value *= operationVal;
			}
			case("/"):
			{
				System.out.println("DEBUG: Division");
				value /= operationVal;
			}
			case("^"):
			{
				System.out.println("DEBUG: Exponent");
				value = (int)Math.pow(value, operationVal);
			}
			case("="):
			{
				System.out.println("DEBUG: Assignment");
				value = operationVal;
			}
			case("%"):
			{
				System.out.println("DEBUG: Modulus");
				value %= operationVal;
			}
		}
	}
	
	private static String[] filter(String line)
	{
		int trim = 0;
		char[] lineArray = line.toCharArray();
		for(int i = 0; i < lineArray.length; i++)
		{
			if(!Character.isWhitespace(lineArray[i]))
			{
				trim = i;
				break;
			}
		}
		return line.substring(trim).split(" ");
	}
}
