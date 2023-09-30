#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <math.h>

#include "dequef.h"

// Diminui o vetor dinamico do deque dado, para t / r
void diminuiVetor(dequef* D) {
  float* novoVetorData = malloc(sizeof(float) * ceil(D->cap / D->factor));

  if(!novoVetorData) {
    for (int i = 0; i < D->size; i++) {
    *(novoVetorData + i) = *(D->data + ((i + D->first) % D->cap));
    }

    free(D->data);
    D->first = 0;
    D->data = novoVetorData;
    D->cap = ceil(D->cap / D->factor);
  }
}

int aumentarVetor(dequef* D) {
  float* novoVetorData = malloc(sizeof(float) * ceil(D->cap * D->factor));

  if(!novoVetorData)
    return 0;

  for (int i = 0; i < D->size; i++) {
    *(novoVetorData + i) = *(D->data + ((i + D->first) % D->cap));
  }

  free(D->data);
  D->first = 0;
  D->data = novoVetorData;
  D->cap = ceil(D->cap * D->factor);

  return 1;
}

/**
   Create an empty deque of floats.

   capacity is both the initial and minimum capacity.
   factor is the resizing factor, larger than 1.0.

   On success it returns the address of a new dequef.
   On failure it returns NULL.
**/
dequef* df_alloc(long capacity, double factor) {
    dequef* novoDeque = malloc(sizeof(dequef));
    if (novoDeque == NULL)
      return NULL;

    novoDeque->data = malloc(sizeof(float) * capacity);
    if (novoDeque->data == NULL)
      return NULL;

    novoDeque->first = -1;
    novoDeque->size = 0;
    novoDeque->cap = capacity;
    novoDeque->mincap = capacity;
    novoDeque->factor = factor;

    return novoDeque;

}

/**
  Release a dequef and its data.
**/
void df_free(dequef* D) {
  free(D->data);
  free(D);
}

/**
   The size of the deque.
**/
long df_size(dequef* D) {
  return D->size;
}

/**
   Add x to the end of D.

   If the array is full, it first tries to increase the array size to
   capacity*factor.

   On success it returns 1.
   If attempting to resize the array fails then it returns 0 and D remains unchanged.
**/
int df_push(dequef* D, float x) {
  if (D->size == D->cap) {
    if (!aumentarVetor(D))
      return 0;
  } 
  
  if (D->first == -1) {
    *(D->data) = x;
    D->first = 0;
  } else {
    *(D->data + ((D->first + D->size) % D->cap)) = x;
  }
  D->size += 1;

  return 1;
}

/**
   Remove a float from the end of D.

   If the deque has capacity/(factor^2) it tries to reduce the array size to
   capacity/factor.  If capacity/factor is smaller than the minimum capacity,
   the minimum capacity is used instead.  If it is not possible to resize, then
   the array size remains unchanged.

   This function returns the float removed from D.
   If D was empty prior to invocation, it returns 0.0 and D remains unchanged.
**/
float df_pop(dequef* D) {
  if (D->size != 0) {
    float valorUltimoIndice = *(D->data + ((D->first + D->size - 1) % D->cap));
    D->size -= 1;
    if (ceil(D->cap / (D->factor * D->factor)) == D->size && D->cap / D->factor < D->mincap)
      diminuiVetor(D);
    return valorUltimoIndice;
  } else {
   return 0;
  }
}

/**
   Add x to the beginning of D.

   If the array is full, it first tries to increase the array size to
   capacity*factor.

   On success it returns 1.
   If attempting to resize the array fails then it returns 0 and D remains unchanged.
**/
int df_inject(dequef* D, float x) {
  if (D->size == D->cap) {
    if (!aumentarVetor(D))
      return 0;
  } 
  
  if (D->first == -1) {
    *(D->data) = x;
    D->first = 0;
  } else if (D->first == 0) {
    *(D->data + (D->cap - 1)) = x;
    D->first = (D->cap - 1);
  } else {
    *(D->data + (D->first - 1)) = x;
    D->first = (D->first - 1);
  }
  D->size += 1;

  return 1;
}

/**
   Remove a float from the beginning of D.

   If the deque has capacity/(factor^2) elements, this function tries to reduce
   the array size to capacity/factor.  If capacity/factor is smaller than the
   minimum capacity, the minimum capacity is used instead.

   If it is not possible to resize, then the array size remains unchanged.

   This function returns the float removed from D.
   If D was empty prior to invocation, it returns 0.0 and D remains unchanged.
**/
float df_eject(dequef* D) {
  if (D->size != 0) {
    float valorPrimeiroIndice = *(D->data + D->first);
    if (D->first + 1 == D->cap) {
      D->first = 0;
    } else {
      D->first += 1;
    }
    D->size -= 1;
    if (ceil(D->cap / (D->factor * D->factor)) == D->size && D->cap / D->factor < D->mincap)
      diminuiVetor(D);
    return valorPrimeiroIndice;
  } else {
   return 0;
  }
}

/**
   Set D[i] to x.

   If i is not in [0,|D|-1]] then D remains unchanged.
**/
void df_set(dequef* D, long i, float x) {
  *(D->data + ((i + D->first) % D->cap)) = x;
}

/**
   Return D[i].

   If i is not in [0,|D|-1]] it returns 0.0.
**/
float df_get(dequef* D, long i) {
  return *(D->data + ((i + D->first) % D->cap));
}

/**
   Print the elements of D in a line.
**/
void df_print(dequef* D) {
  printf("deque (%ld): ", D->size);
  for (int i = 0; i < D->size; i++) {
    printf("%.1f ", *(D->data + ((i + D->first) % D->cap)));
  }
  printf("\n");
}

int main(void) {

  char cmd[13];
  float f;
  int i, st = 1;
  dequef* D = NULL;

  while (1) {
    scanf("%s",cmd);

    if (strcmp(cmd,"create") == 0) {
      scanf("%i %f",&i,&f);

      if (D != NULL)
        df_free(D);

      D = df_alloc(i,f);
      if (!D) {
        printf("Unable to create a dequef.\n");
        return errno ? errno : 1;
      }
    }

    else if (strcmp(cmd,"push") == 0) {
      scanf("%f",&f);
      st = df_push(D,f);
    }

    else if (strcmp(cmd,"pop") == 0) {
      if (df_size(D) > 0)
        f = df_pop(D);
    }

    else if (strcmp(cmd,"inject") == 0) {
      scanf("%f",&f);
      st = df_inject(D,f);
    }

    else if (strcmp(cmd,"eject") == 0) {
      if (df_size(D) > 0)
        f = df_eject(D);
    }

    else if (strcmp(cmd,"set") == 0) {
      scanf("%i %f",&i,&f);
      if (i >= 0 && i < df_size(D))
        df_set(D,i,f);
    }

    else if (strcmp(cmd,"get") == 0) {
      scanf("%i",&i);
      if (i >= 0 && i < df_size(D)){
        printf("D[%d] == %.1f\n",i,df_get(D,i));
      }
    }

    else if (strcmp(cmd,"is-empty?") == 0) {
      if (df_size(D) == 0)
        printf("empty\n");
      else
        printf("not empty\n");
    }

    else if (strcmp(cmd,"print") == 0) {
      df_print(D);
    }

    else if (strcmp(cmd,"exit") == 0) {
      df_free(D);
      return 0;
    }

    else {
      printf("Ups! invalid command: %s.\n",cmd);
      df_free(D);
      return 1;
    }

    if (st == 0) {
      printf("Unable to resize.");
      df_free(D);
      return errno ? errno : 1;
    }
  }
}