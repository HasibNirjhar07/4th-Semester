--1. Find the names of all the instructors from the ‘Biology’ department.

SELECT name
FROM instructor
WHERE dept_name = 'Biology';

--2. Show the Course ID and the Title of all the courses registered for by the student with ID ‘12345’.

SELECT course_id, title 
FROM course 
WHERE course_id
IN 
(SELECT course_id FROM takes WHERE ID = '12345');

--3. Find the names and department names of all the students who have taken a course offered by the ‘Comp. Sci.’department.


SELECT name, dept_name
FROM student
WHERE ID
IN
(SELECT ID FROM takes WHERE course_id IN (SELECT course_id FROM course WHERE dept_name = 'Comp. Sci.'));


--4. Find the names of the students who take ‘CS-101’ course in ‘Spring, 2018’.

SELECT name
FROM student
WHERE ID
IN
(SELECT ID FROM takes WHERE
year=2018 AND semester='Spring' AND course_id='CS-101');

--5. Find the names of students who have taken the highest number of courses with a specific prefix ’CS’.

SELECT name
FROM Student
WHERE ID IN (
SELECT ID
FROM (
        SELECT ID, RANK() OVER (ORDER BY COUNT(course_id) DESC) as rank
        FROM takes
        WHERE course_id LIKE 'CS%'
        GROUP BY ID
    )
    WHERE rank = 1
);

--6. Find the names of students who have taken courses taught by at least three different instructors

SELECT name
FROM Student
WHERE ID IN (
Select takes.ID
From takes,teaches,instructor
Where takes.course_id = teaches.course_id AND teaches.ID = instructor.ID
Group By takes.ID
Having COUNT(distinct instructor.ID)>=3);


-- 7. Find the course name and section having the minimum number of enrollments. Do not include the sections that do
-- not have any students enrolled.

SELECT c.title, s.sec_id
FROM course c, section s
WHERE c.course_id = s.course_id
AND s.course_id IN 
(
    SELECT t.course_id
    FROM takes t
    GROUP BY t.course_id
    HAVING COUNT(*) = 
    (
        SELECT MIN(enrollment_count)
        FROM 
        (
            SELECT COUNT(*) as enrollment_count
            FROM takes tk
            GROUP BY tk.course_id
            Having COUNT(*) > 0
        )
    )
);
-- 8. Find the name of the instructor, dept_name, and count of students he/she advising. If an instructor is not advising
-- any student, show 0.

Select Max(instructor.name) as name, Max(instructor.dept_name) as department, COUNT(NVL(student.ID,0)) as No_of_Student
From instructor,advisor,Student
Where advisor.s_id= student.ID AND advisor.i_id = instructor.ID
Group By instructor.ID;


-- 9. Find the name and department of the students who take more courses than the average number of courses taken
-- by a student.

SELECT s.name, s.dept_name
FROM student s
WHERE s.ID IN
(
    SELECT t.ID
    FROM takes t
    GROUP BY t.ID
    HAVING COUNT(*) > 
    (
        SELECT AVG(takes_count)
        FROM
        (
            SELECT COUNT(*) as takes_count
            FROM takes tk
            GROUP BY tk.ID
        )
    )
);


-- 10. Insert each instructor as a student with total credit set to 0 in the same department they are teaching.

INSERT INTO student
(SELECT i.ID, i.name, i.dept_name, 0
FROM instructor i where i.id<>'76543');


-- 11. Remove all the newly added students from the previous query.

DELETE FROM student
WHERE ID IN 
(
    SELECT ID FROM instructor where id<>'76543'
);



-- 12. Update the ‘tot_cred’ for each student based on the credits taken.

UPDATE Student
SET tot_cred = NVL
(
    (SELECT SUM(course.credits) AS credits
     FROM takes
     LEFT JOIN course ON takes.course_id = course.course_id
     WHERE takes.ID = Student.ID), 0
);


-- 13. Update the salary of each instructor to 10000 times the number of course sections they have taught.

UPDATE instructor
SET salary = CASE 
    WHEN (SELECT COUNT(*) * 10000 FROM teaches t WHERE t.instructor_ID = instructor.ID GROUP BY t.instructor_ID) < 29000
    THEN 29000
    ELSE (SELECT COUNT(*) * 10000 FROM teaches t WHERE t.instructor_ID = instructor.ID GROUP BY t.instructor_ID)
END
WHERE ID IN (SELECT instructor_ID FROM teaches);


-- 14. Grades are mapped to a grade point as follows: A:10, B:8, C:6, D:4, and F:0. Create a table to store these mappings,
-- and write a query to find the Credit Point Information (CPI) of each student, using this table. Make sure students who
-- have not got a non-null grade in any course are displayed with a CPI of null.


CREATE TABLE grade_mappings (
    grade CHAR(1) PRIMARY KEY,
    grade_point NUMBER
);

INSERT INTO grade_mappings (grade, grade_point) VALUES ('A', 10);
INSERT INTO grade_mappings (grade, grade_point) VALUES ('B', 8);
INSERT INTO grade_mappings (grade, grade_point) VALUES ('C', 6);
INSERT INTO grade_mappings (grade, grade_point) VALUES ('D', 4);
INSERT INTO grade_mappings (grade, grade_point) VALUES ('F', 0);

SELECT ID,
       SUM(NVL(grade_mappings.grade_point, 0)) / COUNT(DISTINCT takes.course_id) AS CPI
FROM takes
LEFT JOIN grade_mappings ON takes.grade = grade_mappings.grade
GROUP BY ID;


