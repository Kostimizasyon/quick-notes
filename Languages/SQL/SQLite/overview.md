# SQLite

## SYNTAX

```sql
CREATE TABLE users(

    id INTEGER PRIMARY KEY, // PRIMARY DEF
    foreign_key INTEGER,

    CONSTRAINT fk_fk
        FOREIGN KEY(foreign_key)
        REFERENCES other_table(id)
);
```
