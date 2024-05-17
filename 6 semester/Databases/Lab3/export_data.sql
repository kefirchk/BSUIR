--
-- PostgreSQL database dump
--

-- Dumped from database version 16.1
-- Dumped by pg_dump version 16.1

-- Started on 2024-03-01 14:08:32

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

--
-- TOC entry 4892 (class 1262 OID 16398)
-- Name: school; Type: DATABASE; Schema: -; Owner: postgres
--

CREATE DATABASE school WITH TEMPLATE = template0 ENCODING = 'UTF8' LOCALE_PROVIDER = libc LOCALE = 'Russian_Russia.1251';


ALTER DATABASE school OWNER TO postgres;

\connect school

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

--
-- TOC entry 6 (class 2615 OID 18277)
-- Name: main_scheme; Type: SCHEMA; Schema: -; Owner: postgres
--

CREATE SCHEMA main_scheme;


ALTER SCHEMA main_scheme OWNER TO postgres;

SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- TOC entry 219 (class 1259 OID 18288)
-- Name: class; Type: TABLE; Schema: main_scheme; Owner: postgres
--

CREATE TABLE main_scheme.class (
    id integer NOT NULL,
    class_number integer NOT NULL,
    class_letter character(1) NOT NULL,
    student_count integer NOT NULL
);


ALTER TABLE main_scheme.class OWNER TO postgres;

--
-- TOC entry 218 (class 1259 OID 18287)
-- Name: class_id_seq; Type: SEQUENCE; Schema: main_scheme; Owner: postgres
--

CREATE SEQUENCE main_scheme.class_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE main_scheme.class_id_seq OWNER TO postgres;

--
-- TOC entry 4893 (class 0 OID 0)
-- Dependencies: 218
-- Name: class_id_seq; Type: SEQUENCE OWNED BY; Schema: main_scheme; Owner: postgres
--

ALTER SEQUENCE main_scheme.class_id_seq OWNED BY main_scheme.class.id;


--
-- TOC entry 229 (class 1259 OID 18327)
-- Name: employee; Type: TABLE; Schema: main_scheme; Owner: postgres
--

CREATE TABLE main_scheme.employee (
    id integer NOT NULL,
    first_name character varying(100) NOT NULL,
    last_name character varying(100) NOT NULL,
    middle_name character varying(100) NOT NULL,
    passport_id character(14) NOT NULL,
    date_of_birth date NOT NULL,
    residential_address_id bigint NOT NULL
);


ALTER TABLE main_scheme.employee OWNER TO postgres;

--
-- TOC entry 228 (class 1259 OID 18326)
-- Name: employee_id_seq; Type: SEQUENCE; Schema: main_scheme; Owner: postgres
--

CREATE SEQUENCE main_scheme.employee_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE main_scheme.employee_id_seq OWNER TO postgres;

--
-- TOC entry 4894 (class 0 OID 0)
-- Dependencies: 228
-- Name: employee_id_seq; Type: SEQUENCE OWNED BY; Schema: main_scheme; Owner: postgres
--

ALTER SEQUENCE main_scheme.employee_id_seq OWNED BY main_scheme.employee.id;


--
-- TOC entry 231 (class 1259 OID 18340)
-- Name: employee_position; Type: TABLE; Schema: main_scheme; Owner: postgres
--

CREATE TABLE main_scheme.employee_position (
    employee_id bigint NOT NULL,
    job_position_id bigint NOT NULL
);


ALTER TABLE main_scheme.employee_position OWNER TO postgres;

--
-- TOC entry 233 (class 1259 OID 18346)
-- Name: gradebook; Type: TABLE; Schema: main_scheme; Owner: postgres
--

CREATE TABLE main_scheme.gradebook (
    id integer NOT NULL,
    employee_id bigint NOT NULL,
    student_id bigint NOT NULL,
    subject_id bigint NOT NULL,
    grade_date date NOT NULL,
    grade smallint NOT NULL
);


ALTER TABLE main_scheme.gradebook OWNER TO postgres;

--
-- TOC entry 4895 (class 0 OID 0)
-- Dependencies: 233
-- Name: COLUMN gradebook.grade; Type: COMMENT; Schema: main_scheme; Owner: postgres
--

COMMENT ON COLUMN main_scheme.gradebook.grade IS 'Возможные значения: от 1 до 10';


--
-- TOC entry 232 (class 1259 OID 18345)
-- Name: gradebook_id_seq; Type: SEQUENCE; Schema: main_scheme; Owner: postgres
--

CREATE SEQUENCE main_scheme.gradebook_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE main_scheme.gradebook_id_seq OWNER TO postgres;

--
-- TOC entry 4896 (class 0 OID 0)
-- Dependencies: 232
-- Name: gradebook_id_seq; Type: SEQUENCE OWNED BY; Schema: main_scheme; Owner: postgres
--

ALTER SEQUENCE main_scheme.gradebook_id_seq OWNED BY main_scheme.gradebook.id;


--
-- TOC entry 225 (class 1259 OID 18312)
-- Name: job_position; Type: TABLE; Schema: main_scheme; Owner: postgres
--

CREATE TABLE main_scheme.job_position (
    id integer NOT NULL,
    name character varying(100) NOT NULL,
    rate real NOT NULL,
    salary money NOT NULL,
    CONSTRAINT job_position_rate_check CHECK ((rate >= (0)::double precision))
);


ALTER TABLE main_scheme.job_position OWNER TO postgres;

--
-- TOC entry 224 (class 1259 OID 18311)
-- Name: job_position_id_seq; Type: SEQUENCE; Schema: main_scheme; Owner: postgres
--

CREATE SEQUENCE main_scheme.job_position_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE main_scheme.job_position_id_seq OWNER TO postgres;

--
-- TOC entry 4897 (class 0 OID 0)
-- Dependencies: 224
-- Name: job_position_id_seq; Type: SEQUENCE OWNED BY; Schema: main_scheme; Owner: postgres
--

ALTER SEQUENCE main_scheme.job_position_id_seq OWNED BY main_scheme.job_position.id;


--
-- TOC entry 230 (class 1259 OID 18335)
-- Name: knowledge_of_subject; Type: TABLE; Schema: main_scheme; Owner: postgres
--

CREATE TABLE main_scheme.knowledge_of_subject (
    employee_id bigint NOT NULL,
    subject_id bigint NOT NULL
);


ALTER TABLE main_scheme.knowledge_of_subject OWNER TO postgres;

--
-- TOC entry 223 (class 1259 OID 18304)
-- Name: residential_address; Type: TABLE; Schema: main_scheme; Owner: postgres
--

