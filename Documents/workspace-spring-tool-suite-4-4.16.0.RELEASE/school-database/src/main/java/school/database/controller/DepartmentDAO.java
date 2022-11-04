package school.database.controller;

import javax.persistence.TypedQuery;

import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;
import org.hibernate.cfg.Configuration;

import school.database.model.Department;

public class DepartmentDAO {
	
	public Department findById(Integer id) {
		SessionFactory factory = new Configuration().configure().buildSessionFactory();
		Session session = factory.openSession();
		Transaction tx = session.beginTransaction();

		String hql = "FROM Department d where d.id =: deptId";
		TypedQuery<Department> query = session.createQuery(hql, Department.class);
		query.setParameter("deptId", id);

		Department result = query.getSingleResult();

		// Close resources
		tx.commit();
		factory.close();
		session.close();
		
		return result;
	}

}
