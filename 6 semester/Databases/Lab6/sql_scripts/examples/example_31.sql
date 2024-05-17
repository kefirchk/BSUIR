-- Вывести фамилию учителя и его предмет, имеющего должность, в названии предмета которого есть слово “язык”.

SELECT
    employee.last_name,
    subject.name
FROM main_scheme.knowledge_of_subject
RIGHT OUTER JOIN main_scheme.employee
    ON employee.id = knowledge_of_subject.employee_id
RIGHT OUTER JOIN main_scheme.subject
    ON subject.id = knowledge_of_subject.subject_id
WHERE EXISTS (SELECT * FROM main_scheme.employee_position 
                WHERE employee_position.employee_id = knowledge_of_subject.employee_id)
                AND subject.name LIKE '%язык%';
