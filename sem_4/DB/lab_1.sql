CREATE TABLE IF NOT EXISTS customers
(
	customer_id int NOT NULL PRIMARY KEY,
	company_name varchar(256),
	last_name varchar(256) UNIQUE NOT NULL,
	first_name varchar(256) UNIQUE NOT NULL,
	address text,
	city varchar(256) DEFAULT 'Moscow',
	post_code varchar(10),
	phone varchar(20),
	email varchar(400)
);

CREATE TABLE IF NOT EXISTS orders
(
	order_id int NOT NULL PRIMARY KEY,
	cust_id int NOT NULL,
	order_date date NOT NULL DEFAULT CURRENT_DATE,
	ship_date date NOT NULL CHECK (ship_date > order_date),
	paid_date date,
	status char(1) CONSTRAINT allowed_values CHECK (status = 'A' OR status = 'C' OR status = 'P'),
	FOREIGN KEY (cust_id) REFERENCES customers(customer_id)
);

ALTER TABLE IF EXISTS customers ALTER COLUMN email TYPE varchar(380);