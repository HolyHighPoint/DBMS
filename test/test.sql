CREATE DATABASE test;
CREATE DATABASE test1;
SHOW DATABASES;
SHOW TABLES;
USE DATABASE test;
SHOW TABLES;
CREATE TABLE customer(
id int(10) NOT NULL,
name char(25),
gender char(1) NOT NULL,
CHECK (gender in('F','M')),
PRIMARY KEY(id)
);
CREATE TABLE customer2(
id int(10) NOT NULL,
name char(25),
gender char(1),
PRIMARY KEY(name)
);
SHOW TABLES;
DESC customer2;
SHOW TABLES;
DESC customer;

CREATE INDEX customer(gender);

INSERT INTO customer VALUES (300001, 'aaaaaa', 'F');
INSERT INTO customer VALUES (300002, 'bbbbbb', 'M');
INSERT INTO customer VALUES (300003, 'cccccc', 'M');
INSERT INTO customer VALUES (300004, 'dddddd', 'F');
INSERT INTO customer VALUES (300005, 'eeeeee', 'F');
INSERT INTO customer VALUES (300006, 'ffffff', 'M');
INSERT INTO customer VALUES (300007, 'gggggg', 'F'), (300008, 'hhhhhh', 'M'), (300009, 'iiiiii', 'M');

INSERT INTO customer VALUES (300006, 'ffffff', 'M');
INSERT INTO customer VALUES ('aaaa', 'ffffff', 'M');
INSERT INTO customer VALUES (300010, 1111111, 'M');
INSERT INTO customer VALUES (300010, 'ffffff', 'MFF');

INSERT INTO customer VALUES (300010, null, 'F');

CREATE INDEX customer(name);
CREATE INDEX customer(id);


DESC customer;


UPDATE customer SET name='MMMMMM' where gender='M';
UPDATE customer SET name='HHHHHH' where name='MMMMMM';

SELECT * FROM customer;

SELECT AVG(id),* FROM customer;
SELECT MAX(id),* FROM customer;
SELECT MIN(id),* FROM customer;
SELECT SUM(id),* FROM customer;

SELECT * FROM customer WHERE name is null;
SELECT * FROM customer WHERE (id<300006 OR name=null) and gender='F';

INSERT INTO customer VALUES (300011, 'jjjjjj', 'G');

SELECT * FROM customer;

UPDATE customer SET gender='G' where gender='F';

SELECT * FROM customer;

INSERT INTO customer2 VALUES (300001, 'aaaaaa', 'F');
INSERT INTO customer2 VALUES (300002, 'bbbbbb', 'M');
INSERT INTO customer2 VALUES (300003, 'cccccc', 'M');
INSERT INTO customer2 VALUES (300004, 'dddddd', 'F');
INSERT INTO customer2 VALUES (300005, 'eeeeee', 'F');
INSERT INTO customer2 VALUES (300006, 'ffffff', 'M');
INSERT INTO customer2 VALUES (300007, 'ffffff', 'F'), (300007, 'gggggg', 'M'),(300007, 'hhhhhh', 'M'),(300007, 'iiiiii', 'F');

SELECT NUM(customer.id),customer.name,customer.gender,AVG(customer2.id),customer2.name,customer2.gender FROM customer,customer2 WHERE (customer.id > 300003) AND (customer2.id < 300003);

SELECT * FROM customer WHERE name Like '%';

SELECT * FROM customer WHERE name Like '%aaaa%';
SELECT * FROM customer WHERE name Like '_aaaa__';
SELECT * FROM customer WHERE name Like '[adH]%';
SELECT * FROM customer WHERE name Like '%[Heg]';
SELECT * FROM customer WHERE name Like '%[!dg]%';

SELECT * FROM customer ORDER BY gender ASC;
SELECT * FROM customer ORDER BY gender DESC;

SELECT * FROM customer ORDER BY id DESC;
SELECT * FROM customer ORDER BY id ASC;

SELECT * FROM customer ORDER BY id DESC LIMIT 5;
SELECT * FROM customer ORDER BY id ASC LIMIT 5 OFFSET 3;

SELECT NUM(id) FROM customer GROUP BY gender ORDER BY id DESC;

SELECT SUM(id),* FROM customer2 GROUP BY gender,id ORDER BY name DESC;


DROP DATABASE test;
DROP DATABASE test1;

