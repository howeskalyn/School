package sbaCoreJava;

//	class InvalidStringException extends Exception {
//		InvalidStringException(String message) {
//			super(message);
//		}
//	}
//	
//	public class ArrayToList implements MyList {
//		public ArrayList<String> arrayToList;
//		
//	}

import java.util.*;

interface MyList {
	void convert(String[] a);

	void replace(int idx);

	ArrayList<String> compact();
}
// ================ PLEASE WRITE CODE HERE =============

//Write your implementation of the InvalidStringException and the ArrayToList classes below

class InvalidStringException extends Exception {
	
	InvalidStringException(String message) {
		super(message);
	}

}

class ArrayToList implements MyList {
	
	public ArrayList<String> arrayToList;
	
	ArrayToList() {
		arrayToList = new ArrayList<String>();
	}

	@Override
	public void convert(String[] a) {
		
		for (int i = 0; i < a.length; i++) {
			arrayToList.add(a[i]);
			System.out.println("I have added the string: " + a[i] + " at the index: " + i);
			//System.out.println("I have added the string: " + a[i] + " at index: " + i);
		}
	}

	@Override
	public void replace(int idx) {
		String old = arrayToList.get(idx);
		arrayToList.set(idx, "");
		System.out.println("I have replaced the string: " + old + " with a null string.");
	}

	@Override
	public ArrayList<String> compact() {
		// remove all empty strings and return a result list
		ArrayList<String> ret = new ArrayList<String>();
		
		for (int i = 0; i < arrayToList.size(); i++) {
			if (!arrayToList.get(i).equals("")) {
				ret.add(arrayToList.get(i));
			}
		}
		
		return ret;
	}


}

// ================ DO NOT MODIFY THE CODE BELOW EVEN IF YOU ARE ABLE TO EDIT IT!!!!!!
public class Solution {

	public static void main(String[] args) {

		Scanner sc = new Scanner(System.in);
		Random rand = new Random(0);

		int n = Integer.parseInt(sc.nextLine());
		String[] a = new String[n];

		for (int i = 0; i < n; i++)
			a[i] = sc.nextLine();

		MyList obj = new ArrayToList();

		obj.convert(a);
		int x = rand.nextInt(n);
		for (int i = 0; i < x; i++)
			obj.replace(rand.nextInt(n));

		ArrayList<String> s = obj.compact();

		for (int i = 0; i < s.size(); i++) {
			if (s.get(i).charAt(0) >= 97 && s.get(i).charAt(0) <= 122) {
				try {
					throw new InvalidStringException("This is an invalid string");
				} catch (InvalidStringException e) {
					System.out.println(e.getMessage());
				}
			}
		}

	}
}