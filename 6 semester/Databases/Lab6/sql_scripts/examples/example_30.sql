-- Найти самого старого сотрудника, вывести его профессию, город проживания и идентификационный номер паспорта.

SELECT
    employee.passport_id,
    residential_address.city,
    job_position.name AS profession
FROM main_scheme.employee
INNER JOIN main_scheme.residential_address
    ON residential_address.id = employee.residential_address_id
INNER JOIN main_scheme.employee_position
    ON employee_position.employee_id = employee.id
INNER JOIN main_scheme.job_position
    ON job_position.id = employee_position.job_position_id
WHERE date_of_birth <= ALL (SELECT date_of_birth FROM main_scheme.employee);
