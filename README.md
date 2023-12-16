# CPSC 525 Final Project: CWE 111 Example

## Usage

`make` to build the program

`make run` to run the program for "normal usage".

`make run-exploit` to run the program with the exploit.

## Description

A company has a system for managing the compensation of each employee. There is an HR system which keeps track of how much each employee should get paid, and this stores its data in CSV file `hr-compensation.csv`. There is also an accounting system, which needs the employee names and compensation amounts in a double space separated format. So the company has written a program to convert the HR system's data to the accounting system format, and the boss decided it was super important that this program runs as fast as possible, so the developer wrote most of the program in Java and some of it in C, and used JNI to call the C code. This works most of the time (`make run`), converting the HR CSV to double space separated format.

However, John the intern was tired of not getting paid anything, and he realized that the C code was vulnerable to a buffer overflow as it copied the employee names to a buffer, assuming that the names were not longer than 5 characters long. Normally, the HR system's UI would ensure this condition, but John also realized the HR system's data was stored in a file with global read and write permissions. So John decided to give himself a little pay by circumventing the HR UI and making his name 7 characters long ("Johnnnn", `make run-exploit`). This has the effect of overflowing the name buffer into the compensation variable's address with the character "n", giving him $110 in compensation.

Now John has managed to inconspicuously give himself some pay, and he can theoretically change his compensation arbitrarily by changing his name (if he had directly changed his compensation amount, the bosses might have noticed that in the HR UI ¯\_(ツ)_/¯).
