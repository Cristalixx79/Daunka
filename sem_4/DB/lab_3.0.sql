DROP VIEW IF EXISTS vCustomers;
CREATE OR REPLACE VIEW vCustomers AS SELECT first_name, last_name FROM customers WHERE company_name LIKE 'A%';

ALTER VIEW vCustomers RENAME COLUMN first_name TO firstn;
ALTER VIEW vCustomers RENAME COLUMN last_name TO lastn;

CREATE OR REPLACE VIEW vCustomers (firstn, lastn, company) AS 
SELECT first_name, last_name, company_name FROM customers WHERE company_name LIKE 'B%';
INSERT INTO vCustomers VALUES ('Cris', 'Bulovski', 'Brairot Production 2');

CREATE VIEW vProducts AS SELECT name, price FROM products WHERE price > 20 WITH CHECK OPTION;
INSERT INTO vProducts VALUES ('apple', 5.33); --не работает
DROP VIEW IF EXISTS vProducts;