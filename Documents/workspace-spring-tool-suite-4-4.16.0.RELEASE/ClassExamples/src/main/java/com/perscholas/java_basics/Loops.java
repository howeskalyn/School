package com.perscholas.java_basics;

import java.util.Scanner;
import java.text.NumberFormat;
import java.util.Locale;

public class Loops {

	public static void main(String[] args) {

//		question1();
//		question2();
		question3();
//		subtractionQuizLoop();
//		breakExample();

	}

	public static void question1() {
		for (int i = 1; i <= 12; i++) {
			for (int j = 1; j <= 12; j++) {
				System.out.printf("%5d", i * j);
			}
			System.out.println();
		}

	}

	public static void question2() {
		Scanner input = new Scanner(System.in);
		System.out.print("\nEnter two positive integers: ");
		int n1 = input.nextInt();
		int n2 = input.nextInt();

		// need to know which int is smaller
		int smallest = n1;
		if (n2 < n1) {
			smallest = n2;
		}

		int gcd = 1;
		for (int k = 1; k <= smallest; k++) {
			if (n1 % k == 0 && n2 % k == 0) {
				gcd = k;
			}
		}

		System.out.println("The gcd is: " + gcd + "\n");
	}

	public static void question3() {
		double tuition = 10000;
		NumberFormat nf = NumberFormat.getCurrencyInstance(Locale.US);

		int year = 0;
		double currentTuition = tuition;
		while (currentTuition < tuition * 2) {
			currentTuition = 1.07 * currentTuition;

			year++;
			System.out.printf("Year %2d: $%s\n", year, nf.format(currentTuition));

		}

		System.out.println("The tuition will be doubled in " + year + " years.");
	}

	public static void subtractionQuizLoop() {

		while (true) {

			final int NUMBER_OF_QUESTIONS = 5;
			int correctCount = 0;
			int numQuestions = 0;
			long startTime = System.currentTimeMillis();
			Scanner input = new Scanner(System.in);

			while (numQuestions < NUMBER_OF_QUESTIONS) {
				// 1. Generate two random single-digit integers
				int number1 = (int) (Math.random() * 10);
				int number2 = (int) (Math.random() * 10);

				// 2. If number1 < number2, swap number1 with number2 - no negatives!
				if (number1 < number2) {
					int temp = number1;
					number1 = number2;
					number2 = temp;
				}

				// 3. Prompt the student to answer "What is number1 - number2?"
				System.out.print("What is " + number1 + " - " + number2 + "? ");
				int answer = input.nextInt();

				// 4. Grade the answer and display the result
				if (number1 - number2 == answer) {
					System.out.println("You are correct!");
					correctCount++;
				} else
					System.out.println("Your answer is wrong.\n" + number1 + " - " + number2 + " should be "
							+ (number1 - number2));

				numQuestions++;
			}

			int wrongCount = NUMBER_OF_QUESTIONS - correctCount;

			System.out.println("\nYou got " + correctCount + " answers correct.");
			System.out.println("You got " + wrongCount + " question(s) wrong.");

			long elapsedTime = System.currentTimeMillis() - startTime;
			System.out.println("It took you " + elapsedTime + " ms to complete " + NUMBER_OF_QUESTIONS + " questions.");

			System.out.print("\nWould you like to play again? (Y/N) ");
			String playAgain = input.next();
			if (playAgain.equalsIgnoreCase("y") == false) {
				break;
			}

		}
	}

	// any odd number will continue
	// if i = 4, print the message and break the loop
	public static void breakExample() {

		System.out.println("Starting the loop...");
		for (int i = 1; i <= 5; i++) {

			if (i % 2 != 0) {
				continue;
			}

			System.out.println(i);

			if (i == 4) {
				System.out.println("Breaking the loop!");
				break;
			}

		}

		System.out.println("Ending the loop.");

	}

}
