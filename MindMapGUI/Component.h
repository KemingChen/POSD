#pragma once
using namespace std;
#include <vector>
#include "stdafx.h"
#include "NodeVisitor.h"
#include "IGraphic.h"
#include "Rect.h"
#include "ComponentType.h"

#define LEFT -1
#define NONE 0
#define RIGHT 1

class Component
{
    private:
        string _id;
        string _description;
        bool _isSelected;
        int _level;
        int _side;

    protected:
        Rect _rect;

    public:
        Component(int id, string description);

        // ID
        string getId();
        void setId(int id);

        // Description
        string getDescription();
        void setDescription(string description);

        string toString();

        // Selected
        bool getIsSelected();
        void setIsSelected(bool value);

        // Level
        int getLevel();
        void setLevel(int level);

        // Position
        int getX();
        int getY();
        virtual void setPosition(int x, int y);

        // Rectangle Size
        int getWidth();
        int getHeight();
        virtual void setRectSize(int width, int height);

        // Side
        int getSide();
        void setSide(int side);

        Rect getBoundingRect();

        // Virtual Method
        virtual Component* getBackFromNode() = 0;
        virtual string getTypeName() = 0;
        virtual Component* clone() = 0;
        virtual string getMap() = 0;
        virtual void addChild(Component* node, Component* backFromNode = NULL, int side = NONE) = 0;
        virtual void removeChild(Component* node) = 0;
        virtual void removeAllChild() = 0;
        virtual Component* getParent() = 0;
        virtual void setParent(Component* node) = 0;
        virtual void addParent(Component* node) = 0;
        virtual void addSibling(Component* node) = 0;
        virtual bool isSelfAreParentLastNode() = 0;
        virtual NodeList* getNodeList() = 0;
        virtual void accept(NodeVisitor* visitor) = 0;
        virtual void draw(IGraphic* painter) = 0;
        virtual Component* getRealComponent() = 0;
        virtual ~Component();
};

struct CompareComponent
{
    bool operator()(Component* first, Component* second)
    {
        return atoi(first->getId().c_str()) < atoi(second->getId().c_str());
    }
};