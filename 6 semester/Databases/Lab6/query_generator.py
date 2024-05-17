class QueryGenerator:
    def generate_insert_query(self, table_name, column_names, entries):
            # Формируем строку с названиями столбцов
            columns = ', '.join(column_names)
    
            # Формируем строку со значениями
            values = ', '.join(f"'{entry}'" if entry else 'NULL' for entry in entries)
    
            # Собираем полный запрос
            query = f"INSERT INTO main_scheme.{table_name} ({columns}) VALUES ({values});"
            return query
        

    def generate_delete_query(self, table_name, column_names, entries):
        # Формируем условие для удаления
        conditions = ' AND '.join(f"{col} = '{entry}'" for col, entry in zip(column_names, entries) if entry)
    
        # Собираем полный запрос
        query = f"DELETE FROM main_scheme.{table_name} WHERE {conditions};"
        return query


    def generate_update_query(self, table_name, column_names, entries):
        if entries[0] == None:
            raise Exception("'id' cannot be NULL")
        
        update_query = f"UPDATE main_scheme.{table_name} SET "
        set_clauses = []

        for col_name, entry in zip(column_names, entries):
            if entry and col_name != 'id':
                # Если значение не пустое, добавляем его в запрос
                set_clauses.append(f"{col_name} = '{entry}'")

        update_query += ", ".join(set_clauses) + f" WHERE {column_names[0]} = {entries[0]}"
        return update_query