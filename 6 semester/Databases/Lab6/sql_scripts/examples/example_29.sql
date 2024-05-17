-- Выбрать всех студентов, учащихся в классах с номером больше 5 и проживающих в Нью-Йорке.

SELECT * FROM main_scheme.student
WHERE class_id = ANY (SELECT id FROM main_scheme.class 
                        WHERE class_number > 5)
AND residential_address_id = ANY (SELECT id FROM main_scheme.residential_address 
                                    WHERE city LIKE 'Нью%');
