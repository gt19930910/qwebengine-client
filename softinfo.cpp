#include "softinfo.h"

SoftInfo::SoftInfo()
{
    init_soft_list();
}

void SoftInfo::init_soft_list()
{
    HKEY hkResult;           // 将要打开键的句柄
    auto ret = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
                            TEXT("SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall"),
                            0,
                            KEY_ALL_ACCESS,
                            &hkResult);
    if (ERROR_SUCCESS != ret) {
        qDebug() << "error";
        return;
    }

    HKEY hkRKey;
    DWORD dwKeyLen = 255;
    DWORD dwNameLen = 255;
    DWORD dwType = REG_BINARY|REG_DWORD|REG_EXPAND_SZ|REG_MULTI_SZ|REG_NONE|REG_SZ;
    DWORD index = 0;
    TCHAR szKeyName[255] = {0};        // 注册表项名称
    TCHAR szBuffer[255] = {0};
    struct SoftInfoStruct softinfo;

    while (ERROR_NO_MORE_ITEMS != RegEnumKeyEx(hkResult, index, szKeyName, &dwKeyLen, 0, NULL, NULL, NULL))
    {
        //此处将TCHAR转成QString
        QString strMidReg = "SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\";
        QString strKeyName = QString::fromWCharArray(szKeyName);
        strMidReg.append(strKeyName);
        //qDebug() << strMidReg;

        if (!strKeyName.isEmpty()) {
            index++;

            QByteArray ba = strMidReg.toLocal8Bit();
            const char* FULLPATH = ba.constData();
            if (RegOpenKeyExA(HKEY_LOCAL_MACHINE,
                              FULLPATH,
                              0,
                              KEY_ALL_ACCESS,
                              &hkRKey) == ERROR_SUCCESS) {

                RegQueryValueEx(hkRKey, TEXT("DisplayName"), 0, &dwType, (LPBYTE)szBuffer, &dwNameLen);
                softinfo.m_strSoftName = QString::fromWCharArray(szBuffer);
                dwNameLen = 255;
                memset(szBuffer, 0, 255);

                RegQueryValueEx(hkRKey, TEXT("DisplayVersion"), 0, &dwType, (LPBYTE)szBuffer, &dwNameLen);
                softinfo.m_strSoftVersion = QString::fromWCharArray(szBuffer);
                dwNameLen = 255;
                memset(szBuffer, 0, 255);

                RegQueryValueEx(hkRKey, TEXT("InstallLocation"), 0, &dwType, (LPBYTE)szBuffer, &dwNameLen);
                softinfo.m_strInstallLocation = QString::fromWCharArray(szBuffer);
                dwNameLen = 255;
                memset(szBuffer, 0, 255);

                RegQueryValueEx(hkRKey, TEXT("Publisher"), 0, &dwType, (LPBYTE)szBuffer, &dwNameLen);
                softinfo.m_strPublisher = QString::fromWCharArray(szBuffer);
                dwNameLen = 255;

                RegQueryValueEx(hkRKey, TEXT("InstallLocation"), 0, &dwType, (LPBYTE)szBuffer, &dwNameLen);
                softinfo.m_strMainProPath = QString::fromWCharArray(szBuffer);
                dwNameLen = 255;
                memset(szBuffer, 0, 255);

                RegQueryValueEx(hkRKey, TEXT("UninstallString"), 0, &dwType, (LPBYTE)szBuffer, &dwNameLen);
                softinfo.m_strUninstallPth = QString::fromWCharArray(szBuffer);
                dwNameLen = 255;
                memset(szBuffer, 0, 255);

                if (!softinfo.m_strSoftName.isEmpty()) {
                    qDebug() << softinfo.m_strSoftName;

//                    if(strKeyName.GetAt(0) == 'K' && strKeyName.GetAt(1) == 'B')
//                        m_sysPatchesArr.push_back(softinfo);
//                    else
                    m_softInfoArr.push_back(softinfo);
                }
            }
            //清零供下一个使用
            dwKeyLen = 255;
            memset(szKeyName, 0, 255);
        }
    }
    qDebug() << "index:" << index;
    RegCloseKey(hkResult);
}
