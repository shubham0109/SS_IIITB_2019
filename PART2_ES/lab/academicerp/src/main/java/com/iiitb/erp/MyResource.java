package com.iiitb.erp;

import com.iiitb.erp.bean.Course;
import com.iiitb.erp.dao.CourseDao;
//import com.iiitb.erp.service.CourseService;
//import com.iiitb.erp.service.impl.CourseServiceImpl;

import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;
import java.util.List;
import java.util.List;
import javax.ws.rs.*;
import javax.ws.rs.core.Response;



/**
 * Root resource (exposed at "myresource" path)
 */
@Path("/myresource")
public class MyResource {


   // private CourseService courseService = new CourseServiceImpl();


    @GET @Path("/addCourse")
    //@Produces({"application/json", "application/xml"})
    @Produces(MediaType.TEXT_PLAIN)
    public String addCourse(){
      /*  int c_id = ;
        String c_name = ;
        int f_id = ;
        int p_id = ;
        int s_id = ;*/

        Course obj=new Course();
        obj.setCourse_id(101);
        obj.setCourse_name("Linear Algebra");
        obj.setFaculty_id(501);
        obj.setPrerequisite(101);
        obj.setSlot_id(901);

        CourseDao crDAO=new CourseDao();
        crDAO.save(obj);
        return "success";

    }

    @GET @Path("/getCourses")
    @Produces(MediaType.TEXT_PLAIN)
    public String getCourses() {

       // List<Course> courses = courseService.getAll();
       // return Response.ok().entity(courses).build();

        CourseDao crs = new CourseDao();
        List <Course> courses = crs.getAll();

        System.out.println(courses.size());
        return "success";
    }

}
