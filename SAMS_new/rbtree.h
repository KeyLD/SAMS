#ifndef _RBTREE_OLD_H
#define _RBTREE_OLD_H

#include <assert.h>
#include <iostream>
#include <queue>

enum RBTColor {
    red,
    black
};
template <typename K, typename V>
class RBTreeNode;

template <typename K, typename V>
class RBTreeIterator
{
public:
    typedef RBTreeNode<K,V>* link_type;
    typedef RBTreeIterator<K,V> iterator;
    typedef RBTreeIterator<K,V>& reference;
    typedef RBTreeIterator<K,V>* pointer;
    link_type node;

    RBTreeIterator(){}

    RBTreeIterator(link_type p)
    {
        if(p==nullptr) RBTreeIterator();
        else {
            node = p;
        }
    }

    void increment()
    {
        if (node != nullptr) {
            node = node->right_son;
            while (node->left_son != nullptr)
                node = node->left_son;
        } else {
            link_type parent = node->parent;
            while (node == parent->right_son) {
                node = parent;
                parent = parent->parent;
            }
            if (node->right_son != parent)
                node = parent;
        }
    }
    void decrement()
    {
        if (IS_RED(node) and node->parent->parent == node)
            node = node->right_son;
        else if (node->left_son != nullptr) {
            node = node->left_son;
            while (node->right_son != nullptr)
                node = node->right_son;
        } else {
            link_type parent = node->parent;
            while (node == parent->left_son) {
                node = parent;
                parent = parent->parent;
            }
            node = parent;
        }
    }


    iterator& operator++()
    {
        increment();
        return *this;
    }

    iterator operator++(int)
    {
        iterator tmp = *this;
        increment();
        return tmp;
    }

    iterator& operator--()
    {
        decrement();
        return *this;
    }

    iterator operator--(int)
    {
        iterator tmp = *this;
        decrement();
        return tmp;
    }

    bool operator==(const iterator& it) const { return node == it.node; }
    bool operator!=(const iterator& it) const { return node != it.node; }

    V& operator*() const { return node->value; }
    V* operator->() const { return &(operator*()); }

};

template <typename K, typename V>
class RBTree {
private:
    typedef RBTreeNode<K, V>* RBTNodePointer;
    typedef RBTreeNode<K, V> RBTNode;

    RBTNodePointer RBTree_root;
    bool rbt_change;
    RBTNodePointer begin_pointer, end_pointer;

    bool insertFixUp(RBTNodePointer);
    void eraseFixUp_left(RBTNodePointer, RBTNodePointer, RBTNodePointer);
    void eraseFixUp_right(RBTNodePointer, RBTNodePointer, RBTNodePointer);
    RBTNodePointer leftRotate(RBTNodePointer);
    RBTNodePointer rightRotate(RBTNodePointer);
    void moveNode(RBTNodePointer, RBTNodePointer);

    void dyeNodeRed(RBTNodePointer node) { node->color = red; } // inline
    void dyeNodeBlack(RBTNodePointer node) { node->color = black; }
    void dyeNode(RBTNodePointer node, RBTNodePointer color_src) { node->color = color_src->color; }
    bool isRedNode(RBTNodePointer node) { return node and node->color == red; }
    bool isBlackNode(RBTNodePointer node) { return !node or node->color == black; }

    RBTNodePointer findPrecursor(RBTNodePointer);
    RBTNodePointer findSuccessor(RBTNodePointer);
    RBTNodePointer findByKey(K);

    bool insertNode(const RBTNodePointer);

    void clear(RBTNodePointer);

    void swap(RBTColor& ac, RBTColor& bc) { std::swap(ac, bc); }

public:
    typedef typename RBTreeIterator<K,V>::iterator iterator;

    RBTree()
        : rbt_change(false)
    {
        begin_pointer = end_pointer = RBTree_root = nullptr;
    }
    ~RBTree()
    {
        if (RBTree_root != nullptr)
            clear(RBTree_root);
    }

    iterator find(K);
    void insert(K, V);
    void erase(K);
    void erase(iterator);

    void bfsPrint();

