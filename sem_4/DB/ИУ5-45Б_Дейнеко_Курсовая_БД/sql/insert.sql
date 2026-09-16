INSERT INTO users(username, passphrase, user_role) VALUES
('a', 'a', 'Manager'),
('b', 'b', 'Customer'),

INSERT INTO products(model, product_type, vendor, price) VALUES
('pc-0001', 'pc', 'msi', 70000),
('pc-0002', 'pc', 'asus', 110000),
('pc-0003', 'pc', 'asus', 130000),
('pc-0004', 'pc', 'msi', 180000),
('pc-0005', 'pc', 'dell', 65000),
('lp-0001', 'laptop', 'lenovo', 80000),
('lp-0002', 'laptop', 'dell', 90000),
('lp-0003', 'laptop', 'hp', 130000),
('lp-0004', 'laptop', 'lenovo', 140000),
('lp-0005', 'laptop', 'honor', 65000),
('pr-0001', 'printer', 'canon', 15000),
('pr-0002', 'printer', 'hp', 18500),
('pr-0003', 'printer', 'canon', 12000),
('rt-0001', 'router', 'tp-link', 3500),
('rt-0002', 'router', 'tp-link', 2400);

INSERT INTO pc(model, processor, ram) VALUES
('pc-0001', 'Ryzen 5 5600', '16GB DDR4'),
('pc-0002', 'Ryzen 7 5700', '32GB DDR5'),
('pc-0003', 'Ryzen 7 7800x3d', '32GB DDR4'),
('pc-0004', 'Ryzen 9 9500x3d', '64GB DDR5'),
('pc-0005', 'Ryzen 5 8400f', '16GB DDR5');

INSERT INTO laptop(model, processor, ram) VALUES
('lp-0001', 'Ryzen 6 7500f', '16GB DDR5'),
('lp-0002', 'Intel i5 12th', '32GB DDR4'),
('lp-0003', 'Ryzen 7 7800x3d', '32GB DDR4'),
('lp-0004', 'Intel i7 14th', '32GB DDR5'),
('lp-0005', 'Ryzen 5 8400f', '16GB DDR5');

INSERT INTO printer(model, printer_type) VALUES
('pr-0001', 'laser'),
('pr-0002', 'laser'),
('pr-0003', 'Injective');

INSERT INTO router(model, frequency, bandwidth) VALUES
('rt-0001', 5.0, 800),
('rt-0002', 2.4, 500);

INSERT INTO orders(customer_id, order_date, ship_date, paid_date, status) VALUES
(2, CURRENT_DATE, CURRENT_DATE, NULL, 'A'),
(2, CURRENT_DATE, CURRENT_DATE, NULL, 'A'),
(2, CURRENT_DATE, CURRENT_DATE, NULL, 'A');

INSERT INTO order_content(order_id, product_model, quantity) VALUES
(3, 'pc-0001', 1),
(4, 'rt-0002', 1),
(5, 'lp-0004', 2);