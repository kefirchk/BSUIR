-- Найти ФИО сотрудников, название предмета, который они знают, и
-- соответствующее количество часов предмета, которое должно равняться
-- максимальному количеству часов среди всех предметов.

SELECT
    subject.name,
    subject.hours,
    employee.last_name,
    employee.first_name,
    employee.middle_name
FROM main_scheme.subject
FULL OUTER JOIN main_scheme.knowledge_of_subject
    ON knowledge_of_subject.subject_id = subject.id
FULL OUTER JOIN main_scheme.employee
    ON employee.id = knowledge_of_subject.employee_id
WHERE subject.hours = (SELECT MAX(hours) AS max_hours
                        FROM main_scheme.subject);