    iterator begin()
    {
        if (rbt_change or begin_pointer == nullptr) {
            begin_pointer = RBTree_root;
            if (!begin_pointer)
                return iterator(nullptr);
            while (begin_pointer->left_son != nullptr)
                begin_pointer = begin_pointer->left_son;
        }
        return begin_pointer;
    }
    iterator end()
    {
        if (rbt_change or end_pointer == nullptr) {
            end_pointer = RBTree_root;
            if (!end_pointer)
                return nullptr;
            while (end_pointer->right_son)
                end_pointer = end_pointer->right_son;
        }
        return end_pointer;
    }
    iterator nextPointer(iterator cur)
    {
        if (cur->right_son) {
            cur = cur->right_son;
            while (cur->left_son)
                cur = cur->left_son;
            return cur;
        } else {
            RBTNodePointer parent = cur->parent;
            while (cur == parent->right_son) {
                cur = parent;
                parent = cur->parent;
            }
            return parent;
        }
    }
};

template <typename K, typename V>
class RBTreeNode {
public:
    K key;
    V value;

    RBTreeNode(K _key = 0, V _value = V())
        : key(_key)
        , value(_value)
    {
        color = red;
        left_son = right_son = parent = nullptr;
    }
    ~RBTreeNode() {}

    friend class RBTree<K, V>;
    friend class RBTreeIterator<K,V>;

    RBTreeNode& operator = (const RBTreeIterator<K,V>& it)
    {
        *this = it.node;
        return *this;
    }

private:
    RBTreeNode* left_son;
    RBTreeNode* right_son;
    RBTreeNode* parent;
    enum RBTColor color;
};




template <typename K, typename V>
RBTreeNode<K, V>* RBTree<K, V>::leftRotate(RBTNodePointer root)
{
    // 左旋必须确保 节点 与 节点的右孩子 不为空
    if (!root || !root->right_son) {
        // error msg
        return nullptr;
    }

    RBTNodePointer super_root;
    RBTNodePointer right_son = root->right_son;
    RBTNodePointer right_son_left = right_son->left_son;

    if (root == RBTree_root) {
        super_root = RBTree_root;
        RBTree_root = root->right_son;
    } else
        super_root = root->parent;

    if (super_root->left_son == root)
        super_root->left_son = right_son;
    else if (super_root->right_son == root)
        super_root->right_son = right_son;
    right_son->parent = super_root;

    right_son->left_son = root;
    root->parent = right_son;

    root->right_son = right_son_left;
    if (right_son_left) //函数只保证旋转的两个节点不是nil
        right_son_left->parent = root;

    return right_son;
}

template <typename K, typename V>
RBTreeNode<K, V>* RBTree<K, V>::rightRotate(RBTNodePointer root)
{
    // 右旋必须确保 节点 和 节点的左孩子 不为空
    if (!root || !root->left_son) {
        // error msg
        return nullptr;
    }

    RBTNodePointer super_root;
    RBTNodePointer left_son = root->left_son;
    RBTNodePointer left_son_right = left_son->right_son;

    if (root == RBTree_root) {
        super_root = RBTree_root;
        RBTree_root = root->left_son;
    } else
        super_root = root->parent;

    if (super_root->left_son == root)
        super_root->left_son = left_son;
    else if (super_root->right_son == root)
        super_root->right_son = left_son;
    left_son->parent = super_root;

    left_son->right_son = root;
    root->parent = left_son;

    root->left_son = left_son_right;
    if (left_son_right) // 函数只保证旋转的两个节点不是nil
        left_son_right->parent = root;

    return left_son;
}

template <typename K, typename V>
RBTreeNode<K, V>* RBTree<K, V>::findByKey(K find_key)
{
    RBTNodePointer cNode = RBTree_root;
    while (cNode != nullptr) {
        if (find_key < cNode->key)
            cNode = cNode->left_son;
        else if (find_key > cNode->key)
            cNode = cNode->right_son;
        else
            return cNode;
    }
    return nullptr;
}

template <typename K, typename V>
typename RBTreeIterator<K,V>::iterator RBTree<K, V>::find(K find_key)
{
    RBTNodePointer cNode = findByKey(find_key);
    assert(cNode != nullptr);
    return (iterator)cNode;
}

template <typename K, typename V>
void RBTree<K, V>::clear(RBTNodePointer root)
{
    if (root->left_son)
        clear(root->left_son);
    if (root->right_son)
        clear(root->right_son);
    delete root;
}

