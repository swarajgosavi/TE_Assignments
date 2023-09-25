CREATE TABLE Library (
    ISBN INT PRIMARY KEY,
    title VARCHAR(20),
    aunthor VARCHAR(20),
    publisher VARCHAR(20),
    pub_year YEAR
);

INSERT INTO Library VALUES
(),
(),

CREATE TABLE Library_Audit (
    ISBN INT PRIMARY KEY,
    title VARCHAR(20),
    aunthor VARCHAR(20),
    publisher VARCHAR(20),
    pub_year YEAR,
    entry_date DATETIME DEFAULT CURRENT_TIMESTAMP 
);

CREATE TRIGGER on_update
AFTER UPDATE ON Library
FOR EACH ROW
BEGIN
INSERT INTO Library_Audit VALUES (old.ISBN, old.title, old.aunthor, old.publisher, old.pub_year, SYSDATE());
end;
