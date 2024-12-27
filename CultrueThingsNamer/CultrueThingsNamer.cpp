#include "CultrueThingsNamer.h"
#include "QCoreApplication";
#include "QFile";
#include "QtextStream";
#include "QString";
#include "QList";
#include "QDebug";
#include "qmessagebox";
#include "QRegularExpression";

#include < QJsonObject > 
#include < QJsonArray >
#include < QJsonDocument > 
#include < QJsonValue >
#include < QJsonParseError >

#include<QRandomGenerator>
#include<QClipboard>


QString rulesPath = "./rules/totalRules.json";
QString elementsPath = "./rules/totalElements.json";
QString UILangPath = "./UI_Lang.json";

QStringList generalCopyOptn;
QList<QString> generalCultureListEN;
QList<QString> generalCultureListREGName;
QList<QString> generalCultureListCN;
QList<QString> generalRuleNameList;
QList<QString> generalRuleElementsList;

QList<QString> spawnedNameCN;
QList<QString> spawnedNameEN;




QJsonDocument static loadFromJSONS(QString path)
{
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {

        QMessageBox msgbox;
        msgbox.setIcon(QMessageBox::Warning);
        msgbox.setText("file open failed:" + file.errorString());
        msgbox.exec();

    }
    QByteArray tgtjson = file.readAll();
    return QJsonDocument::fromJson(tgtjson);
}

QJsonObject ruleJsonObj = loadFromJSONS(rulesPath).object();
QJsonObject elementsJsonObj = loadFromJSONS(elementsPath).object();
QJsonObject UIStringTable = loadFromJSONS(UILangPath).object();

void buildupNameBySelectedElements(int indexInCulture,int indexInRule)
{


        


}

