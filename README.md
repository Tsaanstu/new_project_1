#***Новый_план_1*** игры ***Новый_текстовый_квест_1*** от команды ***Новая_команда_1.***
=====================



Состав команды:
-----------------------------------
1) [Ира (капитан команды)](https://park.mail.ru/profile/i.nikiforova/)

2) [Вова](https://park.mail.ru/profile/v.atasunts/)

3) [Кирилл](https://park.mail.ru/profile/k.smetankin/)

4) [Надя](https://park.mail.ru/profile/n.merkulova/)

**Архитектура проекта состоит из двух частей:**

**I** - основная архитектура игры - текстовый квест

**II** - встроенные мини-игры - 2D игры

Игра состоит из четырех уровней. Переходы с одного уровня на другой сопровождается прохождением соответствующей мини-игры. Переход может осуществляться не по порядку.

***

**Предворительный план выполнения:**

* **1 неделя.**

	1. Доработать сюжет игры и сценарий первого уровня

	2. Начало реализации первого уровня игры

    3. Разработать базовую архитектуру - Ира и Вова

    4. Начало создания первой мини-игры - викторина - Кирилл 

	5. Начало создания второй мини-игры - аналог Pacman / Лабиринт - Вова

    6. Объединение написанных модулей

    P.S. К концу недели мини-игры должны находится в состоянии "запускаются, не полностью реализованы"

* **2 неделя.**

	1. Корректировка логики, завершение первого уровня игры

    2. Сценарий второго уровня

    3. Начало реализации второго уровня

	4. Начало создания 3 мини-игры - аналог Flappy Bird - Надя

	5. Объединение написанных модулей

	6. Окончание работы над 1 и 2 мини-игрой


* **3 неделя.**

	1. Возможная корректировка логики, исправление багов, завершение второго уровня игры

    2. Сценарий третьего уровня

    3. Начало реализации третьего уровня

	4. Окончание работы над 3 мини-игрой

	5. Объединение написанных модулей

	6. Возможно написание четвертой мини-игры (если будем успевать по времени)


* **4 неделя.**

	1. Завершение третьего уровня игры, исправление багов

    2. Сценарий четвертого уровня

    3. Реализация четвертого уровня

 	4. Объединение написанных модулей

	5. Общие доработки и завершение проекта

***

**Распределение обязанностей:**

* [Ира](https://park.mail.ru/profile/i.nikiforova/) - сценарий, базовая архитектура, меню

* [Вова](https://park.mail.ru/profile/v.atasunts/) - базовая архитектура, хранение данных, игра типа "Лабиринт"

* [Кирилл](https://park.mail.ru/profile/k.smetankin/) - игра типа "Викторина", хранение данных

* [Надя](https://park.mail.ru/profile/n.merkulova/) - игра типа "Flappy bird", сценарий


***

**update 08.04.2018**

Проект разбивается на составные части таким образом, что есть Makefile и папка project, в ней main_game, mini_game_1, mini_game_2 ...

В каждой такой папке есть src, include + где нужно fonts, audio, img ...

Команды хранятся целиком в массиве или map, главные текстовые поля считываются из файла и записываются в свой map

Файлы с главными текстами называются в соответствии со сценарием в формате "номеруровня.номерветки.txt"

Все мини-игры имеют такой интерфейс: bool mini_game_N(Player& player), где N - номер игры

Карта 5 х 5, мини-игры встречаются в определенных клетках (при определенных условиях ?) 

Пока решено оформить все в одном стиле 8bit(?), ч\б и сделать 4 уровня

***

**Возможные варианты героев:**

ведьма

дракон

гномы

скелет

эльфы ?

гоблин ?

рыцари ?



