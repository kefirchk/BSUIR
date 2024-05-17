-- Вывести название должности, ФИО сотрудника, оклад которого составляет 70000 условных денежных единиц.

SELECT
    job_position.name,
    job_position.salary,
    employee.last_name,
    employee.first_name,
    employee.middle_name
FROM main_scheme.employee_position 
FULL OUTER JOIN main_scheme.job_position 
    ON employee_position.job_position_id = job_position.id
INNER JOIN main_scheme.employee
    ON employee.id = employee_position.employee_id
WHERE salary = '70000';
