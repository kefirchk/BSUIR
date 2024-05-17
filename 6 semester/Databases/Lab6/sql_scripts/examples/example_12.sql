-- Выбрать все классы от 7 до 11 включительно и отсортировать их по номеру класса по убыванию.

SELECT * FROM main_scheme.class
WHERE class_number BETWEEN 7 AND 11
ORDER BY class_number DESC;
