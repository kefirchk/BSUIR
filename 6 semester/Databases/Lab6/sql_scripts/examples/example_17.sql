-- Выбрать информацию о должностях сотрудников с информацией о доступных должностях,
-- где оклад больше 80000 тыс. условных денежных единиц.

SELECT * FROM main_scheme.employee_position 
FULL OUTER JOIN main_scheme.job_position 
    ON employee_position.job_position_id = job_position.id 
WHERE salary > '80000';
