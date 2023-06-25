# SQL

## SQLBolt tutorial

Variants include SQLite, MySQL, Postgres, Oracle, and Microsoft SQL Server

Relational databases are 2D tables

SELECT statements are queries
  * `SELECT col1, col2 FROM table;`
  * Wildcard `*` gets all columns. Useful for previewing table

WHERE filters down rows
  * `SELECT col1, col2 FROM table WHERE cond1 AND cond2 OR cond3;`
  * Conditions can include `<, >, =, <=, >=, !=`, BETWEEN...AND, NOT, IN (a,b,c)

String filters include:
  * `=, !=`, which is exact and case-sensitive
  * (NOT) LIKE, which is case-insensitive
  * `%` matches 0 or more characters (like `.*`)
  * `_` matches any single character (like `*`)
  * (NOT) IN ("A", "B",...)
  * Full text search is more efficient in Apache Lucene or Sphinx

DISTINCT col1 discards rows with duplicate column value(s)
  * Does so blindly. Better to use GROUP BY

ORDER BY col1 ASC/DESC sorts the data

LIMIT num reduces number of rows to return. OFFSET num specifies where to begin
printing
  * Generally applied last

Normalization spreads data across many orthogonal tables
  * Prevents duplicate data and allows scalable growth, at cost of more complex
    queries

JOIN combines row data from two tables using a primary key (index, e.g.)
  * INNER JOIN table2 ON id1 = id2 keeps only data with keys in both tables
  * LEFT/RIGHT/FULL JOIN keeps extra data, and will introduce NULL values

Check for NULL with `WHERE col1 IS (NOT) NULL`

Mathematical and aggregate functions can be applied to datai
  * See database docs for details
  * Use alias `SELECT f(col1) AS name1`
  * Can also alias table names
  * Aggregate functions: `COUNT(col1)` (counts non-null), `COUNT(*)` (counts
    rows), `MIN(col1)`, `MAX(col1)`, `AVG(col1)`, `SUM(col1)`

GROUP BY col1 applies aggregate function to each group rather than entire result
  * Goes after WHERE statement
  * Use HAVING to filter out groups

Execution order: FROM/JOIN, WHERE, GROUP BY, HAVING, SELECT, DISTINCT, ORDER
BY, LIMIT/OFFSET

```
SELECT DISTINCT column, AGG_FUNC(column_or_expression), …
FROM mytable
    JOIN another_table
      ON mytable_column = another_table_column
    WHERE constraint_expression
    GROUP BY column
    HAVING constraint_expression
    ORDER BY column ASC/DESC
    LIMIT count OFFSET COUNT;
```

Schema = data types of each column

INSERT INTO table1 VALUES (val1, val2, ...), (val1, val2, ...)
  * Can specify few columns: INSERT INTO table1 (col1, col2 ) VALUES (val1,
    val2), (val1, val2)

UPDATE table1 SET col1 = val1, col2 = val2, ... WHERE cond1
  * Tip: test condition with SELECT to make sure you have the right rows

DELETE FROM table1 WHERE cond1
  * No WHERE clause would wipe entire table

CREATE TABLE IF NOT EXISTS table1 (col1 type1 constraint1 DEFAULT default1, ...)
  * Column constraint and default are optional
  * Types: INTEGER, BOOLEAN, FLOAT, DOUBLE, REAL, CHARACTER(num), VARCHAR(num),
    TEXT, DATE, DATETIME, BLOB (normally needs metadata)
  * Constraints: PRIMARY KEY (values in this column are unique), AUTOINCREMENT,
    UNIQUE (similar to primary key), NOT NULL, CHECK(expr1), FOREIGN KEY (check
    if this val has match in other table)

ALTER TABLE table1 ADD col1 type1 constraint1 DEFAULT default1
  * MySQL allows specifying where to insert column with FIRST and AFTER clauses

ALTER TABLE table1 DROP col1
  * Some databases like SQLite don't support DROP. Need to create copy and
    migrate data manually

ALTER TABLE table1 RENAME TO table2

DROP TABLE IF EXISTS table1 removes table data and schema
  * Should remove dependent rows/tables, e.g. with FOREIGN KEY dependency

Subqueries gather data for comparison
  * E.g., ... WHERE salary > (SELECT AVG(revenue) FROM table)

Correlated subqueries depend on outer query
```
SELECT *
FROM employees
WHERE salary > 
   (SELECT AVG(revenue_generated)
    FROM employees AS dept_employees
    WHERE dept_employees.department = employees.department);
```

Can have subquery act as dynamic list for WHERE col1 IN list1

UNION appends similar queries. UNION ALL keeps duplicate rows
  * Happens before ORDER BY
  * INTERSECT takes intersection of queries
  * EXCEPT takes rows in first but not second query
  * Some databases support INTERSECT/EXCEPT ALL, which keeps duplicate rows