CREATE TABLE main_scheme.residential_address (
    id integer NOT NULL,
    city character varying(100) NOT NULL,
    street character varying(100) NOT NULL,
    house_number integer,
    CONSTRAINT residential_address_house_number_check CHECK ((house_number >= 1))
);


ALTER TABLE main_scheme.residential_address OWNER TO postgres;

--
-- TOC entry 222 (class 1259 OID 18303)
-- Name: residential_address_id_seq; Type: SEQUENCE; Schema: main_scheme; Owner: postgres
--

CREATE SEQUENCE main_scheme.residential_address_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE main_scheme.residential_address_id_seq OWNER TO postgres;

--
-- TOC entry 4898 (class 0 OID 0)
-- Dependencies: 222
-- Name: residential_address_id_seq; Type: SEQUENCE OWNED BY; Schema: main_scheme; Owner: postgres
--

ALTER SEQUENCE main_scheme.residential_address_id_seq OWNED BY main_scheme.residential_address.id;


--
-- TOC entry 227 (class 1259 OID 18320)
-- Name: schedule; Type: TABLE; Schema: main_scheme; Owner: postgres
--

CREATE TABLE main_scheme.schedule (
    id integer NOT NULL,
    class_id bigint NOT NULL,
    subject_id bigint NOT NULL
);


ALTER TABLE main_scheme.schedule OWNER TO postgres;

--
-- TOC entry 226 (class 1259 OID 18319)
-- Name: schedule_id_seq; Type: SEQUENCE; Schema: main_scheme; Owner: postgres
--

CREATE SEQUENCE main_scheme.schedule_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE main_scheme.schedule_id_seq OWNER TO postgres;

--
-- TOC entry 4899 (class 0 OID 0)
-- Dependencies: 226
-- Name: schedule_id_seq; Type: SEQUENCE OWNED BY; Schema: main_scheme; Owner: postgres
--

ALTER SEQUENCE main_scheme.schedule_id_seq OWNED BY main_scheme.schedule.id;


--
-- TOC entry 217 (class 1259 OID 18279)
-- Name: student; Type: TABLE; Schema: main_scheme; Owner: postgres
--

CREATE TABLE main_scheme.student (
    id integer NOT NULL,
    first_name character varying(100) NOT NULL,
    last_name character varying(100) NOT NULL,
    patronymic character varying(100) NOT NULL,
    passport_id character(14) NOT NULL,
    date_of_birth date NOT NULL,
    class_id bigint NOT NULL,
    residential_address_id bigint NOT NULL
);


ALTER TABLE main_scheme.student OWNER TO postgres;

--
-- TOC entry 216 (class 1259 OID 18278)
-- Name: student_id_seq; Type: SEQUENCE; Schema: main_scheme; Owner: postgres
--

CREATE SEQUENCE main_scheme.student_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE main_scheme.student_id_seq OWNER TO postgres;

--
-- TOC entry 4900 (class 0 OID 0)
-- Dependencies: 216
-- Name: student_id_seq; Type: SEQUENCE OWNED BY; Schema: main_scheme; Owner: postgres
--

ALTER SEQUENCE main_scheme.student_id_seq OWNED BY main_scheme.student.id;


--
-- TOC entry 221 (class 1259 OID 18295)
-- Name: subject; Type: TABLE; Schema: main_scheme; Owner: postgres
--

CREATE TABLE main_scheme.subject (
    id integer NOT NULL,
    name character varying(100) NOT NULL,
    hours integer DEFAULT 0,
    classroom integer NOT NULL,
    CONSTRAINT subject_hours_check CHECK ((hours >= 0))
);


ALTER TABLE main_scheme.subject OWNER TO postgres;

--
-- TOC entry 220 (class 1259 OID 18294)
-- Name: subject_id_seq; Type: SEQUENCE; Schema: main_scheme; Owner: postgres
--

CREATE SEQUENCE main_scheme.subject_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE main_scheme.subject_id_seq OWNER TO postgres;

--
-- TOC entry 4901 (class 0 OID 0)
-- Dependencies: 220
-- Name: subject_id_seq; Type: SEQUENCE OWNED BY; Schema: main_scheme; Owner: postgres
--

ALTER SEQUENCE main_scheme.subject_id_seq OWNED BY main_scheme.subject.id;


--
-- TOC entry 4679 (class 2604 OID 18291)
-- Name: class id; Type: DEFAULT; Schema: main_scheme; Owner: postgres
--

ALTER TABLE ONLY main_scheme.class ALTER COLUMN id SET DEFAULT nextval('main_scheme.class_id_seq'::regclass);


--
-- TOC entry 4685 (class 2604 OID 18330)
-- Name: employee id; Type: DEFAULT; Schema: main_scheme; Owner: postgres
--

ALTER TABLE ONLY main_scheme.employee ALTER COLUMN id SET DEFAULT nextval('main_scheme.employee_id_seq'::regclass);


--
-- TOC entry 4686 (class 2604 OID 18349)
-- Name: gradebook id; Type: DEFAULT; Schema: main_scheme; Owner: postgres
--

ALTER TABLE ONLY main_scheme.gradebook ALTER COLUMN id SET DEFAULT nextval('main_scheme.gradebook_id_seq'::regclass);


--
-- TOC entry 4683 (class 2604 OID 18315)
-- Name: job_position id; Type: DEFAULT; Schema: main_scheme; Owner: postgres
--

ALTER TABLE ONLY main_scheme.job_position ALTER COLUMN id SET DEFAULT nextval('main_scheme.job_position_id_seq'::regclass);


--
-- TOC entry 4682 (class 2604 OID 18307)
-- Name: residential_address id; Type: DEFAULT; Schema: main_scheme; Owner: postgres
--

ALTER TABLE ONLY main_scheme.residential_address ALTER COLUMN id SET DEFAULT nextval('main_scheme.residential_address_id_seq'::regclass);


--
-- TOC entry 4684 (class 2604 OID 18323)
-- Name: schedule id; Type: DEFAULT; Schema: main_scheme; Owner: postgres
--

ALTER TABLE ONLY main_scheme.schedule ALTER COLUMN id SET DEFAULT nextval('main_scheme.schedule_id_seq'::regclass);


--
-- TOC entry 4678 (class 2604 OID 18282)
-- Name: student id; Type: DEFAULT; Schema: main_scheme; Owner: postgres
--

ALTER TABLE ONLY main_scheme.student ALTER COLUMN id SET DEFAULT nextval('main_scheme.student_id_seq'::regclass);


--
-- TOC entry 4680 (class 2604 OID 18298)
-- Name: subject id; Type: DEFAULT; Schema: main_scheme; Owner: postgres
--

