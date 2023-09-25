create procedure proc_Grade2() 
BEGIN 
DECLARE point1 INT DEFAULT 0; 
DECLARE point2 INT DEFAULT 0; 
DECLARE marks INT; 
DECLARE class VARCHAR(255); 
SELECT COUNT(*) FROM Stud_Marks INTO point1; 
SET point2 = 0; 
WHILE point2 < point1 DO 
	SELECT total_marks INTO marks FROM Stud_Marks LIMIT point2,1;
	IF total_marks <= 1500 AND total_mark >= 990 THEN
		SET class = 'distinction';
	ELSE IF total_marks <= 989 AND total_marks >= 900 THEN
		SET class = 'first class';
	ELSE IF total_marks <= 899 AND total_marks >=825 THEN
		SET class = 'second class';
	ELSE
		SET class = 'third class';
	END IF;
	INSERT INTO Result(name, class) values((SELECT (name) FROM Stud_Marks LIMIT point2,1), class); 
	SET point2 = point2 + 1;
END WHILE;
End;
$$

