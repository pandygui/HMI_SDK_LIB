#include "SettingsEmergencyUI.h"
#include <QDebug>
#include "Home/app/Home.h"
#include "Home/data/Settings/SettingsEmergencyData.h"
SettingsEmergencyUI::SettingsEmergencyUI(QWidget *parent)
    :QWidget(parent)
    ,CView(Home::eViewId_Settings_Emergency)
    ,m_pBackBtn(NULL)
    ,m_pTitleLabel(NULL)
{
    this->setGeometry(QRect(0,40,800,440));
    this->setStyleSheet("QWidget{border:none;background:transparent;}");
    m_pBackgroundLabel = new QLabel(this);
    m_pBackgroundLabel->setGeometry(QRect(0,0,800,440));
    m_pBackgroundLabel->setStyleSheet("QLabel{border-image:url(:/images/bg.png);background:transparent;}");
    m_pBackgroundLabel->lower();
    m_pBackgroundLabel->show();
    m_pBackBtn = new CPushButton(this);
    m_pBackBtn->setStyleSheet("QPushButton{border-image:url(:/Settings/button_back.png);background:transparent;}");
    m_pBackBtn->setGeometry(QRect(16,21,29,29));
    m_pBackBtn->setFocusPolicy(Qt::NoFocus);
    m_pBackBtn->show();

    m_pTitleLabel = new QLabel(this);
    m_pTitleLabel->setGeometry(QRect(54,21,300,29));
    m_pTitleLabel->setStyleSheet("QLabel{color:#4BA9FF;font-size:24px;border:none;background:transparent;}");
    m_pTitleLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    m_pTitleLabel->setText(tr("Setting"));
    m_pTitleLabel->show();
    m_pVList = new CVListWidget(this);
    m_pVList->setGeometry(54,67,718,386);
    m_pVList->SetLeftMargin(0);
    m_pVList->SetSplitLine(":/Settings/line.png",":/Settings/line.png");
    m_pVList->SetScrollBarStyle(4);
    m_pVList->SetItemBackgroundInfo("",":/Settings/list_push_bg.png","");
    QStringList titieList;
    titieList <<tr("Emergency rescue") ;

    for(int i = 0 ; i < titieList.size() ;i++)
    {
        CListWidgetItem item (QSize(718,57));
        QStringList list;
        list<<":/Settings/button_h_on.png"<<""<<"";
        item.SetSpecifiedID(-1);
        item.SetSpecifiedIDStatus(1);
        item.AddText(QRect(0,0,300,57),titieList.at(i),Qt::AlignLeft|Qt::AlignVCenter,24);
        item.AddButton(QRect(647,0,71,57),list);
        m_pVList->InsertItem(i,item);
    }
    m_pVList->show();

    InitConnect();
}

SettingsEmergencyUI::~SettingsEmergencyUI()
{

}

void SettingsEmergencyUI::InitConnect()
{
    connect(m_pBackBtn,SIGNAL(clicked()),this,SLOT(OnBack()),Qt::UniqueConnection);

    connect(m_pVList,SIGNAL(listButtonReleased(int,int)),this,SLOT(OnListBtnClick(int,int)),Qt::UniqueConnection);
    connect(m_pVList,SIGNAL(listItemReleased(int)),this,SLOT(OnListClick(int)),Qt::UniqueConnection);

}

void SettingsEmergencyUI::OnBack()
{
    Home::Inst()->ViewBack();
}

void SettingsEmergencyUI::viewAction(int state)
{

}



void SettingsEmergencyUI::OnListBtnClick(int index, int btnIndex)
{
    qDebug()<<"SettingsEmergencyUI index = " << index <<" btnIndex = " <<btnIndex;
    int idStatus =  m_pVList->GetSpecifiedIDStatus(index);

    if(idStatus == 0)
    {
        QStringList list;
        list<<":/Settings/button_h_on.png"<<"none"<<"none";
        m_pVList->SetItemButtonPixmap(index,btnIndex,list);
        m_pVList->SetSpecifiedIDStatus(index,1);

        //TODO : add  open code
        SettingsEmergencyData::Inst()->SetEmergencRescueStatus("Open");
    }
    else if(idStatus == 1)
    {
        QStringList list;
        list<<":/Settings/button_h_close.png"<<"none"<<"none";
        m_pVList->SetItemButtonPixmap(index,btnIndex,list);
        m_pVList->SetSpecifiedIDStatus(index,0);

        //TODO: add open code
        SettingsEmergencyData::Inst()->SetEmergencRescueStatus("Close");
    }
}

void SettingsEmergencyUI::OnListClick(int index)
{

}
