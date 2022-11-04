package genericsSlideExample;

public class myRunner {
	public static void main(String[] args) {

		// initialize the class with Integer data
		DemoClass dObj = new DemoClass();

		dObj.method(25); // passing int
		dObj.method("Per Scholas"); // passing String
		dObj.method(2563.5); // passing float
		dObj.method('H'); // passing Char
	}
}
