package com.test.controller;

import java.util.List;

import javax.persistence.TypedQuery;

import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;
import org.hibernate.cfg.Configuration;

import com.test.model.OrderDetail;

public class OrderDetailDAO {
	
	public List<OrderDetail> findOrderDetailByOrderNumber(Integer orderNumber) {
	
		SessionFactory factory = new Configuration().configure().buildSessionFactory();
		Session session = factory.openSession();
		Transaction tx = session.beginTransaction();
	
		String hql = "FROM OrderDetail o where o.orderNumber = :orderNumber";
		TypedQuery<OrderDetail> query = session.createQuery(hql, OrderDetail.class);
		query.setParameter("orderNumber", orderNumber);
		List<OrderDetail> result = query.getResultList();

		// Close resources
		tx.commit();
		factory.close();
		session.close();
		
		return result;
	}
	
}
