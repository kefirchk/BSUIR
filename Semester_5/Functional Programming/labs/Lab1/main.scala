//========================================================
// Вариант 3
// Построить генератор случайных чисел по следующей схеме. Вводите 10-значное число Z с клавиатуры. 
// Формируете два новых целых числа A и B: первое  A состоит из первых пяти цифр, второе B – из последних  цифр числа Z, начиная с шестой.
// Дописываете к числу В число А. Получаете число W. Находите С= Z*W. 
// Первые три цифры результата С, будучи поделенными на 1000, дают первое случайное число REZ.
// Чтобы сформировать следующее случайное число, формируете два новых целых числа A и B:
// первое  A состоит из первых пяти цифр, второе B  – из последних  цифр числа C, начиная с шестой.
// Дописываете к числу В число А. Получаете число W. Находите C= C*W. Первые три цифры результата C,
// будучи поделенными на 1000, дают второе случайное число REZ. Сформируйте 3 случайных чисел по этой схеме.
//========================================================

object Main234 {
  def func(numberString: String): String = {
    var w = 0L
    var z = 0L
    var c = 0L
    var aString = ""
    var bString = ""
    var cString = ""
    var rez: Float = 0.0F

    z = numberString.toLong
    println("z = " + z)
    aString = numberString.substring(0, 5)
    bString = numberString.substring(5, 10)
    println("a = " + aString)
    println("b = " + bString)
    w = (bString + aString).toLong
    println("w = " + w)
    cString = (z * w).toString()

    if(cString.toLong < 0)
      cString = cString.substring(1,11)
    else
      cString = cString.substring(0, 10)

    println("c = " + cString)
    rez = cString.substring(0, 3).toFloat / 1000
    println("rez = " + rez)
    println("-----------------------------")
    cString
  }

  def main(args: Array[String]): Unit = {
    print("Enter the number: ")
    var numberString = "" 
    var flag = 0
    while(numberString.length() != 10 || flag == 1) {
      flag = 0
      numberString = scala.io.StdIn.readLine()
      if (numberString.length() != 10) {
        println("Incorrect number, try again");
      }else {
        for (i <- 0 to 9) {
          if (numberString.charAt(i) < '0' || numberString.charAt(i) > '9') {
            println("Incorrect number, try again");
            flag = 1
          }
        }
      }
    }

    for (i <- 1 to 3) {
      numberString = func(numberString)
    }
  }
}


//========================================================
// Вариант 1
// Построить генератор случайных чисел по следующей схеме. 
// Вводите 10-значное число  с клавиатуры. Формируете два новых целых числа A и B:
// первое  A состоит из первых пяти цифр, второе B  – из последних  цифр введенного числа, начиная с шестой.
// Перемножаете числа A и B друг на друга. 
// Первые три цифры результата С, будучи поделенными на 1000, дают первое случайное число REZ.
// Чтобы сформировать следующее случайное число, прибавляете к Z число  С и повторяете процесс.
// Формируете два новых целых числа A и B: первое  A состоит из первых пяти цифр, второе B  – из последних  цифр числа Z, начиная с шестой.
// Перемножаете числа A и B друг на друга. Первые три цифры результата С, будучи поделенными на 1000, дают второе случайное число.
// Чтобы сформировать следующее случайное число, прибавляете к Z число  С и повторяете процесс. Сформируйте 5 случайных чисел.
// Если z отрицателен, то это значит, что надо заменить первую цифру единицы на ноль и убрать знак “минус”,
// кроме того, нужно поддерживать длину строки не меньше 10 символов. Сказанное, демонстрируется следующим примером:

//========================================================

//одиночный объект
// object Main {
//   // основной метод входа в программу
//   def main(args: Array[String]): Unit = {
//     var startNumber = ""
//     var A = 0
//     var B = 0
//     var C = 0
//     var Z = 0
//     var REZ: Float = 0.0f

