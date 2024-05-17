-- Выбрать информацию о должностях сотрудников с информацией о доступных должностях,
-- включая те должности, которые не заняты сотрудниками, 
-- при этом ставка должна быть в диапазоне от 0.8 до 1.

SELECT * FROM main_scheme.employee_position
FULL OUTER JOIN main_scheme.job_position
    ON employee_position.job_position_id = job_position.id
WHERE rate BETWEEN 0.8 AND 1;
