SELECT * FROM Student NATURAL JOIN PlacementDrive;

SELECT s.s_id, s.s_name, s.CGPA, s.s_branch, s.S_dob, p.Pcompany_name FROM Student s INNER JOIN PlacementDrive p ON s.Drive_id = p.Drive_id ORDER BY s.Drive_id;

SELECT s_name, s_branch FROM Student INNER JOIN PlacementDrive USING(Drive_id) WHERE package = 12;

SELECT s_name, Tcompany_name FROM Student INNER JOIN Training USING(T_id) WHERE T_Fee > 3000;

SELECT T_id, s_name, Tcompany_name, T_Fee, T_year FROM Training INNER JOIN Student USING(T_id) WHERE s_name="Swaraj Goasvi";

SELECT count(T_id) FROM Training WHERE T_year < 2020;

SELECT s_name FROM Student INNER JOIN PlacementDrive USING(Drive_id) WHERE Pcompany_name = "Google" AND location = "mumbai";

SELECT s_name FROM Student INNER JOIN Training USING(T_id) WHERE Tcompany_name = "Google" AND T_year = 2023;

CREATE VIEW Student_training_details AS SELECT * FROM Student NATURAL JOIN Training;

INSERT INTO Student_details VALUES (11, "Advait Kulkarni", 9.01, "2003-06-24");
ALTER Student_details SET CGPA=9.21 WHERE s_id = 11;
UPDATE Student_details SET CGPA=9.21 WHERE s_id = 11;
DELETE FROM Student_details WHERE s_id = 11;
DROP VIEW Student_details;
