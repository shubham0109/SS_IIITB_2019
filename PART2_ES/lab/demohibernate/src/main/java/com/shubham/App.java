package com.shubham;

import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;
import org.hibernate.cfg.Configuration;

public class App 
{
    public static void main( String[] args )
    {


     /*   Alien alien = new Alien();
        alien.setAid(1);
        alien.setAname("Shubham");
        alien.setAcolor("Red");*/


        Course course = new Course();
        course.setCourse_id(101);
        course.setCourse_name("Linear Algebra");
        course.setFaculty_id(501);
        course.setSlot_id(901);



        Configuration con = new Configuration().configure().addAnnotatedClass(Course.class);
        SessionFactory sf = con.buildSessionFactory();
        Session session = sf.openSession();

        Transaction tx = session.beginTransaction();

        session.save(course);


        tx.commit();
    }
}