ALTER TABLE ONLY main_scheme.subject ALTER COLUMN id SET DEFAULT nextval('main_scheme.subject_id_seq'::regclass);


--
-- TOC entry 4872 (class 0 OID 18288)
-- Dependencies: 219
-- Data for Name: class; Type: TABLE DATA; Schema: main_scheme; Owner: postgres
--

INSERT INTO main_scheme.class VALUES (1, 10, 'А', 24) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.class VALUES (2, 3, 'Б', 27) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.class VALUES (3, 8, 'В', 32) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.class VALUES (4, 4, 'Г', 28) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.class VALUES (5, 2, 'Д', 26) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.class VALUES (6, 6, 'Е', 30) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.class VALUES (7, 7, 'Ж', 31) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.class VALUES (8, 5, 'З', 29) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.class VALUES (9, 1, 'И', 25) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.class VALUES (10, 11, 'K', 25) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.class VALUES (11, 9, 'Л', 13) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.class VALUES (12, 10, 'М', 19) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.class VALUES (13, 1, 'Н', 18) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.class VALUES (14, 11, 'О', 26) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.class VALUES (15, 11, 'В', 25) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.class VALUES (16, 6, 'П', 14) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.class VALUES (17, 3, 'Р', 7) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.class VALUES (18, 2, 'С', 15) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.class VALUES (19, 8, 'Т', 13) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.class VALUES (20, 7, 'У', 14) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.class VALUES (21, 9, 'Ф', 14) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.class VALUES (22, 2, 'Х', 7) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.class VALUES (23, 2, 'Ш', 8) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.class VALUES (24, 2, 'Ц', 16) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.class VALUES (25, 4, 'Ч', 9) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.class VALUES (26, 6, 'Я', 11) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.class VALUES (27, 7, 'Э', 12) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.class VALUES (28, 5, 'Щ', 10) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.class VALUES (29, 3, 'Ы', 15) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.class VALUES (30, 9, 'А', 14) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.class VALUES (31, 10, 'Б', 14) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.class VALUES (32, 8, 'Б', 13) ON CONFLICT DO NOTHING;


--
-- TOC entry 4882 (class 0 OID 18327)
-- Dependencies: 229
-- Data for Name: employee; Type: TABLE DATA; Schema: main_scheme; Owner: postgres
--

INSERT INTO main_scheme.employee VALUES (1, 'Иван', 'Глецевич', 'Иванович', 'AB1234547CD89 ', '1978-05-15', 31) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee VALUES (2, 'Петр', 'Петров', 'Петрович', 'EF9876543UH21 ', '1998-02-15', 42) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee VALUES (3, 'Анна', 'Сидорова', 'Александровна', 'KL6567890MN32 ', '1989-08-20', 43) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee VALUES (4, 'Мария', 'Козлова', 'Игоревна', 'OP6543230QR54 ', '1971-07-25', 34) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee VALUES (5, 'Сергей', 'Васильев', 'Дмитриевич', 'ST0187654UV76 ', '1990-03-30', 35) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee VALUES (6, 'Елена', 'Никитина', 'Павловна', 'WX2345478YZ98 ', '1980-11-05', 36) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee VALUES (7, 'Алексей', 'Григорьев', 'Андреевич', 'CD4765432AB09 ', '1981-09-12', 37) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee VALUES (8, 'Ольга', 'Павлова', 'Сергеевна', 'EF2109376GH43 ', '1982-04-18', 38) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee VALUES (9, 'Дмитрий', 'Федоров', 'Владимирович', 'IK0987654KL76 ', '1982-12-23', 39) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee VALUES (10, 'Наталья', 'Иванова', 'Михайловна', 'MN5332109OP65 ', '1985-10-28', 31) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee VALUES (11, 'Ирина', 'Петрова', 'Алексеевна', 'QR7653321ST87 ', '1989-06-02', 41) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee VALUES (12, 'Андрей', 'Сидоров', 'Петрович', 'UV1098365WX32 ', '1975-01-07', 42) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee VALUES (13, 'Виктория', 'Смирнова', 'Анатольевна', 'ZZ8765432WX10 ', '2000-09-12', 33) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee VALUES (14, 'Артем', 'Кузнецов', 'Иванович', 'BC5432409DE87 ', '1999-07-17', 14) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee VALUES (15, 'Татьяна', 'Морозова', 'Алексеевна', 'FG4210987HI54 ', '1973-04-22', 25) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee VALUES (16, 'Григорий', 'Новиков', 'Петрович', 'JK1058765LM32 ', '1974-12-27', 16) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee VALUES (17, 'Василиса', 'Зайцева', 'Дмитриевна', 'NO5876543PQ21 ', '1987-10-02', 57) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee VALUES (18, 'Егор', 'Павлов', 'Сергеевич', 'RS7654320TU98 ', '1984-05-08', 58) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee VALUES (19, 'Людмила', 'Соколова', 'Игоревна', 'VW5442109XY76 ', '1966-01-13', 49) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee VALUES (20, 'Александра', 'Иванова', 'Александровна', 'AB2409876CD43 ', '1983-08-18', 30) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee VALUES (21, 'Денис', 'Петров', 'Владимирович', 'EF8765462GH65 ', '1979-06-23', 44) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee VALUES (22, 'Екатерина', 'Сидорова', 'Михайловна', 'IJ6643210KL87 ', '1970-02-28', 42) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee VALUES (23, 'Антон', 'Козлов', 'Павлович', 'MN4321098OP64 ', '1998-11-03', 43) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee VALUES (24, 'Олег', 'Васильев', 'Андреевич', 'QR0987664ST32 ', '1996-07-08', 54) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee VALUES (25, 'Марина', 'Григорьева', 'Петровна', 'UV7634321WX09 ', '1991-03-13', 54) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee VALUES (26, 'Николай', 'Никитин', 'Сергеевич', 'CD3213987AB76 ', '2001-12-18', 56) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee VALUES (27, 'Елена', 'Федорова', 'Ивановна', 'GH9876533IJ43 ', '2000-10-23', 57) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee VALUES (28, 'Игорь', 'Иванов', 'Александрович', 'KL6533210MN65 ', '2000-06-28', 48) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee VALUES (29, 'Лариса', 'Петрова', 'Владимировна', 'OP2309876QR87 ', '1972-02-03', 49) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee VALUES (30, 'Владимир', 'Сидоров', 'Михайлович', 'ST4921098UV54 ', '1994-09-08', 43) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee VALUES (31, 'Анастасия', 'Козлова', 'Павловна', 'WX6549210YZ32 ', '1995-07-13', 39) ON CONFLICT DO NOTHING;


