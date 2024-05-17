-- Получить комбинацию всех записей из журнала оценок с каждым учеником 25 числа месяца
-- в базе данных и вывести ФИО, оценку и дату оценки ученика, при этом оценка должна 
-- быть равна 9 и отчество ученика должно быть “Иванович” или “Ивановна”.

SELECT
    first_name,
    last_name,
    middle_name,
    grade,
    grade_date
FROM main_scheme.gradebook 
CROSS JOIN main_scheme.student
WHERE EXTRACT(DAY FROM grade_date) = 25
    AND middle_name LIKE 'Иван%'
    AND grade = 9;
