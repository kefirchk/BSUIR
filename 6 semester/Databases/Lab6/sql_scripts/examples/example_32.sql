-- Вывести фамилии всех студентов, их город, улицу и номер дома, которые живут в Нью-Йорке, и их оценку.

SELECT
    student.last_name,
    residential_address.city,
    residential_address.street,
    residential_address.house_number,
    gradebook.grade
FROM main_scheme.student 
FULL OUTER JOIN main_scheme.residential_address
    ON student.residential_address_id = residential_address.id 
FULL OUTER JOIN main_scheme.class
    ON class.id = student.class_id
FULL OUTER JOIN main_scheme.gradebook
    ON gradebook.student_id = student.id
WHERE city = 'Нью-Йорк';
