-- Вывести ФИО учеников, у которых имя начинается с буквы “А”.

SELECT 
    main_scheme.student.first_name,
    main_scheme.student.last_name,
    main_scheme.student.middle_name
FROM main_scheme.student 
WHERE first_name LIKE 'А%';
