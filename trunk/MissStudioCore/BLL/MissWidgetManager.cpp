#include "MissWidgetManager.h"

#include "../Widget/MissWidget.h"

MissWidgetManager::MissWidgetManager()
{
    //ctor
}

MissWidgetManager::~MissWidgetManager()
{
    //dtor
}

std::tr1::shared_ptr<wxFrame> MissWidgetManager::CreateWidget()
{
    return new MissWidget(0L);
}
