-- Выбрать все предметы (название и часы), у которых количество часов равно максимальному количеству часов среди всех предметов.

SELECT
    name,
    hours
FROM main_scheme.subject
WHERE hours >= ALL (SELECT hours FROM main_scheme.subject);
