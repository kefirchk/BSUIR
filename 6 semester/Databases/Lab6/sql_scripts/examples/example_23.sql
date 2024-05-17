-- Вывести имя и фамилию ученика, номер класса и оценку, полученную
-- в промежуток времени от 01.01.2023 до 01.05.2023, которая больше или 
-- равна средней оценки среди всех оценок.

SELECT
    student.last_name,
    student.first_name,
    class.class_number,
    gradebook.grade
FROM main_scheme.student
LEFT OUTER JOIN main_scheme.class
    ON class.id = student.class_id
LEFT OUTER JOIN main_scheme.gradebook
    ON gradebook.student_id = student.id
WHERE gradebook.grade_date BETWEEN '2023-01-01' AND '2023-05-01'
AND grade >= (SELECT ROUND(AVG(grade), 1) AS avg_grade
                FROM main_scheme.gradebook);
