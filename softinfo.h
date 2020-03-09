#ifndef SOFTINFO_H
#define SOFTINFO_H

#pragma once
#include <vector>
#include <Windows.h>
#include <windows.h>
#include <qt_windows.h>
#include <QDebug>

struct SoftInfoStruct
{
    // 软件名
    QString m_strSoftName;
    // 软件版本号
    QString m_strSoftVersion;
    // 软件安装目录
    QString m_strInstallLocation;
    // 软件发布厂商
    QString m_strPublisher;
    // 主程序所在完整路径
    QString m_strMainProPath;
    // 卸载exe所在完整路径
    QString m_strUninstallPth;
};

class SoftInfo
{
public:
    SoftInfo();

    // 获取所有已安装常用软件名
    void init_soft_list();

    //void get_soft_name(std::vector<LPCTSTR>& softName);
private:
    std::vector<SoftInfoStruct> m_softInfoArr;
    std::vector<SoftInfoStruct> m_sysPatchesArr;
};

#endif // SOFTINFO_H
