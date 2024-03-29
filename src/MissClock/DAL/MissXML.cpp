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
//     TiXmlElement *elemPic = new TiXmlElement("背景图片");
//     TiXmlText *elemPicText = new TiXmlText(pSkin->GetBGPicPath().utf8_str());
//     elemPic->LinkEndChild(elemPicText);
//     root->LinkEndChild(elemPic);
//     TiXmlElement *elemLoc = new TiXmlElement("区域代码");
//     TiXmlText *elemLocText = new TiXmlText(pSkin->GetLocale().utf8_str());
//     elemLoc->LinkEndChild(elemLocText);
//     root->LinkEndChild(elemLoc);
// 
//     TiXmlElement *elemShow = new TiXmlElement("显示条目");
//     root->LinkEndChild(elemShow);
//     int nCount = pSkin->GetElementSize();
//     for(int ix = 0;ix != nCount; ++ix)
//     {
//         TiXmlElement *elem = new TiXmlElement(pSkin->GetElement(ix).m_Name.utf8_str());
//         elem->SetAttribute("显示",pSkin->GetElement(ix).m_Show?1:0);
//         elem->SetAttribute("字体",pSkin->GetElement(ix).m_Font.GetFaceName().utf8_str());
//         elem->SetAttribute("字号",pSkin->GetElement(ix).m_Font.GetPointSize());
//         elem->SetAttribute("粗体",pSkin->GetElement(ix).m_Font.GetWeight());
//         elem->SetAttribute("斜体",pSkin->GetElement(ix).m_Font.GetStyle());
//         elem->SetAttribute("颜色",pSkin->GetElement(ix).m_Colour.GetAsString(wxC2S_HTML_SYNTAX).utf8_str());
//         elem->SetAttribute("对齐",wxString::Format(wxT("%.1f"),pSkin->GetElement(ix).m_Alignment).utf8_str());
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

    if (root)///检测主节点ApplictionConfig是否存在
    {
        ///背景图片节点
        //TiXmlElement * CurElement = root->FirstChildElement("背景图片");
        rapidxml::xml_node<>* CurElement = root->first_node("\xE8\x83\x8C\xE6\x99\xAF\xE5\x9B\xBE\xE7\x89\x87");

        ///背景图片节点检测开始
        if (CurElement)
        {
            //const char* CurStr = CurElement->GetText();
            const char* CurStr = CurElement->value();
            pSkin->SetBGPicPath(wxString(CurStr, wxConvUTF8));

            //pSkin->SetBGPicPath(wxString(CurElement->value(), wxConvUTF8, CurElement->value_size()));
            //wxMessageBox(BGS, _("背景图片节点检测"));
        }
        ///背景图片节点检测结束

        ///区域格式节点
        //CurElement = root->FirstChildElement("区域代码");
        CurElement = root->first_node("\xE5\x8C\xBA\xE5\x9F\x9F\xE4\xBB\xA3\xE7\xA0\x81");
        if (CurElement)
        {
            //const char* CurStr = CurElement->GetText();
            const char* CurStr = CurElement->value();

            pSkin->SetLocale( wxString(CurStr, wxConvUTF8) );
            ///wxMessageBox(BGS, _("区域格式节点检测"));
        }
        ///区域格式节点检测结束
        //CurElement = root->FirstChildElement("显示条目");
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

                //CurStr = CurElement->Attribute("显示");
                rapidxml::xml_attribute<>* CurAttr = CurElement->first_attribute("\xE6\x98\xBE\xE7\xA4\xBA");
                elem.m_Show=(wxString(CurAttr->value(), wxConvUTF8)==wxT("1"));

                //CurStr = CurElement->Attribute("字体");
                CurAttr = CurElement->first_attribute("\xE5\xAD\x97\xE4\xBD\x93");
                wxString fontname=wxString(CurAttr->value(), wxConvUTF8);

                //CurStr = CurElement->Attribute("字号");
                CurAttr = CurElement->first_attribute("\xE5\xAD\x97\xE5\x8F\xB7");
                int fontsize=atoi(CurAttr->value());

                //CurStr = CurElement->Attribute("粗体");
                CurAttr = CurElement->first_attribute("\xE7\xB2\x97\xE4\xBD\x93");
                int fontbold=atoi(CurAttr->value());

                //CurStr = CurElement->Attribute("斜体");
                CurAttr = CurElement->first_attribute("\xE6\x96\x9C\xE4\xBD\x93");
                int fontitalic=atoi(CurAttr->value());

                elem.m_Font = wxFont(fontsize,wxFONTFAMILY_DEFAULT, fontitalic,fontbold,false,fontname);

                //CurStr = CurElement->Attribute("颜色");
                CurAttr = CurElement->first_attribute("\xE9\xA2\x9C\xE8\x89\xB2");
                elem.m_Colour.Set(wxString(CurAttr->value(), wxConvUTF8));

                //CurStr = CurElement->Attribute("对齐");
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
    TiXmlElement *elem = new TiXmlElement("窗口尺寸");
    elem->SetAttribute("宽度",pRemindSkin->GetOverallWidth());
    elem->SetAttribute("最小高度",pRemindSkin->GetMinHeight());
    elem->SetAttribute("最大高度",pRemindSkin->GetMaxHeight());
    root->LinkEndChild(elem);

    elem = new TiXmlElement("关闭按钮");
    elem->SetAttribute("字体",pRemindSkin->GetCloseBtnInfo().fontBtn.GetFaceName().utf8_str());
    elem->SetAttribute("字号",pRemindSkin->GetCloseBtnInfo().fontBtn.GetPointSize());
    elem->SetAttribute("粗体",pRemindSkin->GetCloseBtnInfo().fontBtn.GetWeight());
    elem->SetAttribute("斜体",pRemindSkin->GetCloseBtnInfo().fontBtn.GetStyle());
    elem->SetAttribute("颜色",pRemindSkin->GetCloseBtnInfo().colorBtn.GetAsString(wxC2S_HTML_SYNTAX).utf8_str());
    elem->SetAttribute("X",pRemindSkin->GetCloseBtnInfo().ptPos.x);
    elem->SetAttribute("Y",pRemindSkin->GetCloseBtnInfo().ptPos.y);

    elemText = new TiXmlText(pRemindSkin->GetCloseBtnInfo().strBtnText.utf8_str());
    elem->LinkEndChild(elemText);
    root->LinkEndChild(elem);

    ///文字信息节点检测结束
    elem = new TiXmlElement("文字信息");
    elem->SetAttribute("字体",pRemindSkin->GetOutTextInfo().fontText.GetFaceName().utf8_str());
    elem->SetAttribute("字号",pRemindSkin->GetOutTextInfo().fontText.GetPointSize());
    elem->SetAttribute("粗体",pRemindSkin->GetOutTextInfo().fontText.GetWeight());
    elem->SetAttribute("斜体",pRemindSkin->GetOutTextInfo().fontText.GetStyle());
    elem->SetAttribute("颜色",pRemindSkin->GetOutTextInfo().colorText.GetAsString(wxC2S_HTML_SYNTAX).utf8_str());
    elem->SetAttribute("X",pRemindSkin->GetOutTextInfo().ptPos.x);
    elem->SetAttribute("Y",pRemindSkin->GetOutTextInfo().ptPos.y);
    elem->SetAttribute("宽度",pRemindSkin->GetOutTextInfo().nTextWidth);
    elem->SetAttribute("底部距离",pRemindSkin->GetOutTextInfo().nBottomHeight);

    elemText = new TiXmlText(pRemindSkin->GetOutTextInfo().strBitmap.utf8_str());
    elem->LinkEndChild(elemText);
    root->LinkEndChild(elem);

    elem = new TiXmlElement("窗口图案");
    root->LinkEndChild(elem);
    int nCount = pRemindSkin->GetPatternSize();
    for(int ix = 0;ix != nCount; ++ix)
    {
        TiXmlElement *e = new TiXmlElement("图案");
        e->SetAttribute("位置", pRemindSkin->GetPatternInfo(ix).ePos);
        elemText = new TiXmlText(pRemindSkin->GetPatternInfo(ix).strBitmap.utf8_str());
        e->LinkEndChild(elemText);
        elem->LinkEndChild(e);
    }

    elem = new TiXmlElement("窗口填充");
    root->LinkEndChild(elem);
    nCount = pRemindSkin->GetFillSize();
    for(int ix = 0;ix != nCount; ++ix)
    {
        TiXmlElement *e = new TiXmlElement("填充");
        e->SetAttribute("位置", pRemindSkin->GetFillInfo(ix).ePos);
        e->SetAttribute("尺寸", pRemindSkin->GetFillInfo(ix).nSize);
        e->SetAttribute("类型", pRemindSkin->GetFillInfo(ix).nType);
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
    if (root)///检测主节点ApplictionConfig是否存在
    {
        ///窗口尺寸节点
        TiXmlElement * CurElement = root->FirstChildElement("窗口尺寸");
        const char* CurStr;
        ///窗口尺寸节点检测开始
        if (CurElement)
        {
            CurStr = CurElement->Attribute("宽度");
            pRemindSkin->SetOverallWidth(atoi(CurStr));
            CurStr = CurElement->Attribute("最小高度");
            pRemindSkin->SetMinHeight(atoi(CurStr));
            CurStr = CurElement->Attribute("最大高度");
            pRemindSkin->SetMaxHeight(atoi(CurStr));
            //pRemindSkin->SetBGPicPath(wxString(CurStr, wxConvUTF8));
        }
        ///窗口尺寸节点检测结束

        ///关闭按钮节点
        CurElement = root->FirstChildElement("关闭按钮");
        if (CurElement)
        {
            MissRemindSkin::CloseBtnInfo btnInfo;
            CurStr = CurElement->GetText();
            btnInfo.strBtnText = wxString(CurStr, wxConvUTF8);

            CurStr = CurElement->Attribute("字体");
            wxString fontname=wxString(CurStr, wxConvUTF8);

            CurStr = CurElement->Attribute("字号");
            int fontsize=atoi(CurStr);

            CurStr = CurElement->Attribute("粗体");
            int fontbold=atoi(CurStr);

            CurStr = CurElement->Attribute("斜体");
            int fontitalic=atoi(CurStr);

            btnInfo.fontBtn = wxFont(fontsize,wxFONTFAMILY_DEFAULT, fontitalic,fontbold,false,fontname);

            CurStr = CurElement->Attribute("颜色");
            btnInfo.colorBtn.Set(wxString(CurStr, wxConvUTF8));

            CurStr = CurElement->Attribute("X");
            btnInfo.ptPos.x = atoi(CurStr);

            CurStr = CurElement->Attribute("Y");
            btnInfo.ptPos.y = atoi(CurStr);

            pRemindSkin->SetBtnInfo(btnInfo);
        }
        ///关闭按钮节点检测结束

        ///文字信息节点
        CurElement = root->FirstChildElement("文字信息");
        if (CurElement)
        {

            MissRemindSkin::OutTextInfo textInfo;

            CurStr = CurElement->Attribute("字体");
            wxString fontname=wxString(CurStr, wxConvUTF8);

            CurStr = CurElement->Attribute("字号");
            int fontsize=atoi(CurStr);

            CurStr = CurElement->Attribute("粗体");
            int fontbold=atoi(CurStr);

            CurStr = CurElement->Attribute("斜体");
            int fontitalic=atoi(CurStr);

            textInfo.fontText = wxFont(fontsize,wxFONTFAMILY_DEFAULT, fontitalic,fontbold,false,fontname);

            CurStr = CurElement->Attribute("颜色");
            textInfo.colorText.Set(wxString(CurStr, wxConvUTF8));

            CurStr = CurElement->Attribute("X");
            textInfo.ptPos.x = atoi(CurStr);

            CurStr = CurElement->Attribute("Y");
            textInfo.ptPos.y = atoi(CurStr);

            CurStr = CurElement->Attribute("宽度");
            textInfo.nTextWidth = atoi(CurStr);

            CurStr = CurElement->Attribute("底部距离");
            textInfo.nBottomHeight = atoi(CurStr);

            CurStr = CurElement->GetText();                       ///文字背景
            textInfo.strBitmap = wxString(CurStr, wxConvUTF8);

            pRemindSkin->SetTextInfo(textInfo);

        }
        ///文字信息节点检测结束

        ///窗口图案
        CurElement = root->FirstChildElement("窗口图案");
        CurElement = CurElement->FirstChildElement();
        MissRemindSkin::PatternInfo elemPattern;
        pRemindSkin->ClearPattern();
        while(CurElement)
        {
            CurStr = CurElement->Attribute("位置");
            elemPattern.ePos = static_cast<MissRemindSkin::PatternPos>(atoi(CurStr));

            CurStr = CurElement->GetText();
            elemPattern.strBitmap = wxString(CurStr, wxConvUTF8);

            pRemindSkin->AddPattern(elemPattern);
            CurElement=CurElement->NextSiblingElement();
        }
        ///窗口填充
        CurElement = root->FirstChildElement("窗口填充");
        CurElement = CurElement->FirstChildElement();
        MissRemindSkin::FillInfo elemFill;
        pRemindSkin->ClearFill();
        while(CurElement)
        {
            CurStr = CurElement->Attribute("位置");
            elemFill.ePos = static_cast<MissRemindSkin::FillPos>(atoi(CurStr));

            CurStr = CurElement->Attribute("尺寸");
            elemFill.nSize = atoi(CurStr);

            CurStr = CurElement->Attribute("类型");
            elemFill.nType = atoi(CurStr);

            CurStr = CurElement->GetText();
            elemFill.strBrush = wxString(CurStr, wxConvUTF8);

            pRemindSkin->AddFill(elemFill);
            CurElement=CurElement->NextSiblingElement();
        }
    }
}
*/
