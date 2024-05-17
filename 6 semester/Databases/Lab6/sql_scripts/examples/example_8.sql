-- Выбрать информацию о знании предмета с информацией о предметах, 
-- включая предметы, по которым нет информации о знании и у которых количество часов равно 45.

SELECT * FROM main_scheme.knowledge_of_subject 
RIGHT OUTER JOIN main_scheme.subject 
    ON knowledge_of_subject.subject_id = subject.id
WHERE hours = 45;