template <typename K, typename V>
void RBTree<K, V>::moveNode(RBTNodePointer replace, RBTNodePointer deleted)
{
    RBTNodePointer deleted_parent = deleted->parent;

    if (deleted_parent->left_son == deleted)
        deleted_parent->left_son = replace;
    else
        deleted_parent->right_son = replace;
    if (replace != nullptr)
        replace->parent = deleted_parent;
    delete deleted;
}

template <typename K, typename V>
inline RBTreeNode<K, V>* RBTree<K, V>::findSuccessor(RBTNodePointer root)
{
    RBTNodePointer cNode = root->right_son;
    while (cNode->left_son != nullptr)
        cNode = cNode->left_son;
    return cNode;
}

template <typename K, typename V>
inline RBTreeNode<K, V>* RBTree<K, V>::findPrecursor(RBTNodePointer root)
{
    RBTNodePointer cNode = root->left_son;
    while (cNode->right_son != nullptr)
        cNode = cNode->right_son;
    return cNode;
}

template <typename K, typename V>
void RBTree<K, V>::insert(K _key, V _value)
{
    RBTNodePointer new_node = new RBTreeNode<K, V>(_key, _value);
    if (RBTree_root == nullptr) {
        RBTree_root = new_node;
        dyeNodeBlack(RBTree_root);
    } else {
        if (insertNode(new_node))
            insertFixUp(new_node);
        else
            std::perror("insert error"); //修改
    }
}

template <typename K, typename V>
bool RBTree<K, V>::insertNode(const RBTNodePointer new_node)
{
    K insert_key = new_node->key;
    RBTNodePointer cNode = RBTree_root;
    while (cNode != nullptr) {
        if (insert_key < cNode->key) {
            if (cNode->left_son == nullptr) {
                cNode->left_son = new_node;
                new_node->parent = cNode;
                return true;
            } else
                cNode = cNode->left_son;
        } else if (insert_key > cNode->key) {
            if (cNode->right_son == nullptr) {
                cNode->right_son = new_node;
                new_node->parent = cNode;
                return true;
            } else
                cNode = cNode->right_son;
        }
    }
    return false;
}

template <typename K, typename V>
bool RBTree<K, V>::insertFixUp(RBTNodePointer root)
{
    RBTNodePointer parent = root->parent;
    while (parent != nullptr && isRedNode(parent)) { //只要父节点的颜色位红色，就保证有祖父节点，因为性质1
        RBTNodePointer grandparent = parent->parent;
        if (grandparent->left_son == parent) {
            if (grandparent->right_son && isRedNode(grandparent->right_son)) {
                dyeNodeBlack(parent);
                dyeNodeBlack(grandparent->right_son);
                if (grandparent != RBTree_root)
                    dyeNodeRed(grandparent);
                root = grandparent;
                parent = root->parent;
                continue;
            } else if (parent->right_son == root)
                leftRotate(parent);
            grandparent = rightRotate(grandparent);
            assert(grandparent != nullptr);
            dyeNodeBlack(grandparent);
            dyeNodeRed(grandparent->left_son);
            dyeNodeRed(grandparent->right_son);
            break;
        } else {
            if (grandparent->left_son && isRedNode(grandparent->left_son)) {
                dyeNodeBlack(parent);
                dyeNodeBlack(grandparent->left_son);
                if (grandparent != RBTree_root)
                    dyeNodeRed(grandparent);
                root = grandparent;
                parent = root->parent;
                continue;
            } else if (parent->left_son == root)
                rightRotate(parent);
            grandparent = leftRotate(grandparent);
            dyeNodeBlack(grandparent);
            dyeNodeRed(grandparent->left_son);
            dyeNodeRed(grandparent->right_son);
            break;
        }
    }
    return true;
}

template <typename K, typename V>
void RBTree<K, V>::erase(K erase_key)
{
    RBTNodePointer deleted = findByKey(erase_key);
    erase(deleted);
}

