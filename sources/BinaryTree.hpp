#pragma once
#include <iostream>
#include <queue>
#define COUNT 10

using namespace std;

namespace ariel
{
    template<typename T>
    class BinaryTree {

    private:
        struct Node {
            T value;
            Node* right_son;
            Node* left_son;
            Node(const T& v, Node* l, Node* r)
                    : value(v), right_son(r), left_son(l) {
            }
        }; // END OF struct Node

    class preorder {
    private:
        Node* pointer_to_current_node;
        queue<Node*> q_pre;
    public:
        void pre_order(Node* root, queue<Node*>& q_pre) {
            if (root == nullptr){
                return;
            } 
            q_pre.push(root);
            pre_order(root->left_son, q_pre);
            pre_order(root->right_son, q_pre);
        }

        preorder(Node* ptr = nullptr): pointer_to_current_node(ptr) {
            if(ptr == nullptr){
                return;
            }
            pre_order(pointer_to_current_node, q_pre);
            q_pre.push(nullptr);
            pointer_to_current_node = q_pre.front();
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

        
        preorder& operator++() {
            pointer_to_current_node = q_pre.front();
            q_pre.pop();
            return *this;
        }

        preorder operator++ (int){
            preorder temp = *this;
            this->pointer_to_current_node = q_pre.front();
            q_pre.pop();
            return temp;
        }

        bool operator==(preorder node){
            return pointer_to_current_node==node.pointer_to_current_node;
        }

        bool operator!=(const preorder& rhs) const {
            return !q_pre.empty();
        }
    };  // END OF CLASS preorder

    class inorder {
    private:
        Node* pointer_to_current_node;
        queue<Node*> q_in;
    public:

        void in_order(Node* root, queue<Node*>& q_in){
            if (root == nullptr){
                return;
            } 
            in_order(root->left_son, q_in);
            q_in.push(root);
            in_order(root->right_son, q_in);
        }

        inorder(Node* ptr = nullptr): pointer_to_current_node(ptr) {
            if(ptr == nullptr){
                return;
            }
            in_order(pointer_to_current_node, q_in);
            q_in.push(nullptr);
            pointer_to_current_node = q_in.front();
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

        bool operator==(inorder node){
            return pointer_to_current_node==node.pointer_to_current_node;
        }

        bool operator!=(const inorder& rhs) const {
            return !q_in.empty();
        }
    };  // END OF CLASS inorder

    class postorder {
    private:
        Node* pointer_to_current_node;
        queue<Node*> q_post;
    public:

        void post_order(Node* root, queue<Node*>& q_post){
            if (root == nullptr){
                return;
            }
            post_order(root->left_son, q_post);
            post_order(root->right_son, q_post);
            q_post.push(root);
        }

        postorder(Node* ptr = nullptr): pointer_to_current_node(ptr) {
            if(ptr == nullptr){
                return;
            }
            post_order(pointer_to_current_node, q_post);
            q_post.push(nullptr);
            pointer_to_current_node = q_post.front();
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

        bool operator==(postorder node){
            return pointer_to_current_node==node.pointer_to_current_node;
        }

        bool operator!=(const postorder& rhs) const {
            return !q_post.empty();
        }
    };  // END OF CLASS postorder

        Node* root;
    public:
        BinaryTree(){
            this->root = nullptr;
        }

        void deep_copy(Node &start, Node &end)
        {
            if (start.left_son!=nullptr)
            {
                end.left_son=new Node(start.left_son->value, nullptr, nullptr);
                deep_copy(*start.left_son,*end.left_son);
            }
            if (start.right_son!=nullptr)
            {
                end.right_son=new Node(start.right_son->value, nullptr, nullptr);
                deep_copy(*start.right_son,*end.right_son);
            }
        }

        BinaryTree(const BinaryTree<T>& node)
        {
            if(node.root!=nullptr)
            {
                root=new Node(node.root->value, nullptr, nullptr);
                deep_copy(*node.root, *root); // *root 2 argument
            }
        }
        BinaryTree(BinaryTree<T> && node) noexcept //https://en.cppreference.com/w/cpp/language/noexcept
        {
            root=node.root;
            node.root=nullptr;
        }

        BinaryTree& operator=(BinaryTree node)
        {
            if(this==&node)
            {
                return *this;
            }
            if(root!=nullptr)
            {
                delete root;
            }
            root=new Node(node.root->value, nullptr, nullptr);
            deep_copy(*node.root,*root);
            return *this;
        }
        BinaryTree& operator=(BinaryTree&& node) noexcept
        {
            *root=node.root;
        }

        ~BinaryTree(){}



        /*BinaryTree<T>& add_root(T r)
        {
            if(root == nullptr){
                root =  new Node(r, nullptr, nullptr);
            }
            else{
                root->value = r;
            }
            return *this;
        }

        Node* search(Node* root, T data){
            if(root == nullptr){
                return nullptr;
            }
            if(root->value == data){
                return root;
            }
            return search(root->left_son, data);
            return search(root->right_son, data); 
        }

        BinaryTree<T>& add_left(T e, T a)
        {
            if(!search(root, e)){
                throw "The BinaryTree root is NULL or The vertex is not found in the tree - add_left";
            }
            else{
                if(!search(root, e)->left_son){
                    Node* left = new Node(a, nullptr, nullptr);
                    search(root, e)->left_son = left;
                }
                else{
                    search(root, e)->left_son->value = a;
                }
            }
            return *this;
        }

        BinaryTree<T>& add_right(T e, T a)
        {
            if(search(root, e) == nullptr){
                throw "The BinaryTree root is NULL or The vertex is not found in the tree - add_right";
            }
            else{
                if(search(root, e)->right_son == nullptr){
                    Node* right = new Node(a, nullptr, nullptr);
                    search(root, e)->right_son = right;
                }
                else{
                    search(root, e)->right_son->value = a;
                }
            }
            return *this;
        }*/

        Node* find(Node* node,T& value){
            if(node==nullptr)
            {
                return nullptr;
            }
            if(node->value==value)
            {
                return node;
            }
            Node* r=find(node->right_son, value);
            if(r)
            {
                return r;
            }
            Node* l=find(node->left_son, value);
            return l;
        }

        BinaryTree<T>& add_root(T root_node)
        {
            if(root==nullptr)
            {
                root=new Node(root_node, nullptr, nullptr);
            }
            root->value=root_node;
            return *this;
        }

        BinaryTree<T>& add_left(T parent, T child)
        {
            if(!find(root, parent))
            {
                throw invalid_argument("invalid_argument: parent missing in left");
            }
            if(!find(root, parent)->left_son)
            {
                find(root, parent)->left_son=new Node(child, nullptr, nullptr);
            }
            find(root, parent)->left_son->value=child;
            return *this;
        }

        BinaryTree<T>& add_right(T parent, T child)
        {
            if(!find(root, parent))
            {
                throw invalid_argument("invalid_argument: parent missing in right");
            }
            if(!find(root, parent)->right_son)
            {
                find(root, parent)->right_son=new Node(child, nullptr, nullptr);
            }
            find(root, parent)->right_son->value=child;
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

        static void print2DUtil(Node *root, int space) 
            { 
            // Base case 
            if (root == NULL) 
                return; 

            // Increase distance between levels 
            space += COUNT; 

            // Process right child first 
            print2DUtil(root->right_son, space); 

            // Print current node after space 
            // count 
            cout<<endl; 
            for (int i = COUNT; i < space; i++) 
                cout<<" "; 
            cout<<root->value<<"\n"; 

            // Process left child 
            print2DUtil(root->left_son, space); 
        } 
    };
}