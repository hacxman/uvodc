#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct {
  int *data;
  int m, n;
} Mat;

void mat_print(Mat *mat) {
  printf();
}

bool mat_eql(Mat *m1, Mat m2) {
  if (m1->m != m2->m || m1->n != m2->n)
    return false;

  int i = 0;
  while (m1->data[i] == m2->data[i])
    i++;

  return i == m1->m * m1->n;
}

const RAD = 1;
const SLO = 2;
const NUL = 4;
const CTV = 8;
const ONE = 16;
const DIA = 32;
const DTR = 64;
const HTR = 128;
const SYM = 256;


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
    flags |= (i == m*n) * NUL;

    // jednotkova?
    i = 0;
    while (i++ < m*n) {
      int j = 0;
      if (i == j) {
        j += n+1; // dovidenia o dlzku riadku + 1
        if (data[i] != 1) break;
      } else {
        if (data[i] != 0) break;
      }
    }
    flags |= (i >= m*n) * ONE;

    // diag
    i = 0;
    while (i++ < m*n) {
      int j = 0;
      if (i == j) {
        j += n+1; // dovidenia o dlzku riadku + 1
      } else {
        if (data[i] != 0) break;
      }
    }
    flags |= (i >= m*n) * DIA;

    // horna trojuh.
    i = 0;
    while (i++ < m*n) {
      int j = 0;

      if (data[i] != 0) break;

      if (i == j) {
        i += n+1;
        j += n - (j % n);
      }
    }
    flags |= (i >= m*n) * HTR;

    // dolan
    i = 0;
    while (i++ < m*n) {
      int j = 0;

      if (data[i] != 0) break;

      if (i == j) {
        j += n+1;
        i += n - (j % n);
      }
    }
    flags |= (i >= m*n) * DTR;

    // sym
    for (i = 0; i < n; i++) {
      for (j = 0; j < m; j++) {
        if (data[i*n+j] != data[j*n+i])
          break;
      }
    }
    flags |= (i >= n) * DTR;

  }

  return flags;
}

int main(void) {
  Mat *mat = malloc(sizeof(Mat));
  mat->m = 0; mat->n = 0;

  printf("m x n:");
  scanf("%d %d", &mat->m, &mat->n);

  int j = 0;
  while (j++ < mat->m*mat->n) {
    scanf("%d", &mat->data[j]);
  }

  int flags = classify(mat);
  if (flags &= RAD) printf(" radkova");
  if (flags &= SLO) printf(" sloupcova");
  if (flags &= NUL) printf(" nulova");
  if (flags &= CTV) printf(" ctvercova");
  if (flags &= ONE) printf(" jednotkova");
  if (flags &= DIA) printf(" diagonalni");
  if (flags &= DTR) printf(" dolni trojuhelnikova");
  if (flags &= HTR) printf(" horni trojuhelnikova");
  if (flags &= SYM) printf(" symetricka");
  printf("\n");

}
