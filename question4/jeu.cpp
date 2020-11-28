#include "jeu.hpp"

#include <math.h>
#include <algorithm>
#include "tableau.hpp"

std::vector<Monstre> programmationDynamique(const std::vector<Monstre>& monstres, unsigned int magie_rouge, unsigned int magie_bleue) {

  unsigned int n = monstres.size();
  std::vector<Monstre> monstres_c(monstres);
  monstres_c.insert(monstres_c.begin(), Monstre("stub", 0, 0, 0));

  std::vector<unsigned int> dimensions {n + 1, magie_rouge + 1, magie_bleue + 1};
  Tableau<unsigned int> tab(dimensions);

  for (int x = 1; x<= n; x++) {
    for (int y = 0; y <= magie_rouge; y++ ) {
      for (int z = 0; z <= magie_bleue; z++) {

        int coeffRouge = y - monstres_c[x].magieRouge();
        int coeffBleu = z - monstres_c[x].magieBleue();

        if (coeffRouge >= 0 && coeffBleu >= 0) {
          tab.at(x, y, z) = std::max({tab.at(x - 1, y, z), monstres_c[x].degat() + tab.at(x - 1, coeffRouge, coeffBleu)});
        }
        else {
          tab.at(x, y, z) = tab.at(x-1, y, z);
        }
      }
    }
  }

  std::vector<Monstre> L;
  int magie_rouge_c = magie_rouge;
  int magie_bleue_c = magie_bleue;
  for (int i = n; i >= 1; i--) {
    Monstre monstre = monstres_c[i];

    if (tab.at(i, magie_rouge_c, magie_bleue_c) > tab.at(i-1, magie_rouge_c, magie_bleue_c) && monstre.magieRouge() <= magie_rouge_c && monstre.magieBleue() <= magie_bleue_c){
      L.push_back(monstre);
      magie_rouge_c -= monstre.magieRouge();
      magie_bleue_c -= monstre.magieBleue();
    }
  }

  return L;
}
