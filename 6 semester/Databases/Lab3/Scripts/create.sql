DROP TABLE IF EXISTS main_scheme.student CASCADE;
DROP TABLE IF EXISTS main_scheme.employee CASCADE;
DROP TABLE IF EXISTS main_scheme.residential_address CASCADE;
DROP TABLE IF EXISTS main_scheme.job_position CASCADE;
DROP TABLE IF EXISTS main_scheme.gradebook CASCADE;
DROP TABLE IF EXISTS main_scheme.class CASCADE;
DROP TABLE IF EXISTS main_scheme.schedule CASCADE;
DROP TABLE IF EXISTS main_scheme.subject CASCADE;
DROP TABLE IF EXISTS main_scheme.employee_position CASCADE;
DROP TABLE IF EXISTS main_scheme.knowledge_of_subject CASCADE;


CREATE TABLE IF NOT EXISTS main_scheme.student
(
    id 						SERIAL PRIMARY KEY,
    first_name 				CHARACTER VARYING(100) NOT NULL,
    last_name 				CHARACTER VARYING(100) NOT NULL,
    middle_name 			CHARACTER VARYING(100) NOT NULL,
    passport_id 			CHARACTER(14) UNIQUE NOT NULL,
    date_of_birth 			DATE NOT NULL,
    class_id 				BIGINT NOT NULL,
    residential_address_id 	BIGINT NOT NULL
);

CREATE TABLE IF NOT EXISTS main_scheme.class
(
    id 				SERIAL PRIMARY KEY,
    class_number 	INTEGER NOT NULL,
    class_letter 	CHAR NOT NULL,
    student_count 	INTEGER NOT NULL
);

CREATE TABLE IF NOT EXISTS main_scheme.subject
(
    id 			SERIAL PRIMARY KEY,
    name 		CHARACTER VARYING(100) NOT NULL,
    hours 		INTEGER DEFAULT(0) CHECK(hours >= 0),
    classroom 	INTEGER NOT NULL
);

CREATE TABLE IF NOT EXISTS main_scheme.residential_address
(
    id 				SERIAL PRIMARY KEY,
    city 			CHARACTER VARYING(100) NOT NULL,
    street 			CHARACTER VARYING(100) NOT NULL,
    house_number 	INTEGER CHECK(house_number >= 1)
);

CREATE TABLE IF NOT EXISTS main_scheme.job_position
(
	id 		SERIAL PRIMARY KEY,
    name 	CHARACTER VARYING(100) NOT NULL,
    rate 	REAL CHECK(rate >= 0) NOT NULL,
    salary 	MONEY NOT NULL
);

CREATE TABLE IF NOT EXISTS main_scheme.schedule
(
	id 			SERIAL PRIMARY KEY,
	week_day	CHARACTER VARYING(20) NOT NULL,
    class_id	BIGINT NOT NULL,
    subject_id 	BIGINT NOT NULL
);

CREATE TABLE IF NOT EXISTS main_scheme.employee
(
    id 						SERIAL PRIMARY KEY,
    first_name 				CHARACTER VARYING(100) NOT NULL,
    last_name 				CHARACTER VARYING(100) NOT NULL,
    middle_name 			CHARACTER VARYING(100) NOT NULL,
    passport_id 			CHARACTER(14) UNIQUE NOT NULL,
    date_of_birth 			DATE NOT NULL,
    residential_address_id 	BIGINT NOT NULL
);

CREATE TABLE IF NOT EXISTS main_scheme.knowledge_of_subject
(
    employee_id BIGINT PRIMARY KEY,
    subject_id 	BIGINT NOT NULL
);

CREATE TABLE IF NOT EXISTS main_scheme.employee_position
(
	employee_id 	BIGINT PRIMARY KEY,
    job_position_id BIGINT NOT NULL
);

CREATE TABLE IF NOT EXISTS main_scheme.gradebook
(
    id 			SERIAL PRIMARY KEY,
    employee_id BIGINT NOT NULL,
    student_id 	BIGINT NOT NULL,
    subject_id 	BIGINT NOT NULL,
    grade_date 	DATE NOT NULL,
    grade 		SMALLINT NOT NULL
);

ALTER TABLE IF EXISTS main_scheme.student
    ADD CONSTRAINT fk_class
		FOREIGN KEY (class_id)
    		REFERENCES main_scheme.class (id)
    			ON DELETE CASCADE;


ALTER TABLE IF EXISTS main_scheme.student
	ADD CONSTRAINT fk_student_residential_address
    	FOREIGN KEY (residential_address_id)
    		REFERENCES main_scheme.residential_address (id)
    			ON DELETE CASCADE;


ALTER TABLE IF EXISTS main_scheme.schedule
    ADD CONSTRAINT fk_schedule 
		FOREIGN KEY (class_id)
    		REFERENCES main_scheme.class (id)
    			ON DELETE CASCADE;


ALTER TABLE IF EXISTS main_scheme.schedule
    ADD CONSTRAINT fk_subject
		FOREIGN KEY (subject_id)
    		REFERENCES main_scheme.subject (id)
    			ON DELETE CASCADE;


ALTER TABLE IF EXISTS main_scheme.employee
    ADD CONSTRAINT fk_employee_residential_address
		FOREIGN KEY (residential_address_id)
    		REFERENCES main_scheme.residential_address (id)
    			ON DELETE CASCADE;


ALTER TABLE IF EXISTS main_scheme.knowledge_of_subject
    ADD CONSTRAINT fk_subject
		FOREIGN KEY (subject_id)
    		REFERENCES main_scheme.subject (id)
    			ON DELETE CASCADE;


ALTER TABLE IF EXISTS main_scheme.knowledge_of_subject
    ADD CONSTRAINT fk_employee 
		FOREIGN KEY (employee_id)
    		REFERENCES main_scheme.employee (id)
    			ON DELETE CASCADE;


ALTER TABLE IF EXISTS main_scheme.employee_position
    ADD CONSTRAINT fk_employee
		FOREIGN KEY (employee_id)
    		REFERENCES main_scheme.employee (id)
    			ON DELETE CASCADE;


ALTER TABLE IF EXISTS main_scheme.employee_position
    ADD CONSTRAINT fk_job_position 
		FOREIGN KEY (job_position_id)
    		REFERENCES main_scheme.job_position (id)
    			ON DELETE CASCADE;
				

ALTER TABLE IF EXISTS main_scheme.gradebook
	ADD CONSTRAINT fk_subject
    	FOREIGN KEY (subject_id)
    		REFERENCES main_scheme.subject (id)
    			ON DELETE CASCADE;


ALTER TABLE IF EXISTS main_scheme.gradebook
    ADD CONSTRAINT fk_employee
		FOREIGN KEY (employee_id)
    		REFERENCES main_scheme.employee (id)
    			ON DELETE CASCADE;


ALTER TABLE IF EXISTS main_scheme.gradebook
	ADD CONSTRAINT fk_student
		FOREIGN KEY (student_id)
    		REFERENCES main_scheme.student (id)
    			ON DELETE CASCADE;


COMMENT ON COLUMN main_scheme.gradebook.grade IS 'Возможные значения: от 1 до 10';
