package com.iiitb.erp.bean;

import javax.persistence.*;

@Entity
public class Course {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private static Integer Course_id;

    private static String Course_name;

    private static Integer Faculty_id;

    private static Integer Prerequisite;

    private static Integer Slot_id;

    public static Integer getCourse_id() {
        return Course_id;
    }


    public Course() {

    }

    public static void setCourse_id(Integer course_id) {
        Course_id = course_id;
    }

    public static String getCourse_name() {
        return Course_name;
    }

    public static void setCourse_name(String course_name) {
        Course_name = course_name;
    }

    public static Integer getFaculty_id() {
        return Faculty_id;
    }

    public static void setFaculty_id(Integer faculty_id) {
        Faculty_id = faculty_id;
    }

    public static Integer getPrerequisite() {
        return Prerequisite;
    }

    public static void setPrerequisite(Integer prerequisite) {
        Prerequisite = prerequisite;
    }

    public static Integer getSlot_id() {
        return Slot_id;
    }

    public static void setSlot_id(Integer slot_id) {
        Slot_id = slot_id;
    }
}
