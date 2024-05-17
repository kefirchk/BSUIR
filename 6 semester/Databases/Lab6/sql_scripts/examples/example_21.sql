-- Найти ФИО людей, которые есть в таблице “employee”, но нет в таблице “student”.
-- При этом необходимо также вывести их город проживания.

WITH uniq_people AS
    (SELECT first_name, last_name, middle_name
    FROM main_scheme.student 
    EXCEPT
    SELECT first_name, last_name, middle_name
    FROM main_scheme.employee)
SELECT first_name, last_name, middle_name, city
FROM main_scheme.student
INNER JOIN main_scheme.residential_address
    ON student.residential_address_id = residential_address.id 
WHERE first_name IN (SELECT first_name FROM uniq_people);
