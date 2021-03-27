#pragma once

template<typename Chemu, typename Chto> class TreeDict {
public:
	TreeDict();
	void add(Chemu che, Chto cht);
	Chto& operator[](Chemu che);
    size_t getSize()const
    {
        return size;
    };
    size_t getHeight()const
    {
        return height;
    }
private:
    struct Para
    {
        Chemu che;
        Chto cht;
    };
    struct Node
    {
        Node* left, * right;
        Para data;
    };
    size_t size;
    size_t height;
    Node* m_root;

};

template<typename Chemu, typename Chto> Chto& TreeDict<Chemu, Chto>::operator[](Chemu che)
{
    Node* cur = m_root;
    Node** next;
    while (cur != nullptr)
    {
        if (cur->data.che == che)
            return cur->data.cht;
        else if (che < cur->data.che)
            next = &cur->left;
        else if (che > cur->data.che)
            next = &cur->right;

        if (*next == nullptr)
        {
            Node* tmp = new Node;
            tmp->left = tmp->right = nullptr;
            Para p;
            p.che = che;
            tmp->data = p;
            *next = tmp;
            return *next;
        }

        cur = *next;

    }
}

template<typename Chemu, typename Chto> void TreeDict<Chemu, Chto>::add(Chemu che, Chto cht)
{
    Node* cur = m_root;
    Node** next;
    while (cur != nullptr)
    {
        if (cur->data.che == che)
            return;
        else if (che < cur->data.che)
            next = &cur->left;
        else if (che > cur->data.che)
            next = &cur->right;

        if (*next == nullptr)
        {
            Node* tmp = new Node;
            tmp->left = tmp->right = nullptr;
            Para p;
            p.che = che;
            p.cht = cht;
            tmp->data = p;
            *next = tmp;
            return;
        }

        cur = *next;
    }

}