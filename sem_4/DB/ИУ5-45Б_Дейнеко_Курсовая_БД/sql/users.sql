CREATE ROLE customer;
CREATE ROLE manager;
GRANT CONNECT ON DATABASE "AIS" TO customer, manager;
GRANT USAGE ON SCHEMA public TO customer, manager;

--customer
GRANT SELECT ON TABLE public.orders, public.order_content, public.products,
  public.pc, public.laptop, public.printer, public.router TO customer;
GRANT INSERT ON TABLE public.orders, public.order_content TO customer;
GRANT UPDATE ON TABLE public.orders, public.order_content, public.products TO customer;

--manager
GRANT ALL PRIVILEGES ON SCHEMA public TO manager WITH GRANT OPTION;
GRANT ALL PRIVILEGES ON ALL TABLES IN SCHEMA public TO manager WITH GRANT OPTION;
GRANT ALL PRIVILEGES ON ALL SEQUENCES IN SCHEMA public TO manager WITH GRANT OPTION;
GRANT ALL PRIVILEGES ON ALL FUNCTIONS IN SCHEMA public TO manager WITH GRANT OPTION;
GRANT SELECT ON TABLE public.v_least_sold_items TO manager;
GRANT SELECT ON TABLE public.v_most_active_clients TO manager;
GRANT SELECT ON TABLE public.v_most_inactive_clients TO manager;
GRANT SELECT ON TABLE public.v_most_sold_items TO manager;
GRANT SELECT ON TABLE public.v_most_sold_products TO manager;
GRANT CREATE ON SCHEMA public TO manager;
GRANT CREATE ON DATABASE "AIS" TO manager;

--creation
CREATE USER ais_manager WITH PASSWORD 'manager';
GRANT manager TO ais_manager;

CREATE USER ais_customer WITH PASSWORD 'cust';
GRANT customer TO ais_customer;
