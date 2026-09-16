--a
CREATE OR REPLACE PROCEDURE insert_new_customer(company_name varchar(256), last_name varchar(256), first_name varchar(256),
	address text, city varchar(256), post_code varchar(10), phone varchar(20), email varchar(256))
LANGUAGE SQL
AS $$
	INSERT INTO customers (company_name, last_name, first_name, address, city, post_code, phone, email) 
	VALUES (company_name, last_name, first_name, address, city, post_code, phone, email);
$$;

CREATE OR REPLACE PROCEDURE loop_ten_times()
LANGUAGE plpgsql AS $$
DECLARE
	counter INT := 0;
BEGIN
	FOR i IN 1..10 LOOP
		RAISE NOTICE 'Iteration: %', counter;
		counter := counter + 1;
	END LOOP;
END;
$$;

--b
CREATE OR REPLACE PROCEDURE update_orders()
LANGUAGE SQL
AS $$
	UPDATE orders SET paid_date = CURRENT_DATE WHERE status = 'A' OR status = 'P';
	UPDATE orders SET paid_date = NULL WHERE status = 'C';
$$;

--test
CREATE OR REPLACE PROCEDURE get_stats(
	INOUT total int
)
LANGUAGE plpgsql
AS $$
BEGIN
	SELECT COUNT(*) INTO total FROM customers;
END;
$$;