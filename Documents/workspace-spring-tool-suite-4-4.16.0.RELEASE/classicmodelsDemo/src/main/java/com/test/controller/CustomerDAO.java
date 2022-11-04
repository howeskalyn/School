package com.test.controller;

import java.util.List;

import javax.persistence.TypedQuery;

import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;
import org.hibernate.cfg.Configuration;

import com.test.model.Customer;
import com.test.model.Employee;

public class CustomerDAO {

	public Customer findByCustomerId(Integer id) {
		SessionFactory factory = new Configuration().configure().buildSessionFactory();
		Session session = factory.openSession();
		Transaction tx = session.beginTransaction();

		String hql = "FROM Customer c where c.id =: custId";
		TypedQuery<Customer> query = session.createQuery(hql, Customer.class);
		query.setParameter("custId", id);

		Customer result = query.getSingleResult();

		// Close resources
		tx.commit();
		factory.close();
		session.close();
		
		return result;
	}
	
//	public List<Employee> findBySalesRep(Integer salesRepId) {
//		SessionFactory factory = new Configuration().configure().buildSessionFactory();
//		Session session = factory.openSession();
//		Transaction tx = session.beginTransaction();
//
//		String hql = "FROM Customer c where c.salesRepEmployeeNumber =: c.salesRepId";
//		TypedQuery<Employee> query = session.createQuery(hql, Employee.class);
//		query.setParameter("salesRepEmployeeNumber", salesRepId);
//
//		List<Employee> result = query.getResultList();
//
//		// Close resources
//		tx.commit();
//		factory.close();
//		session.close();
//
//		return result;
//		
//	}


}
