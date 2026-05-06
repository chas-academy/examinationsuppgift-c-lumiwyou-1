/**
 * @file main.c
 * @author Lumi Hyväri <lumi.hyvari@gmail.com>
 * @brief Elevhanteringssystem som hanterar 5 elever och deras resultat från 13 olika prov under ett läsår.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define STUDENTS_COUNT 5
#define MAX_NAME_LENGTH 10
#define SCORES_COUNT 13
#define MAX_SCRORE 10

//#define MIN_UPPERCASE 65
//#define MAX_UPPERCASE 90
#define MIN_UNDERCASE 97
#define MAX_UNDERCASE 122

/// @brief Innehåller studentresultat
typedef struct {
    char name[MAX_NAME_LENGTH];
    int scores[SCORES_COUNT];
    int sum;
    int average;
} StudentResult;

/// @brief Läser in studentresultat från `stdin`
/// @param student Pekare till `student` variabel att lagra i
void read_a_student(StudentResult * student) {
    scanf("%10s", &student->name);
    for(int s = 0; s < SCORES_COUNT; s++) {
        scanf("%d", &student->scores[s]);
    }
}

/// @brief Gör stor begynnelsebokstav
/// @param student Pekare till `student` variabel vars namnfält ska modifieras
void capitalize_name(StudentResult * student) {
    // Kontrollera om undercase
    if(student->name[0] >= MIN_UNDERCASE && student->name[0] <= MAX_UNDERCASE) {
        student->name[0] -= 32;
    }
}

/// @brief Beräkna summa och genomsnitt
/// @param student Pekare till `student` variabel att modifiera summa- och genomsnittsfält
void calculate_values(StudentResult * student) {
    // Beräkna summa av poäng
    student->sum = 0;
    student->average = 0;
    for(int s = 0; s < SCORES_COUNT; s++) {
        student->sum += student->scores[s];
    }
    // Beräkna medelpoäng
    student->average = student->sum / SCORES_COUNT;
}

/// @brief Hitta student med högsta genomsnitt
/// @param students Pekare till `student` variabel att iterera
/// @return Pekare till `student` som har högst genomsnitt
StudentResult * get_highest_average(StudentResult * students) {
    // `best_student` är per default satt som första element i `students`
    StudentResult * best_student = &students[0];
    for(int s = 0; s < STUDENTS_COUNT; s++) {
        if(students[s].average > best_student->average) {
            best_student = &students[s];
        }
    }
    return best_student;
}

/// @brief Beräknar det totala genomsnittet av alla studenter
/// @param students Pekare till `student` variabel att iterera
/// @return Totala genomsnittet av alla studenter
int calculate_total_average(StudentResult * students) {
    int total_sum = 0;
    int total_average = 0;
    for(int s = 0; s < STUDENTS_COUNT; s++) {
        total_sum += students[s].average;
    }
    return total_average = total_sum / STUDENTS_COUNT;
}

int main(void) {
    /**
     * Genomför olika steg där studenter inhämtas från `stdin`, korrigeras, värden beräknas, och utvärderingar görs 
     * där resultat från varje steg skrivs ut i `stdout`.
     */
    // Läs in studenter och deras poäng
    StudentResult students[STUDENTS_COUNT];
    //memset(students, 0, sizeof(students));

    // Iterera och inhämta studenter
    for(int s = 0; s < STUDENTS_COUNT; s++) {
        StudentResult * current_student = &students[s];
        read_a_student(current_student);
        capitalize_name(current_student);
        calculate_values(current_student);
    }

    // Utvärdera vilken elev som har högst genomsnitt
    StudentResult * best_student = get_highest_average(students);
    printf("%s\n", best_student->name);

    // Beräkna total genomsnittet för alla studenter
    float total_average = calculate_total_average(students);

    // Loopa genom alla studenter och kontrollera vilka som är under snittet
    for(int s = 0; s < STUDENTS_COUNT; s++) {
        if(students[s].average < total_average) {
            printf("%s\n", students[s].name);
        }
    }
}