-- Выбрать всех учеников из классов, где количество учеников меньше 15.

SELECT * FROM main_scheme.student
WHERE class_id IN 
    (SELECT id FROM main_scheme.class 
        WHERE student_count < 15);
