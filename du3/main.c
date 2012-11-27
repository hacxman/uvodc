// author: maros zatko, uco: 323830
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct {
  int *data;
  int m, n;
} Mat;

const RAD = 1;
const SLO = 2;
const NUL = 4;
const CTV = 8;
const ONE = 16;
const DIA = 32;
const DTR = 64;
const HTR = 128;
const SYM = 256;


int is_one(int *data, int m, int n) {
  // jednotkova?
  int i = 0;
  int j = 0;
  while (i < m*n) {
    if (i == j) {
      j += n+1; // dovidenia o dlzku riadku + 1
      if (data[i] != 1) break;
    } else {
      if (data[i] != 0) break;
    }
    i++;
  }
  return (i >= m*n) * ONE;
}

int is_diag(int *data, int m, int n) {
  // diag
  int i = 0;
  int j = 0;
  while (i < m*n) {
    if (i == j) {
      j += n+1; // dovidenia o dlzku riadku + 1
    } else {
      if (data[i] != 0) break;
    }
    i++;
  }
  return (i >= m*n) * DIA;
}

int is_uptr(int *data, int m, int n) {
  // horna trojuh.
  int i = n;
  int j = n;
  while (i < m*n) {

    if (data[i] != 0) break;

    if (i == j) {
      i += n - (j % n);
      j += n+1;
    }
    i++;
  }
  return (i >= m*n) * HTR;
}

int is_downtr(int *data, int m, int n) {
  // dolan
  int i = 1;
  int j = n-1;
  while (i < m*n) {

    if (data[i] != 0) break;

    if (i == j) {
      j += n;
      i += n - (i % n) + 1;
    }
    i++;
  }
  return (i >= m*n) * DTR;
}

int is_sym(int *data, int m, int n) {
  int i = 0, j = 0;
  // sym
  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      if (data[i*n+j] != data[j*n+i])
        break;
    }
  }
  return (i >= n && j >= m) * SYM;
}

int classify(Mat *mat) {
  int flags = 0;
  int m = mat->m, n = mat->n;
  int *data = mat->data;
  if (m == 1) flags |= RAD;
  if (n == 1) flags |= SLO;
//  if ((flags & SLO) && (flags & RAD)) flags |= ;
  if (m == n) {
    flags |= CTV;

    int i = 0;
    while (data[i] == 0 && i++ < m*n);
    flags |= (i >= m*n) * NUL;

    flags |= is_one(data, m, n);
    flags |= is_diag(data, m, n);
    flags |= is_uptr(data, m, n);
    flags |= is_downtr(data, m, n);
    flags |= is_sym(data, m, n);
  }

  return flags;
}


int main(void) {
  Mat *mat = malloc(sizeof(Mat));
  mat->m = 0; mat->n = 0;

  do {
    printf("m x n:");
    if (scanf("%d %d", &mat->m, &mat->n) == 2) {
      break;
    }
    printf("chyba vstupu\n");
    while (getchar() != '\n');

  } while(1);

  mat->data = malloc(sizeof(int) * mat->m * mat->n);
  int j = 0;
  while (j++ < mat->m*mat->n) {
    scanf("%d", &(mat->data[j-1]));
  }

  int flags = classify(mat);
  if (flags & RAD) printf(" radkova");
  if (flags & SLO) printf(" sloupcova");
  if (flags & NUL) printf(" nulova");
  if (flags & CTV) printf(" ctvercova");
  if (flags & ONE) printf(" jednotkova");
  if (flags & DIA) printf(" diagonalni");
  if (flags & DTR) printf(" dolni-trojuhelnikova");
  if (flags & HTR) printf(" horni-trojuhelnikova");
  if (flags & SYM) printf(" symetricka");
  if (!flags) printf("zadana vlastnost");
  printf("\n");

}
