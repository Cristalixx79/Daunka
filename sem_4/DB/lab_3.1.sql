CREATE ROLE "read_only_role";
CREATE ROLE "read_write_role";

GRANT SELECT ON TABLE customers TO read_only_role;
GRANT SELECT, INSERT, UPDATE, DELETE ON TABLE customers TO read_write_role;

GRANT read_only_role TO user1;
REVOKE read_only_role FROM user1;
GRANT read_write_role TO user1;
REVOKE read_write_role FROM user1;

CREATE ROLE "create_table_role";
CREATE ROLE "create_no_table_role";

GRANT USAGE ON SCHEMA public TO create_table_role;
REVOKE ALL PRIVILEGES ON SCHEMA public FROM create_no_table_role;

GRANT create_table_role TO creator_user;
REVOKE create_table_role FROM creator_user;
GRANT create_no_table_role TO readonly_user;
REVOKE create_no_table_role FROM readonly_user;

