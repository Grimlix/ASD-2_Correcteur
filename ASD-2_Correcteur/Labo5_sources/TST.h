
/* 
 * File:   TST.h
 * Author: Gianinetti Lucas, Hungerbühler Nicolas, Wojciechowski Cassandre
 *
 * Remarques: classe TernarySearchTrie qui prend la plupart des fonctions de l'AVL
 *            mise à disposition. Ils suffisaient d'ajouter 2 aspects : l'enfant du
 *            milieu (mid) et le boolean disant que le mot est terminé ou non (endWord).
 *            Nous avons alors garder uniquement les fonctions que vous avions besoin.
 *            C'est à dire surtout : put (insérer un élément) et contains (savoir s'il
 *            y a un mot dans ce conteneur). Et lorsqu'on insère un element il faut 
 *            vérifier si celui-ci est toujours équilibré. Donc on va avoir besoin
 *            des fonctions de hauteur (get la hauter et la changer) et bien sûr des 
 *            rotations pour le rééquilibrer. L'équilibre et les rotations sont exactement
 *            les même que pour un AVL car l'enfant du milieu n'est pas tenu en compte.
 *            Nous avons décidé de garder le destructeur.
 *          
 */

#ifndef TST_H
#define TST_H

#include <string>

using namespace std;

class TernarySearchTree {
private:

   struct Node {
      char key;
      bool endWord; //Valeur disant si on est au bout d'un mot qu'on peut prendre
      Node* right; // sous arbre avec des cles plus grandes
      Node* mid; // Sous arbre avec la cle exacte
      Node* left; // sous arbre avec des cles plus petites
      int nodeHeight; // hauteur du sous-arbre dont ce noeud est la racine.

      Node(char key) : key(key), endWord(false), right(nullptr), mid(nullptr), left(nullptr), nodeHeight(0) {
      }
   };

   //
   // Racine de l'arbre.
   //
   Node* root;

public:
   //
   // Constructeur. La racine est vide
   //

   TernarySearchTree() : root(nullptr) {
   }

   //
   // Destructeur.
   //

   ~TernarySearchTree() {
      deleteSubTree(root);
   }

   // Insertion d'une paire cle / valeur.
   // endWord valeur par default est false.
   //

   void put(const std::string key) {
      root = put(root, key, 0);
   }

   bool contains(const string& key) {
      Node* x = root;
      int pos = 0;
      char word;

      while (x != nullptr) {
         word = key[pos];
         if (word < x->key) {
            x = x->left;
         } else if (word > x->key) {
            x = x->right;
         } else if (x->endWord == true && pos == key.length() - 1) {
            //On est à la fin du mot et le dernier noeud à son boolean de fin de mot
            //a vrai. On a alors trouver le mot
            return true;
         } else { // else c'est le milieu
            x = x->mid;
         }
      }
      return false;
   }

private:
   //
   // Profondeur de l'arbre.
   //

   int height(Node* x) {
      return x == nullptr ? -1 : x->nodeHeight;
   }

   // HELPER: Mise à jour de la hauteur d'un sous-arbre à partir des hauteurs de ses enfants

   void updateNodeHeight(Node* x) {
      x->nodeHeight = std::max(height(x->right), height(x->left)) + 1;
   }

   //
   // AVL: rotation droite avec mise à jour des tailles et hauteurs
   //

   Node* rotateRight(Node* x) {
      Node* y = x->left;
      x->left = y->right;
      y->right = x;

      updateNodeHeight(x);
      updateNodeHeight(y);
      return y;
   }

   //
   // AVL: rotation gauche avec mise à jour des tailles et hauteurs
   //

   Node* rotateLeft(Node* x) {
      Node* y = x->right;
      x->right = y->left;
      y->left = x;

      updateNodeHeight(x);
      updateNodeHeight(y);
      return y;
   }

   void deleteSubTree(Node* x) {
      if (x == nullptr) return;
      deleteSubTree(x->right);
      deleteSubTree(x->mid);
      deleteSubTree(x->left);

      delete x;
   }

   //
   // AVL: calcul et restoration de l'équilibre d'un noeud.
   //

   int balance(Node* x) {
      if (x == nullptr) return 0;
      return height(x->left) - height(x->right);
   }

   Node* restoreBalance(Node* x) {

      if (balance(x) < -1) // left < right-1
      {
         if (balance(x->right) > 0)
            x->right = rotateRight(x->right);
         x = rotateLeft(x);
      } else if (balance(x) > 1) // left > right+1
      {
         if (balance(x->left) < 0)
            x->left = rotateLeft(x->left);
         x = rotateRight(x);
      } else updateNodeHeight(x);
      return x;
   }

   Node* put(Node* x, const std::string& key, int pos) {
      char nodeVal = key[pos];

      //Creer le nouveau noeud
      if (x == nullptr) {
         x = new Node(nodeVal);
      }

      if (nodeVal < x->key) {
         //put left
         x->left = put(x->left, key, pos);
      } else if (nodeVal > x->key) {
         //put right
         x->right = put(x->right, key, pos);
      } else if (pos < key.length() - 1) {
         //put mid
         x->mid = put(x->mid, key, pos + 1);
      } else { // x->key == key
         x->endWord = true;
      }

      return restoreBalance(x);
   }

};



#endif /* TST_H */