/*
    void onrmstabCEComboboxIndexChanged(int index)
    {


    }
    void onrmcanmtabCEComboBoxIndexChanged(int index)
    {

    }
*/
CultrueThingsNamer::CultrueThingsNamer(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    generalCopyOptn.append(UIStringTable.value("gnlCpyOptn_CN").toString());
    generalCopyOptn.append(UIStringTable.value("gnlCpyOptn_CNWS").toString());
    generalCopyOptn.append(UIStringTable.value("gnlCpyOptn_EN").toString());
    generalCopyOptn.append(UIStringTable.value("gnlCpyOptn_ENWS").toString());

    ui.rmstab_button_SpawnOptn->setText(UIStringTable.value("bnSpawn").toString());
    ui.rmpstab_button_spawnOptn->setText(UIStringTable.value("bnSpawn").toString());
    ui.rmcanmtab_button_SpawnOptn->setText(UIStringTable.value("bnSpawn").toString());

    ui.rmstab_button_CopyOptn->setText(UIStringTable.value("bnCopy").toString());
    ui.rmpstab_button_copyOptn->setText(UIStringTable.value("bnCopy").toString());
    ui.rmcanmtab_button_CopyOptn->setText(UIStringTable.value("bnCopy").toString());

    ui.rmstab_comboBox_CopyPhaseOptn->addItems(generalCopyOptn);
    ui.rmcanmtab_comboBox_CopyPhaseOptn->addItems(generalCopyOptn);

    ui.rmstab_result_textBrowser->setFontPointSize(30);
    ui.rmcanmtab_result_textBrowser->setFontPointSize(30);

    
    for (auto rootobj : ruleJsonObj)
    {
        generalCultureListREGName.append(ruleJsonObj.keys());
        generalCultureListEN.append(rootobj.toObject().value("ENName").toString());
        generalCultureListCN.append(rootobj.toObject().value("CHName").toString());
    }
    ui.rmstab_comboBox_CultureOptn->addItems(generalCultureListCN);
    ui.rmcanmtab_comboBox_CultureOptn->addItems(generalCultureListCN);

    connect
    (ui.rmstab_comboBox_CultureOptn, &QComboBox::currentIndexChanged, this, [=]
        {

            generalRuleNameList.clear();
            generalRuleElementsList.clear();
            QString tgtENName = generalCultureListREGName[ui.rmstab_comboBox_CultureOptn->currentIndex()];
            //ui.rmstab_result_textBrowser->setText(tgtENName);
            QJsonObject currentJsonObject = ruleJsonObj.value(tgtENName).toObject().value("CityName").toObject();
            for (auto crtJnObj : currentJsonObject)
            {
                generalRuleNameList.append(crtJnObj.toObject().value("RuleName").toString());
                generalRuleElementsList.append(crtJnObj.toObject().value("RuleElement").toString());
            }
            
            ui.rmstab_comboBox_RuleOptn->clear();
            ui.rmstab_comboBox_RuleOptn->addItems(generalRuleNameList);
            /*
            ui.rmstab_result_textBrowser->append("/n");
            for (auto s : ruleList)
            {
                ui.rmstab_result_textBrowser->append(s);
            }
            */
            
        }
    
    
    );

    connect(ui.rmstab_button_SpawnOptn,&QPushButton::clicked , this, [=] 
        {
            //buildupNameBySelectedElements(ui.rmcanmtab_comboBox_CultureOptn->currentIndex(), ui.rmstab_comboBox_RuleOptn->currentIndex());
            
            
            int indexInRule = ui.rmstab_comboBox_RuleOptn->currentIndex();
            int indexInCulture = ui.rmstab_comboBox_CultureOptn->currentIndex();
            if (!ui.rmstab_comboBox_RuleOptn->currentText().isNull())
            {
                spawnedNameEN.clear();
                spawnedNameCN.clear();

                QRegularExpression regex("\\S+;{1}\\S+");
                QRegularExpressionMatch mtc = regex.match(generalRuleElementsList[indexInRule]);
                if (mtc.hasMatch())
                {

                    QStringList ResultPart1 = generalRuleElementsList[indexInRule].split(";");
                    QJsonArray tgtArray;
                    for (auto at : ResultPart1)
                    {
                        if (at == "Space")
                        {
                            spawnedNameEN.append(" ");
                            spawnedNameCN.append(" ");
                        }
                        else
                        {
                            if (at.lastIndexOf(",") != -1)//Has OR
                            {
                                int tgtrmIndex = QRandomGenerator::global()->bounded(1, at.split(",").size() - 1);
                                QString tgt = at.split(",")[tgtrmIndex < 0 ? 0 : tgtrmIndex];
                                tgtArray = elementsJsonObj.value(generalCultureListREGName[indexInCulture]).toObject().value(tgt).toArray();
                            }
                            else
                            {
                                tgtArray = elementsJsonObj.value(generalCultureListREGName[indexInCulture]).toObject().value(at).toArray();
                            }
                            int rmNum = QRandomGenerator::global()->bounded(0, tgtArray.size() - 1);
                            spawnedNameEN.append(tgtArray[rmNum < 0 ? 0 : rmNum].toObject().value("EN").toString());
                            spawnedNameCN.append(tgtArray[rmNum < 0 ? 0 : rmNum].toObject().value("CN").toString());
                        }

                    }

                    QString Result;
                    for (auto s : spawnedNameCN)
                    {
                        Result.append(s + "");
                    }

                    for (auto s : spawnedNameEN)
                    {
                        Result.append(s);
                    }
                    ui.rmstab_result_textBrowser->clear();
                    //ui.rmstab_result_textBrowser->repaint();
                    ui.rmstab_result_textBrowser->setText(Result);
                }
                else
                {
                    QMessageBox msgbox;
                    msgbox.setIcon(QMessageBox::Warning);
                    msgbox.setText("error: rule stringTable not match");
                    msgbox.exec();
                }
            }
            else
            {
                QMessageBox msgbox;
                msgbox.setIcon(QMessageBox::Warning);
                msgbox.setText("error: this culture haven't name-build up elements yet");
                msgbox.exec();
            }
            /*
            QMessageBox msgbox;
            msgbox.setText(QString::number(indexInRule));
            msgbox.exec();
            */
            

            
        }
    );
    connect(ui.rmstab_button_CopyOptn,&QPushButton::clicked,this,[=]
        {
            if (!spawnedNameCN.isEmpty())
            {
                QClipboard* cb = QApplication::clipboard();
                QString Result;
                switch (ui.rmstab_comboBox_CopyPhaseOptn->currentIndex())
                {
                case 0:
                    for (auto s : spawnedNameCN)
                    {
                        Result.append(s);
                        Result.append(" ");
                    }
                    Result.removeLast();
                    break;
                case 1:
                    for (auto s : spawnedNameCN)
                    {
                        Result.append(s);
                    }
                    break;
                case 2:
                    for (auto s : spawnedNameEN)
                    {
                        Result.append(s);
                        Result.append(" ");
                    }
                    Result.removeLast();
                    break;
                case 3:
                    for(auto s:spawnedNameEN)
                    {
                        Result.append(s);
                    }
                    break;
                }
                
                
                cb->setText(Result);
                    
                
            }
            else
            {
                QMessageBox msgbox;
                msgbox.setIcon(QMessageBox::Warning);
                msgbox.setText("No Result Existing!");
                msgbox.exec();
            }

        }
    );
    /*
    -------------------------------------------------------------------------------------------------------------------------
    */

    connect(ui.rmcanmtab_comboBox_CultureOptn, &QComboBox::currentIndexChanged, this, [=]
        {
            generalRuleNameList.clear();
            generalRuleElementsList.clear();
            QString tgtENName = generalCultureListREGName[ui.rmcanmtab_comboBox_CultureOptn->currentIndex()];
            QJsonObject currentJsonObject = ruleJsonObj.value(tgtENName).toObject().value("CharacterName").toObject();
            for (auto crtJnObj : currentJsonObject)
            {
                generalRuleNameList.append(crtJnObj.toObject().value("RuleName").toString());
                generalRuleElementsList.append(crtJnObj.toObject().value("RuleElement").toString());
            }

            ui.rmcanmtab_comboBox_RuleOptn->clear();
            ui.rmcanmtab_comboBox_RuleOptn->addItems(generalRuleNameList);
        }
    );

    connect(ui.rmcanmtab_button_SpawnOptn, &QPushButton::clicked,this,[=]
        {
            int indexInRule = ui.rmcanmtab_comboBox_RuleOptn->currentIndex();
            int indexInCulture = ui.rmcanmtab_comboBox_CultureOptn->currentIndex();
            if (!ui.rmcanmtab_comboBox_RuleOptn->currentText().isNull())
            {
                spawnedNameEN.clear();
                spawnedNameCN.clear();

                QRegularExpression regex("\\S+;{1}\\S+");
                QRegularExpressionMatch mtc = regex.match(generalRuleElementsList[indexInRule]);
                if (mtc.hasMatch())
                {

                    QStringList ResultPart1 = generalRuleElementsList[indexInRule].split(";");
                    QJsonArray tgtArray;
                    for (auto at : ResultPart1)
                    {
                        if (at == "Space")
                        {
                            spawnedNameEN.append(" ");
                            spawnedNameCN.append(" ");
                        }
                        else
                        {
                            if (at.lastIndexOf(",") != -1)//Has OR
                            {
                                int tgtrmIndex = QRandomGenerator::global()->bounded(0, at.split(",").size() - 1);
                                QString tgt = at.split(",")[tgtrmIndex < 0 ? 0 : tgtrmIndex];
                                tgtArray = elementsJsonObj.value(generalCultureListREGName[indexInCulture]).toObject().value(tgt).toArray();
                            }
                            else
                            {
                                tgtArray = elementsJsonObj.value(generalCultureListREGName[indexInCulture]).toObject().value(at).toArray();
                            }
                            int rmNum = QRandomGenerator::global()->bounded(0, tgtArray.size() - 1);
                            spawnedNameEN.append(tgtArray[rmNum < 0 ? 0 : rmNum].toObject().value("EN").toString());
                            spawnedNameCN.append(tgtArray[rmNum < 0 ? 0 : rmNum].toObject().value("CN").toString());
                        }

                    }

                    QString Result;
                    for (auto s : spawnedNameCN)
                    {
                        Result.append(s + "");
                    }

                    for (auto s : spawnedNameEN)
                    {
                        Result.append(s);
                    }
                    ui.rmcanmtab_result_textBrowser->clear();
                    ui.rmcanmtab_result_textBrowser->setText(Result);
                }
                else
                {
                    QMessageBox msgbox;
                    msgbox.setIcon(QMessageBox::Warning);
                    msgbox.setText("error: rule stringTable not match");
                    msgbox.exec();
                }
            }
            else
            {
                QMessageBox msgbox;
                msgbox.setIcon(QMessageBox::Warning);
                msgbox.setText("error: this culture haven't name-build up elements yet");
                msgbox.exec();
            }
        }

    );
    connect(ui.rmcanmtab_button_CopyOptn,&QPushButton::clicked,this,[=]
        {
            if (!spawnedNameCN.isEmpty())
            {
                QClipboard* cb = QApplication::clipboard();
                QString Result;
                switch (ui.rmcanmtab_comboBox_CopyPhaseOptn->currentIndex())
                {
                case 0:
                    for (auto s : spawnedNameCN)
                    {
                        Result.append(s);
                        Result.append(" ");
                    }
                    Result.removeLast();
                    break;
                case 1:
                    for (auto s : spawnedNameCN)
                    {
                        Result.append(s);
                    }
                    break;
                case 2:
                    for (auto s : spawnedNameEN)
                    {
                        Result.append(s);
                        Result.append(" ");
                    }
                    Result.removeLast();
                    break;
                case 3:
                    for (auto s : spawnedNameEN)
                    {
                        Result.append(s);
                    }
                    break;
                }


                cb->setText(Result);


            }
            else
            {
                QMessageBox msgbox;
                msgbox.setIcon(QMessageBox::Warning);
                msgbox.setText("No Result Existing!");
                msgbox.exec();
            }
        }
    );


}



CultrueThingsNamer::~CultrueThingsNamer()
{

}
