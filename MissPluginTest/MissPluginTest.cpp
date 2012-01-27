#include "MissPluginTest.h"
#include "../MissAPI/interface/IMissMain.h"
#include "../MissAPI/interface/IMissTaskIcon.h"
#include "../MissAPI/interface/IMissHotKey.h"

#include <vector>


MissPluginTest::MissPluginTest(IMissMain* pParent):
MissPluginBase(pParent)
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
    GetMain()->GetTaskIcon()->ShowBalloon(wxT("标题测试"),wxT("内容测试。"));
}

void MissPluginTest::ModifyHotKey(int nFuncIndex, const wxString& strHotKey)
{
}

void MissPluginTest::LoadPlugin()
{
    std::vector<SHotKey> vecHotKey(1);
    vecHotKey[0].strDescription = wxT("弹出气泡提示。");
    vecHotKey[0].strHotKey = wxT("Win+Q");
    IMissMain*   q = GetMain();
    IMissHotKey* p = q->GetHotKey();
    p->RegHotKeys(vecHotKey,this);
}
