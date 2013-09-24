Joshua Kruger
Harrison Kurtz
Josh Amaku
---------------
How to run:
1. g++ *.h *.cpp -o Interface
2. ./Interface
---------------
Some test commands to try:

CREATE TABLE animals (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind);

INSERT INTO animals VALUES FROM ("Joe", "cat", 4);
INSERT INTO animals VALUES FROM ("Spot", "dog", 10);
INSERT INTO animals VALUES FROM ("Snoopy", "dog", 3);
INSERT INTO animals VALUES FROM ("Tweety", "bird", 1);

SHOW animals;

dogs <- select (kind == "dog") animals;


CREATE TABLE species (kind VARCHAR(10)) PRIMARY KEY (kind);
INSERT INTO species VALUES FROM RELATION project (kind) animals;
a <- rename (aname, akind) (project (name, kind) animals);
answer <- common_names;

WRITE animals;
EXIT;

--------------


