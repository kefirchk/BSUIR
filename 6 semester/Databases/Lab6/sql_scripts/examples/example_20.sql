-- Найти фамилии учеников и сотрудников школы, которые живут по одному адресу и имеют одну и ту же фамилию.

SELECT 
    residential_address_id,
    last_name,
    residential_address.city,
    residential_address.street,
    residential_address.house_number
FROM main_scheme.employee
INNER JOIN main_scheme.residential_address
    ON residential_address.id = employee.residential_address_id
INTERSECT
SELECT
    residential_address_id,
    last_name,
    residential_address.city,
    residential_address.street,
    residential_address.house_number
FROM main_scheme.student
INNER JOIN main_scheme.residential_address
    ON residential_address_id = student.residential_address_id;
