-- Найти имя и фамилию учеников, их класс, а также предмет, по которому они получили
-- минимальную оценку среди всех оценок. Кроме того, необходимо вывести дату этой оценки
-- и фамилию учителя, который выставил оценку.

SELECT
    student.last_name AS student_last_name,
    student.first_name AS student_first_name,
    main_scheme.class.class_number,
    main_scheme.class.class_letter,
    subject.name,
    employee.last_name AS teacher_last_name,
    gradebook.grade,
    gradebook.grade_date
FROM main_scheme.student
INNER JOIN main_scheme.class
    ON class.id = student.class_id
INNER JOIN main_scheme.gradebook
    ON gradebook.student_id = student.id
INNER JOIN main_scheme.employee
    ON gradebook.employee_id = employee.id
INNER JOIN main_scheme.subject
    ON subject.id = gradebook.subject_id
WHERE main_scheme.gradebook.grade = 
    (SELECT MIN(grade) AS min_grade
    FROM main_scheme.gradebook);
