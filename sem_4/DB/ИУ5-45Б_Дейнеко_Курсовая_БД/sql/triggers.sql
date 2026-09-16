CREATE OR REPLACE FUNCTION public.calculate_new_quantity()
    RETURNS trigger
    LANGUAGE 'plpgsql'
    COST 100
    VOLATILE NOT LEAKPROOF
AS $BODY$
DECLARE
  in_stock_quantity INT := 0;
BEGIN
  SELECT products.in_stock INTO in_stock_quantity FROM products WHERE products.model = NEW.product_model;
  IF NEW.quantity > in_stock_quantity THEN
    RAISE EXCEPTION 'Error %', in_stock_quantity;
  ELSE
    UPDATE products SET in_stock = in_stock - NEW.quantity WHERE products.model = NEW.product_model;
    RETURN NEW;
  END IF;
END;
$BODY$;

CREATE TRIGGER calculate_new_quantity_trigger
    BEFORE INSERT
    ON public.order_content
    FOR EACH ROW
    EXECUTE FUNCTION public.calculate_new_quantity();

CREATE OR REPLACE FUNCTION public.delete_product_laptop()
    RETURNS trigger
    LANGUAGE 'plpgsql'
    COST 100
    VOLATILE NOT LEAKPROOF
AS $BODY$
BEGIN
	DELETE FROM products WHERE products.model = OLD.model;
	RETURN OLD;
END;
$BODY$;

CREATE TRIGGER delete_product_laptop_trigger
    AFTER DELETE
    ON public.laptop
    FOR EACH ROW
    EXECUTE FUNCTION public.delete_product_laptop();

CREATE OR REPLACE FUNCTION public.delete_product_pc()
    RETURNS trigger
    LANGUAGE 'plpgsql'
    COST 100
    VOLATILE NOT LEAKPROOF
AS $BODY$
BEGIN
	DELETE FROM products WHERE products.model = OLD.model;
	RETURN OLD;
END;
$BODY$;

CREATE TRIGGER delete_product_pc_trigger
    AFTER DELETE
    ON public.pc
    FOR EACH ROW
    EXECUTE FUNCTION public.delete_product_pc();

CREATE OR REPLACE FUNCTION public.delete_product_printer()
    RETURNS trigger
    LANGUAGE 'plpgsql'
    COST 100
    VOLATILE NOT LEAKPROOF
AS $BODY$
BEGIN
	DELETE FROM products WHERE products.model = OLD.model;
	RETURN OLD;
END;
$BODY$;

CREATE TRIGGER delete_product_printer_trigger
    AFTER DELETE
    ON public.printer
    FOR EACH ROW
    EXECUTE FUNCTION public.delete_product_printer();

CREATE OR REPLACE FUNCTION public.delete_product_router()
    RETURNS trigger
    LANGUAGE 'plpgsql'
    COST 100
    VOLATILE NOT LEAKPROOF
AS $BODY$
BEGIN
	DELETE FROM products WHERE products.model = OLD.model;
	RETURN OLD;
END;
$BODY$;

CREATE TRIGGER delete_product_router_trigger
    AFTER DELETE
    ON public.router
    FOR EACH ROW
    EXECUTE FUNCTION public.delete_product_router();