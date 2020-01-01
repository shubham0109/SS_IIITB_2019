package com.iiitb.erp.dao;

import com.iiitb.erp.bean.Course;
import com.iiitb.erp.util.SessionUtil;
import org.hibernate.Session;
import org.hibernate.Transaction;
import org.hibernate.query.Query;

import java.util.List;

public class CourseDao {


    public void save(Course course) {
        Session session = SessionUtil.getSession();
        Transaction transaction = session.beginTransaction();

        session.save(course);

        transaction.commit();
        session.close();
    }

    public List<Course> getAll() {
        Session session = SessionUtil.getSession();
        Transaction transaction = session.beginTransaction();

        String hql = "FROM Course ";
        Query query = session.createQuery(hql);

        List<Course> courses = query.list();

        System.out.println(courses.size());
        transaction.commit();
        session.close();

        return courses;
    }
}