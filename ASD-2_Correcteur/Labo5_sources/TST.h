/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TST.h
 * Author: nichu
 *
 * Created on 18. janvier 2020, 00:45
 */

#ifndef TST_H
#define TST_H


#include <string>

using namespace std;

class TernarySearchTree {
private:
   //
   // Noeux de l'arbre. contient une cle, une valeur, et les liens vers les
   // sous-arbres droit et gauche.
   //

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
   
   ////////////////////////////////////////////
   ////////////////////////////////////////////
   ////////////////////////////////////////////

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
   // endWord default value is false.
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
            //we are at the end of the word and the node is true
            //we found the word!
            return true;
         } else { // else it's middle.
            x = x->mid;
         }
      }
      return false;
   }

   ////////////////////////////////////////////
   ////////////////////////////////////////////
   ////////////////////////////////////////////

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

      return restoreBalance(x); // AVL. sinon on aurait return x; 
   }

};



#endif /* TST_H */

