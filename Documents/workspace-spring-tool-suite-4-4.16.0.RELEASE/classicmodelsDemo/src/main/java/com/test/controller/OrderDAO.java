package com.test.controller;

import java.util.List;

import javax.persistence.TypedQuery;

import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;
import org.hibernate.cfg.Configuration;

import com.test.model.Order;

public class OrderDAO {

	public Order findOrderByOrderNumber(Integer orderNumber) {
		SessionFactory factory = new Configuration().configure().buildSessionFactory();
		Session session = factory.openSession();
		Transaction tx = session.beginTransaction();

		String hql = "FROM Order o where o.orderNumber = :orderNumber";
		TypedQuery<Order> query = session.createQuery(hql, Order.class);
		query.setParameter("orderNumber", orderNumber);
		Order result = query.getSingleResult();

		// Close resources
		tx.commit();
		factory.close();
		session.close();

		return result;
	}
	
	public List<Order> findOrderByStatus(String status) {
		SessionFactory factory = new Configuration().configure().buildSessionFactory();
		Session session = factory.openSession();
		Transaction tx = session.beginTransaction();

		String hql = "FROM Order o where o.status = :status";
		TypedQuery<Order> query = session.createQuery(hql, Order.class);
		query.setParameter("status", status);
		List<Order> result = query.getResultList();

		// Close resources
		tx.commit();
		factory.close();
		session.close();

		return result;
	}
	
	public void insert(Order order) {
		SessionFactory factory = new Configuration().configure().buildSessionFactory();
		Session session = factory.openSession();
		Transaction tx = session.beginTransaction();
		
		session.save(order);
		
		tx.commit();
		factory.close();
		session.close();
	}
	
	public void update(Order order) {
		SessionFactory factory = new Configuration().configure().buildSessionFactory();
		Session session = factory.openSession();
		Transaction tx = session.beginTransaction();
		
		session.merge(order);
		
		tx.commit();
		factory.close();
		session.close();
	}

}
