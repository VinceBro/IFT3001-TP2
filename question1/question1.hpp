//
// Created by vincebro on 2020-11-23.
//

#ifndef QUESTION1__QUESTION1_HPP_
#define QUESTION1__QUESTION1_HPP_

#include <vector>
#include <random>
#include <iostream>
#include <algorithm>
#include <tuple>
#include <fstream>
#include <chrono>
#include <functional>

int AlgorithmeProbabiliste1(const std::vector<int>& A, std::default_random_engine& generateur );

int AlgorithmeProbabiliste2(const std::vector<int>& A, std::default_random_engine& generateur );

int RandomUnOuZero(void);

int RandomUnSurN(int n);

std::vector<std::tuple<int, int>> GenererDonneesRandom(std::function<int (const std::vector<int> &, std::default_random_engine &)> fonctionProbabiliste, std::function<int ()> fonctionGeneratrice, std::default_random_engine& generateur);

std::vector<std::tuple<int, int>> GenererDonneesRandomUnSurN(std::function<int (const std::vector<int> &, std::default_random_engine &)> fonctionProbabiliste, std::default_random_engine& generateur);

void EcrireDonneesSurDisque(std::vector<std::tuple<int, int>>& donnees, std::string nomFichier);

int main(void);
#endif //QUESTION1__QUESTION1_HPP_
