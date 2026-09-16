--a
CALL insert_customer('Microsoft', 'Arschan', 'Allen', '12 Jocker Ave.', 'Soult-Lake-City', 
	'919-232', '+1-432-913-18-73', 'arschan234@gmail.com');
--b
CALL update_orders();

CALL loop_ten_times();

--c
SELECT mean_value(1, 5, 78);
SELECT mean_value(5, 78);
--d
SELECT * FROM find_by_company_name('Bebra org');
--e
SELECT * FROM find_by_price(23, 100);
--f
SELECT * FROM find_by_order_date('2025-02-03', '2025-06-03');
--g
SELECT * FROM find_by_company_name2('Bebra org', 'Apex Innovations');
SELECT * FROM find_most_active();

--3
INSERT INTO orders(order_id, cust_id, order_date, ship_date, paid_date, status) VALUES
(54, 12, '2025-02-24', '2025-02-28', '2025-02-24', 'A');

SELECT * FROM products ORDER BY product_id;
SELECT * FROM items ORDER BY item_id;
SELECT * FROM orders ORDER BY order_id;

--4/6
DELETE FROM products WHERE product_id = 16;
--5
CALL update_orders();
--8
ALTER TABLE products ADD COLUMN temp1 INT;

SELECT * FROM logs;