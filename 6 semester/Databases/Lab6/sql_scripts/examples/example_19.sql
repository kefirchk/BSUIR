-- Объединить и вывести имена и фамилии учеников и сотрудников в алфавитном порядке,
-- у которых имя начинается на букву “И”. Для учеников также вывести номер и 
-- букву класса, к которому они принадлежат.

SELECT
    first_name,
    last_name,
    class_number,
    class_letter
FROM main_scheme.student
INNER JOIN main_scheme.class
    ON student.class_id = main_scheme.class.id
WHERE first_name LIKE 'И%'
UNION
SELECT
    first_name,
    last_name,
    NULL,
    NULL
FROM main_scheme.employee
WHERE first_name LIKE 'И%'
ORDER BY last_name;
