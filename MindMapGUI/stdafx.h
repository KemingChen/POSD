// stdafx.h : 可在此標頭檔中包含標準的系統 Include 檔，
// 或是經常使用卻很少變更的
// 專案專用 Include 檔案
//
#pragma once

#include <SDKDDKVer.h>

#include <stdio.h>
#include <tchar.h>

// TODO:  在此參考您的程式所需要的其他標頭
#include <gtest/gtest_prod.h>
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