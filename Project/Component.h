#pragma once
using namespace std;

class Component
{
        friend class NodeTest;
        FRIEND_TEST(NodeTest, setId);
        FRIEND_TEST(NodeTest, setDescription);
        FRIEND_TEST(NodeTest, getParent);
        FRIEND_TEST(NodeTest, setParent);
        FRIEND_TEST(NodeTest, toString);

    protected:
        // Protected Variable
        string _id;
        string _description;
        string _typeName;
        Component* _parentNode;

    public:
        typedef list<Component*> NodeList;

        // Public Method
        Component(int id);
        string getId();
        void setId(int id);
        string getTypeName();
        string getDescription();
        void setDescription(string description);
        Component* getParent();
        string toString();
        virtual string getMap() = 0;
        virtual void addChild(Component* node) = 0;
        virtual void removeChild(Component* node) = 0;
        virtual void removeAllChild() = 0;
        virtual void addParent(Component* node) = 0;
        virtual void addSibling(Component* node) = 0;
        virtual bool isSelfAreParentLastNode() = 0;
        virtual NodeList* getNodeList() = 0;
        virtual ~Component();
};