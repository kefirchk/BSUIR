-- Выбрать расписание занятий по вторникам с информацией о классах, используя INNER JOIN.

SELECT
    week_day,
    class_number,
    class_letter
FROM main_scheme.schedule
INNER JOIN main_scheme.class
    ON schedule.class_id = main_scheme.class.id
WHERE week_day = 'Вторник';
