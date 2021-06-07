#include "sources/BinaryTree.hpp"
using namespace std;
using namespace ariel;

int main(){

BinaryTree<char> tree_of_chars; 
tree_of_chars.add_root('E');
tree_of_chars.add_left('E', 'T');     // Now 'T' is the left child of 'E'
tree_of_chars.add_right('E', 'A');      // Now 'A' is the right child of 'E' 
cout << tree_of_chars << endl;

for (auto it=tree_of_chars.begin_preorder(); it!=tree_of_chars.end_preorder(); ++it) {
    cout << (*it) << " " ;
  }  // prints: E T A - estimated time of arrival - זמן הגעה משוער, מופיע בדרך כלל בשדה תעופה
  cout << endl;
  for (auto it=tree_of_chars.begin_inorder(); it!=tree_of_chars.end_inorder(); ++it) {
    cout << (*it) << " " ;
  }  // prints: T E A - beverage - משקה מוכר
  cout << endl;
  for (auto it=tree_of_chars.begin_postorder(); it!=tree_of_chars.end_postorder(); ++it) {
    cout << (*it) << " " ;
  }  // prints: T A E - Is a famous Filipino word which is usually often used in expressing a great feeling towards something - מילה פיליפינית מוכרת שמבטאת הרגשה טובה למשהו.
  cout << endl;
  cout << endl;

BinaryTree<char> tree_of_chars2; 
tree_of_chars2.add_root('W');
tree_of_chars2.add_left('W', 'T');     // Now 'T' is the left child of 'W'
tree_of_chars2.add_right('W', 'O');      // Now 'O' is the right child of 'W' 
cout << tree_of_chars2 << endl;

for (auto it=tree_of_chars2.begin_preorder(); it!=tree_of_chars2.end_preorder(); ++it) {
    cout << (*it) << " " ;
  }  // prints: W T O - World Trade Organization - ארגון המסחר העולמי.
  cout << endl;
  for (auto it=tree_of_chars2.begin_inorder(); it!=tree_of_chars2.end_inorder(); ++it) {
    cout << (*it) << " " ;
  }  // prints: T W O - NUMBER - מספר.
  cout << endl;
  for (auto it=tree_of_chars2.begin_postorder(); it!=tree_of_chars2.end_postorder(); ++it) {
    cout << (*it) << " " ;
  }  // prints: T O W -  pull (another vehicle or boat) along with a rope, chain, or tow bar - לגרור.
  cout << endl;
    return 0;
}