--
-- TOC entry 4884 (class 0 OID 18340)
-- Dependencies: 231
-- Data for Name: employee_position; Type: TABLE DATA; Schema: main_scheme; Owner: postgres
--

INSERT INTO main_scheme.employee_position VALUES (1, 1) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee_position VALUES (2, 2) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee_position VALUES (3, 3) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee_position VALUES (4, 4) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee_position VALUES (5, 5) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee_position VALUES (6, 6) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee_position VALUES (7, 7) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee_position VALUES (8, 8) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee_position VALUES (9, 9) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee_position VALUES (10, 10) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee_position VALUES (11, 11) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee_position VALUES (12, 12) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee_position VALUES (13, 13) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee_position VALUES (14, 14) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee_position VALUES (15, 15) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee_position VALUES (16, 16) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee_position VALUES (17, 17) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee_position VALUES (18, 18) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee_position VALUES (19, 19) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee_position VALUES (20, 20) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee_position VALUES (21, 21) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee_position VALUES (22, 22) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee_position VALUES (23, 23) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee_position VALUES (24, 24) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee_position VALUES (25, 25) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee_position VALUES (26, 26) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee_position VALUES (27, 27) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee_position VALUES (28, 28) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee_position VALUES (29, 29) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.employee_position VALUES (30, 30) ON CONFLICT DO NOTHING;


--
-- TOC entry 4886 (class 0 OID 18346)
-- Dependencies: 233
-- Data for Name: gradebook; Type: TABLE DATA; Schema: main_scheme; Owner: postgres
--

INSERT INTO main_scheme.gradebook VALUES (1, 1, 1, 1, '2023-01-15', 8) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.gradebook VALUES (2, 2, 2, 2, '2023-02-20', 7) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.gradebook VALUES (3, 3, 3, 3, '2023-03-25', 9) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.gradebook VALUES (4, 4, 4, 1, '2023-04-30', 6) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.gradebook VALUES (5, 5, 5, 2, '2023-05-05', 8) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.gradebook VALUES (6, 6, 6, 3, '2023-06-10', 7) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.gradebook VALUES (7, 7, 7, 1, '2023-07-15', 9) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.gradebook VALUES (8, 8, 8, 2, '2023-08-20', 5) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.gradebook VALUES (9, 9, 9, 3, '2023-09-25', 8) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.gradebook VALUES (10, 1, 1, 1, '2023-10-30', 7) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.gradebook VALUES (11, 1, 1, 2, '2023-11-05', 6) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.gradebook VALUES (12, 1, 2, 3, '2023-12-10', 9) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.gradebook VALUES (13, 3, 3, 1, '2024-01-15', 8) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.gradebook VALUES (14, 4, 4, 2, '2024-02-20', 7) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.gradebook VALUES (15, 5, 5, 3, '2024-03-25', 9) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.gradebook VALUES (16, 6, 6, 1, '2024-04-30', 6) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.gradebook VALUES (17, 7, 7, 2, '2024-05-05', 8) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.gradebook VALUES (18, 8, 8, 3, '2024-06-10', 7) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.gradebook VALUES (19, 1, 9, 1, '2024-07-15', 9) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.gradebook VALUES (20, 2, 2, 2, '2024-08-20', 5) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.gradebook VALUES (21, 2, 2, 3, '2024-09-25', 8) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.gradebook VALUES (22, 2, 2, 1, '2024-10-30', 7) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.gradebook VALUES (23, 2, 3, 2, '2024-11-05', 6) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.gradebook VALUES (24, 4, 4, 3, '2024-12-10', 9) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.gradebook VALUES (25, 5, 12, 1, '2023-01-15', 8) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.gradebook VALUES (26, 6, 12, 2, '2023-02-20', 7) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.gradebook VALUES (27, 7, 17, 3, '2023-03-25', 9) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.gradebook VALUES (28, 8, 18, 1, '2023-04-30', 6) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.gradebook VALUES (29, 9, 19, 2, '2023-05-05', 8) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.gradebook VALUES (30, 3, 13, 3, '2023-06-10', 7) ON CONFLICT DO NOTHING;


--
-- TOC entry 4878 (class 0 OID 18312)
-- Dependencies: 225
-- Data for Name: job_position; Type: TABLE DATA; Schema: main_scheme; Owner: postgres
--

INSERT INTO main_scheme.job_position VALUES (1, 'Директор', 1, '100 000,00 ?') ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.job_position VALUES (2, 'Заместитель директора', 0.9, '90 000,00 ?') ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.job_position VALUES (3, 'Учитель математики', 0.8, '80 000,00 ?') ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.job_position VALUES (4, 'Учитель русского языка', 0.8, '80 000,00 ?') ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.job_position VALUES (5, 'Учитель физики', 0.8, '80 000,00 ?') ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.job_position VALUES (6, 'Учитель химии', 0.8, '80 000,00 ?') ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.job_position VALUES (7, 'Учитель биологии', 0.8, '80 000,00 ?') ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.job_position VALUES (8, 'Учитель истории', 0.8, '80 000,00 ?') ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.job_position VALUES (9, 'Учитель географии', 0.8, '80 000,00 ?') ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.job_position VALUES (10, 'Учитель английского языка', 0.8, '80 000,00 ?') ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.job_position VALUES (11, 'Учитель физической культуры', 0.8, '80 000,00 ?') ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.job_position VALUES (12, 'Учитель искусства', 0.8, '80 000,00 ?') ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.job_position VALUES (13, 'Учитель музыки', 0.8, '80 000,00 ?') ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.job_position VALUES (14, 'Учитель информатики', 0.8, '80 000,00 ?') ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.job_position VALUES (15, 'Учитель технологии', 0.8, '80 000,00 ?') ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.job_position VALUES (16, 'Учитель начальных классов', 0.8, '80 000,00 ?') ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.job_position VALUES (17, 'Педагог-психолог', 0.7, '70 000,00 ?') ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.job_position VALUES (18, 'Социальный педагог', 0.7, '70 000,00 ?') ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.job_position VALUES (19, 'Логопед', 0.7, '70 000,00 ?') ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.job_position VALUES (20, 'Библиотекарь', 0.7, '70 000,00 ?') ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.job_position VALUES (21, 'Администратор', 0.6, '60 000,00 ?') ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.job_position VALUES (22, 'Секретарь', 0.6, '60 000,00 ?') ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.job_position VALUES (23, 'Бухгалтер', 0.6, '60 000,00 ?') ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.job_position VALUES (24, 'Сторож', 0.5, '50 000,00 ?') ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.job_position VALUES (25, 'Уборщик', 0.5, '50 000,00 ?') ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.job_position VALUES (26, 'Воспитатель', 0.7, '70 000,00 ?') ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.job_position VALUES (27, 'Медсестра', 0.6, '60 000,00 ?') ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.job_position VALUES (28, 'Дежурный по физической культуре', 0.7, '70 000,00 ?') ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.job_position VALUES (29, 'Дежурный по охране', 0.6, '60 000,00 ?') ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.job_position VALUES (30, 'Дежурный по уборке', 0.5, '50 000,00 ?') ON CONFLICT DO NOTHING;


