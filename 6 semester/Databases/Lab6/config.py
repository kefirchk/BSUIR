HOST = '127.0.0.1'
USER = 'postgres'
PASSWORD = '1234'
DB_NAME = 'school'
TABLE_NAMES = [
    "class",
    "employee",
    "employee_position",
    "gradebook",
    "job_position",
    "knowledge_of_subject",
    "residential_address",
    "schedule",
    "student",
    "subject"
]

# В запросах нужно указывать схему, из которой берем таблицы для запросов
# SCHEME_NAME = "main_scheme"