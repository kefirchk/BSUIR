-- Выбрать всех сотрудников (ФИО) и их адреса проживания из Гродно, включая адреса без сотрудников.

SELECT * FROM main_scheme.employee 
RIGHT OUTER JOIN main_scheme.residential_address
    ON employee.residential_address_id = residential_address.id 
WHERE city = 'Гродно';
