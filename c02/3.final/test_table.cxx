///
/// test_table.cxx
///

#include "names.h"
#include "stochastic.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// horror: solo hay un departmento!
// Pilas! Los horrores son senales para que Uds mejoren el programa
// deberian tener por lo menos media docena de departamentos
const char *dept[] = {
  "Ingenieria de Computacion", "Ingeniería en Electrónica", "Ingeniería en Geofísica", "Ingeniería de Materiales",
  "Ingeniería en Producción", "Ingeniería en Mecánica", "Licenciatura en Física"
};

struct Student {
  const char *sid;
  int cohort;
  const char *name;
  const char *dept;
  float gpa;
};

// random student constructor
static Student *random_student() {
  // prep for sid, cohort, gpa
  const int oldest = 2000;
  const int recent = 2020;
  const int delta = 654321 / (recent - oldest);
  const int cohort = random_int(oldest, recent + 1);
  const int number = random_int(1, delta);
  const int random_num = random_int(0, 7);
  const int NB = 16; // buffer size
  const double gpa = random_int(310, 495)/100.0;
  // usando la tecnica del snprintf otra vez (vean names.cxx)
  char buffer[NB]; // buffer to construct sid
  snprintf(buffer, NB, "%02d-%06d", cohort % 100, number);
  const char *sid = strdup(buffer);

  // allocate memory for the student and initialize fields
  Student *student = (Student *) malloc(sizeof(Student));
  student->sid = sid;
  student->cohort = cohort;
  student->name = random_name();
  student->dept = dept[random_num];
  student->gpa = gpa;
  return student;
}

// genera un archivo con N estudiantes "aleatorios"
static int generate_file(int N, const char *filename) {
  FILE *file = fopen(filename, "w");
  for (int i = 0; i < N; ++i) {
    Student *s = random_student();
    fprintf(file, "%s, %d, %s, %s, %4.2f\n", s->sid, s->cohort, s->name, s->dept, s->gpa);
    free(s); 
  }
  fclose(file);
  return 0;
}


static int NS = 0;
static const int CAPACITY = 10000;
static Student *student[CAPACITY];

// funcion privada: agrega un estudiante al arreglo, si hay espacio disponible
static void add_student(Student *s) {
  if (NS < CAPACITY) {
    student[NS] = s;
    ++NS;
  } else {
    fprintf(stderr, "No se pudo agregar %s: no hay capacidad", s->sid);
  }
}

static int load_file(const char *filename) {
  FILE *file = fopen(filename, "r");
  for (int i = 0; i<CAPACITY; ++i) {
    Student *s = (Student *) malloc(sizeof(Student));
    char sid[16], f[12], m[6], l[12], t[16], c[3], r[16], dept[128], cohort[6], gpa[5], name[64];
    fscanf(file, "%s %s %s %s %s %s %s %s %s", sid, cohort, f, m, l, t, c, r, gpa);
    if (feof(file)) {
      break;
    }
    for (int j = 0; j < sizeof(sid)/sizeof(sid[0]); ++j) {
      if (sid[j] == ',' || sid[j] == ' ') {
        sid[j] = '\0';
      }
    }
    for (int k = 0; k < sizeof(cohort)/sizeof(cohort[0]); ++k) {
      if (cohort[k] == ',') {
        cohort[k] = '\0';
      }
    }
    for (int q = 0; q < sizeof(l)/sizeof(l[0]); ++q) {
      if (l[q] == ',') {
        l[q] = '\0';
      }
    }
    for (int q = 0; q < sizeof(r)/sizeof(r[0]); ++q) {
      if (r[q] == ',') {
        r[q] = '\0';
      }
    }
    snprintf(name, 64, "%s %s %s", f, m, l);
    snprintf(dept, 128, "%s %s %s", t, c, r);
    s->sid = strdup(sid);
    s->name = strdup(name);
    char *ptr;
    s->cohort = (int) strtol(strdup(cohort), &ptr, 10);
    s->dept = strdup(dept);
    s->gpa =  strtod(strdup(gpa), NULL);
    add_student(s);
    fprintf(stdout, "%s, %d, %s, %s, %f \n", s->sid, s->cohort, s->name, s->dept, s->gpa);
    free(s);
  }
  fclose(file);
  fprintf(stdout, "Cargamos %d estudiantes \n", NS);
  return 0;
}

int find_min_student(int i, int j, Student *s[]) {
  int mindx = i;
  Student *min = s[mindx];
  for (i; i<j; ++i) {
    if (strcmp((const char *) min->sid, (const char *) s[i]->sid)>0) {
      mindx=i;
      min=s[mindx];
    }
  }
  return mindx;
}

// ordena un arreglo de estudiantes ...
// de hecho cualquier arreglo de apuntadores a estudiantes (convenzanse!)
static void sort(int N, Student *s[]) {
  for (int i=0; i<N; ++i) {
    int mindx= find_min_student(i, N, s);
    Student *tmp=s[i];
    s[i]=s[mindx];
    s[mindx]=tmp;
  }
}

// salvar los estudiantes en memoria, escribiendolos en un archivo
static int save_file(int N, Student *s[], const char *filename) {
  FILE *file = fopen(filename, "w");
  for (int i = 0; i < N; ++i) {
    Student *m = s[i];
    fprintf(file, "%s, %d, %s, %s, %f\n", m->sid, m->cohort, m->name, m->dept, m->gpa);
    free(s);
  }
  fclose(file);
  return 0;
}

static int sort_file(const char *filename) {
  load_file(filename);
  sort(NS, student); // <<< ven la maravilla, solo usamos los primeros NS elementos
  save_file(NS, student, filename);
}

int test_table(int argc, const char *argv[]) {
  if (argc == 2) {
    // prueba rapida del generador de nombres
    for (int i = 0; i < 32; ++i) {
      fprintf(stdout, "%s\n", random_name());
    }
    return 0;
  }

  if (strcmp(argv[2], "gen") == 0) {
    int N = (4 <= argc ? atoi(argv[3]) : 32);
    const char *filename = (5 <= argc ? argv[4] : "students.txt");
    int status = generate_file(N, filename);
    return status;
  }

  if (strcmp(argv[2], "load") == 0) {
    const char *filename = (4 <= argc ? argv[3] : "students.txt");
    int status = load_file(filename);
    return status;
  }

  if (strcmp(argv[2], "sort") == 0) {
    const char *filename = (4 <= argc ? argv[3] : "students.txt");
    int status = sort_file(filename);
    return status;
  }
}
