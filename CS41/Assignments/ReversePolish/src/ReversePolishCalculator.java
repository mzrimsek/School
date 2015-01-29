/**
 * @author Mike Zrimsek
 * @version 01.28.2015
 */

public class ReversePolishCalculator
{
	LinkedStack<String> stack;
	String formula;
	
	public ReversePolishCalculator(String formula)
	{
		this.formula = formula.trim();
		stack = populateStack();
	}
	
	public void calculate()
	{
		// do algorithm here
		System.out.println(stack);
	}
	
	// checks for valid data and then add data to the stack
	private LinkedStack<String> populateStack()
	{
		LinkedStack<String> stack = new LinkedStack<String>();
		if (isValidFormula()) for (String s : formula.split(" "))
			if (!s.equals("=")) stack.push(s.trim());
		return stack;
	}
	
	// checks if entered formula is valid
	private boolean isValidFormula()
	{
		boolean val = formula.length() != 0
				&& formula.charAt(formula.length() - 1) == '=';
		if (val == false) System.out.println("Invalid formula!");
		return val;
	}
}
