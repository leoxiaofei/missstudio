//#include "../StdAfx.h"
#include "MissXML.h"
#include "../BLL/MissSkin.h"
//#include "MissRemindSkin.h"
#include "../../MissTools/rapidxml_utils.hpp"

bool MissXML::SaveSkin(const MissSkin* pSkin)
{
    bool ret(false);
//     TiXmlDocument * xmlDocs = new TiXmlDocument();
//     TiXmlDeclaration * xmlDec = new TiXmlDeclaration("1.0", "UTF-8", "yes");
//     xmlDocs->LinkEndChild(xmlDec);
// 
//     TiXmlElement* root = new TiXmlElement("ApplictionConfig");
//     xmlDocs->LinkEndChild(root);
// 
//     TiXmlElement *elemPic = new TiXmlElement("����ͼƬ");
//     TiXmlText *elemPicText = new TiXmlText(pSkin->GetBGPicPath().utf8_str());
//     elemPic->LinkEndChild(elemPicText);
//     root->LinkEndChild(elemPic);
//     TiXmlElement *elemLoc = new TiXmlElement("�������");
//     TiXmlText *elemLocText = new TiXmlText(pSkin->GetLocale().utf8_str());
//     elemLoc->LinkEndChild(elemLocText);
//     root->LinkEndChild(elemLoc);
// 
//     TiXmlElement *elemShow = new TiXmlElement("��ʾ��Ŀ");
//     root->LinkEndChild(elemShow);
//     int nCount = pSkin->GetElementSize();
//     for(int ix = 0;ix != nCount; ++ix)
//     {
//         TiXmlElement *elem = new TiXmlElement(pSkin->GetElement(ix).m_Name.utf8_str());
//         elem->SetAttribute("��ʾ",pSkin->GetElement(ix).m_Show?1:0);
//         elem->SetAttribute("����",pSkin->GetElement(ix).m_Font.GetFaceName().utf8_str());
//         elem->SetAttribute("�ֺ�",pSkin->GetElement(ix).m_Font.GetPointSize());
//         elem->SetAttribute("����",pSkin->GetElement(ix).m_Font.GetWeight());
//         elem->SetAttribute("б��",pSkin->GetElement(ix).m_Font.GetStyle());
//         elem->SetAttribute("��ɫ",pSkin->GetElement(ix).m_Colour.GetAsString(wxC2S_HTML_SYNTAX).utf8_str());
//         elem->SetAttribute("����",wxString::Format(wxT("%.1f"),pSkin->GetElement(ix).m_Alignment).utf8_str());
//         elem->SetAttribute("X",pSkin->GetElement(ix).m_X);
//         elem->SetAttribute("Y",pSkin->GetElement(ix).m_Y);
//         TiXmlText *elemText = new TiXmlText(wxString(pSkin->GetElement(ix).m_Content.c_str(),wxConvLocal ).utf8_str());
//         elem->LinkEndChild(elemText);
//         elemShow->LinkEndChild(elem);
//     }
//     wxString SkinAddr = pSkin->GetSkinPath() + wxT("ClockSkin.xml");
//     ret=xmlDocs->SaveFile(SkinAddr.mb_str());
//     delete xmlDocs;
    return ret;
}

