-- Вывести расписание занятия для 11-х классов (день недели, фамилия учителя,
-- название предмета, номер кабинета, номер класса, общее количество учеников 11-х классов).

WITH common_class_info AS
    (SELECT SUM(student_count) AS all_students,
    class_number FROM main_scheme.class
    GROUP BY main_scheme.class.class_number)
SELECT
    schedule.week_day,
    employee.last_name,
    subject.name, subject.classroom,
    class.class_number,
    common_class_info.all_students AS count_of_students
FROM main_scheme.class
INNER JOIN main_scheme.schedule
    ON schedule.class_id = main_scheme.class.id
INNER JOIN main_scheme.subject
    ON schedule.subject_id = subject.id
INNER JOIN main_scheme.knowledge_of_subject
    ON knowledge_of_subject.subject_id = subject.id
INNER JOIN main_scheme.employee
    ON employee.id = knowledge_of_subject.employee_id
INNER JOIN common_class_info
    ON main_scheme.class.class_number = common_class_info.class_number
WHERE main_scheme.class.class_number = 11;