//     print("Enter the number: ") // приглашение на ввод числа
//     startNumber = scala.io.StdIn.readLine() // запись числа
//     if (startNumber.length() != 10) { // проверка на количество цифр
//       print("Incorrect number")
//       sys.exit(0)
//     }
//     for (i <- 1 to 5) { // цикл генерации пяти случайных чисел
//       A = startNumber.substring(0, 5).toInt  // выделение подстроки для числа A
//       B = startNumber.substring(5, 10).toInt // выделение подстроки для числа B
//       C = A * B // формирование числа
//       REZ = C
//         .toString()
//         .substring(0, 3)
//         .toFloat / 1000 // получение случайного числа
//       Z += C // для формирования следующего числа
//       println("----------" + "Random number " + i + " ----------:")
//       println("A=" + A)
//       println("B=" + B)
//       println("C=" + C)
//       println("REZ=" + REZ)
//       println("Z=" + Z)
//       if (Z < 0) {
//         Z = ("0" + (Z
//           .toString()
//           .substring(1, Z.toString().length()))).toInt
//       }
//       if (Z.toString().length() < 10) {
//         Z += 1000000000 
//       }
//       startNumber = Z.toString()
//       println("startNumber = " + startNumber + "\n");
//     }
//   }
// }



// object Main234 {
//   val borders = Array[Float](0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0)
//   var countOfNumbers = Array[Int](0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

//   def random(startNumber : Float, begin : Float, end : Float): Float = {
//     return begin + (end - begin) * startNumber
//   }

//   def main(args: Array[String]): Unit = {
//     print("Enter start number (от 0 до 1): ")
//     var startNumber = "" 
//     var count = 0 
//     startNumber = scala.io.StdIn.readLine()
//     println("Enter amount of numbers:")
//     count = scala.io.StdIn.readInt()
//     var i = 1
//     while(count > 0)
//     {
//         if(i > 10)
//         {
//           i = 1
//         }
//         var rand_number = random(startNumber.toFloat, borders(i - 1), borders(i))
//         println(rand_number)
//         count = count - 1
//         i += 1
//         countOfNumbers((rand_number * 10).toInt) += 1
//     }
//     println("\n--------------STATISTICS---------------")
//     for(i <- 1 to 10)
//     {
//       println(i + " -- " + countOfNumbers(i - 1))
//     }
//   }
// }

object Main234 {
  var countOfNumbers = Array[Int](0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

  def random(numberString: String, index: Int): String = {
    var w = 0L
    var z = 0L
    var c = 0L
    var aString = ""
    var bString = ""
    var cString = ""
    var rez: Float = 0.0F

    z = numberString.toLong
    aString = numberString.substring(0, 5)
    bString = numberString.substring(5, 10)
    w = (bString + aString).toLong
    cString = (z * w).toString()

    if(cString.toLong < 0)
      cString = cString.substring(1,11)
    else
      cString = cString.substring(0, 10)

    rez = cString.substring(0, 3).toFloat / 1000
    var i = 0
    var isNotFoundToInsert = false
    
    if(countOfNumbers((rez * 10).toInt) < index / 10 + 1)
    {
      countOfNumbers((rez * 10).toInt) += 1
      isNotFoundToInsert = true
    }


    while(isNotFoundToInsert != true && i < 10)
    {
      if(countOfNumbers(i) < index / 10 + 1)
      {
        rez = ("0." + i.toString() + rez.toString().substring(3, rez.toString().length())).toFloat
        countOfNumbers(i) += 1
        isNotFoundToInsert = true
      }
      i += 1
    }
    println("rez = " + rez)
    println("-----------------------------")
    cString
  }




  def main(args: Array[String]): Unit = {
    print("Enter the number: ")
    var numberString = "" 
    var flag = 0
    while(numberString.length() != 10 || flag == 1) {
      flag = 0
      numberString = scala.io.StdIn.readLine()
      if (numberString.length() != 10) {
        println("Incorrect number, try again");
      }else {
        for (i <- 0 to 9) {
          if (numberString.charAt(i) < '0' || numberString.charAt(i) > '9') {
            println("Incorrect number, try again");
            flag = 1
          }
        }
      }
    }

    for (i <- 1 to 10) {
      numberString = random(numberString, i - 1)
    }
    println("---------STATISTICS----------")
    for(i <- 1 to 10)
    {
      println(i + " -- " + countOfNumbers(i - 1))
    }
  }
}