void MissXML::LoadSkin(MissSkin* pSkin, const wxString& strSkinPath)
{
    //pSkin->SetSkinName( SkinName );
    //wxString SkinAddr = wxString::Format(wxT("%s\\Skin\\%s\\"),Miss::GetAppExePath().c_str(), SkinName.c_str());
    pSkin->SetSkinPath(strSkinPath);

    //TiXmlDocument doc((strSkinPath + wxT("ClockSkin.xml")).mb_str());
    rapidxml::file<> fdoc((strSkinPath + wxT("ClockSkin.xml")).mb_str());  

    //doc.LoadFile();
    rapidxml::xml_document<> doc;
    doc.parse<0>(fdoc.data());   

    //TiXmlElement* root = doc.FirstChildElement("ApplictionConfig");
    rapidxml::xml_node<>* root = doc.first_node("ApplictionConfig");  

    if (root)///������ڵ�ApplictionConfig�Ƿ����
    {
        ///����ͼƬ�ڵ�
        //TiXmlElement * CurElement = root->FirstChildElement("����ͼƬ");
        rapidxml::xml_node<>* CurElement = root->first_node("\xE8\x83\x8C\xE6\x99\xAF\xE5\x9B\xBE\xE7\x89\x87");

        ///����ͼƬ�ڵ��⿪ʼ
        if (CurElement)
        {
            //const char* CurStr = CurElement->GetText();
            const char* CurStr = CurElement->value();
            pSkin->SetBGPicPath(wxString(CurStr, wxConvUTF8));

            //pSkin->SetBGPicPath(wxString(CurElement->value(), wxConvUTF8, CurElement->value_size()));
            //wxMessageBox(BGS, _("����ͼƬ�ڵ���"));
        }
        ///����ͼƬ�ڵ������

        ///�����ʽ�ڵ�
        //CurElement = root->FirstChildElement("�������");
        CurElement = root->first_node("\xE5\x8C\xBA\xE5\x9F\x9F\xE4\xBB\xA3\xE7\xA0\x81");
        if (CurElement)
        {
            //const char* CurStr = CurElement->GetText();
            const char* CurStr = CurElement->value();

            pSkin->SetLocale( wxString(CurStr, wxConvUTF8) );
            ///wxMessageBox(BGS, _("�����ʽ�ڵ���"));
        }
        ///�����ʽ�ڵ������
        //CurElement = root->FirstChildElement("��ʾ��Ŀ");
        CurElement = root->first_node("\xE6\x98\xBE\xE7\xA4\xBA\xE6\x9D\xA1\xE7\x9B\xAE");

        if (CurElement)
        {
            //CurElement = CurElement->FirstChildElement();
            CurElement = CurElement->first_node();

            MissElement elem;
            pSkin->ClearElement();
            while(CurElement)
            {
                //const char* CurStr = CurElement->Value();
                const char* CurStr = CurElement->name();
                elem.m_Name=wxString(CurStr, wxConvUTF8);

                //CurStr = CurElement->Attribute("��ʾ");
                rapidxml::xml_attribute<>* CurAttr = CurElement->first_attribute("\xE6\x98\xBE\xE7\xA4\xBA");
                elem.m_Show=(wxString(CurAttr->value(), wxConvUTF8)==wxT("1"));

                //CurStr = CurElement->Attribute("����");
                CurAttr = CurElement->first_attribute("\xE5\xAD\x97\xE4\xBD\x93");
                wxString fontname=wxString(CurAttr->value(), wxConvUTF8);

                //CurStr = CurElement->Attribute("�ֺ�");
                CurAttr = CurElement->first_attribute("\xE5\xAD\x97\xE5\x8F\xB7");
                int fontsize=atoi(CurAttr->value());

                //CurStr = CurElement->Attribute("����");
                CurAttr = CurElement->first_attribute("\xE7\xB2\x97\xE4\xBD\x93");
                int fontbold=atoi(CurAttr->value());

                //CurStr = CurElement->Attribute("б��");
                CurAttr = CurElement->first_attribute("\xE6\x96\x9C\xE4\xBD\x93");
                int fontitalic=atoi(CurAttr->value());

                elem.m_Font = wxFont(fontsize,wxFONTFAMILY_DEFAULT, fontitalic,fontbold,false,fontname);

                //CurStr = CurElement->Attribute("��ɫ");
                CurAttr = CurElement->first_attribute("\xE9\xA2\x9C\xE8\x89\xB2");
                elem.m_Colour.Set(wxString(CurAttr->value(), wxConvUTF8));

                //CurStr = CurElement->Attribute("����");
                CurAttr = CurElement->first_attribute("\xE5\xAF\xB9\xE9\xBD\x90");
                elem.m_Alignment = atof(CurAttr->value());

                //CurStr = CurElement->Attribute("X");
                CurAttr = CurElement->first_attribute("X");
                elem.m_X = atoi(CurAttr->value());

                //CurStr = CurElement->Attribute("Y");
                CurAttr = CurElement->first_attribute("Y");
                elem.m_Y = atoi(CurAttr->value());

                //CurStr = CurElement->GetText();
                CurStr = CurElement->value();
                elem.m_Content = wxString(CurStr, wxConvUTF8).mb_str();

                pSkin->AddElement(elem);
                //CurElement=CurElement->NextSiblingElement();
                CurElement = CurElement->next_sibling();

            }
        }
    }
}

