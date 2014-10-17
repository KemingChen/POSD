// stdafx.h : �i�b�����Y�ɤ��]�t�зǪ��t�� Include �ɡA
// �άO�g�`�ϥΫo�ܤ��ܧ�
// �M�ױM�� Include �ɮ�
//
#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

// TODO:  �b���Ѧұz���{���һݭn����L���Y
#include <string>
#include <list>
#include "Component.h"
#include "Composite.h"
#include "Node.h"
#include "Root.h"

typedef list<Component*> NodeList;

struct CompareComponent
{
    bool operator()(Component* first, Component* second)
    {
        return atoi(first->getId().c_str()) < atoi(second->getId().c_str());
    }
};