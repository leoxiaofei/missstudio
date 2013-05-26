#include "MissPluginMain.h"

#include "../Common/MissGlobal.h"
#include "MissCommunicate.h"
#include "MissHotKeyFunc.h"

#include "MissAPI/interface/IMissStorage.h"
#include "MissAPI/interface/IMissNetwork.h"

#include <vector>
#include <iostream>

using std::tr1::shared_ptr;

class MissPluginMain::Impl
{
public:
    shared_ptr<MissHotKeyFunc> pHotKeyFunc;
	shared_ptr<MissCommunicate> pCommunicate;	
};

MissPluginMain::MissPluginMain()
: MissPluginBase()
, m_pImpl(new Impl)
{
    //ctor
	Init();
}

MissPluginMain::~MissPluginMain()
{
    //dtor
}

void MissPluginMain::Init()
{
	m_pImpl->pHotKeyFunc = shared_ptr<MissHotKeyFunc>(new MissHotKeyFunc());
	m_pImpl->pCommunicate = shared_ptr<MissCommunicate>(new MissCommunicate());

	m_pImpl->pHotKeyFunc->GetHandle()->Bind(wxEVT_HOTKEYFUNC, &MissPluginMain::OnHotkey, this);

}

void MissPluginMain::LoadPlugin()
{
    MissGlobal::IMain = GetMain();
    shared_ptr<MissConfigFile> ptConfig;
    if (shared_ptr<IMissStorage> ptStorage = GetMain()->QueryIF<IMissStorage>(IF_STORAGE))
    {
        ptConfig = ptStorage->GetConfigFile(wxT("config.ini"));
		///�����ȼ�����
		m_pImpl->pHotKeyFunc->InitHotkey(ptConfig);
    }

	///��������
	if (shared_ptr<IMissNetwork> ptNetwork = GetMain()->QueryIF<IMissNetwork>(IF_NETWORK))
	{
		std::tr1::shared_ptr<IMissUDP> ptUDP = ptNetwork->GetUDP();
		///����ͨѶ����
		m_pImpl->pCommunicate->InitNet(ptUDP);
	}
	

}

void MissPluginMain::UnloadPlugin()
{
}

bool MissPluginMain::GetPlugInfo( SPlugInfo& info ) const
{
    info.strPluginName = wxT("��ʧ��Q");
    info.strVersion = wxT("1.0.0");
    info.strSpecification = wxT("���ھ������ļ�ʹͨѶ����");
    info.strAuthor = wxT("leoxiaofei");
    info.strEmail = wxT("xxffsoft@163.com");
    info.strWeb = wxT("http://www.leoxiaofei.com");
    return true;
}

wxString MissPluginMain::GetPluginName() const
{
    return wxT("��ʧ��Q");
}

wxString MissPluginMain::GetPluginGUID() const
{
    return wxT("296341CA-4262-423d-A3F1-15CB12AD4CEC");
}

void MissPluginMain::OnHotkey( wxCommandEvent& event )
{
	std::cout<<event.GetId()<<std::endl;
}