--
-- TOC entry 4883 (class 0 OID 18335)
-- Dependencies: 230
-- Data for Name: knowledge_of_subject; Type: TABLE DATA; Schema: main_scheme; Owner: postgres
--

INSERT INTO main_scheme.knowledge_of_subject VALUES (1, 1) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.knowledge_of_subject VALUES (2, 2) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.knowledge_of_subject VALUES (3, 3) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.knowledge_of_subject VALUES (4, 4) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.knowledge_of_subject VALUES (5, 5) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.knowledge_of_subject VALUES (6, 6) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.knowledge_of_subject VALUES (7, 7) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.knowledge_of_subject VALUES (8, 8) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.knowledge_of_subject VALUES (9, 9) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.knowledge_of_subject VALUES (10, 10) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.knowledge_of_subject VALUES (11, 11) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.knowledge_of_subject VALUES (12, 12) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.knowledge_of_subject VALUES (13, 13) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.knowledge_of_subject VALUES (14, 14) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.knowledge_of_subject VALUES (15, 15) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.knowledge_of_subject VALUES (16, 16) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.knowledge_of_subject VALUES (17, 17) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.knowledge_of_subject VALUES (18, 18) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.knowledge_of_subject VALUES (19, 19) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.knowledge_of_subject VALUES (20, 20) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.knowledge_of_subject VALUES (21, 21) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.knowledge_of_subject VALUES (22, 22) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.knowledge_of_subject VALUES (23, 23) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.knowledge_of_subject VALUES (24, 24) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.knowledge_of_subject VALUES (25, 25) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.knowledge_of_subject VALUES (26, 26) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.knowledge_of_subject VALUES (27, 27) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.knowledge_of_subject VALUES (28, 28) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.knowledge_of_subject VALUES (29, 29) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.knowledge_of_subject VALUES (30, 30) ON CONFLICT DO NOTHING;


--
-- TOC entry 4876 (class 0 OID 18304)
-- Dependencies: 223
-- Data for Name: residential_address; Type: TABLE DATA; Schema: main_scheme; Owner: postgres
--

INSERT INTO main_scheme.residential_address VALUES (1, 'Нью-Йорк', 'Бродвей', 123) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (2, 'Лос-Анджелес', 'Сансет-бульвар', 456) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (3, 'Чикаго', 'Мичиган-авеню', 789) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (4, 'Хьюстон', 'Мэйн-стрит', 321) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (5, 'Финикс', 'Центральная авеню', 654) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (6, 'Филадельфия', 'Маркет-стрит', 987) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (7, 'Сан-Антонио', 'Риверволк', 147) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (8, 'Сан-Диего', 'Оушен-бульвар', 258) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (9, 'Даллас', 'Элм-стрит', 369) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (10, 'Сан-Хосе', 'Первая улица', 753) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (11, 'Остин', 'Конгресс-авеню', 852) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (12, 'Джэксонвилл', 'Бей-стрит', 963) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (13, 'Индианаполис', 'Монумент-серкуль', 159) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (14, 'Сан-Франциско', 'Ломбард-стрит', 357) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (15, 'Колумбус', 'Хай-стрит', 468) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (16, 'Форт-Уэрт', 'Санданс-сквер', 579) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (17, 'Шарлотт', 'Трейд-стрит', 684) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (18, 'Сиэтл', 'Пайк-стрит', 795) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (19, 'Денвер', 'Колфакс-авеню', 876) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (20, 'Вашингтон', 'Пенсильвания-авеню', 987) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (21, 'Бостон', 'Ньюбери-стрит', 369) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (22, 'Нэшвилл', 'Бродвей', 753) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (23, 'Балтимор', 'Иннер-Харбор', 852) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (24, 'Оклахома-Сити', 'Бриктаун', 963) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (25, 'Портленд', 'Пёрл-дистрикт', 159) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (26, 'Лас-Вегас', 'Стрип', 357) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (27, 'Милуоки', 'Уотер-стрит', 468) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (28, 'Альбукерке', 'Шоссе 66', 579) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (29, 'Тусон', 'Четвертая авеню', 684) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (30, 'Майами', 'Оушен Драйв', 795) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (31, 'Минск', 'Независимости', 123) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (32, 'Логойск', 'Интернациональная', 456) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (33, 'Витебск', 'Космонавтов', 789) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (34, 'Гродно', 'Малинина', 321) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (35, 'Гомель', 'Могилевская', 654) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (36, 'Гомель', 'Луговая', 987) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (37, 'Несвиж', 'Первомайская', 147) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (38, 'Мир', 'Пушкинская', 258) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (39, 'Брест', 'Деревянная', 369) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (40, 'Кобрин', 'Цветочная', 753) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (41, 'Мозырь', 'Победителей', 852) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (42, 'Орша', 'Центральная', 963) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (43, 'Орша', 'Центральная', 159) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (44, 'Кобрин', 'Лесная', 357) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (45, 'Клецк', 'Домашняя', 468) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (46, 'Несвиж', 'Московская', 579) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (47, 'Солигорск', 'Солевая', 684) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (48, 'Держинск', 'Горная', 795) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (49, 'Фаниполь', 'Клубничная', 876) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (50, 'Лунинец', 'Солнечная', 987) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (51, 'Калинковичи', 'Карла Маркса', 369) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (52, 'Могилев', 'Центральная', 753) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (53, 'Климовичи', 'Лесная', 852) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (54, 'Минск', 'Каменная', 963) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (55, 'Минск', 'Космонавтов', 159) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (56, 'Минск', 'Железная', 357) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (57, 'Марьина Горка', 'Интернациональная', 468) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (58, 'Волковыск', 'Советская', 579) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (59, 'Гродно', 'Полевая', 684) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.residential_address VALUES (60, 'Минск', 'Мирная', 795) ON CONFLICT DO NOTHING;


