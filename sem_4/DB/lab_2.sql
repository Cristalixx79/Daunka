--a
SELECT * FROM customers;
--b
SELECT customer_id, last_name, first_name FROM customers;
--c
SELECT * FROM customers ORDER BY first_name DESC;
--d
SELECT * FROM customers LIMIT 10;
--e
SELECT * FROM products WHERE price > 100;
--f
SELECT * FROM orders WHERE ship_date BETWEEN (CURRENT_DATE - INTERVAL '6 months') AND CURRENT_DATE;
--g
SELECT * FROM orders WHERE cust_id IN (SELECT customer_id FROM customers WHERE customer_id=11);
--h
SELECT * FROM customers WHERE company_name LIKE 'A%';
--i
SELECT * FROM orders WHERE paid_date IS NULL;
--j
SELECT cust_id, COUNT(*) AS orders_count FROM orders GROUP BY cust_id ORDER BY cust_id;
--k
SELECT cust_id, COUNT(*) AS orders_count FROM orders GROUP BY cust_id HAVING COUNT(*) > 2 ORDER BY cust_id;
--l
SELECT c.customer_id, c.first_name, c.last_name 
FROM orders JOIN customers AS c ON (orders.cust_id = c.customer_id) 
WHERE paid_date IS NULL ORDER BY customer_id;
--m
SELECT DISTINCT * FROM products;
--n
SELECT * FROM orders WHERE EXISTS 
(SELECT customer_id FROM customers WHERE customer_id = cust_id AND first_name LIKE 'A%');
--o
SELECT customer_id, 
	CASE WHEN COUNT(o.cust_id)>=3 THEN 'Good client'
		ELSE 'Just client'
	END
FROM customers JOIN orders AS o ON (o.cust_id = customer_id) GROUP BY customer_id ORDER BY customer_id;

-- Задания по вариантам (5)
SELECT * FROM orders WHERE order_date < '2026-01-01' ORDER BY order_id DESC;

SELECT * FROM customers WHERE NOT EXISTS 
(SELECT * FROM orders WHERE customer_id = orders.cust_id) ORDER BY last_name;
