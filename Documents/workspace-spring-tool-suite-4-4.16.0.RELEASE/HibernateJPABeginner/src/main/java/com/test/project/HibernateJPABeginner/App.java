package com.test.project.HibernateJPABeginner;

import com.test.hib.controller.findUser_Hql;

public class App 
{
	public static void main(String[] args) {
		
		findUser_Hql u = new findUser_Hql();
//		u.findUser();
//		u.findUserSelect();
//		u.getRecordbyId();
		u.getmaxSalary();
		
	}
}