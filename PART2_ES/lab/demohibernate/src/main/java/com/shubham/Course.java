package com.shubham;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;

@Entity
public class Course {
    @Id
    private int Course_id;

    private String Course_name;

    private int Faculty_id;

    private int Prerequisite;

    private int Slot_id;


    public int getCourse_id() {
        return Course_id;
    }

    public void setCourse_id(int course_id) {
        Course_id = course_id;
    }

    public String getCourse_name() {
        return Course_name;
    }

    public void setCourse_name(String course_name) {
        Course_name = course_name;
    }

    public int getFaculty_id() {
        return Faculty_id;
    }

    public void setFaculty_id(int faculty_id) {
        Faculty_id = faculty_id;
    }

    public int getPrerequisite() {
        return Prerequisite;
    }

    public void setPrerequisite(int prerequisite) {
        Prerequisite = prerequisite;
    }

    public int getSlot_id() {
        return Slot_id;
    }

    public void setSlot_id(int slot_id) {
        Slot_id = slot_id;
    }
}
