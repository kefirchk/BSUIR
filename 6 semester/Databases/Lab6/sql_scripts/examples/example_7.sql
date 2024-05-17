-- Вывести фамилию и имя сотрудников, которых зовут “Алексей”, их дату рождения,
-- идентификационный номер паспорта и их адреса проживания (город и улицу), 
-- включая тех сотрудников, у которых нет адреса.

SELECT
    first_name,
    last_name,
    date_of_birth,
    passport_id,
    city,
    street
FROM main_scheme.employee
LEFT OUTER JOIN main_scheme.residential_address 
    ON employee.residential_address_id = residential_address.id;
