package database;

import java.util.List;

public class ConnectionExample {

	public static void main(String[] args) {
		EmployeeDAO employeeDAO = new EmployeeDAO();

		List<Employee> employees = employeeDAO.findByFirstName("Mary", "Patterson");

		for (Employee e : employees) {
			System.out.println(e.getFirstName() + " " + e.getLastName());
		}

		// create a find by email function to look up an employee by email
		List<Employee> employees2 = employeeDAO.findByEmail("mpatterso@classicmodelcars.com");

		for (Employee e : employees2) {
			System.out.println(e.getEmail());
		}

	}
}
