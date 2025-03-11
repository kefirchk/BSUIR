//========================================================
// ЛАБОРАТОРНАЯ РАБОТА №2. Работа со списками и функциями
// Вариант 2
// 1.	Написать функцию для подсчета суммы отрицательных элементов списка. Список задать самостоятельно.
// 2.	Написать функцию для подсчета суммы последних трех элементов списка из 10 элементов. Список задать самостоятельно.
// 3.	Написать функцию для отыскания индексов всех максимальных элементов списка. Список задать самостоятельно.
// 4.	Написать функцию для проверки того, что список не упорядочен  ни по возрастанию, ни по убыванию. Список задать самостоятельно.
// 5.	Написать функцию для проверки наличия трех одинаковых элементов в списке. Список задать самостоятельно. Функция возвращает значение такого элемента.

import scala.collection.JavaConverters

//========================================================
// Задача 1.
//========================================================
// object Main2 {
//   def negative_sum(lst: List[Int]): Int = {
//     val negative_numbers = lst.filter(x => x < 0)
//     if(negative_numbers.isEmpty) 0
//     else negative_numbers.sum
//   }

//   def main(args: Array[String]): Unit = {
//     println("Enter elements of the list (integers), separated by spaces:")
//     val list = scala.io.StdIn.readLine().split(" ").map(_.toInt).toList
//     println("Entered list: " + list)
//     if(list.isEmpty) {
//       println("The list is empty") 
//     } else {
//       println("Sum of negative numbers: " + negative_sum(list))
//     }
//   }
// }

//========================================================
// Задача 2.
//========================================================
// object Main2 {
//   def sum_last_3(lst: List[Int], index : Int): Int = {
//     if(lst.isEmpty)
//       return 0
//     if(index > 6)
//       lst.head + sum_last_3(lst.tail, index + 1)
//     else
//       sum_last_3(lst.tail, index + 1)
//   }

//   def main(args: Array[String]): Unit = {
//     println("Enter 10 elements of the list (integers), separated by 'Enter':")
//     var list = List[Int]()
//     for(i <- 1 to 10)
//       list = list :+ scala.io.StdIn.readInt()
//     println("Entered list: " + list)
//     if(list.isEmpty) {
//         println("The list is empty") 
//     } else {
//       println("Sum of last three numbers: " + sum_last_3(list, 0))
//     }
//   }
// }

//========================================================
// Задача 3.
//========================================================
// var indexes = List[Int]()
// object Main2 {
//   def find_max(lst: List[Int], max : Int): Int = {
//     if(lst.isEmpty) return max 
//     if(lst.head > max)
//       find_max(lst.tail, lst.head)
//     else
//       find_max(lst.tail, max)
//   }

//   def get_indexes(lst: List[Int], index: Int, max: Int): List[Int] = {
//     if(lst.isEmpty) return indexes
//     if(max == lst.head) 
//       indexes = indexes :+ index
//     get_indexes(lst.tail, index + 1, max)
//   }

//   def main(args: Array[String]): Unit = {
//     println("Enter elements of the list (integers), separated by spaces:")
//     val list = scala.io.StdIn.readLine().split(" ").map(_.toInt).toList
//     println("Entered list: " + list)
//     if(list.isEmpty) {
//       println("The list is empty") 
//     } else {
//       val max = find_max(list, list.head)
//       println("Max number: " + max)
//       println("Indexes of max numbers: " + get_indexes(list, 0, max).mkString(", "))
//     }
//   }
// }

//========================================================
// Задача 4.
//========================================================
// object Main2 {
//   def is_sorted(lst: List[Int]): Boolean = {
//     is_sorted_in_ascendeing_order(lst, lst.head) & is_sorted_in_descending_order(lst.reverse, lst.reverse.head)
//   }

//   def is_sorted_in_ascendeing_order(lst: List[Int], prev: Int): Boolean = {
//     if(lst.isEmpty)
//       true
//     else if(prev > lst.head)
//       false
//     else
//       is_sorted_in_ascendeing_order(lst.tail, lst.head)
//   }

//   def is_sorted_in_descending_order(lst: List[Int], prev: Int): Boolean = {
//     if(lst.isEmpty)
//       true
//     else if(prev < lst.head)
//       false
//     else
//       is_sorted_in_descending_order(lst.tail, lst.head)
//   }

//   def main(args: Array[String]): Unit = {
//     println("Enter elements of the list (integers), separated by spaces:")
//     val list = scala.io.StdIn.readLine().split(" ").map(_.toInt).toList
//     println("Entered list: " + list)
//     if(list.isEmpty) {
//         println("The list is empty") 
//     } else {
//       if(is_sorted(list))
//         println("List is sorted")
//       else
//         println("List is not sorted")
//     }
//   }
// }

//========================================================
// Задача 5.
//========================================================
// var numbers = List[Int]()
// object Main2 {
//   def find_same_numbers(lst: List[Int], repeation_count: Int): List[Int] = {
//     if(lst.isEmpty)
//       return numbers
//     var count = count_numbers(lst, lst.head)
//     if(count == repeation_count)
//       numbers = numbers :+ lst.head
//     find_same_numbers(lst.tail, repeation_count)
//   }

//   def count_numbers(lst: List[Int], value: Int): Int = {
//     if(lst.isEmpty)
//       return 0
//     else if(value == lst.head)
//       1 + count_numbers(lst.tail, value)
//     else
//       count_numbers(lst.tail, value)
//   }

//   def main(args: Array[String]): Unit = {
//     println("Enter elements of the list (integers), separated by spaces:")
//     val list = scala.io.StdIn.readLine().split(" ").map(_.toInt).toList
//     println("Entered list: " + list)
//     if(list.isEmpty) {
//       println("The list is empty") 
//     } else {
//       val lst_of_values = find_same_numbers(list, 3)
//       println("Values: " + lst_of_values.mkString(", "))
//     }
//   }
// }

// Сумма на четных позициях:
object Main2 {
  def odd_sum(lst: List[Int], index : Int): Int = {
    if(lst.isEmpty)
        return 0
    if(index % 2 == 0)
        lst.head + odd_sum(lst.tail, index + 1)
    else
        odd_sum(lst.tail, index + 1)
  }

  def main(args: Array[String]): Unit = {
    println("Enter elements of the list (integers), separated by spaces:")
    val list = scala.io.StdIn.readLine().split(" ").map(_.toInt).toList
    println("Entered list: " + list)
    if(list.isEmpty) {
      println("The list is empty") 
    } else {
      println("Sum of odd index numbers: " + odd_sum(list, 0))
    }
  }
}