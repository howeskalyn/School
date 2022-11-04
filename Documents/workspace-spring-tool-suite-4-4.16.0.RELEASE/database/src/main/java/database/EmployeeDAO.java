package database;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class EmployeeDAO {
	
	public List<Employee> findByFirstName(String firstName, String lastName) {
		String dburl = "jdbc:mysql://localhost:3306/classicmodels";
		String user = "root";
		String password = "password";

		Connection connection = null;
		PreparedStatement stmt = null;
		ResultSet result = null;
		
		ArrayList<Employee> employees = new ArrayList<>();
		
//		String firstName = "Mary";
//		String lastName = "Patterson";

		try {
			connection = DriverManager.getConnection(dburl, user, password);
			//System.out.println("connection is read only " + connection.isReadOnly());

			String SelectSQL = "Select * FROM employees where firstName = ? and lastName = ?";
			stmt = connection.prepareStatement(SelectSQL);
			stmt.setString(1, firstName);
			stmt.setString(2, lastName);
			
			
			result = stmt.executeQuery();
			// int u = stmt.executeUpdate(SelectSQL);

			while (result.next()) {
				// get column 1 from the result set - remember it is 1-based
				// Integer one = result.getInt(1);
				
				Employee e = new Employee();
				e.setFirstName(firstName);
				e.setLastName(lastName);
				e.setEmail(result.getString("email"));
				
				employees.add(e);

//				String name = result.getString("firstName");
//				String email = result.getString("email");
//				System.out.println(one + " | " + name + " | " + email);
				
				
			}

			//System.out.println(result.toString());

		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			try {
				result.close();
			} catch (SQLException e) {
				e.printStackTrace();
			} finally {
				try {
					stmt.close();
				} catch (SQLException e) {
					e.printStackTrace();
				} finally {
					try {
						connection.close();
					} catch (SQLException e) {
						e.printStackTrace();
					}
				}

			}

		}
		
		return employees;
	}
	
	public List<Employee> findByEmail(String email) {
		String dburl = "jdbc:mysql://localhost:3306/classicmodels";
		String user = "root";
		String password = "password";

		Connection connection = null;
		PreparedStatement stmt = null;
		ResultSet result = null;
		
		ArrayList<Employee> employees = new ArrayList<>();

		try {
			connection = DriverManager.getConnection(dburl, user, password);
			//System.out.println("connection is read only " + connection.isReadOnly());

			String SelectSQL = "Select * FROM employees where email = ?";
			stmt = connection.prepareStatement(SelectSQL);
			stmt.setString(1, email);
				
			result = stmt.executeQuery();

			while (result.next()) {
				Employee e = new Employee();
				e.setEmail(email);
				
				employees.add(e);
				
			}

			//System.out.println(result.toString());

		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			try {
				result.close();
			} catch (SQLException e) {
				e.printStackTrace();
			} finally {
				try {
					stmt.close();
				} catch (SQLException e) {
					e.printStackTrace();
				} finally {
					try {
						connection.close();
					} catch (SQLException e) {
						e.printStackTrace();
					}
				}

			}

		}
		
		return employees;
	}
	
	
}
