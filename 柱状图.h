#pragma once

#include<string>
#include <iostream>

#include <cmath>
#include<graphics.h>
#include "myalgorithm.h"

inline void changeprecistion(std::wstring& ws, int precision) {
    auto len = ws.length(); int i = 0;
    for (; i < len; i++) {
        if (ws[i] == '.')
            break;
    }
    if (i + precision + 1 >= len)
        return;
    ws = ws.substr(0, mystl::mymin((size_t)(i + precision + 1), len));
}
template<typename RandomIt>
inline void analysis(RandomIt begin, RandomIt end, std::wstring title = L"ͳ��ͼ")
{
    int size = end - begin; auto& arr = begin;
    // ��ʼ��ͼ��ģʽ
    initgraph(1000, 600, SHOWCONSOLE);  // ���Ը�����Ҫ�������ڴ�С
    setbkcolor(WHITE);
    cleardevice();
    setlinecolor(BLACK);
    int margin_top = 40;
    int margin_bottom = 60;
    int margin_left = 70;
    int margin_right = 30;
    int width = getwidth();
    int height = getheight();
    int ��״ͼ�ɷ����� = width - margin_left - margin_right;
    int ��״ͼ�ɷ���߶� = height - (margin_top + margin_bottom);
    int ÿ�����ӿ��ÿ�� = ��״ͼ�ɷ����� / size;
    double maxData = 0;
    const int size1 = 22, size2 = 32;
    for (int i = 0; i < size; ++i) {
        if (arr[i] > maxData) {
            maxData = arr[i];
        }
    }
    maxData = maxData == 0 ? 1 : maxData;
    double scale = static_cast<double>(��״ͼ�ɷ���߶�) / static_cast<double>(maxData);

    // ����Ӧ����ʾ�Ŀ̶�ֵ
    double interval = 50.0;  // ����Ϊ���ʵĿ̶ȼ��
    double remainder = fmod(maxData, interval);
    double maxScale = maxData;
    if (remainder != 0) {
        maxScale = maxData + interval - remainder; // �����ֵ��չ���̶�ֵ��������
    }

    // ���Ʊ���


    settextstyle(size2, 0, _T("΢���ź�"));
    settextcolor(BLACK);
    RECT r = { 0, 0, width, 50 };
    drawtext(title.c_str(), &r, DT_CENTER | DT_VCENTER);

    settextstyle(size1, 0, _T("΢���ź�"));
    std::wstring ttt;
    ttt = std::to_wstring(maxData);
    r = { 0, margin_top - 10, margin_left,margin_top + 30 };
    //��ͳ��ͼy���ʾ�̶�
    line(r.right - 20, r.top + size1 / 2, r.right - 10, r.top + size1 / 2);
    changeprecistion(ttt, 1);
    drawtext(ttt.c_str(), &r, DT_CENTER | DT_VCENTER);

    ttt = std::to_wstring(maxData / 2);
    r = { 0, margin_top + ��״ͼ�ɷ���߶� / 2 - 10, margin_left,margin_top + ��״ͼ�ɷ���߶� / 2 + 30 };
    line(r.right - 20, r.top + size1 / 2, r.right - 10, r.top + size1 / 2);
    changeprecistion(ttt, 1);
    drawtext(ttt.c_str(), &r, DT_CENTER | DT_VCENTER);

    ttt = std::to_wstring(maxData / 4 * 3);
    r = { 0, margin_top + ��״ͼ�ɷ���߶� / 4 - 10, margin_left,margin_top + ��״ͼ�ɷ���߶� / 4 + 30 };
    line(r.right - 20, r.top + size1 / 2, r.right - 10, r.top + size1 / 2);
    changeprecistion(ttt, 1);
    drawtext(ttt.c_str(), &r, DT_CENTER | DT_VCENTER);

    ttt = std::to_wstring(maxData / 4);
    r = { 0, margin_top + ��״ͼ�ɷ���߶� / 2 + ��״ͼ�ɷ���߶� / 4 - 10, margin_left,margin_top + ��״ͼ�ɷ���߶� / 2 + ��״ͼ�ɷ���߶� / 4 + 30 };
    line(r.right - 20, r.top + size1 / 2, r.right - 10, r.top + size1 / 2);
    changeprecistion(ttt, 1);
    drawtext(ttt.c_str(), &r, DT_CENTER | DT_VCENTER);
    //���ԭ��
    ttt = L"0";
    r = { 0, margin_top + ��״ͼ�ɷ���߶� - 10, margin_left,margin_top + ��״ͼ�ɷ���߶� + 30 };
    drawtext(ttt.c_str(), &r, DT_CENTER | DT_VCENTER);


    // �����������
    scale = static_cast<double>(��״ͼ�ɷ���߶�) / static_cast<double>(maxData);

    settextstyle(size1, 0, _T("Times New Roman"));
    // chart
    for (int i = 0; i < size; ++i) {

        int x1 = margin_left + i * ÿ�����ӿ��ÿ�� + ÿ�����ӿ��ÿ�� / 5;

        int x2 = x1 + ÿ�����ӿ��ÿ�� - ÿ�����ӿ��ÿ�� / 5;
        int y2 = margin_top + ��״ͼ�ɷ���߶�;
        int y1 = y2 - arr[i] * scale;
        setfillcolor(BLUE);
        fillrectangle(x1, y1, x2, y2);
        settextcolor(BLACK);

        wchar_t msg[50];
        wsprintfW(msg, L"%.1f", arr[i]);
        RECT r = { x1, y1 - 20, x2,y1 };
        drawtext(msg, &r, DT_CENTER | DT_VCENTER);
        drawtext(L" ", &r, DT_CENTER | DT_VCENTER);
        wsprintfW(msg, L"��%d��", i + 1);

        r = { x1, y2 + 20, x2,y2 + 40 };
        drawtext(msg, &r, DT_CENTER | DT_VCENTER);
    }

    //x

    line(margin_left - 10, margin_top + ��״ͼ�ɷ���߶� + 10, width - margin_right + 10, margin_top + ��״ͼ�ɷ���߶� + 10
    );
    line(width - margin_right + 2,
        margin_top + ��״ͼ�ɷ���߶� + 2,
        width - margin_right + 10,
        margin_top + ��״ͼ�ɷ���߶� + 10
    );
    line(width - margin_right + 2,
        margin_top + ��״ͼ�ɷ���߶� + 18,
        width - margin_right + 10,
        margin_top + ��״ͼ�ɷ���߶� + 10
    );
    // y
    line(margin_left - 10, margin_top, margin_left - 10, margin_top + ��״ͼ�ɷ���߶� + 10
    );
    line(margin_left - 10,
        margin_top,
        margin_left - 18,
        margin_top + 8
    );
    line(margin_left - 10,
        margin_top, margin_left - 2,
        margin_top + 8
    );
    //ԭ��
    fillcircle(margin_left - 10, margin_top + ��״ͼ�ɷ���߶� + 10, 3); std::wcin >> ttt; closegraph();
}

