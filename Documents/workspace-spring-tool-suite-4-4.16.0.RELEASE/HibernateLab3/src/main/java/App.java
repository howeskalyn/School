import com.perscholas.controller.EmployeController;

public class App {
	public static void main(String[] args) {
		System.out.println("Hello World!");
		EmployeController e = new EmployeController();
		e.createEmployeeTable();
	}
}