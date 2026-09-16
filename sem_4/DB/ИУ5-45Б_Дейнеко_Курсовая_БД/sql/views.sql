CREATE OR REPLACE VIEW public.v_least_sold_items
 AS
 SELECT order_content.product_model,
    sum(order_content.quantity) AS orders_with_model
   FROM order_content
  GROUP BY order_content.product_model
  ORDER BY (sum(order_content.quantity));

CREATE OR REPLACE VIEW public.v_most_active_clients
 AS
 SELECT users.username,
    count(*) AS user_orders_count
   FROM users
     JOIN orders o ON o.customer_id = users.user_id
  GROUP BY users.username
  ORDER BY (count(*)) DESC;

CREATE OR REPLACE VIEW public.v_most_inactive_clients
 AS
 SELECT users.username,
    count(*) AS user_orders_count
   FROM users
     JOIN orders o ON o.customer_id = users.user_id
  GROUP BY users.username
  ORDER BY (count(*));

CREATE OR REPLACE VIEW public.v_most_sold_items
 AS
 SELECT order_content.product_model,
    sum(order_content.quantity) AS orders_with_model
   FROM order_content
  GROUP BY order_content.product_model
  ORDER BY (sum(order_content.quantity)) DESC;

CREATE OR REPLACE VIEW public.v_most_sold_products
 AS
 SELECT pr.product_type,
    sum(order_content.quantity) AS orders_with_product_type
   FROM order_content
     JOIN products pr ON pr.model = order_content.product_model
  GROUP BY pr.product_type
  ORDER BY (sum(order_content.quantity)) DESC;