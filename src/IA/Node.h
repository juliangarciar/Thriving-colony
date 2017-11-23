#ifndef NODE_H
#define NODE_H

class Node {
    
    public:
        Node();
        ~Node();

        virtual void question();

    protected:
        Node *father;
        Node **children;

    private:
};

#endif