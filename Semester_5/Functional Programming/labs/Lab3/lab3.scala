//========================================================
// ЛАБОРАТОРНАЯ РАБОТА №3. Работа со строками
// Вариант 2
// 1.	Дан текст: "1+1=2". С помощью техники регулярных выражений заменить цифры на слова: 1 - one, 2 - two.
// 2.	Найти в тексте "Being quit buetiful girl she never thought of buety" все слова, начинающиеся на bue.
// 3.	В тексте "one plus one is something" заменить one на two.
// 4.	Поменять местами первое и последнее слово в тексте world is nice.
// 5.	Дан текст: "Hello to all my friends". Выбросить все согласные.
// 6.   Дан текст: "Hello to everybody". Удалить каждую вторую букву в слове.
// 7.   Дан текст: "Hello to everybody". Удалить все вхождения буквы е.
// 8.   Дан текст: "Be healthy". Вставить слова always, чтобы получить "Be always healthy".

import scala.util.matching.Regex

object Main1 {
  def main(args: Array[String]): Unit = {
    var str = "1+1=2"
    println("Start string: " + str);
    val pattern1 : Regex = "1".r
    val pattern2 : Regex = "2".r
    str = pattern1.replaceAllIn(str, "one");
    str = pattern2.replaceAllIn(str, "two");
    println("Result string: " + str);
  }
}

object Main2 {
  def main(args: Array[String]): Unit = {
    var str = "Being quit buetiful girl she never thought of buety"
    println("String: " + str);
    val pattern = "\\bbue\\w*".r
    var result = pattern.findAllIn(str).toList.mkString(", ")
    println(result)

  }
}


object Main3 {
  def main(args: Array[String]): Unit = {
    var str = "one plus one is something"
    println("Start string: " + str);
    val pattern : Regex = "one".r
    str = pattern.replaceAllIn(str, "two");
    println("Result string: " + str);
  }
}


object Main4 {
  def main(args: Array[String]): Unit = {
    var str = "world is nice"
    println("Start string: " + str);
    var words = str.split(" ")
    val pattern1: Regex = words.head.r
    val pattern2: Regex = words.last.reverse.r
    str = pattern1.replaceFirstIn(str, words.last)
    str = pattern2.replaceFirstIn(str.reverse, words.head.reverse)
    println("Result string: " + str.reverse);
  }
}


object Main5 {
  def main(args: Array[String]): Unit = {
    val str = "Hello to all my friends"
    println("Start string: " + str);
    val vowelsPattern = "[^eyuioaEYUIOA ]".r
    val result = vowelsPattern.replaceAllIn(str, "")
    println("String without consonants: " + result)
  }
}


object Main6 {
  def main(args: Array[String]): Unit = {
    val str = "Hello to everybody"
    println("Start string: " + str);
    val words = str.split(" ")
    val lastWord = words.reverse.head
    //var result = List("")
    val result = str.replaceAll("(.)\\w?", "$1")

    //words.map(word => {
    //    val filterStr = word.zipWithIndex.filter(_._2 % 2 == 0).map(_._1).mkString
    //    result = result :+ filterStr
    //})
    println("String without every second letter:" + result)//.mkString(" "))
  }
}


object Main7 {
  def main(args: Array[String]): Unit = {
    val str = "Hello to everybody"
    println("Start string: " + str);
    val pattern: Regex = "e".r
    val result = pattern.replaceAllIn(str, "")
    println("String without letter 'e': " + result)
  }
}


object Main8 {
  def main(args: Array[String]): Unit = {
    val str1 = "Be healthy"
    val str2 = "always"
    println("Start string: " + str1);
    val words = str1.split(" ")
    val result = words(0) + " " + str2 + " " + words(1)
    println("Result string: " + result)
  }
}


object dop1 {
  def main(args: Array[String]): Unit = {
    val str = "mother"
    val pattern = "t".r
    println("Start string: " + str);
    val result = pattern.replaceAllIn(str, "ttt")
    println("Result string: " + result)
  }
}


object dop2 {
  def main(args: Array[String]): Unit = {
    val str = "one and two"
    val pattern = " ".r
    println("Start string: " + str);
    val result = pattern.replaceAllIn(str, "")
    println("Result string: " + result)
  }
}
