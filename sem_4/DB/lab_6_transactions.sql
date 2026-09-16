-- 6
CREATE TABLE products (
    id INTEGER PRIMARY KEY,
    name TEXT,
    stock INTEGER
);

CREATE TABLE reservations (
    id INTEGER PRIMARY KEY,
    product_id INTEGER,
    quantity INTEGER,
    reserved_at TIMESTAMP,
    try SMALLINT
);

-- 7
INSERT INTO products (id, name, stock) VALUES
(1, 'Ноутбук', 10),
(2, 'Мышь', 50),
(3, 'Клавиатура', 5);

SELECT * FROM products;

-- 8
BEGIN;
INSERT INTO reservations (id, product_id, quantity, reserved_at, try)
VALUES (1, 1, 2, NOW(), 0);

SAVEPOINT before_second_reserve;

INSERT INTO reservations (id, product_id, quantity, reserved_at, try)
VALUES (2, 1, 100, NOW(), 0);

UPDATE products
SET stock = stock - 100
WHERE id = 1 AND stock >= 100;

ROLLBACK TO SAVEPOINT before_second_reserve;

UPDATE products
SET stock = stock - 2
WHERE id = 1;

UPDATE reservations
SET try = 1
WHERE id = 1;
COMMIT;

SELECT * FROM reservations;
SELECT * FROM products;


/*
BEGIN;
SELECT * FROM products WHERE id = 1 FOR UPDATE;
SELECT pg_sleep(20); -- задержка 20 секунд
COMMIT;
*/

/*
UPDATE products SET stock = stock - 1 WHERE id = 1;
*/

SELECT * FROM products WHERE id = 1;