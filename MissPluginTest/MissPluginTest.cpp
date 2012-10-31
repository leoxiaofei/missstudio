#include "MissPluginTest.h"
#include "../MissAPI/interface/IMissMain.h"
#include "../MissAPI/interface/IMissTaskIcon.h"
#include "../MissAPI/interface/IMissHotKey.h"
#include "../MissAPI/interface/IMissConfig.h"
#include "../MissAPI/interface/IMissWidgetManager.h"

#include <vector>

#include "MissWidgetFunc.h"


MissPluginTest::MissPluginTest():
MissPluginBase(),
MissHotKeyFuncBase(),
MissWidgetFactoryBase()
{
    //ctor
    SPlugInfo info;
    info.strPluginName = wxT("迷失测试插件");
    info.strVersion = wxT("1.0.0");
    info.strSpecification = wxT("这是迷失用来测试插件功能的插件");
    info.strAuthor = wxT("leoxiaofei");
    info.strEmail = wxT("xxffsoft@163.com");
    info.strWeb = wxT("http://www.leoxiaofei.com");
    SetPlugInfo(info);
}

MissPluginTest::~MissPluginTest()
{
    //dtor
}

void MissPluginTest::RunFunc(int nFuncIndex)
{
    if(nFuncIndex == 1)
    {
        GetMain()->GetTaskIcon()->ShowBalloon(wxString::Format(wxT("内容%d测试。"),nFuncIndex));
        std::vector<wxString> vecWidgetName;
        vecWidgetName.push_back(wxT("Widget测试"));
        GetMain()->GetWidgetManager()->RegWidgetFactory(this, vecWidgetName);
//        MissWidgetFunc *pFunc = new MissWidgetFunc();
//        MissWidgetUpdateFunc *pUpdate= GetMain()->GetWidget()->CreateWidget(pFunc);
//        GetMain()->RegSecTimer(pUpdate);
    }
}

void MissPluginTest::ModifiedHotKey(int nFuncIndex, const wxString& strHotKey)
{
    std::tr1::shared_ptr<IMissConfig> config = GetMain()->GetConfig();
    config->Write(wxString::Format(wxT("函数%d"),nFuncIndex), strHotKey);
}

void MissPluginTest::LoadPlugin()
{
    HotKeyDataSet vecHotKey(2);
    std::tr1::shared_ptr<IMissConfig> config = GetMain()->GetConfig();
    //wxString strHotkey;
    vecHotKey[0].strFuncDesc = wxT("弹出气泡提示。");
    if(!config->Read(wxT("函数0"),vecHotKey[0].strHotKey))
    {
        vecHotKey[0].strHotKey = wxT("Win+Q");
    }

    vecHotKey[1].strFuncDesc = wxT("弹出气泡提示2。");
    if(!config->Read(wxT("函数1"),vecHotKey[1].strHotKey))
    {
        vecHotKey[1].strHotKey = wxT("Win+W");
    }

    GetMain()->GetHotKey()->RegHotKeys(vecHotKey,this);
}

MissWidgetFuncBase* MissPluginTest::CreateWidgetFunc(unsigned int nIndex)
{
    return new MissWidgetFunc();
}

void MissPluginTest::CreateSuccessed(MissWidgetUpdateFunc* pUpdate)
{
    GetMain()->RegSecTimer(pUpdate);
}
