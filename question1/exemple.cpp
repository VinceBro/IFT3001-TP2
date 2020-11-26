#include <iostream>
#include <random>
#include <vector>

// La fonction Mystere1 est tiree de l'exercise 5 de la serie 5 et
// n'est utilise ici qu'a titre d'exemple. Notez comment un seul
// generateur de nombre aleatoire est utilise pour toute l'execution
// du programme. Notez que l'objet "uniforme" de type
// std::uniform_int_distribution utilise le generateur pour retourner un
// nombre entre 1 et n.
int Mystere1(const std::vector<int>& A, std::default_random_engine& generateur) {
  const unsigned int n = A.size();		     // Theta(1)
  std::uniform_int_distribution<int> uniforme(1, n); // Theta(1)
  const unsigned int p = uniforme(generateur);	     // Theta(1)

  unsigned int nombre_iterations = 0;

  int c = 0;
  for (unsigned int i = 1; i <= n * p; i++) {
    c = c + A[i % n];
    nombre_iterations++;
  }

  return nombre_iterations;
}

//int main(void) {
//  // Un seul generateur de nombre aleatoire doit etre utilise pendant
//  // toute l'experience
//  std::default_random_engine generateur;
//
//  // Ce code demontre que pour une meme instance, c'est-a-dire un meme
//  // vecteur, on obtient des temps de calcul differents.
//  std::vector<int> vecteur(10, 1);
//  for (int i = 0; i < 10; i++) {
//    std::cout << Mystere1(vecteur, generateur) << std::endl;
//  }

//  return 0;
//}
