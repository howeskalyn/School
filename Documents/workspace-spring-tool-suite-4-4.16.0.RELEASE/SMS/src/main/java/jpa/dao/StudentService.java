package jpa.dao;

import javax.persistence.TypedQuery;

import java.util.List;

import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;
import org.hibernate.cfg.Configuration;

import jpa.entitymodels.Student;

public class StudentService {

	// reads Student table and returns the data as a List<Student>
	public List<Student> getAllStudents() {
		SessionFactory factory = new Configuration().configure().buildSessionFactory();
		Session session = factory.openSession();
		Transaction tx = session.beginTransaction();

		String hql = "FROM Student s";
		TypedQuery<Student> query = session.createQuery(hql, Student.class);
		List<Student> result = query.getResultList();

		// close resources
		tx.commit();
		factory.close();
		session.close();

		return result;
	}

	// takes a Student’s email as a String, parses the student list for a Student
	// with that email, and returns a Student Object
	public Student getStudentByEmail(String sEmail) {
		SessionFactory factory = new Configuration().configure().buildSessionFactory();
		Session session = factory.openSession();
		Transaction tx = session.beginTransaction();

		// must use JAVA VARIABLE names in the hql - hence why we need s.sEmail instead
		// of email
		String hql = "FROM Student s where s.sEmail =: studentEmail";
		TypedQuery<Student> query = session.createQuery(hql, Student.class);
		query.setParameter("studentEmail", sEmail);

		Student result = query.getSingleResult();

		tx.commit();
		factory.close();
		session.close();

		return result;

	}

	// takes two parameters: first is the user email & second is the password from the user input
	// return whether or not a student was found
	public boolean validateStudent(String sEmail, String sPassword) {
		boolean found = false;

		// need to find by email
		Student pulledStudent = getStudentByEmail(sEmail);

		// verify that sPassword matches password pulled
		if (pulledStudent.getSPass().equals(sPassword)) {
			found = true;
		}

		return found;
	}

	// takes a Student’s email and a Course ID & checks in the join table (Student_Course)
	// to find if a Student with that Email is currently attending a Course with that ID
	// if the Student is NOT attending that Course, register the student for that course
	public void registerStudentToCourse(String sEmail, int cId) {
		
		// pull Student_Course by courseId & if studentId == email they're already attending

	}
}
