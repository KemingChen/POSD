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

#define DECORATE_PADDING 1
#define MAX_WIDTH 100
#define INNER_PADDING 10
#define MIN_DOUBLE_CLICK_TIME 200
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define OUTTER_X_PADDING 20
#define OUTTER_Y_PADDING 5

class Component;
typedef std::vector<Component*> NodeList;