/*
bool MissXML::SaveRemindSkin(const MissRemindSkin* pRemindSkin)
{
    bool ret(false);
    TiXmlDocument * xmlDocs = new TiXmlDocument();
    TiXmlDeclaration * xmlDec = new TiXmlDeclaration("1.0", "UTF-8", "yes");
    xmlDocs->LinkEndChild(xmlDec);

    TiXmlElement* root = new TiXmlElement("ApplictionConfig");
    xmlDocs->LinkEndChild(root);

    TiXmlText *elemText(NULL);
    TiXmlElement *elem = new TiXmlElement("���ڳߴ�");
    elem->SetAttribute("���",pRemindSkin->GetOverallWidth());
    elem->SetAttribute("��С�߶�",pRemindSkin->GetMinHeight());
    elem->SetAttribute("���߶�",pRemindSkin->GetMaxHeight());
    root->LinkEndChild(elem);

    elem = new TiXmlElement("�رհ�ť");
    elem->SetAttribute("����",pRemindSkin->GetCloseBtnInfo().fontBtn.GetFaceName().utf8_str());
    elem->SetAttribute("�ֺ�",pRemindSkin->GetCloseBtnInfo().fontBtn.GetPointSize());
    elem->SetAttribute("����",pRemindSkin->GetCloseBtnInfo().fontBtn.GetWeight());
    elem->SetAttribute("б��",pRemindSkin->GetCloseBtnInfo().fontBtn.GetStyle());
    elem->SetAttribute("��ɫ",pRemindSkin->GetCloseBtnInfo().colorBtn.GetAsString(wxC2S_HTML_SYNTAX).utf8_str());
    elem->SetAttribute("X",pRemindSkin->GetCloseBtnInfo().ptPos.x);
    elem->SetAttribute("Y",pRemindSkin->GetCloseBtnInfo().ptPos.y);

    elemText = new TiXmlText(pRemindSkin->GetCloseBtnInfo().strBtnText.utf8_str());
    elem->LinkEndChild(elemText);
    root->LinkEndChild(elem);

    ///������Ϣ�ڵ������
    elem = new TiXmlElement("������Ϣ");
    elem->SetAttribute("����",pRemindSkin->GetOutTextInfo().fontText.GetFaceName().utf8_str());
    elem->SetAttribute("�ֺ�",pRemindSkin->GetOutTextInfo().fontText.GetPointSize());
    elem->SetAttribute("����",pRemindSkin->GetOutTextInfo().fontText.GetWeight());
    elem->SetAttribute("б��",pRemindSkin->GetOutTextInfo().fontText.GetStyle());
    elem->SetAttribute("��ɫ",pRemindSkin->GetOutTextInfo().colorText.GetAsString(wxC2S_HTML_SYNTAX).utf8_str());
    elem->SetAttribute("X",pRemindSkin->GetOutTextInfo().ptPos.x);
    elem->SetAttribute("Y",pRemindSkin->GetOutTextInfo().ptPos.y);
    elem->SetAttribute("���",pRemindSkin->GetOutTextInfo().nTextWidth);
    elem->SetAttribute("�ײ�����",pRemindSkin->GetOutTextInfo().nBottomHeight);

    elemText = new TiXmlText(pRemindSkin->GetOutTextInfo().strBitmap.utf8_str());
    elem->LinkEndChild(elemText);
    root->LinkEndChild(elem);

    elem = new TiXmlElement("����ͼ��");
    root->LinkEndChild(elem);
    int nCount = pRemindSkin->GetPatternSize();
    for(int ix = 0;ix != nCount; ++ix)
    {
        TiXmlElement *e = new TiXmlElement("ͼ��");
        e->SetAttribute("λ��", pRemindSkin->GetPatternInfo(ix).ePos);
        elemText = new TiXmlText(pRemindSkin->GetPatternInfo(ix).strBitmap.utf8_str());
        e->LinkEndChild(elemText);
        elem->LinkEndChild(e);
    }

    elem = new TiXmlElement("�������");
    root->LinkEndChild(elem);
    nCount = pRemindSkin->GetFillSize();
    for(int ix = 0;ix != nCount; ++ix)
    {
        TiXmlElement *e = new TiXmlElement("���");
        e->SetAttribute("λ��", pRemindSkin->GetFillInfo(ix).ePos);
        e->SetAttribute("�ߴ�", pRemindSkin->GetFillInfo(ix).nSize);
        e->SetAttribute("����", pRemindSkin->GetFillInfo(ix).nType);
        elemText = new TiXmlText(pRemindSkin->GetFillInfo(ix).strBrush.utf8_str());
        e->LinkEndChild(elemText);
        elem->LinkEndChild(e);
    }

    wxString SkinAddr = pRemindSkin->GetSkinPath() + wxT("RemindSkin.xml");
    ret=xmlDocs->SaveFile(SkinAddr.mb_str());
    delete xmlDocs;
    return ret;
}

void MissXML::LoadRemindSkin(MissRemindSkin* pRemindSkin, const wxString& SkinName)
{
    wxString SkinAddr = wxString::Format(wxT("Skin\\%s\\"),SkinName.c_str());
    pRemindSkin->SetSkinPath(SkinAddr);

    SkinAddr += wxT("RemindSkin.xml");
    TiXmlDocument doc(SkinAddr.mb_str());
    doc.LoadFile();
    TiXmlElement* root = doc.FirstChildElement("ApplictionConfig");
    if (root)///������ڵ�ApplictionConfig�Ƿ����
    {
        ///���ڳߴ�ڵ�
        TiXmlElement * CurElement = root->FirstChildElement("���ڳߴ�");
        const char* CurStr;
        ///���ڳߴ�ڵ��⿪ʼ
        if (CurElement)
        {
            CurStr = CurElement->Attribute("���");
            pRemindSkin->SetOverallWidth(atoi(CurStr));
            CurStr = CurElement->Attribute("��С�߶�");
            pRemindSkin->SetMinHeight(atoi(CurStr));
            CurStr = CurElement->Attribute("���߶�");
            pRemindSkin->SetMaxHeight(atoi(CurStr));
            //pRemindSkin->SetBGPicPath(wxString(CurStr, wxConvUTF8));
        }
        ///���ڳߴ�ڵ������

        ///�رհ�ť�ڵ�
        CurElement = root->FirstChildElement("�رհ�ť");
        if (CurElement)
        {
            MissRemindSkin::CloseBtnInfo btnInfo;
            CurStr = CurElement->GetText();
            btnInfo.strBtnText = wxString(CurStr, wxConvUTF8);

            CurStr = CurElement->Attribute("����");
            wxString fontname=wxString(CurStr, wxConvUTF8);

            CurStr = CurElement->Attribute("�ֺ�");
            int fontsize=atoi(CurStr);

            CurStr = CurElement->Attribute("����");
            int fontbold=atoi(CurStr);

            CurStr = CurElement->Attribute("б��");
            int fontitalic=atoi(CurStr);

            btnInfo.fontBtn = wxFont(fontsize,wxFONTFAMILY_DEFAULT, fontitalic,fontbold,false,fontname);

            CurStr = CurElement->Attribute("��ɫ");
            btnInfo.colorBtn.Set(wxString(CurStr, wxConvUTF8));

            CurStr = CurElement->Attribute("X");
            btnInfo.ptPos.x = atoi(CurStr);

            CurStr = CurElement->Attribute("Y");
            btnInfo.ptPos.y = atoi(CurStr);

            pRemindSkin->SetBtnInfo(btnInfo);
        }
        ///�رհ�ť�ڵ������

        ///������Ϣ�ڵ�
        CurElement = root->FirstChildElement("������Ϣ");
        if (CurElement)
        {

            MissRemindSkin::OutTextInfo textInfo;

            CurStr = CurElement->Attribute("����");
            wxString fontname=wxString(CurStr, wxConvUTF8);

            CurStr = CurElement->Attribute("�ֺ�");
            int fontsize=atoi(CurStr);

            CurStr = CurElement->Attribute("����");
            int fontbold=atoi(CurStr);

            CurStr = CurElement->Attribute("б��");
            int fontitalic=atoi(CurStr);

            textInfo.fontText = wxFont(fontsize,wxFONTFAMILY_DEFAULT, fontitalic,fontbold,false,fontname);

            CurStr = CurElement->Attribute("��ɫ");
            textInfo.colorText.Set(wxString(CurStr, wxConvUTF8));

            CurStr = CurElement->Attribute("X");
            textInfo.ptPos.x = atoi(CurStr);

            CurStr = CurElement->Attribute("Y");
            textInfo.ptPos.y = atoi(CurStr);

            CurStr = CurElement->Attribute("���");
            textInfo.nTextWidth = atoi(CurStr);

            CurStr = CurElement->Attribute("�ײ�����");
            textInfo.nBottomHeight = atoi(CurStr);

            CurStr = CurElement->GetText();                       ///���ֱ���
            textInfo.strBitmap = wxString(CurStr, wxConvUTF8);

            pRemindSkin->SetTextInfo(textInfo);

        }
        ///������Ϣ�ڵ������

        ///����ͼ��
        CurElement = root->FirstChildElement("����ͼ��");
        CurElement = CurElement->FirstChildElement();
        MissRemindSkin::PatternInfo elemPattern;
        pRemindSkin->ClearPattern();
        while(CurElement)
        {
            CurStr = CurElement->Attribute("λ��");
            elemPattern.ePos = static_cast<MissRemindSkin::PatternPos>(atoi(CurStr));

            CurStr = CurElement->GetText();
            elemPattern.strBitmap = wxString(CurStr, wxConvUTF8);

            pRemindSkin->AddPattern(elemPattern);
            CurElement=CurElement->NextSiblingElement();
        }
        ///�������
        CurElement = root->FirstChildElement("�������");
        CurElement = CurElement->FirstChildElement();
        MissRemindSkin::FillInfo elemFill;
        pRemindSkin->ClearFill();
        while(CurElement)
        {
            CurStr = CurElement->Attribute("λ��");
            elemFill.ePos = static_cast<MissRemindSkin::FillPos>(atoi(CurStr));

            CurStr = CurElement->Attribute("�ߴ�");
            elemFill.nSize = atoi(CurStr);

            CurStr = CurElement->Attribute("����");
            elemFill.nType = atoi(CurStr);

            CurStr = CurElement->GetText();
            elemFill.strBrush = wxString(CurStr, wxConvUTF8);

            pRemindSkin->AddFill(elemFill);
            CurElement=CurElement->NextSiblingElement();
        }
    }
}
*/
