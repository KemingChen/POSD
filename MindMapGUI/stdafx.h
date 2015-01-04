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
#include <vector>

#define MAX_WIDTH 90
#define INNER_PADDING 10
#define MIN_DOUBLE_CLICK_TIME 200

class Component;
typedef std::vector<Component*> NodeList;