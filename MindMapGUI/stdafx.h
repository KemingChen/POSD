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

#define DECORATE_PADDING 2
#define MAX_WIDTH 100
#define INNER_PADDING 10
#define MIN_DOUBLE_CLICK_TIME 200
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define OUTTER_X_PADDING 20
#define OUTTER_Y_PADDING 5

#define NO_SELECTED -1
#define SPLITE "#"
#define SPACE " "
#define ENCODED_SPACE "&nbsp;"

class Component;
typedef std::vector<Component*> NodeList;