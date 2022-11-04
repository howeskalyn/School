package sbaCoreJava;

import java.util.*;

interface Sport {
	void calculateAvgAge(int[] age);

	void retirePlayer(int id);
}

// ================ PLEASE WRITE CODE HERE =============

/*
 * Write your implementation of the Cricket and Football classes below.
 */

class Cricket implements Sport {

	public int[] playerIDs;

	Cricket() {
		playerIDs = new int[11];
		for (int i = 0; i < playerIDs.length; i++) {
			playerIDs[i] = 1;
		}
		System.out.println("A new cricket team has been formed");
	}

	@Override
	public void calculateAvgAge(int[] age) {
		double sum = 0;

		for (int i = 0; i < age.length; i++) {
			sum += age[i];
		}

		double averageAge = sum / age.length;
		System.out.printf("The average age of the team is %.2f", averageAge);

	}

	@Override
	public void retirePlayer(int id) {

		if (playerIDs[id] == -1) {
			System.out.println("Player has already retired");
		} else {
			playerIDs[id] = -1;
			System.out.println("Player with id: " + id + " has retired");
		}
	}

}

class Football implements Sport {
	public int[] playerIDs;
	
	Football() {
		playerIDs = new int[11];
		for (int i = 0; i < playerIDs.length; i++) {
			playerIDs[i] = 1;
		}
		System.out.println("A new football team has been formed");
	}

	@Override
	public void calculateAvgAge(int[] age) {
		double sum = 0;

		for (int i = 0; i < age.length; i++) {
			sum += age[i];
		}

		double averageAge = sum / age.length;
		System.out.printf("The average age of the team is %.2f", averageAge);

	}

	@Override
	public void retirePlayer(int id) {
		
		if (playerIDs[id] == -1) {
			System.out.println("Player has already retired");
		} else {
			playerIDs[id] = -1;
			System.out.println("Player with id: " + id + " has retired");
		}
	}
	
	public void playerTransfer(int fee, int id) {
		if (playerIDs[id] == 1) {
			System.out.println("Player with id: " + id + " has been transferred with a fee of " + fee);
		} else if (playerIDs[id] == -1) {
			System.out.println("Player has retired");
		}
	}

}
