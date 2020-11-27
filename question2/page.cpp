#include "page.hpp"

#include <algorithm>
#include <assert.h>
#include <stdlib.h>
#include <random>
#include <chrono>
#include <iostream>

int partition(std::vector<Resultat> & arr, int l, int r, std::default_random_engine & generateur)
{
  std::uniform_int_distribution<int> uniforme(l, r);
  const unsigned int s = uniforme(generateur);

  std::swap(arr[r], arr[s]);

  Resultat x = arr[r];
  int i = l;
  for (int j = l; j <= r - 1; j++) {
    if (arr[j] <= x) {
      std::swap(arr[i], arr[j]);
      i++;
    }
  }
  std::swap(arr[i], arr[r]);
  return i;
}

int kthSmallest(std::vector<Resultat> & arr, int l, int r, int k, std::default_random_engine & generateur)
{
  if (k > 0 && k <= r - l + 1) {

    int index = partition(arr, l, r, generateur);

    if (index - l == k - 1)
      return index;

    if (index - l > k - 1)
      return kthSmallest(arr, l, index - 1, k, generateur);

    return kthSmallest(arr, index + 1, r,
                       k - index + l - 1, generateur);
  }
  throw std::exception();
}
void retournePage(const std::vector<Resultat>& resultats_non_tries, unsigned int nombre_resultats_par_page, unsigned int numero_page, std::vector<Resultat>& page) {
  assert(!resultats_non_tries.empty());
  assert(page.empty());
  assert(nombre_resultats_par_page > 0);
  assert(numero_page < (resultats_non_tries.size() + nombre_resultats_par_page - 1) / nombre_resultats_par_page); // (a + b - 1) / b = plafond(a/b)

  std::default_random_engine generateur(std::chrono::system_clock::now().time_since_epoch().count());
  std::vector<Resultat>  resultats(resultats_non_tries);
  int k = nombre_resultats_par_page;
  int p = numero_page;
  unsigned int nombre_resultats = resultats.size();
  const unsigned int nombre_pages = ((nombre_resultats + nombre_resultats_par_page - 1) / nombre_resultats_par_page);
  const unsigned int nombre_resultats_sur_la_page = (numero_page < nombre_pages - 1 || (nombre_resultats % nombre_resultats_par_page == 0))
                                                    ? nombre_resultats_par_page
                                                    : nombre_resultats % nombre_resultats_par_page;
  int index_min = k*p + 1;
  int index_max = index_min + nombre_resultats_sur_la_page;
  if (index_max >= resultats.size()) {
    index_max = resultats.size();
  }

  int index1 = kthSmallest(resultats, 0, resultats.size() - 1, index_min, generateur);
  int index2 = kthSmallest(resultats, index1, resultats.size() - 1, index_max - index1, generateur);

  if (index_max == resultats.size()) {
    page = std::vector<Resultat>(resultats.begin() + index1, resultats.begin() + index2 + 1);
  }
  else {
    page = std::vector<Resultat>(resultats.begin() + index1, resultats.begin() + index2);
  }
  std::sort(page.begin(), page.end());
}
