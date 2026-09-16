CREATE TABLE IF NOT EXISTS public.users
(
    user_id integer NOT NULL GENERATED ALWAYS AS IDENTITY ( INCREMENT 1 START 1 MINVALUE 1 MAXVALUE 2147483647 CACHE 1 ),
    username text COLLATE pg_catalog."default" NOT NULL,
    passphrase text COLLATE pg_catalog."default" NOT NULL,
    user_role text COLLATE pg_catalog."default" NOT NULL,
    CONSTRAINT users_pkey PRIMARY KEY (user_id),
    CONSTRAINT users_user_role_check CHECK (user_role = ANY (ARRAY['Manager'::text, 'Customer'::text, 'Staff'::text]))
);
CREATE TABLE IF NOT EXISTS public.orders
(
    order_id integer NOT NULL GENERATED ALWAYS AS IDENTITY ( INCREMENT 1 START 1 MINVALUE 1 MAXVALUE 2147483647 CACHE 1 ),
    customer_id integer NOT NULL,
    order_date date NOT NULL,
    ship_date date NOT NULL,
    paid_date date,
    status character(1) COLLATE pg_catalog."default" NOT NULL,
    CONSTRAINT orders_pkey PRIMARY KEY (order_id),
    CONSTRAINT orders_customer_id_fkey FOREIGN KEY (customer_id)
        REFERENCES public.users (user_id) MATCH SIMPLE
        ON UPDATE NO ACTION
        ON DELETE NO ACTION,
    CONSTRAINT order_date_check CHECK (order_date <= ship_date),
    CONSTRAINT paid_date_check CHECK (order_date <= paid_date),
    CONSTRAINT status_check CHECK (status = 'A'::bpchar OR status = 'P'::bpchar OR status = 'C'::bpchar)
);
CREATE TABLE IF NOT EXISTS public.order_content
(
    order_content_id integer NOT NULL GENERATED ALWAYS AS IDENTITY ( INCREMENT 1 START 1 MINVALUE 1 MAXVALUE 2147483647 CACHE 1 ),
    order_id integer NOT NULL,
    product_model text COLLATE pg_catalog."default" NOT NULL,
    quantity integer NOT NULL,
    CONSTRAINT order_content_pkey PRIMARY KEY (order_content_id),
    CONSTRAINT fk_product_model FOREIGN KEY (product_model)
        REFERENCES public.products (model) MATCH SIMPLE
        ON UPDATE NO ACTION
        ON DELETE NO ACTION,
    CONSTRAINT order_content_order_id_fkey FOREIGN KEY (order_id)
        REFERENCES public.orders (order_id) MATCH SIMPLE
        ON UPDATE NO ACTION
        ON DELETE NO ACTION,
    CONSTRAINT positive_quantity CHECK (quantity > 0)
);
CREATE TABLE IF NOT EXISTS public.products
(
    model text COLLATE pg_catalog."default" NOT NULL,
    product_type text COLLATE pg_catalog."default" NOT NULL,
    vendor text COLLATE pg_catalog."default" NOT NULL,
    price numeric,
    in_stock integer,
    is_available boolean DEFAULT true,
    CONSTRAINT products_pkey PRIMARY KEY (model),
    CONSTRAINT in_stock_positive CHECK (in_stock > 0)
);
CREATE TABLE IF NOT EXISTS public.pc
(
    ps_id integer NOT NULL GENERATED ALWAYS AS IDENTITY ( INCREMENT 1 START 1 MINVALUE 1 MAXVALUE 2147483647 CACHE 1 ),
    model text COLLATE pg_catalog."default" NOT NULL,
    processor text COLLATE pg_catalog."default" NOT NULL,
    ram text COLLATE pg_catalog."default" NOT NULL,
    CONSTRAINT pc_pkey PRIMARY KEY (ps_id),
    CONSTRAINT pc_model_fkey FOREIGN KEY (model)
        REFERENCES public.products (model) MATCH SIMPLE
        ON UPDATE NO ACTION
        ON DELETE NO ACTION
);
CREATE TABLE IF NOT EXISTS public.laptop
(
    laptop_id integer NOT NULL GENERATED ALWAYS AS IDENTITY ( INCREMENT 1 START 1 MINVALUE 1 MAXVALUE 2147483647 CACHE 1 ),
    model text COLLATE pg_catalog."default" NOT NULL,
    processor text COLLATE pg_catalog."default" NOT NULL,
    ram text COLLATE pg_catalog."default" NOT NULL,
    CONSTRAINT laptop_pkey PRIMARY KEY (laptop_id),
    CONSTRAINT laptop_model_fkey FOREIGN KEY (model)
        REFERENCES public.products (model) MATCH SIMPLE
        ON UPDATE NO ACTION
        ON DELETE NO ACTION
);
CREATE TABLE IF NOT EXISTS public.printer
(
    printer_id integer NOT NULL GENERATED ALWAYS AS IDENTITY ( INCREMENT 1 START 1 MINVALUE 1 MAXVALUE 2147483647 CACHE 1 ),
    model text COLLATE pg_catalog."default" NOT NULL,
    printer_type text COLLATE pg_catalog."default" NOT NULL,
    CONSTRAINT printer_pkey PRIMARY KEY (printer_id),
    CONSTRAINT printer_model_fkey FOREIGN KEY (model)
        REFERENCES public.products (model) MATCH SIMPLE
        ON UPDATE NO ACTION
        ON DELETE NO ACTION
);
CREATE TABLE IF NOT EXISTS public.router
(
    router_id integer NOT NULL GENERATED ALWAYS AS IDENTITY ( INCREMENT 1 START 1 MINVALUE 1 MAXVALUE 2147483647 CACHE 1 ),
    model text COLLATE pg_catalog."default" NOT NULL,
    frequency real NOT NULL,
    bandwidth real NOT NULL,
    CONSTRAINT router_pkey PRIMARY KEY (router_id),
    CONSTRAINT router_model_fkey FOREIGN KEY (model)
        REFERENCES public.products (model) MATCH SIMPLE
        ON UPDATE NO ACTION
        ON DELETE NO ACTION
);