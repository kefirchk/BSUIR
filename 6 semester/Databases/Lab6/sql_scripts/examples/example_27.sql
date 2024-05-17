-- Вывести имя и фамилию людей, город их проживания, а также id класса (если этот человек
-- является учеников школы). Эти люди должны проживать в таких городах, где живут ещё хотя
-- бы два человека, но не по его адресу.

SELECT
    student.last_name, student.first_name,
    residential_address.city, student.class_id
FROM main_scheme.student
LEFT OUTER JOIN main_scheme.residential_address
    ON residential_address.id = student.residential_address_id
WHERE residential_address.city IN (SELECT city
                                    FROM main_scheme.residential_address
                                    GROUP BY city HAVING COUNT(city) > 2)
UNION SELECT
    employee.first_name, employee.last_name,
    residential_address.city, NULL
FROM main_scheme.employee
LEFT OUTER JOIN main_scheme.residential_address
    ON residential_address.id = employee.residential_address_id
WHERE residential_address.city IN (SELECT city
                                    FROM main_scheme.residential_address
                                    GROUP BY city HAVING COUNT(city) > 2);
