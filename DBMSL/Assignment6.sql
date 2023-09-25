CREATE TABLE O_EmpId(
    eid INT AUTO_INCREMENT PRIMARY KEY,
    ename VARCHAR(20),
    salary INT
) ;
 
INSERT INTO O_EmpId(ename, salary) VALUES
( 'Shubham' ,1200) , 
( 'Kaustubh' , 4561 ) , 
( 'Ayush' , 1230 ) , 
( 'Swaraj' , 9990 ) , 
( 'Advait' , 78890 ) ;

CREATE TABLE N_EmpId(
    eid INT AUTO_INCREMENT PRIMARY KEY,
    ename VARCHAR(20),
    salary INT
) ; 

DELIMITER $$
CREATE PROCEDURE add_employee( IN employee_id INT )
BEGIN

DECLARE empid_2 INT;
DECLARE exit_loop BOOLEAN;

DECLARE c1 CURSOR FOR SELECT eid FROM O_EmpId WHERE eid >= employee_id;
DECLARE CONTINUE HANDLER FOR NOT FOUND SET exit_loop = true;

OPEN c1;
emp_loop: loop
FETCH c1 INTO empid_2;
IF NOT EXISTS (SELECT * FROM N_EmpId WHERE eid = empid_2) THEN
INSERT INTO N_EmpId SELECT * FROM O_EmpId WHERE eid = empid_2;
END IF;

IF exit_loop THEN
CLOSE c1;
LEAVE emp_loop;
END IF;
END loop emp_loop;

END
$$
DELIMITER ;

