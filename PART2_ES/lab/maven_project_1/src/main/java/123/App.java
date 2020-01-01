package 123;

public class App 
{
    public static void main( String[] args )
    {

        Configuration configuration = new Configuration();
        configuration.addAnnotatedClass(User.class);
        SessionFactory sessionFactory = configuration.buildSessionFactory();

        User user = new User();
        user.setId(1);
        user.setName("Shubham");
        user.setEmail("shubham.kumar@iiitb.org");

        Session session = sessionFactory.openSession();
        session.beginTransaction();

        session.save(user);

        session.getTransaction().commit();
        session.close();
    }
}
