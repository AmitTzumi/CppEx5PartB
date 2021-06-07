#pragma once
#include <iostream>
#include <queue>
#include <memory>
int constexpr COUNT = 10;

using namespace std;

namespace ariel
{
    template<typename T>
    class BinaryTree {

    private:
        struct Node {
            T value;
            shared_ptr <Node> right_son;
            shared_ptr <Node> left_son;
            Node(const T& v, Node* l, Node* r)
                    : value(v), right_son(r), left_son(l) {
            }

            Node(const Node &other) : value(other.value) 
            {
                if (other.left_son != nullptr) {
                    shared_ptr <Node> temp{new Node(*other.left_son)};
                    left_son = temp;
                } 
                else {
                    left_son = nullptr;
                }
                if (other.right_son != nullptr) {
                    shared_ptr <Node> temp{new Node(*other.right_son)};
                    right_son = temp;
                } 
                else {
                    right_son = nullptr;
                }
            }

            Node &operator=(const Node &other) 
            {
                if (this == &other) {
                    return *this;
                }
                value = other.value;
                if (other.left_son != nullptr) {
                    left_son = new Node(*other.left_son);
                } 
                else {
                    left_son = nullptr;
                }
                if (other.right_son != nullptr) {
                    right_son = new Node(*other.right_son);
                } 
                else {
                    right_son = nullptr;
                }
            }

            Node(Node &&other) noexcept { //בנאי שמקבל פוינטר ושומר אותו בשדות של המחלקה
                value = other.value;
                right_son = other.right_son;
                other.right_son = nullptr;
                left_son = other.left_son;
                other.left_son = nullptr;
            }

            Node &operator=(Node &&other) noexcept { //אופרטור השמה שמוחק את הפוינטר הישן ושם במקומו אחד חדש
                if (this == &other) {
                    return *this;
                }
                value = other.value;
                right_son = other.right_son;
                other.right_son = nullptr;
                left_son = other.left_son;
                other.left_son = nullptr;
            }

            ~Node() = default;
        }; // END OF struct Node

    class preorder {
    private:
        shared_ptr<Node> pointer_to_current_node;
        queue<shared_ptr<Node>> q_pre;
    public:
        void pre_order(shared_ptr <Node> *root, queue<shared_ptr<Node>>& q_pre) {
            if (*root == nullptr){
                return;
            } 
            q_pre.push(*root);
            pre_order(&(*root)->left_son, q_pre);
            pre_order(&(*root)->right_son, q_pre);
        }

        preorder(shared_ptr <Node> ptr): pointer_to_current_node(ptr) {
            if(ptr == nullptr){
                return;
            }
            pre_order(&pointer_to_current_node, q_pre);
            q_pre.push(nullptr);
            shared_ptr <Node> temp = q_pre.front();
            pointer_to_current_node = temp;
            q_pre.pop();
        }

        // Note that the method is const as this operator does not
        // allow changing of the iterator.
        // Note that it returns T& as it allows to change what it points to.
        // A const_iterator class will return const T&
        // and the method will still be const
        T& operator*() const {
            return pointer_to_current_node->value;
        }

        T* operator->() const {
            return &(pointer_to_current_node->value);
        }

        
        preorder& operator++() { //i++ prefix increment operator
            pointer_to_current_node = q_pre.front();
            q_pre.pop();
            return *this;
        }

        preorder operator++ (int){ //++i postfix increment operator
            preorder temp = *this;
            pointer_to_current_node = q_pre.front();
            q_pre.pop();
            return temp;
        }

        bool operator==(const preorder& node) const {
            return pointer_to_current_node == node.pointer_to_current_node;
        }

        bool operator!=(const preorder& node) const {
            return pointer_to_current_node != node.pointer_to_current_node;;
        }
    };  // END OF CLASS preorder

    class inorder {
    private:
        shared_ptr <Node> pointer_to_current_node;
        queue<shared_ptr<Node>> q_in;
    public:

        void in_order(shared_ptr <Node> *root, queue<shared_ptr<Node>>& q_in){
            if (*root == nullptr){
                return;
            } 
            in_order(&(*root)->left_son, q_in);
            q_in.push(*root);
            in_order(&(*root)->right_son, q_in);
        }

        inorder(shared_ptr <Node> ptr): pointer_to_current_node(ptr) {
            if(ptr == nullptr){
                return;
            }
            in_order(&pointer_to_current_node, q_in);
            q_in.push(nullptr);
            shared_ptr <Node> temp = q_in.front();
            pointer_to_current_node = temp;
            q_in.pop();
        }

        // Note that the method is const as this operator does not
        // allow changing of the iterator.
        // Note that it returns T& as it allows to change what it points to.
        // A const_iterator class will return const T&
        // and the method will still be const
        T& operator*() const {
            return pointer_to_current_node->value;
        }

        T* operator->() const {
            return &(pointer_to_current_node->value);
        }

        inorder& operator++() {
            pointer_to_current_node = q_in.front();
            q_in.pop();
            return *this;
        }

        inorder operator++ (int){
            inorder temp = *this;
            this->pointer_to_current_node = q_in.front();
            q_in.pop();
            return temp;
        }

        bool operator==(const inorder& node) const{
            return pointer_to_current_node == node.pointer_to_current_node;
        }

