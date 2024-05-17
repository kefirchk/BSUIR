-- Выбрать адреса проживания в Минске и отсортировать их по номеру дома.

SELECT * FROM main_scheme.residential_address
WHERE city = 'Минск' 
ORDER BY house_number;
