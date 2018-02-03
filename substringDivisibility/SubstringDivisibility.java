
/*
 * Project Euler #43 (Modified)
 * 
 *  Created on: Feb 2, 2018
 *  Author: Dylan DiGeronimo, Jacob Fallin, Kexian Wu
 *  I pledge my honor that I have abided by the Stevens Honor System.
 */

import java.util.Arrays;

public class SubstringDivisibility {
	private static long sum = 0;
	static final int[] primes = new int[] { 2, 3, 5, 7, 11, 13, 17 };

	// Method to sort a string alphabetically
	public static String sortString(String inputString) {
		// Convert input string to char array
		char tempArray[] = inputString.toCharArray();
		// Sort tempArray
		Arrays.sort(tempArray);
		// Return new sorted string
		return new String(tempArray);
	}

	// Recursively call permutations on all valid prefixes with one of character
	// in suffix being appended to them and print all permutations that have
	// sub-string divisibility property in ascending order
	private static void generateAll(String prefix, String suffix) {
		String newPrefix;
		int NewPrefixLen;
		if (suffix.length() == 0) {
			sum += Long.valueOf(prefix);
			System.out.println(prefix);
		} else {
			for (int i = 0; i < suffix.length(); i++) {
				newPrefix = prefix + suffix.charAt(i);
				NewPrefixLen = newPrefix.length();
				if (NewPrefixLen > 3) {
					if (Integer.parseInt(newPrefix.substring(NewPrefixLen - 3)) % primes[NewPrefixLen - 4] == 0) {
						generateAll(newPrefix, suffix.substring(0, i) + suffix.substring(i + 1));
					} else {
						continue;
					}

				} else {
					generateAll(newPrefix, suffix.substring(0, i) + suffix.substring(i + 1));
				}
			}
		}

	}

	public static void main(String[] args) {

		// Check the number of arguments passed to the function
		if ((args == null) || (args.length != 1)) {
			System.out.println("Wrong number of args");
			System.exit(-1);
		}

		// Check if input value is of type Integer
		try {
			Integer.parseInt(args[0]);
		} catch (Exception e) {
			System.out.println("Input value must be an integer");
			System.exit(-1);
		}

		// Check the total digits of the input number
		if (args[0].length() < 4 || args[0].length() > 10) {
			System.out.println("The total digits of the input number should be between 4 and 10");
			System.exit(-1);
		}

		// Parse the command line argument
		String n = args[0];

		// Start the timer
		long start = System.nanoTime();

		// Sort numeric string
		n = sortString(n);

		// Print all permutations that have sub-string divisibility property in
		// ascending order
		generateAll("", n);

		// Print out the sum of these numbers
		System.out.printf("Sum: " + sum + '\n');

		// Print the time
		System.out.printf("Elapsed time: %.6f ms\n", (System.nanoTime() - start) / 1e6);
	}

}