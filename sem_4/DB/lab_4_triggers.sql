CREATE TABLE IF NOT EXISTS logs(
	log_id INT PRIMARY KEY GENERATED ALWAYS AS IDENTITY,
	table_title TEXT NOT NULL,
	operation TEXT NOT NULL,
	log_timestamp TIMESTAMP DEFAULT NOW(),
	username text DEFAULT CURRENT_USER
);

--3
CREATE OR REPLACE FUNCTION test_insert_trigger()
RETURNS trigger
LANGUAGE plpgsql
AS $$
BEGIN
	INSERT INTO logs(table_title, operation) VALUES ('orders', 'INSERT');
	RETURN NEW;
END;
$$;

CREATE OR REPLACE TRIGGER test_trigger_insert AFTER INSERT ON orders
FOR EACH ROW EXECUTE FUNCTION test_insert_trigger();

--DROP TRIGGER IF EXISTS test_trigger_insert ON products;

--4
CREATE OR REPLACE FUNCTION test_update_trigger()
RETURNS trigger
LANGUAGE plpgsql 
AS $$
BEGIN
	INSERT INTO logs(table_title, operation) VALUES ('orders', 'UPDATE');
	RETURN NEW;
END;
$$;

CREATE OR REPLACE TRIGGER test_trigger_update AFTER UPDATE ON orders
EXECUTE FUNCTION test_update_trigger();

--DROP TRIGGER IF EXISTS test_trigger_update ON orders;

--5/6
CREATE OR REPLACE FUNCTION test_delete_trigger()
RETURNS trigger
LANGUAGE plpgsql 
AS $$
BEGIN
	INSERT INTO logs(table_title, operation) VALUES ('products', 'DELETE');
	DELETE FROM items WHERE items.product_id = OLD.product_id;
	RETURN OLD;
END;
$$;

CREATE OR REPLACE TRIGGER test_trigger_delete BEFORE DELETE ON products
FOR EACH ROW EXECUTE FUNCTION test_delete_trigger();

--DROP TRIGGER IF EXISTS test_trigger_delete ON products;

--8
CREATE OR REPLACE FUNCTION block_ddl_on_tables()
RETURNS event_trigger
LANGUAGE plpgsql
AS $$
DECLARE
    obj record;
BEGIN
    IF TG_EVENT = 'sql_drop' THEN
        FOR obj IN SELECT * FROM pg_event_trigger_dropped_objects() LOOP
            IF obj.object_type = 'table' THEN
                RAISE EXCEPTION 'DROPPING TABLES IS FORBIDDEN! Table "%" cannot be dropped.', obj.object_identity;
            END IF;
        END LOOP;
    END IF;
    
    IF TG_EVENT = 'ddl_command_end' THEN
        IF (SELECT command_tag FROM pg_event_trigger_ddl_commands()) = 'ALTER TABLE' THEN
            RAISE EXCEPTION 'ALTERING TABLES IS FORBIDDEN! Use ALTER permission is revoked.';
        END IF;
    END IF;
END;
$$;

CREATE EVENT TRIGGER block_drop_tables ON sql_drop EXECUTE FUNCTION block_ddl_on_tables();

CREATE EVENT TRIGGER block_alter_tables ON ddl_command_end WHEN TAG IN ('ALTER TABLE')
EXECUTE FUNCTION block_ddl_on_tables();

-- DROP EVENT TRIGGER IF EXISTS block_drop_tables;
-- DROP EVENT TRIGGER IF EXISTS block_alter_tables;