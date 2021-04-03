#pragma once
#include <cmath>

template<typename Key, typename Value> class TreeDict
{
private:
    struct Para
    {
        Key key;
        Value value;
    };
    struct Node
    {
        Node* left, * right, * prev;
        Para data;
    };
    size_t size;
    Node* m_root;

     size_t getHeightR(Node* tmp)const
     {
         int a = 0, b = 0;
         if (tmp->left != nullptr)
         {
             a = getHeightR(tmp->left);
             a++;
         }
         if (tmp->right != nullptr)
         {
             b = getHeightR(tmp->right);
             b++;
         }
         if (a == 0 && b == 0)
             return 1;
         if (a > b)
             return a;
         else
             return b;

     }
     size_t getHeight(Node* current)const
     {
         int a = 0, b = 0;
         Node* tmp = current;
         if (tmp != nullptr) {
             if (tmp->left != nullptr || tmp->right != nullptr)
             {
                 if (tmp->left != nullptr)
                     a = getHeightR(tmp->left);
                 if (tmp->right != nullptr)
                     b = getHeightR(tmp->right);
             }
             else return 1;
         }
         else return 0;
         if (a > b)
             return a++;
         else
             return b++;
     }
     bool checkRotate(Node* current);
     void leadRotate(Node* current);
     void DoRotate(Node* current);
public:
    TreeDict()
    {
        size = 0;
        m_root = nullptr;
    }
    
    //v
    void add(Key key, Value val);
    Value& operator[](Key key);
    size_t getSize()const
    {
        return size;
    };
    size_t getHeight()const
    {
        int a = 0, b = 0;
        Node* tmp = m_root;
        if (tmp != nullptr) {
            if (tmp->left != nullptr || tmp->right != nullptr)
            {
                if (tmp->left != nullptr)
                    a = getHeightR(tmp->left);
                if (tmp->right != nullptr)
                    b = getHeightR(tmp->right);
            }
            else return 1;
        }
        else return 0;
        if (a > b)
            return a++;
        else
            return b++;
    }
};

template<typename Key, typename Value> Value& TreeDict<Key, Value>::operator[](Key key)
{
    if (!m_root)
    {
        Node* tmp = new Node;
        tmp->left = tmp->right = tmp->prev = nullptr;
        Para p;
        p.key = key;
        tmp->data = p;
        m_root = tmp;

        return m_root->data.value;
    }

    Node* cur = m_root;
    Node** next = nullptr;

    while (cur != nullptr)
    {
        if (cur->data.key == key)
            return cur->data.value;

        if (key < cur->data.key)
            next = &cur->left;
        else if (key > cur->data.key)
            next = &cur->right;

        if (*next == nullptr)
        {
            Node* tmp = new Node;
            tmp->prev = cur;
            tmp->left = tmp->right = nullptr;
            Para p;
            p.key = key;
            tmp->data = p;

            *next = tmp;
            return (*next)->data.value;
        }

        cur = *next;
    }
}

template<typename Key, typename Value> bool TreeDict<Key, Value>::checkRotate(Node* current)
{
    return math::abs(getHeight(current->left) - getHeight(current->right)) < 2;
}

template<typename Key, typename Value> void TreeDict<Key, Value>::leadRotate(Node* current)
{
    while (current != m_root)
    {
        std::cout << m_root->data.value;
        if (checkRotate(current) == 1)
            current = current->prev;
        else
        {
            DoRotate(current);
        }
    }
}
template<typename Key, typename Value> void TreeDict<Key, Value>::DoRotate(Node* current)
{
    Node* tmp = current;
    if (getHeight(current->left) > getHeight(current->right))
    {
        if (getHeight(current->left->left) > getHeight(current->left->right))
        {
            current->prev->left = current->left;
            tmp->left->prev = tmp->prev;
            tmp->left->right = tmp;
            tmp->prev = tmp->left;
        }
        else
        {
            Node* tmpLeft = current->left;
            current->left = current->left->right;
            tmpLeft->right->prev = tmpLeft->prev;
            tmpLeft->right->left = tmpLeft;
            tmpLeft->prev = tmpLeft->right;
            current->prev->left = current->left;
            tmp->left->prev = tmp->prev;
            tmp->left->right = tmp;
            tmp->prev = tmp->left;
        }
    }
    else
    {
        if (getHeight(current->right->right) > getHeight(current->right->left))
        {
            current->prev->right = current->right;
            tmp->right->prev = tmp->prev;
            tmp->right->left = tmp;
            tmp->prev = tmp->right;
        }
        else 
        {
            Node* tmpRight = current->right;
            current->right = current->right->left;
            tmpRight->left->prev = tmpRight->prev;
            tmpRight->left->right = tmpRight;
            tmpRight->prev = tmpRight->left;
            current->prev->right = current->right;
            tmp->right->prev = tmp->prev;
            tmp->right->left = tmp;
            tmp->prev = tmp->right;
        }
    }
}

template<typename Key, typename Value> void TreeDict<Key, Value>::add(Key key, Value value)
{
    size++;
    if (!m_root)
    {
        Node* tmp = new Node;
        tmp->left = tmp->right = tmp->prev = nullptr;
        Para p;
        p.key = key;
        p.value = value;
        tmp->data = p;
        m_root = tmp;

        return;
    }

    Node* cur = m_root;
    Node** next = nullptr;

    while (cur != nullptr)
    {
        if (cur->data.key == key)
            return;

        if (key > cur->data.key)
            next = &cur->left;
        else if (key < cur->data.key)
            next = &cur->right;

        if (*next == nullptr)
        {
            Node* tmp = new Node;
            tmp->left = tmp->right = nullptr;
            tmp->prev = cur;
            Para p;
            p.key = key;
            p.value = value;
            tmp->data = p;
            *next = tmp;
            leadRotate(tmp);
            return;
        }
        cur = *next;
        
    }

}
