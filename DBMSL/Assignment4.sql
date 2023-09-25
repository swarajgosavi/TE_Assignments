--create table 
CREATE TABLE circle(
	radius FLOAT,
	area FLOAT
);

--set delimiter
DELIMITER $$

--creation of procedure
CREATE PROCEDURE calarea(IN radius FLOAT)
	BEGIN
	DECLARE r, area FLOAT;
	SET r = radius;
	IF r>=5 AND r <= 9 THEN
		SET area = 3.14 * r * r;
		INSERT INTO circle VALUES(r, area);
		SELECT 'Area Calucated and inserted' AS message;
	ELSE
		SELECT 'Radius is not in range 5 to 9' AS message;
	END IF;
	END;
	$$

--reset dilimiter
DELIMITER ;

--calling of procedure
CALL calarea(5);
CALL calarea(8.76);
CALL calarea(-36);
CALL calarea(28);

--procedure with exception handling
CREATE PROCEDURE area2 (IN radius FLOAT)
BEGIN
DECLARE testCondition CONDITION FOR SQLSTATE '45000';
DECLARE r, area FLOAT;
SET r = radius;
IF r>=5 AND r <= 9 THEN
	SET area = 3.14 * r * r;
	INSERT INTO circle VALUES(r, area);
	SELECT 'Area Calucated and inserted' AS message;
ELSEIF r < 0 THEN
         SIGNAL SQLSTATE '01000';
ELSE
         SIGNAL SQLSTATE '45000'
      SET MESSAGE_TEXT = 'Radius is not in range 5 to 9', MYSQL_ERRNO = 1001;
END IF;
END;
