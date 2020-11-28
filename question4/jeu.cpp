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

        int chose2, chose1;
        int valeur = tab.at(x-1, y, z);
        int coeffRouge = y - monstres_c[x].magieRouge();
        if(coeffRouge >= 0 ) {
          chose1 = monstres_c[x].degat() + tab.at(x - 1, coeffRouge, z);
        }
        int coeffBleu = z - monstres_c[x].magieBleue();
        if (coeffBleu >=0 ){
          chose2 = monstres_c[x].degat() + tab.at(x - 1, y ,coeffBleu);
        }
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
    int sauce1 = tab.at(i, magie_rouge_c, magie_bleue_c);
    int sauce2 = tab.at(i-1, magie_rouge_c, magie_bleue_c);
    Monstre monstre = monstres_c[i];
    int magie_rouge_monstre = monstres_c[i].magieRouge();
    int magie_bleue_monstre = monstres_c[i].magieBleue();

    if (tab.at(i, magie_rouge_c, magie_bleue_c) > tab.at(i-1, magie_rouge_c, magie_bleue_c) && monstre.magieRouge() <= magie_rouge_c && monstre.magieBleue() <= magie_bleue_c){
      L.push_back(monstre);
      magie_rouge_c -= monstre.magieRouge();
      if (magie_rouge_c < 0) throw std::exception();
      magie_bleue_c -= monstre.magieBleue();
      if (magie_bleue_c < 0) throw std::exception();
    }

  }
  // Inserez votre code ici
  return L;
}
