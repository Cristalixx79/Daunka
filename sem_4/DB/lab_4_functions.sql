--c
CREATE OR REPLACE FUNCTION mean_value(value1 REAL, value2 REAL, value3 REAL)
RETURNS REAL
LANGUAGE SQL
AS $$
	SELECT (value1 + value2 + value3) / 3 ::REAL
$$;

CREATE OR REPLACE FUNCTION mean_value(value1 REAL, value2 REAL)
RETURNS REAL
LANGUAGE SQL
AS $$
	SELECT (value1 + value2) / 2 ::REAL
$$;

--d
CREATE OR REPLACE FUNCTION find_by_company_name(company VARCHAR(256))
RETURNS SETOF customers
LANGUAGE SQL
AS $$
	SELECT * FROM customers WHERE company_name = company;
$$;

--e
CREATE OR REPLACE FUNCTION find_by_price(price_s NUMERIC, price_e NUMERIC)
RETURNS SETOF products
LANGUAGE SQL
AS $$
	SELECT * FROM products WHERE price BETWEEN price_s AND price_e;
$$;

--f
CREATE OR REPLACE FUNCTION find_by_order_date(date_s DATE, date_e DATE)
RETURNS SETOF orders
LANGUAGE plpgsql
AS $$
BEGIN
    IF date_e IS NULL THEN 
        RETURN QUERY SELECT * FROM orders WHERE order_date = date_s;
    ELSE 
        RETURN QUERY SELECT * FROM orders WHERE order_date BETWEEN date_s AND date_e;
    END IF;
END;
$$;

--g
CREATE OR REPLACE FUNCTION find_by_company_name2(company VARCHAR(256), company2 VARCHAR(256))
RETURNS SETOF customers
LANGUAGE SQL
AS $$
	SELECT * FROM customers WHERE company_name = company OR company_name = company2;
$$;

CREATE OR REPLACE FUNCTION find_most_active()
RETURNS TABLE(city VARCHAR(256), avg_count REAL)
LANGUAGE plpgsql
AS $$
BEGIN
    CREATE OR REPLACE VIEW vordercount AS 
	SELECT cust_id, COUNT(*) AS order_count FROM orders GROUP BY cust_id ORDER BY cust_id;

	RETURN QUERY SELECT c.city, CAST(AVG(vordercount.order_count) AS REAL) AS avg_count
	FROM vordercount JOIN customers AS c ON(vordercount.cust_id = c.customer_id) GROUP BY c.city ORDER BY avg_count DESC;
END;
$$;