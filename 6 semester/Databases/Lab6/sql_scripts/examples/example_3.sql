-- Вывести номер класса и букву класса, в которых количество студентов больше 30, отсортированные по номеру класса.

SELECT
    class_number,
    class_letter,
    student_count
FROM main_scheme.class
WHERE student_count > 30 
ORDER BY class_number;
