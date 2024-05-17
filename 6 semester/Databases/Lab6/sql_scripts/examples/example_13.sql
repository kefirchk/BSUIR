-- Выбрать все предметы, в названии которых есть слово “Язык”.

SELECT * FROM main_scheme.subject 
WHERE name LIKE '%язык%';
