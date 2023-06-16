/** Implementation of functions for a gradebook.
@file grades.cpp
@author Angel Fuentes
*/

#include "grades.h"
#include "lib/statistics.h"
using namespace std;

bool is_valid(int n_students, int n_hws) {
  return n_students > 0 && n_students <= MAX_S && n_hws > 0 && n_hws <= MAX_HW;
}

int student_average(const int grades[MAX_S][MAX_HW], int n_students, int n_hws,
                    int student_id) {
  if (!is_valid(n_students, n_hws) || student_id < 0 ||
      student_id >= n_students) {
    return -1;
  }

  return average(grades[student_id], n_hws);
}

int top_score_student(const int grades[MAX_S][MAX_HW], int n_students,
                      int n_hws) {
  if (!is_valid(n_students, n_hws)) {
    return -1;
  }

  int top = -1;
  int top_avg = -1;
  for (int i = 0; i < n_students; i++) {
    int avg = student_average(grades, n_students, n_hws, i);
    if (i == 0 || avg > top_avg) {
      top_avg = avg;
      top = i;
    }
  }

  return top;
}

void hw_stats(const int grades[MAX_S][MAX_HW], int n_students, int n_hws,
              int hw_id, int& min, int& max, int& med, int& avg) {
  if (!is_valid(n_students, n_hws) || hw_id < 0 || hw_id >= n_hws) {
    return;
  }

  int scores[MAX_S];
  for (int i = 0; i < n_students; i++) {
    scores[i] = grades[i][hw_id];
  }

  all_stats(scores, n_students, min, max, med, avg);
}
