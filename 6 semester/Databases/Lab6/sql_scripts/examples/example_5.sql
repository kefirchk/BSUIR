-- Выбрать все адреса проживания, где номер дома находится в диапазоне от 100 до 200.

SELECT * FROM main_scheme.residential_address
WHERE house_number BETWEEN 100 AND 200;
