/**
 * 
 * @author Mike Zrimsek
 * @version 01.29.2015
 */

public class ReversePolishCalculator
{
	private LinkedStack<String> stack;
	private String formula;
	
	public ReversePolishCalculator(String formula)
	{
		stack = new LinkedStack<String>();
		this.formula = formula;
	}
	
	/**
	 * 
	 * @return True if result of expression was successfully calculated and
	 *         prints the reason for failing if it was not
	 */
	public boolean calculate()
	{
		String[] formulaTokens = formula.split(" ");
		// Checks for overall expression requirements
		if (!isValidFormula(formulaTokens)) return false;
		for (String s : formulaTokens)
		{
			if (!s.equals("="))
			{
				if (isOperator(s))
				{
					try
					{
						s = doOperation(s, stack.pop(), stack.pop());
					}
					// Only throws exception if there not enough operands for
					// all the inputed operators
					catch (NullPointerException npe)
					{
						System.out.println("Error: Too many operators.");
						return false;
					}
				}
				if (!s.equals("NAN"))
					stack.push(s);
				else
				{
					System.out.println("Error: Divide by zero.");
					return false;
				}
			}
		}
		// Stack size will only be more than one after calculating if there are
		// not enough operators for all inputed operands
		if (stack.size() != 1)
		{
			System.out.println("Error: Too many operands.");
			return false;
		}
		return true;
	}
	
	/**
	 * 
	 * @param op
	 *            The operation to be performed
	 * @param num2
	 *            The second number used
	 * @param num1
	 *            The first number used
	 * @return The result of the operation or 'NAN' for a divide by zero error
	 */
	private String doOperation(String op, String num2, String num1)
	{
		double n1 = Double.valueOf(num1);
		double n2 = Double.valueOf(num2);
		double val = 0;
		if (op.equals("+")) // n n +
			val = n1 + n2;
		else if (op.equals("-")) // n n -
			val = n1 - n2;
		else if (op.equals("*")) // n n *
			val = n1 * n2;
		else
		// n n /
		{
			if (n2 == 0) return "NAN"; // divide by zero error
			val = n1 / n2;
		}
		return val + "";
	}
	
	/**
	 * 
	 * @param tokens
	 *            Array of inputed expression tokens
	 * @return True if inputed expression is valid and prints the reason for
	 *         failing if it is not.
	 */
	private boolean isValidFormula(String[] tokens)
	{
		// Smallest expression is n n + =
		if (tokens.length < 4)
		{
			System.out.println("Error: Expression too short.");
			return false;
		}
		// Expressions must terminate with '='
		else if (!tokens[tokens.length - 1].equals("="))
		{
			System.out
					.println("Error: Expression must be terminated with '=' character.");
			return false;
		}
		else
		{
			for (String s : tokens)
			{
				// Expression only contains numbers, operators, and '='
				if (!isOperator(s) && !isDigit(s) && (!s.equals("=")))
				{
					System.out.println("Error: Invalid input character.");
					return false;
				}
			}
		}
		return true;
	}
	
	/**
	 * 
	 * @param s
	 *            String to test
	 * @return True if value is a +, -, *, or /
	 */
	private boolean isOperator(String s)
	{
		return s.equals("+") || s.equals("-") || s.equals("*") || s.equals("/");
	}
	
	/**
	 * 
	 * @param s
	 *            String to test
	 * @return True if value is a number
	 */
	private boolean isDigit(String s)
	{
		try
		{
			Double.valueOf(s);
		}
		catch (NumberFormatException e)
		{
			return false;
		}
		return true;
	}
	
	public String toString()
	{
		return stack.toString();
	}
}
