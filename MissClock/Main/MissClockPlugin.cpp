#include "MissClockPlugin.h"
#include "../../MissAPI/interface/IMissMain.h"
#include "../../MissAPI/interface/IMissTaskIcon.h"
#include "../../MissAPI/interface/IMissHotKey.h"
#include "../../MissAPI/interface/IMissConfig.h"
#include "../../MissAPI/interface/IMissWidgetManager.h"

#include <vector>

#include "MissClockWidget.h"


MissClockPlugin::MissClockPlugin():
MissPluginBase(),
MissHotKeyFuncBase(),
MissWidgetFactoryBase()
{
    //ctor
    SPlugInfo info;
    info.strPluginName = wxT("迷失日历时钟");
    info.strVersion = wxT("1.0.0");
    info.strSpecification = wxT("迷失日历时钟插件");
    info.strAuthor = wxT("leoxiaofei");
    info.strEmail = wxT("xxffsoft@163.com");
    info.strWeb = wxT("http://www.leoxiaofei.com");
    SetPlugInfo(info);
}

MissClockPlugin::~MissClockPlugin()
{
    //dtor
}

void MissClockPlugin::RunFunc(int nFuncIndex)
{
    GetMain()->GetTaskIcon()->ShowBalloon(wxString::Format(wxT("内容%d测试。"),nFuncIndex));
    /*
    if(nFuncIndex == 1)
    {
        MissWidgetFunc *pFunc = new MissWidgetFunc();
        MissWidgetUpdateFunc *pUpdate= GetMain()->GetWidget()->CreateWidget(pFunc);
        GetMain()->RegSecTimer(pUpdate);
    }
    */
}

void MissClockPlugin::ModifiedHotKey(int nFuncIndex, const wxString& strHotKey)
{
    std::tr1::shared_ptr<IMissConfig> config = GetMain()->GetConfig();
    config->Write(wxString::Format(wxT("函数%d"),nFuncIndex), strHotKey);
}

void MissClockPlugin::LoadPlugin(const std::tr1::shared_ptr<IMissMain>& pParent)
{
    MissPluginBase::LoadPlugin(pParent);
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

    std::vector<wxString> vecWidgetName;
    vecWidgetName.push_back(wxT("日历时钟"));
    GetMain()->GetWidgetManager()->RegWidgetFactory(this,vecWidgetName);
    //GetMain()->GetHotKey()->RegHotKeys(vecHotKey,this);
}

MissWidgetFuncBase* MissClockPlugin::CreateWidgetFunc(unsigned int nIndex)
{
    return new MissClockWidget();
}

void MissClockPlugin::CreateSuccessed(MissWidgetUpdateFunc* pUpdate)
{
    GetMain()->RegSecTimer(pUpdate);
}
