package genericsSlideExample;

public class DemoClass {

	// create a generics method
	public <T> void method(T data) {
		System.out.println("\nIn Method:");
		System.out.println("Data Passed: " + data);
	}

}

