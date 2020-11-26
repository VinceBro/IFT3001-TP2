#include "page.hpp"

#include <algorithm>
#include <assert.h>
#include <stdlib.h>
#include <random>
#include <chrono>
#include <iostream>

void effaceMoi(const std::vector<Resultat> resultats) {
  // Cette fonction a deux utilites:
  //  1) Vous prouver qu'on peut declarer et implementer de nouvelles
  //  	 fonctions dans un .cpp sans les declarer dans le fichier .hpp
  //  	 (que vous ne devez pas modifier)
  //  2) Vous faire réaliser que cette fonction qui ne semble rien faire
  //     s'exécute en fait en Theta(n) puisque le vecteur est copie
  //     (il n'est pas passe par reference)
  //  Maintenant que vous le savez, vous pouvez effacer cette fonction.
}
//int partition(std::vector<Resultat>& nums, int lo, int hi, std::default_random_engine & generateur) {
//  std::uniform_int_distribution<int> uniforme(lo, hi);
//  const unsigned int s = uniforme(generateur);
//  Resultat val = nums[s];                 // pivot
//  std::swap(nums[s], nums[hi]);           // move to last position
//  int res = lo;                        // The smallest index which is larger than pivot
//  for(int i = lo; i < hi; i++) {
//    if(val < nums[i])
//      std::swap(nums[res++], nums[i]);
//  }
//  std::swap(nums[res], nums[hi]);
//  return res;
//}
//int partition(std::vector<Resultat>& A, int l, int r, std::default_random_engine & generateur) {
//  assert(l<=r);
//  assert(r != -1);
//  assert(l != -1);
//  std::uniform_int_distribution<int> uniforme(l, r);
//  const unsigned int s = uniforme(generateur);
//  Resultat p = A[s];
//  int i = l;
//
//  for(int j = l; j < r; j++) {
//    if (A[j] < p) {
//      std::swap(A[i], A[j]);
//      i++;
//    }
//  }
//
//  std::swap(A[i], A[s]);
//  return i;
//}
//Resultat selection(std::vector<Resultat>&  A, int l, int r, int k, std::default_random_engine & generateur) {
//    int index = partition(A, l, r, generateur);
//
//    if (index == k - 1)
//      return A[index];
//
//   if (index> k - 1)
//      return selection(A, l, index - 1, k, generateur);
//
//    return selection(A, index + 1, r,
//                       k, generateur);
//}
//int selection(std::vector<Resultat>& A,int l, int r, int k, std::default_random_engine & generateur) {
//  int order = A.size() - k; // reuslt position
//  while(r > l) {
//    int idx = partition(A, l, r, generateur);
//    if(idx == order)
//      return idx;
//    else if(idx > order)
//      r = idx - 1;
//    else
//      l = idx + 1;
//  }
//  return r;
//}
int partition(std::vector<Resultat> & arr, int l, int r)
{
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
int kthSmallest(std::vector<Resultat> & arr, int l, int r, int k)
{
  // If k is smaller than number of
  // elements in array
  if (k > 0 && k <= r - l + 1) {

    // Partition the array around last
    // element and get position of pivot
    // element in sorted array
    int index = partition(arr, l, r);

    // If position is same as k
    if (index - l == k - 1)
      return index;

    // If position is more, recur
    // for left subarray
    if (index - l > k - 1)
      return kthSmallest(arr, l, index - 1, k);

    // Else recur for right subarray
    return kthSmallest(arr, index + 1, r,
                       k - index + l - 1);
  }

  // If k is more than number of
  // elements in array
  throw std::exception();
}


//Resultat selection(std::vector<Resultat>&  A, int l, int r, int k, std::default_random_engine & generateur) {
////  if (l==r) {
////    return A[l];
////  }
//  int s = partition(A, l, r, generateur);
//  int coeff = s- l + 1;
//  if (coeff == k) return A[s];
//  else if (coeff > k ) return selection(A, l, s-1,k, generateur);
//  else return selection(A, s + 1, r, k-s+l - 1, generateur);
//}
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
  int index1 = kthSmallest(resultats, 0, resultats.size() - 1, index_min);
  int index2 = kthSmallest(resultats, index1, resultats.size() - 1, index_max - index1);
  if (index_max == resultats.size()) {
    page = std::vector<Resultat>(resultats.begin() + index1, resultats.begin() + index2 + 1);
    std::sort(page.begin(), page.end());
  }
  else {
    page = std::vector<Resultat>(resultats.begin() + index1, resultats.begin() + index2);
    std::sort(page.begin(), page.end());
  }
}
