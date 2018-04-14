
/*
 *  ReciprocalCycles.java
 *
 *  Created on: Apr 14, 2018
 *  Author: Dylan DiGeronimo, Jacob Fallin, Kexian Wu
 *  I pledge my honor that I have abided by the Stevens Honor System.
 *  Problem: https://projecteuler.net/problem=26 (modified)
 */

import java.util.ArrayList;

public class ReciprocalCycles {
	private static String printResult(int denominator, ArrayList<Integer> digits, boolean cycle, int start_idx) {
		int i;
		StringBuilder newString = new StringBuilder();
		// Prints out a unit fraction
		newString.append("1/");
		newString.append(Integer.toString(denominator));
		newString.append(" = ");

		// "digits" arrayList is empty only when denominator equals to 1
		if (digits.isEmpty()) {
			newString.append(1);
		} else if (cycle == true) {
			// there is a recurring pattern
			newString.append("0.");
			for (i = 0; i < digits.size(); i++) {
				if (i == start_idx) {
					// Adds "C" before the recurring cycle
					newString.append("(");
				}
				// Appends all digits
				newString.append(digits.get(i));
			}
			newString.append("), cycle length ");
			// Calculates the length of the recurring cycle
			newString.append(Integer.toString(digits.size() - start_idx));

		}
		// the case when cycle is false
		else {
			newString.append("0.");
			// Appends all digits
			for (i = 0; i < digits.size(); i++) {
				newString.append(digits.get(i));
			}
		}
		// Converts the character buffer of the StringBuilder into a string object
		return newString.toString();

	}

	public static void main(String[] args) {
		// Check the number of arguments passed to the function
		if ((args == null) || (args.length != 1)) {
			System.out.println("Usage: java ReciprocalCycles <denominator>");
			System.exit(-1);
		}

		// Check if input value is of type Integer
		try {
			Integer.parseInt(args[0]);
		} catch (Exception e) {
			System.out.println("Error: Denominator must be an integer in [1, 2000]. Received '" + args[0] + "'.");
			System.exit(-1);
		}
		// Parse the command line argument
		int denominator = Integer.parseInt(args[0]);

		// Check whether the number in the range [1,2000]
		if (denominator < 1 || denominator > 2000) {
			System.out.println("Error: Denominator must be an integer in [1, 2000]. Received '" + denominator + "'.");
			System.exit(-1);
		}
		// Initiate vectors to store remainders and decimals
		ArrayList<Integer> remainders = new ArrayList<>();
		ArrayList<Integer> digits = new ArrayList<>();
		// Initiate values
		int mod = 1;
		int digit = -1;
		boolean cycle = false;
		int start_idx = 0;
		while (true) {
			// find remainder
			mod = mod % denominator;
			// Test whether the number is terminating
			if (mod == 0) {
				// Stop immediately when remainder becomes zero
				break;
			} else if (remainders.contains(mod)) {
				// Detects a repeated remainder (in a cycle if we see the same remainder twice)
				// Determines the start index of recurring digits
				start_idx = remainders.indexOf(mod);
				cycle = true;
				break;
			} else {
				// Calculates the actual digit
				digit = mod * 10 / denominator;
				// Adds the digit to "remainders" arrayList
				remainders.add(mod);
				// Adds the digit to "digits" arrayList
				digits.add(digit);
				// Next step
				mod *= 10;
			}
		}
		// Pretty print
		System.out.println(printResult(denominator, digits, cycle, start_idx));

	}
}
