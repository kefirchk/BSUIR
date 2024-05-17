-- Выбрать всех студентов, родившихся между 2000 и 2010 годами.

SELECT * FROM main_scheme.student
WHERE date_of_birth BETWEEN '2000-01-01' AND '2010-12-31';

