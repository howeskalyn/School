package com.perscholas.controller;

import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;
import org.hibernate.cfg.Configuration;
import com.perscholas.model.Employee;

public class EmployeeController {
	public void createEmployeeTable() {
		SessionFactory factory = new Configuration().configure().buildSessionFactory();
		Session session = factory.openSession();

		Transaction t = session.beginTransaction();
		Employee uone = new Employee();
		t.commit();
		System.out.println("successfully saved");
		factory.close();
		session.close();
	}
}
