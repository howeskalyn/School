package com.sba.SMS;

import java.util.List;

import jpa.dao.StudentService;
import jpa.entitymodels.Student;

public class App {
	public static void main(String[] args) {
		
		// ---- Testing StudentService Method ----
		StudentService ss = new StudentService();
		
		// 1
		List<Student> allStudents = ss.getAllStudents();
		for (Student s : allStudents) {
			System.out.println(s.toString());
		}
		
		// 2
		Student stud = ss.getStudentByEmail("htaffley6@columbia.edu");
		System.out.println(stud.toString());
		
		// 3
		System.out.println(ss.validateStudent("htaffley6@columbia.edu", "xowtOQ")); // TRUE
		System.out.println(ss.validateStudent("htaffley6@columbia.edu", "hi")); // FALSE
		
		// 4
		

	}
}