        bool operator!=(const inorder& node) const {
            return pointer_to_current_node != node.pointer_to_current_node;
        }
    };  // END OF CLASS inorder

    class postorder {
    private:
        shared_ptr <Node> pointer_to_current_node;
        queue<shared_ptr<Node>> q_post;
    public:

        void post_order(shared_ptr <Node> *root, queue<shared_ptr<Node>>& q_post){
            if (*root == nullptr){
                return;
            }
            post_order(&(*root)->left_son, q_post);
            post_order(&(*root)->right_son, q_post);
            q_post.push(*root);
        }

        postorder(shared_ptr <Node> ptr): pointer_to_current_node(ptr) {
            if(ptr == nullptr){
                return;
            }
            post_order(&pointer_to_current_node, q_post);
            q_post.push(nullptr);
            shared_ptr <Node> temp = q_post.front();
            pointer_to_current_node = temp;
            q_post.pop();
        }

        // Note that the method is const as this operator does not
        // allow changing of the iterator.
        // Note that it returns T& as it allows to change what it points to.
        // A const_iterator class will return const T&
        // and the method will still be const
        T& operator*() const {
            return pointer_to_current_node->value;
        }

        T* operator->() const {
            return &(pointer_to_current_node->value);
        }

        
        postorder& operator++() {
            pointer_to_current_node = q_post.front();
            q_post.pop();
            return *this;
        }

        postorder operator++(int){
            postorder temp = *this;
            this->pointer_to_current_node = q_post.front();
            q_post.pop();
            return temp;
        }

        bool operator==(const postorder& node) const {
            return pointer_to_current_node == node.pointer_to_current_node;
        }

        bool operator!=(const postorder& node) const {
            return pointer_to_current_node != node.pointer_to_current_node;
        }
    };  // END OF CLASS postorder

        shared_ptr <Node> root;
    public:
        BinaryTree() : root(nullptr){}

        BinaryTree(const BinaryTree<T>& node)
        {
            shared_ptr <Node> temp{new Node(*node.root)};
            root = temp;
        }

        BinaryTree(BinaryTree<T> && node) noexcept  
        {
            root = node.root;
            node.root=nullptr;
        }

        BinaryTree& operator=(const BinaryTree &node)
        {
            if(this==&node)
            {
                return *this;
            }
            shared_ptr <Node> temp{new Node(*node.root)};
            root = temp;
            return *this;
        }

        BinaryTree& operator=(BinaryTree&& node) noexcept
        {
            if(this == &node){
                return *this;
            }
            root = node.root;
            node.root = nullptr;
            return *this;
        }

        ~BinaryTree() = default;

        shared_ptr<Node> find(shared_ptr<Node> node,T& value){
            if(node == nullptr)
            {
                return nullptr;
            }
            if(node->value == value)
            {
                return node;
            }
            shared_ptr <Node> l =find(node->left_son, value);
            shared_ptr <Node> r =find(node->right_son, value);
            if(l == nullptr)
            {
                return r;
            }
            return l;
        }

        BinaryTree<T>& add_root(T root_node)
        {
            if(root==nullptr)
            {
                shared_ptr <Node> temp{new Node{root_node, nullptr, nullptr}};
                root = temp;
            }
            else{
                root->value = root_node;
            }
            return *this;
        }

        BinaryTree<T>& add_left(T parent, T child)
        {
            shared_ptr <Node> n = find(root, parent);
            if(n == nullptr){
                throw runtime_error("Error : parent is no exist in the tree.\n");
            }
            if(n->left_son == nullptr){
                shared_ptr<Node> temp{new Node{child, nullptr, nullptr}};
                n->left_son = temp;
            }
            else{
                n->left_son->value = child;
            }
            return *this;
        }

        BinaryTree<T>& add_right(T parent, T child)
        {
            shared_ptr <Node> n = find(root, parent);
            if(n == nullptr){
                throw runtime_error("Error : parent is no exist in the tree.\n");
            }
            if(n->right_son == nullptr){
                shared_ptr<Node> temp{new Node{child, nullptr, nullptr}};
                n->right_son = temp;
            }
            else{
                n->right_son->value = child;
            }
            return *this;
        }

        inorder begin()
        {
            return inorder(root);
        }
        inorder end()
        {
            return inorder(nullptr);
        }
        preorder end_preorder()
        {
            return preorder(nullptr);
        }
        preorder begin_preorder()
        {
            return preorder(root);
        }
        inorder end_inorder()
        {
            return inorder(nullptr);
        }
        inorder begin_inorder()
        {
            return inorder(root);
        }
        postorder end_postorder()
        {
            return postorder(nullptr);
        }
        postorder begin_postorder()
        {
            return postorder(root);
        }
        friend std::ostream &operator<<(std::ostream &out, const BinaryTree<T> &bt)
        {
            print2DUtil(bt.root, 0);
            return out;
        }

        static void print2DUtil(shared_ptr<Node> start, int space) 
            { 
            // Base case 
            if (start == NULL){
                return; 
            }

            // Increase distance between levels 
            space += COUNT; 

            // Process right child first 
            print2DUtil(start->right_son, space); 

            // Print current node after space 
            // count 
            cout<<endl; 
            for (int i = COUNT; i < space; i++){
                cout<<" "; 
            }
            cout<<start->value<<"\n"; 

            // Process left child 
            print2DUtil(start->left_son, space); 
        } 
    };
}