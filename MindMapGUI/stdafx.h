// stdafx.h : �i�b�����Y�ɤ��]�t�зǪ��t�� Include �ɡA
// �άO�g�`�ϥΫo�ܤ��ܧ�
// �M�ױM�� Include �ɮ�
//
#pragma once

#include <SDKDDKVer.h>

#include <stdio.h>
#include <tchar.h>

// TODO:  �b���Ѧұz���{���һݭn����L���Y
#include <gtest/gtest_prod.h>
#include <string>
#include <list>
#include <vector>
#include "Component.h"
#include "Composite.h"
#include "Node.h"
#include "Root.h"

typedef std::vector<Component*> NodeList;

struct CompareComponent
{
    bool operator()(Component* first, Component* second)
    {
        return atoi(first->getId().c_str()) < atoi(second->getId().c_str());
    }
};