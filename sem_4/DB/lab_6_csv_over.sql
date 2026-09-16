--2
COPY customers TO 'C:/postgre_data/customers.csv' WITH (FORMAT CSV, HEADER true, ENCODING 'UTF-8', DELIMITER ';');
SELECT * FROM customers ORDER BY customer_id;

--3
COPY customers FROM 'C:/postgre_data/customers.csv' WITH (FORMAT CSV, HEADER true, ENCODING 'UTF-8', DELIMITER ';');
SELECT * FROM orders;

--4
SELECT last_name, first_name, company_name, 
	ROW_NUMBER() OVER (ORDER BY company_name) AS num,
	RANK() OVER (ORDER BY company_name) AS ranking,
	DENSE_RANK() OVER (ORDER BY company_name) AS dense_ranking 
FROM customers;

SELECT * FROM products ORDER BY product_id;
SELECT name, price,
	SUM(price) OVER (ORDER BY product_id) AS summ,
	MAX(price) OVER (ORDER BY product_id) AS maxx
FROM products;

SELECT * FROM products ORDER BY product_id;
SELECT name, price,
	SUM(price) OVER (PARTITION BY re_order) AS summ,
	MAX(price) OVER (PARTITION BY re_order) AS maxx
FROM products;

SELECT name, price,
	LAG(price, 1, 0) OVER (ORDER BY product_id) AS prev,
	LEAD(price, 1, 0) OVER (ORDER BY product_id) AS nxt,
	price - LAG(price, 1, 0) OVER (ORDER BY product_id) AS diff
FROM products;

--5
CREATE DATABASE reservation_lab;