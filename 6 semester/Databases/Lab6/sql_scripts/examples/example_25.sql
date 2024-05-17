-- Найти ФИО сотрудников, название должности и процентную ставку, которая больше медианной ставки среди ставок.

SELECT
    employee.last_name,
    employee.first_name,
    employee.middle_name,
    job_position.name,
    job_position.rate
FROM main_scheme.employee
INNER JOIN main_scheme.employee_position
    ON employee_position.employee_id = employee.id
INNER JOIN main_scheme.job_position
    ON job_position.id = employee_position.job_position_id
WHERE main_scheme.job_position.rate > (SELECT PERCENTILE_CONT(0.5) 
                                        WITHIN GROUP(ORDER BY rate) AS median_rate
                                        FROM main_scheme.job_position);