--
-- TOC entry 4880 (class 0 OID 18320)
-- Dependencies: 227
-- Data for Name: schedule; Type: TABLE DATA; Schema: main_scheme; Owner: postgres
--

INSERT INTO main_scheme.schedule VALUES (1, 1, 1) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.schedule VALUES (2, 2, 2) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.schedule VALUES (3, 3, 3) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.schedule VALUES (4, 4, 4) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.schedule VALUES (5, 5, 5) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.schedule VALUES (6, 6, 6) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.schedule VALUES (7, 7, 7) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.schedule VALUES (8, 8, 8) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.schedule VALUES (9, 9, 9) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.schedule VALUES (10, 10, 10) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.schedule VALUES (11, 11, 11) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.schedule VALUES (12, 12, 12) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.schedule VALUES (13, 13, 13) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.schedule VALUES (14, 14, 14) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.schedule VALUES (15, 15, 15) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.schedule VALUES (16, 16, 16) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.schedule VALUES (17, 17, 17) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.schedule VALUES (18, 18, 18) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.schedule VALUES (19, 19, 19) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.schedule VALUES (20, 20, 20) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.schedule VALUES (21, 21, 21) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.schedule VALUES (22, 22, 22) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.schedule VALUES (23, 23, 23) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.schedule VALUES (24, 24, 24) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.schedule VALUES (25, 25, 25) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.schedule VALUES (26, 26, 26) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.schedule VALUES (27, 27, 27) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.schedule VALUES (28, 28, 28) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.schedule VALUES (29, 29, 29) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.schedule VALUES (30, 30, 30) ON CONFLICT DO NOTHING;


--
-- TOC entry 4870 (class 0 OID 18279)
-- Dependencies: 217
-- Data for Name: student; Type: TABLE DATA; Schema: main_scheme; Owner: postgres
--

INSERT INTO main_scheme.student VALUES (1, 'Иван', 'Иванов', 'Иванович', 'AB1234567CD89 ', '2007-05-10', 1, 1) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.student VALUES (2, 'Петр', 'Петров', 'Петрович', 'EF9876543GH21 ', '2008-02-15', 2, 2) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.student VALUES (3, 'Анна', 'Сидорова', 'Александровна', 'KL4567890MN32 ', '2009-08-20', 3, 3) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.student VALUES (4, 'Мария', 'Козлова', 'Игоревна', 'OP6543210QR54 ', '2010-07-25', 4, 4) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.student VALUES (5, 'Сергей', 'Васильев', 'Дмитриевич', 'ST0987654UV76 ', '2011-03-30', 5, 5) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.student VALUES (6, 'Елена', 'Никитина', 'Павловна', 'WX2345678YZ98 ', '2012-11-05', 6, 6) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.student VALUES (7, 'Алексей', 'Григорьев', 'Андреевич', 'CD8765432AB09 ', '2013-09-12', 7, 7) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.student VALUES (8, 'Ольга', 'Павлова', 'Сергеевна', 'EF2109876GH43 ', '2014-04-18', 8, 8) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.student VALUES (9, 'Дмитрий', 'Федоров', 'Владимирович', 'IJ0987654KL76 ', '2015-12-23', 9, 9) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.student VALUES (10, 'Наталья', 'Иванова', 'Михайловна', 'MN5432109OP65 ', '2016-10-28', 10, 10) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.student VALUES (11, 'Ирина', 'Петрова', 'Алексеевна', 'QR7654321ST87 ', '2017-06-02', 11, 11) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.student VALUES (12, 'Андрей', 'Сидоров', 'Петрович', 'UV1098765WX32 ', '2018-01-07', 12, 12) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.student VALUES (13, 'Виктория', 'Смирнова', 'Анатольевна', 'YZ8765432WX10 ', '2007-09-12', 13, 13) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.student VALUES (14, 'Артем', 'Кузнецов', 'Иванович', 'BC5432109DE87 ', '2008-07-17', 14, 14) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.student VALUES (15, 'Татьяна', 'Морозова', 'Алексеевна', 'FG3210987HI54 ', '2009-04-22', 15, 15) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.student VALUES (16, 'Григорий', 'Новиков', 'Петрович', 'JK1098765LM32 ', '2010-12-27', 16, 16) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.student VALUES (17, 'Василиса', 'Зайцева', 'Дмитриевна', 'NO9876543PQ21 ', '2011-10-02', 17, 17) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.student VALUES (18, 'Егор', 'Павлов', 'Сергеевич', 'RS7654321TU98 ', '2012-05-08', 18, 18) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.student VALUES (19, 'Людмила', 'Соколова', 'Игоревна', 'VW5432109XY76 ', '2013-01-13', 19, 19) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.student VALUES (20, 'Александра', 'Иванова', 'Александровна', 'AB2109876CD43 ', '2014-08-18', 20, 20) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.student VALUES (21, 'Денис', 'Петров', 'Владимирович', 'EF8765432GH65 ', '2015-06-23', 21, 21) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.student VALUES (22, 'Екатерина', 'Сидорова', 'Михайловна', 'IJ6543210KL87 ', '2016-02-28', 22, 22) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.student VALUES (23, 'Антон', 'Козлов', 'Павлович', 'MN4321098OP54 ', '2017-11-03', 23, 23) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.student VALUES (24, 'Олег', 'Васильев', 'Андреевич', 'QR0987654ST32 ', '2018-07-08', 24, 24) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.student VALUES (25, 'Марина', 'Григорьева', 'Петровна', 'UV7654321WX09 ', '2007-03-13', 25, 25) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.student VALUES (26, 'Николай', 'Никитин', 'Сергеевич', 'CD3210987AB76 ', '2008-12-18', 26, 26) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.student VALUES (27, 'Елена', 'Федорова', 'Ивановна', 'GH9876543IJ43 ', '2009-10-23', 27, 27) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.student VALUES (28, 'Игорь', 'Иванов', 'Александрович', 'KL6543210MN65 ', '2010-06-28', 28, 28) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.student VALUES (29, 'Лариса', 'Петрова', 'Владимировна', 'OP2109876QR87 ', '2011-02-03', 29, 29) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.student VALUES (30, 'Владимир', 'Сидоров', 'Михайлович', 'ST4321098UV54 ', '2012-09-08', 30, 30) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.student VALUES (31, 'Анастасия', 'Козлова', 'Павловна', 'WX6543210YZ32 ', '2013-07-13', 21, 30) ON CONFLICT DO NOTHING;


--
-- TOC entry 4874 (class 0 OID 18295)
-- Dependencies: 221
-- Data for Name: subject; Type: TABLE DATA; Schema: main_scheme; Owner: postgres
--

