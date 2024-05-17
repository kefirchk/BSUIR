-- Вывести название предмета, день недели, номер класса, общее количество учеников,
-- для которых номер класса является общим, а также количество таких классов.
-- При этом день недели должен быть понедельником, а номера классов должны иметь номер от 9 до 11.

WITH common_class_info AS 
    (SELECT class_number,
        SUM(student_count) AS all_student_count,
        COUNT(class_number) AS all_classes
    FROM main_scheme.class
    GROUP BY class_number)
SELECT
    subject.name,
    schedule.week_day,
    common_class_info.class_number,
    common_class_info.all_student_count,
    common_class_info.all_classes
FROM main_scheme.subject
INNER JOIN main_scheme.schedule
    ON main_scheme.schedule.subject_id = main_scheme.subject.id
INNER JOIN main_scheme.class
    ON main_scheme.class.id = main_scheme.schedule.class_id
INNER JOIN common_class_info
    ON common_class_info.class_number = main_scheme.class.class_number
WHERE common_class_info.class_number 
BETWEEN 9 AND 11 AND schedule.week_day = 'Понедельник';