template <typename K, typename V>
void RBTree<K, V>::erase(iterator erase_it)
{
    RBTNodePointer deleted = new RBTNode;
    *deleted = erase_it;
    if (deleted != nullptr) {
        if (deleted->right_son) {
            RBTNodePointer replace = findSuccessor(deleted);

            deleted->value = replace->value;
            deleted->key = replace->key;

            RBTNodePointer replace_right = replace->right_son, replace_parent = replace->parent;
            RBTNodePointer replace_brother = replace_parent->left_son == replace ? replace_parent->right_son : replace_parent->left_son;
            bool is_replace_black = isBlackNode(replace);
            moveNode(replace_right, replace);

            if (is_replace_black)
                eraseFixUp_right(replace_right, replace_parent, replace_brother);
        } else if (deleted->left_son) {
            RBTNodePointer replace = findPrecursor(deleted);

            deleted->value = replace->value;
            deleted->key = replace->key;

            RBTNodePointer replace_left = replace->left_son, replace_parent = replace->parent;
            RBTNodePointer replace_brother = replace_parent->left_son == replace ? replace_parent->right_son : replace_parent->left_son;
            bool is_replace_black = isBlackNode(replace);
            moveNode(replace_left, replace);

            if (is_replace_black)
                eraseFixUp_left(replace_left, replace_parent, replace_brother);
        } else {
            moveNode(deleted->right_son, deleted);
        }
    }
}

template <typename K, typename V>
void RBTree<K, V>::eraseFixUp_right(RBTNodePointer deleted, RBTNodePointer parent, RBTNodePointer brother)
{
    if (isRedNode(deleted)) { //ok
        dyeNodeBlack(deleted);
    } else if (isRedNode(brother)) {
        parent = leftRotate(parent);
        swap(parent->color, parent->left_son->color);
    } else if (isRedNode(brother->left_son)) { //ok
        RBTNodePointer brother_left = brother->left_son;
        rightRotate(brother);
        dyeNode(brother_left, parent);
        dyeNodeBlack(parent);
        leftRotate(parent);
    } else if (isRedNode(brother->right_son)) { //ok
        dyeNode(brother, parent);
        dyeNodeBlack(parent);
        dyeNodeBlack(brother->right_son);
        leftRotate(parent);
    } else if (isRedNode(parent)) { //ok
        dyeNodeRed(brother);
        dyeNodeBlack(parent);
    } else { //ok
        dyeNodeRed(brother);
        deleted = parent;
        parent = deleted->parent;
        if (parent == nullptr)
            return;
        else if (parent->left_son == deleted)
            eraseFixUp_right(deleted, parent, parent->right_son);
        else
            eraseFixUp_left(deleted, parent, parent->left_son);
    }
}

template <typename K, typename V>
void RBTree<K, V>::eraseFixUp_left(RBTNodePointer deleted, RBTNodePointer parent, RBTNodePointer brother)
{
    if (isRedNode(deleted)) { //ok
        dyeNodeBlack(deleted);
    } else if (isRedNode(brother)) {
        parent = rightRotate(parent);
        swap(parent->color, parent->right_son->color);
    } else if (isRedNode(brother->right_son)) { //ok
        RBTNodePointer brother_right = brother->right_son;
        leftRotate(brother);
        dyeNode(brother_right, parent);
        dyeNodeBlack(parent);
        rightRotate(parent);
    } else if (isRedNode(brother->left_son)) { //ok
        dyeNode(brother, parent);
        dyeNodeBlack(parent);
        dyeNodeBlack(brother->left_son);
        rightRotate(parent);
    } else if (isRedNode(parent)) { //ok
        dyeNodeRed(brother);
        dyeNodeBlack(parent);
    } else { //ok
        dyeNodeRed(brother);
        deleted = parent;
        parent = deleted->parent;
        if (parent == nullptr)
            return;
        else if (parent->left_son == deleted)
            eraseFixUp_right(deleted, parent, parent->right_son);
        else
            eraseFixUp_left(deleted, parent, parent->left_son);
    }
}

template <typename K, typename V>
void RBTree<K, V>::bfsPrint()
{
    std::queue<RBTNodePointer> que;
    que.push(RBTree_root);
    while (!que.empty()) {
        RBTreeNode<int, int>* cNode = que.front();
        que.pop();
        std::cout << cNode->key << "  " << (cNode->color == black ? "black" : "red") << std::endl;
        if (cNode->left_son != nullptr)
            que.push(cNode->left_son);
        if (cNode->right_son != nullptr)
            que.push(cNode->right_son);
    }
}

#endif
