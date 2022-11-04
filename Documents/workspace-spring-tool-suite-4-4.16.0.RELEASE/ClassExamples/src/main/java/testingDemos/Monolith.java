package testingDemos;

import java.util.Scanner;
import java.util.List;
import java.util.Arrays;

public class Monolith {

	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		String[] invalidCharArray = "!@#$%^&*()".split("");
		List<String> invalidChars = Arrays.asList(invalidCharArray);
		
		System.out.println("Create a username: ");
		String userName = scanner.nextLine();
		String[] userNameCharacterArray = userName.split("");
		for (String currentChar: userNameCharacterArray) {
			if (invalidChars.contains(currentChar)) {
				System.out.println("Invalid username!");
				return;
			}
		}
		
		System.out.println("Username is valid!");
		

	}

}
