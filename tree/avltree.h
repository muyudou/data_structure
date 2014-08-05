class AvlTree
{
public:
    int height(AvlNode *t) const
    {
        return t == NULL ? -1, t->height;
    }

    void insert(const Comparable &x, AvlNode *&t)
    {
        if (t == NULL)
        {
            AvlNode *node = new AvlNode(x, NULL, NULL);
            t = node;
            return;
        }
        if (x < root->element)
            insert(x, root->left);
        else if (x > root->element)
            insert(x, root->right);
        else
            return;
    }
private:
    struct AvlNode
    {
        Comparable element;
        AvlNode *left;
        AvlNode *right;
        int height;

        AvlNode(const Comparable &theElement, AvlNode *lt, 
                AvlNode *rt, int h = 0)
        {
            element = theElement;
            left = lt;
            right = rt;
            height = h;
        }
    };
    AvlNode *root;
};