INSERT INTO main_scheme.subject VALUES (1, 'Математика', 60, 101) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.subject VALUES (2, 'Физика', 45, 102) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.subject VALUES (3, 'История', 30, 103) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.subject VALUES (4, 'Литература', 45, 104) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.subject VALUES (5, 'Биология', 60, 105) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.subject VALUES (6, 'Химия', 45, 106) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.subject VALUES (7, 'География', 30, 107) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.subject VALUES (8, 'Английский язык', 60, 108) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.subject VALUES (9, 'Французский язык', 45, 109) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.subject VALUES (10, 'Немецкий язык', 30, 110) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.subject VALUES (11, 'Испанский язык', 45, 111) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.subject VALUES (12, 'Информатика', 60, 112) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.subject VALUES (13, 'Физкультура', 30, 113) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.subject VALUES (14, 'Музыка', 45, 114) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.subject VALUES (15, 'ИЗО', 60, 115) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.subject VALUES (16, 'Трудовое обучение', 30, 116) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.subject VALUES (17, 'Обществознание', 45, 117) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.subject VALUES (18, 'Право', 60, 118) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.subject VALUES (19, 'Экономика', 30, 119) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.subject VALUES (20, 'Психология', 45, 120) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.subject VALUES (21, 'Философия', 60, 121) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.subject VALUES (22, 'Религиоведение', 30, 122) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.subject VALUES (23, 'Хореография', 45, 123) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.subject VALUES (24, 'Театральное искусство', 60, 124) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.subject VALUES (25, 'Основы медицины', 30, 125) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.subject VALUES (26, 'Дизайн', 45, 126) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.subject VALUES (27, 'Астрономия', 60, 127) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.subject VALUES (28, 'Геология', 30, 128) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.subject VALUES (29, 'Архитектура', 45, 129) ON CONFLICT DO NOTHING;
INSERT INTO main_scheme.subject VALUES (30, 'Лингвистика', 60, 130) ON CONFLICT DO NOTHING;


--
-- TOC entry 4902 (class 0 OID 0)
-- Dependencies: 218
-- Name: class_id_seq; Type: SEQUENCE SET; Schema: main_scheme; Owner: postgres
--

SELECT pg_catalog.setval('main_scheme.class_id_seq', 32, true);


--
-- TOC entry 4903 (class 0 OID 0)
-- Dependencies: 228
-- Name: employee_id_seq; Type: SEQUENCE SET; Schema: main_scheme; Owner: postgres
--

SELECT pg_catalog.setval('main_scheme.employee_id_seq', 31, true);


--
-- TOC entry 4904 (class 0 OID 0)
-- Dependencies: 232
-- Name: gradebook_id_seq; Type: SEQUENCE SET; Schema: main_scheme; Owner: postgres
--

SELECT pg_catalog.setval('main_scheme.gradebook_id_seq', 30, true);


--
-- TOC entry 4905 (class 0 OID 0)
-- Dependencies: 224
-- Name: job_position_id_seq; Type: SEQUENCE SET; Schema: main_scheme; Owner: postgres
--

SELECT pg_catalog.setval('main_scheme.job_position_id_seq', 30, true);


--
-- TOC entry 4906 (class 0 OID 0)
-- Dependencies: 222
-- Name: residential_address_id_seq; Type: SEQUENCE SET; Schema: main_scheme; Owner: postgres
--

SELECT pg_catalog.setval('main_scheme.residential_address_id_seq', 60, true);


--
-- TOC entry 4907 (class 0 OID 0)
-- Dependencies: 226
-- Name: schedule_id_seq; Type: SEQUENCE SET; Schema: main_scheme; Owner: postgres
--

SELECT pg_catalog.setval('main_scheme.schedule_id_seq', 30, true);


--
-- TOC entry 4908 (class 0 OID 0)
-- Dependencies: 216
-- Name: student_id_seq; Type: SEQUENCE SET; Schema: main_scheme; Owner: postgres
--

SELECT pg_catalog.setval('main_scheme.student_id_seq', 31, true);


--
-- TOC entry 4909 (class 0 OID 0)
-- Dependencies: 220
-- Name: subject_id_seq; Type: SEQUENCE SET; Schema: main_scheme; Owner: postgres
--

SELECT pg_catalog.setval('main_scheme.subject_id_seq', 30, true);


--
-- TOC entry 4695 (class 2606 OID 18293)
-- Name: class class_pkey; Type: CONSTRAINT; Schema: main_scheme; Owner: postgres
--

ALTER TABLE ONLY main_scheme.class
    ADD CONSTRAINT class_pkey PRIMARY KEY (id);


--
-- TOC entry 4705 (class 2606 OID 18334)
-- Name: employee employee_passport_id_key; Type: CONSTRAINT; Schema: main_scheme; Owner: postgres
--

ALTER TABLE ONLY main_scheme.employee
    ADD CONSTRAINT employee_passport_id_key UNIQUE (passport_id);


--
-- TOC entry 4707 (class 2606 OID 18332)
-- Name: employee employee_pkey; Type: CONSTRAINT; Schema: main_scheme; Owner: postgres
--

ALTER TABLE ONLY main_scheme.employee
    ADD CONSTRAINT employee_pkey PRIMARY KEY (id);


--
-- TOC entry 4711 (class 2606 OID 18344)
-- Name: employee_position employee_position_pkey; Type: CONSTRAINT; Schema: main_scheme; Owner: postgres
--

ALTER TABLE ONLY main_scheme.employee_position
    ADD CONSTRAINT employee_position_pkey PRIMARY KEY (employee_id);


--
-- TOC entry 4713 (class 2606 OID 18351)
-- Name: gradebook gradebook_pkey; Type: CONSTRAINT; Schema: main_scheme; Owner: postgres
--

ALTER TABLE ONLY main_scheme.gradebook
    ADD CONSTRAINT gradebook_pkey PRIMARY KEY (id);


--
-- TOC entry 4701 (class 2606 OID 18318)
-- Name: job_position job_position_pkey; Type: CONSTRAINT; Schema: main_scheme; Owner: postgres
--

ALTER TABLE ONLY main_scheme.job_position
    ADD CONSTRAINT job_position_pkey PRIMARY KEY (id);


--
-- TOC entry 4709 (class 2606 OID 18339)
-- Name: knowledge_of_subject knowledge_of_subject_pkey; Type: CONSTRAINT; Schema: main_scheme; Owner: postgres
--

ALTER TABLE ONLY main_scheme.knowledge_of_subject
    ADD CONSTRAINT knowledge_of_subject_pkey PRIMARY KEY (employee_id);


