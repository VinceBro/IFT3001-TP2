#include <vector>
#include <random>
#include <iostream>
#include <algorithm>
#include <tuple>
#include <fstream>
#include <chrono>
#include <functional>

int AlgorithmeProbabiliste1(const std::vector<int> &A, std::default_random_engine &generateur) {
  unsigned int c = 0;
  const unsigned int n = A.size();
  std::uniform_int_distribution<int> uniforme(0, n - 1);
  const unsigned int k = uniforme(generateur);

  if (A[0] == k) {
    for (int i = k ; i <= n; i++){
      for(int j = 1 ; j <= k; j++) {
        c++;
      }
    }
  }
  return c;
}

int AlgorithmeProbabiliste2(const std::vector<int> &A, std::default_random_engine &generateur) {
  unsigned int c = 0;
  const unsigned int n = A.size();
  std::uniform_int_distribution<int> uniforme(0, n - 1);
  const unsigned int k = uniforme(generateur);
  if (A[0] == 0) {
    for (int i = 1; i <= k; i++){
      c++;
    }
  }
  return c;
}

int RandomUnOuZero(void) {
  return std::rand() % 2;
}

int RandomUnSurN(int n) {
  if (std::rand() % n == 0){
    return 0;
  }
  return 1;
}

std::vector<std::tuple<int, int>> GenererDonneesRandom(std::function<int(const std::vector<int> &,
                                                                         std::default_random_engine &)> fonctionProbabiliste,
                                                       std::function<int()> fonctionGeneratrice,
                                                       std::default_random_engine& generateur) {
  int n = 10;
  int c = 0;
  std::vector<std::tuple<int, int>> donnees;
  while (n <= 100) {
    if (c == 10) {
      n += 10;
      c = 0;
      if (n == 110) break;
    }
    std::vector<int> vecteur(n);
    std::generate(vecteur.begin(), vecteur.end(), fonctionGeneratrice);
    int y = fonctionProbabiliste(vecteur, generateur);
    donnees.push_back(std::make_tuple(n, y));
    c++;
  }
  return donnees;
}

std::vector<std::tuple<int, int>> GenererDonneesRandomUnSurN(std::function<int(const std::vector<int> &,
                                                                               std::default_random_engine &)> fonctionProbabiliste,
                                                             std::default_random_engine& generateur) {
  int n = 10;
  int c = 0;
  std::vector<std::tuple<int, int>> donnees;
  while (n <= 100) {
    if (c == 10) {
      n += 10;
      c = 0;
      if (n == 110) break;
    }
    std::vector<int> vecteur(n);
    std::generate(vecteur.begin(), vecteur.end(), [n](){return RandomUnSurN(n);});
    int y = fonctionProbabiliste(vecteur, generateur);
    donnees.push_back(std::make_tuple(n, y));
    c++;
  }
  return donnees;
}

void EcrireDonneesSurDisque(std::vector<std::tuple<int, int>>& donnees, std::string nomFichier) {
  std::tuple<int, int> derniere_entree = donnees.back();
  donnees.pop_back();
  std::ofstream outFile(nomFichier);
  outFile << "[";
  for (const auto &e : donnees) {
    outFile << "(" << std::get<0>(e) << ", " << std::get<1>(e) << "), ";
  }
  outFile << "(" << std::get<0>(derniere_entree) << ", " << std::get<1>(derniere_entree) << ")";
  outFile << "]";

}

int main(void) {
  std::default_random_engine generateur(std::chrono::system_clock::now().time_since_epoch().count());

  std::cout << "Ecriture donnees AlgorithmeProbabiliste1 " << std::endl;
  std::vector<std::tuple<int, int>> donnees =
      GenererDonneesRandom(AlgorithmeProbabiliste1, RandomUnOuZero, generateur);
  EcrireDonneesSurDisque(donnees, "prob1.txt");

  std::cout << "Ecriture donnees AlgorithmeProbabiliste2 cas aléatoire" << std::endl;
  donnees =
      GenererDonneesRandomUnSurN(AlgorithmeProbabiliste2, generateur);
  EcrireDonneesSurDisque(donnees, "prob2aleatoire.txt");

  std::cout << "Ecriture donnees AlgorithmeProbabiliste2 meilleur cas" << std::endl;
  donnees =
      GenererDonneesRandom(AlgorithmeProbabiliste2, [](){return 0;}, generateur);
  EcrireDonneesSurDisque(donnees, "prob2meilleur.txt");

  std::cout << "Ecriture donnees AlgorithmeProbabiliste2 pire cas" << std::endl;
  donnees =
      GenererDonneesRandom(AlgorithmeProbabiliste2, [](){return 1;}, generateur);
  EcrireDonneesSurDisque(donnees, "prob2pire.txt");
}
