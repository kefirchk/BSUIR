-- Выбрать расписание занятий с информацией о предметах, где аудитория равна 101.

SELECT * FROM main_scheme.schedule
INNER JOIN main_scheme.subject
    ON schedule.subject_id = subject.id
WHERE classroom = 101;