--
-- TOC entry 4699 (class 2606 OID 18310)
-- Name: residential_address residential_address_pkey; Type: CONSTRAINT; Schema: main_scheme; Owner: postgres
--

ALTER TABLE ONLY main_scheme.residential_address
    ADD CONSTRAINT residential_address_pkey PRIMARY KEY (id);


--
-- TOC entry 4703 (class 2606 OID 18325)
-- Name: schedule schedule_pkey; Type: CONSTRAINT; Schema: main_scheme; Owner: postgres
--

ALTER TABLE ONLY main_scheme.schedule
    ADD CONSTRAINT schedule_pkey PRIMARY KEY (id);


--
-- TOC entry 4691 (class 2606 OID 18286)
-- Name: student student_passport_id_key; Type: CONSTRAINT; Schema: main_scheme; Owner: postgres
--

ALTER TABLE ONLY main_scheme.student
    ADD CONSTRAINT student_passport_id_key UNIQUE (passport_id);


--
-- TOC entry 4693 (class 2606 OID 18284)
-- Name: student student_pkey; Type: CONSTRAINT; Schema: main_scheme; Owner: postgres
--

ALTER TABLE ONLY main_scheme.student
    ADD CONSTRAINT student_pkey PRIMARY KEY (id);


--
-- TOC entry 4697 (class 2606 OID 18302)
-- Name: subject subject_pkey; Type: CONSTRAINT; Schema: main_scheme; Owner: postgres
--

ALTER TABLE ONLY main_scheme.subject
    ADD CONSTRAINT subject_pkey PRIMARY KEY (id);


--
-- TOC entry 4714 (class 2606 OID 18352)
-- Name: student fk_class; Type: FK CONSTRAINT; Schema: main_scheme; Owner: postgres
--

ALTER TABLE ONLY main_scheme.student
    ADD CONSTRAINT fk_class FOREIGN KEY (class_id) REFERENCES main_scheme.class(id) ON DELETE CASCADE;


--
-- TOC entry 4719 (class 2606 OID 18382)
-- Name: knowledge_of_subject fk_employee; Type: FK CONSTRAINT; Schema: main_scheme; Owner: postgres
--

ALTER TABLE ONLY main_scheme.knowledge_of_subject
    ADD CONSTRAINT fk_employee FOREIGN KEY (employee_id) REFERENCES main_scheme.employee(id) ON DELETE CASCADE;


--
-- TOC entry 4721 (class 2606 OID 18387)
-- Name: employee_position fk_employee; Type: FK CONSTRAINT; Schema: main_scheme; Owner: postgres
--

ALTER TABLE ONLY main_scheme.employee_position
    ADD CONSTRAINT fk_employee FOREIGN KEY (employee_id) REFERENCES main_scheme.employee(id) ON DELETE CASCADE;


--
-- TOC entry 4723 (class 2606 OID 18402)
-- Name: gradebook fk_employee; Type: FK CONSTRAINT; Schema: main_scheme; Owner: postgres
--

ALTER TABLE ONLY main_scheme.gradebook
    ADD CONSTRAINT fk_employee FOREIGN KEY (employee_id) REFERENCES main_scheme.employee(id) ON DELETE CASCADE;


--
-- TOC entry 4718 (class 2606 OID 18372)
-- Name: employee fk_employee_residential_address; Type: FK CONSTRAINT; Schema: main_scheme; Owner: postgres
--

ALTER TABLE ONLY main_scheme.employee
    ADD CONSTRAINT fk_employee_residential_address FOREIGN KEY (residential_address_id) REFERENCES main_scheme.residential_address(id) ON DELETE CASCADE;


--
-- TOC entry 4722 (class 2606 OID 18392)
-- Name: employee_position fk_job_position; Type: FK CONSTRAINT; Schema: main_scheme; Owner: postgres
--

ALTER TABLE ONLY main_scheme.employee_position
    ADD CONSTRAINT fk_job_position FOREIGN KEY (job_position_id) REFERENCES main_scheme.job_position(id) ON DELETE CASCADE;


--
-- TOC entry 4716 (class 2606 OID 18362)
-- Name: schedule fk_schedule; Type: FK CONSTRAINT; Schema: main_scheme; Owner: postgres
--

ALTER TABLE ONLY main_scheme.schedule
    ADD CONSTRAINT fk_schedule FOREIGN KEY (class_id) REFERENCES main_scheme.class(id) ON DELETE CASCADE;


--
-- TOC entry 4724 (class 2606 OID 18407)
-- Name: gradebook fk_student; Type: FK CONSTRAINT; Schema: main_scheme; Owner: postgres
--

ALTER TABLE ONLY main_scheme.gradebook
    ADD CONSTRAINT fk_student FOREIGN KEY (student_id) REFERENCES main_scheme.student(id) ON DELETE CASCADE;


--
-- TOC entry 4715 (class 2606 OID 18357)
-- Name: student fk_student_residential_address; Type: FK CONSTRAINT; Schema: main_scheme; Owner: postgres
--

ALTER TABLE ONLY main_scheme.student
    ADD CONSTRAINT fk_student_residential_address FOREIGN KEY (residential_address_id) REFERENCES main_scheme.residential_address(id) ON DELETE CASCADE;


--
-- TOC entry 4717 (class 2606 OID 18367)
-- Name: schedule fk_subject; Type: FK CONSTRAINT; Schema: main_scheme; Owner: postgres
--

ALTER TABLE ONLY main_scheme.schedule
    ADD CONSTRAINT fk_subject FOREIGN KEY (subject_id) REFERENCES main_scheme.subject(id) ON DELETE CASCADE;


--
-- TOC entry 4720 (class 2606 OID 18377)
-- Name: knowledge_of_subject fk_subject; Type: FK CONSTRAINT; Schema: main_scheme; Owner: postgres
--

ALTER TABLE ONLY main_scheme.knowledge_of_subject
    ADD CONSTRAINT fk_subject FOREIGN KEY (subject_id) REFERENCES main_scheme.subject(id) ON DELETE CASCADE;


--
-- TOC entry 4725 (class 2606 OID 18397)
-- Name: gradebook fk_subject; Type: FK CONSTRAINT; Schema: main_scheme; Owner: postgres
--

ALTER TABLE ONLY main_scheme.gradebook
    ADD CONSTRAINT fk_subject FOREIGN KEY (subject_id) REFERENCES main_scheme.subject(id) ON DELETE CASCADE;


-- Completed on 2024-03-01 14:08:33

--
-- PostgreSQL database dump complete
--

