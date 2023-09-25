-- Ceate Tables
CREATE TABLE Training(
	T_id INT PRIMARY KEY AUTO_INCREMENT,
	Tcompany_name VARCHAR(255),
	T_Fee INT,
	T_year YEAR
);

CREATE TABLE PlacementDrive(
	Drive_id INT PRIMARY KEY AUTO_INCREMENT,
	Pcompany_name VARCHAR(255),
	package INT,
	location VARCHAR(255)
);

CREATE TABLE Student(
	s_id INT PRIMARY KEY AUTO_INCREMENT,
	Drive_id INT,
	T_id INT,
	s_name VARCHAR(255),
	CGPA FLOAT,
	s_branch VARCHAR(255),
	S_dob DATE,
	FOREIGN KEY(Drive_id) REFERENCES PlacementDrive(Drive_id) ON DELETE CASCADE,
	FOREIGN KEY(T_id) REFERENCES Training(T_id) ON DELETE CASCADE
);


-- Insert Data

insert into PlacementDrive(Pcompany_name,package,location)
values
( 'Siemens' , 24 , 'pune' ) ,
( 'Barclays' , 12 , 'pune' ) , 
( 'Espressif Systems' , 15 , 'mumbai' ) , 
( 'Mastercard' , 40 , 'bengaluru' ) , 
( 'Google' , 50 , 'mumbai' ) ;

insert into Training(Tcompany_name, T_Fee, T_year)
values
( 'Siemens' , 3000 , '2022' ) ,
( 'Barclays' , 1000 , '2019' ) , 
( 'Espressif Systems' , 3500 , '2023' ) , 
( 'Mastercard' , 4000 , '2019' ) , 
( 'Google' , 5000 , '2023' ) ;

insert into Student( Drive_id , T_id , s_name , CGPA , s_branch, S_dob )
values
( 4 , 3 , 'Swaraj Goasvi' , 8.41 , 'CE', '2003-05-20' ),
( 2 , 3 , 'Niraj KArande' , 9.00 , 'CE', '2003-07-20' ),
( 1 , 2 , 'Joel Alphonso' , 9.33 , 'CE', '2003-06-28' ),
( 2 , 2 , 'Shivam Ketan' , 8.12 , 'IT', '2003-08-16' ),
( 1 , 4 , 'Gopal Saraf' , 8.76 , 'IT', '2001-11-25' ),
( 4 , 1 , 'Advait Nagarkar' , 8.00 , 'IT', '2004-04-24' ),
( 3 , 3 , 'Rana Vanikar' , 6.87 , 'ENTC', '2003-08-01' ),
( 2 , 5 , 'Mihir Sardesai' , 7.80 , 'ENTC', '2003-10-18' ),
( 5 , 5 , 'Shubham Panchal' , 9.30 , 'CE', '2003-04-02' ),
( 4 , 4 , 'Shrinidhi Kulkarni' , 6.90 , 'CE', '2003-06-08' );


-- Queries

SELECT * FROM Student WHERE ( s_branch in ('CE', 'IT')) AND (s_name LIKE 'D%' || s_name LIKE 'A%');

SELECT DISTINCT Pcompany_name FROM PlacementDrive;

SELECT T_id, Tcompany_name, T_Fee+(T_Fee*15/100) AS T_Fee, T_year FROM Training WHERE T_year = 2019;

DELETE FROM Student WHERE CGPA < 7;

SELECT Pcompany_name FROM PlacementDrive WHERE location in ('pune', 'mumbai');

SELECT s.s_name FROM Student s JOIN Training t ON s.T_id = t.T_id WHERE t.T_year in('2021', '2019');

SELECT s_name, CGPA FROM Student ORDER BY CGPA DESC LIMIT 1;
SELECT s_name, CGPA FROM Student WHERE CGPA BETWEEN 7 AND 9;

SELECT t.T_id, t.T_Fee, s.s_name FROM Student s JOIN Training t ON s.T_id = t.T_id ORDER BY t.T_Fee DESC;

SELECT d.Pcompany_name, s.s_name, d.location, d.package from Student s JOIN PlacementDrive d ON d.Drive_id = s.Drive_id WHERE d.package in (30, 40, 50);


-- Views and Index

CREATE INDEX stundent_name ON Student(s_name);

CREATE INDEX index_training ON Training(Tcompany_name, T_year);

CREATE UNIQUE INDEX index_drive ON PlacementDrive(package);

CREATE INDEX index_student ON Student(s_name(20));

CREATE VIEW Student_details AS SELECT s_id, s_name, CGPA, S_dob FROM Student;

CREATE VIEW Placement AS SELECT s.s_name, t.Tcompany_name, d.Pcompany_name FROM Student s, Training t, PlacementDrive d WHERE s.Drive_id = d.Drive_id AND s.T_id = t.T_id;
