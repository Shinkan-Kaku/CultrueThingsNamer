#include "CultrueThingsNamer.h"
#include "QCoreApplication"
#include "QFile"
#include "QtextStream"
#include "QString"
#include "QList"
#include "QDebug"
#include "qmessagebox"
#include "QRegularExpression"

#include < QJsonObject > 
#include < QJsonArray >
#include < QJsonDocument > 
#include < QJsonValue >
#include < QJsonParseError >

#include<QRandomGenerator>
#include<QClipboard>
#include <QIcon>


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

QString LE_SpawnMode_1 = "CN";
QString LE_SpawnMode_2 = "CN";
QString LE_SpawnMode_3 = "CN";

bool lineInputRequired_1 = false, lineInputRequired_2 = false, lineInputRequired_3 = false;



QJsonDocument static loadFromJSONS(QString path)
{
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {

        QMessageBox msgbox;
        msgbox.setIcon(QMessageBox::Critical);
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
    setWindowIcon(QIcon("./CultrueThingsNamer.ico"));
    setWindowTitle(UIStringTable.value("title_CultureThingNamer").toString());

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

    ui.rmpstab_ENMode_checkBox_1->setText(UIStringTable.value("ckBoxENMode").toString());
    ui.rmpstab_ENMode_checkBox_2->setText(UIStringTable.value("ckBoxENMode").toString());
    ui.rmpstab_ENMode_checkBox_3->setText(UIStringTable.value("ckBoxENMode").toString());

    ui.rmstab_comboBox_CopyPhaseOptn->addItems(generalCopyOptn);
    ui.rmcanmtab_comboBox_CopyPhaseOptn->addItems(generalCopyOptn);

    QFont settedFont;
    settedFont.setPointSizeF(30);

    ui.rmstab_result_textBrowser->setFontPointSize(30);
    ui.rmcanmtab_result_textBrowser->setFontPointSize(30);

    

    ui.rmpstab_result_lineEd_1->setFont(settedFont);
    ui.rmpstab_result_lineEd_2->setFont(settedFont);
    ui.rmpstab_result_lineEd_3->setFont(settedFont);

    ui.rmpstab_result_lineEd_1->setReadOnly(true);
    ui.rmpstab_result_lineEd_2->setReadOnly(true);
    ui.rmpstab_result_lineEd_3->setReadOnly(true);

    LE_SpawnMode_1 = "CN";
    LE_SpawnMode_2 = "CN";
    LE_SpawnMode_3 = "CN";

    
    for (auto rootobj : ruleJsonObj)
    {
        generalCultureListREGName.append(ruleJsonObj.keys());
        generalCultureListEN.append(rootobj.toObject().value("ENName").toString());
        generalCultureListCN.append(rootobj.toObject().value("CHName").toString());
    }
    ui.rmstab_comboBox_CultureOptn->addItems(generalCultureListCN);
    ui.rmpstab_comboBox_CultureOptn->addItems(generalCultureListCN);
    ui.rmcanmtab_comboBox_CultureOptn->addItems(generalCultureListCN);

    /*------------------------------------------------------------------(P1)-----------------------------------------------------------*/

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
                            try
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
                            catch (const std::runtime_error& e)
                            {
                                QMessageBox msgbox;
                                msgbox.setIcon(QMessageBox::Critical);
                                msgbox.setText(e.what());
                                msgbox.exec();
                            }



                            
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
                    msgbox.setIcon(QMessageBox::Critical);
                    msgbox.setText("error: rule stringTable not match");
                    msgbox.exec();
                }
            }
            else
            {
                QMessageBox msgbox;
                msgbox.setIcon(QMessageBox::Critical);
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
                msgbox.setIcon(QMessageBox::Critical);
                msgbox.setText("No Result Existing!");
                msgbox.exec();
            }

        }
    );
    /*
    ---------------------------------------------------(P2--)------------------------------------------------------------------
    */
    connect(ui.rmpstab_comboBox_CultureOptn, &QComboBox::currentIndexChanged, this, [=] 
        {
            generalRuleNameList.clear();
            generalRuleElementsList.clear();
            QString tgtENName = generalCultureListREGName[ui.rmpstab_comboBox_CultureOptn->currentIndex()];

            QJsonObject currentJsonObject = elementsJsonObj.value(tgtENName).toObject();
            QStringList elementsList = currentJsonObject.keys();
            for (auto crtKeys : elementsList)
            {
                
                generalRuleNameList.append(crtKeys);
                generalRuleElementsList.append(crtKeys);
            }
            generalRuleNameList.append("Input");
            generalRuleElementsList.append("Input");

            ui.rmpstab_result_comboBox_1->clear();
            ui.rmpstab_result_comboBox_2->clear();
            ui.rmpstab_result_comboBox_3->clear();
            ui.rmpstab_result_comboBox_1->addItems(generalRuleNameList);
            ui.rmpstab_result_comboBox_2->addItems(generalRuleNameList);
            ui.rmpstab_result_comboBox_3->addItems(generalRuleNameList);
            /*
            ui.rmstab_result_textBrowser->append("/n");
            for (auto s : ruleList)
            {
                ui.rmstab_result_textBrowser->append(s);
            }
            */
        });

    connect(ui.rmpstab_result_comboBox_1, &QComboBox::currentIndexChanged, this, [=] 
        {
            lineInputRequired_1 = (ui.rmpstab_result_comboBox_1->currentText() == "Input");
            ui.rmpstab_result_lineEd_1->setReadOnly(!lineInputRequired_1);
        });
    connect(ui.rmpstab_result_comboBox_2, &QComboBox::currentIndexChanged, this, [=] 
        {
            lineInputRequired_2 = (ui.rmpstab_result_comboBox_2->currentText() == "Input");
            ui.rmpstab_result_lineEd_2->setReadOnly(!lineInputRequired_2);
        });
    connect(ui.rmpstab_result_comboBox_3, &QComboBox::currentIndexChanged, this, [=] 
        {
            lineInputRequired_3 = (ui.rmpstab_result_comboBox_3->currentText() == "Input");
            ui.rmpstab_result_lineEd_3->setReadOnly(!lineInputRequired_3);
        });

    connect(ui.rmpstab_ENMode_checkBox_1, &QCheckBox::checkStateChanged, this, [=] 
        {
            LE_SpawnMode_1 = ui.rmpstab_ENMode_checkBox_1->isChecked() ? "EN" : "CN";  
        });

    connect(ui.rmpstab_ENMode_checkBox_2, &QCheckBox::checkStateChanged, this, [=]
        {
            LE_SpawnMode_2 = ui.rmpstab_ENMode_checkBox_2->isChecked() ? "EN" : "CN";
        });

    connect(ui.rmpstab_ENMode_checkBox_3, &QCheckBox::checkStateChanged, this, [=]
        {
            LE_SpawnMode_3 = ui.rmpstab_ENMode_checkBox_3->isChecked() ? "EN" : "CN";
        });

    connect(ui.rmpstab_button_spawnOptn, &QPushButton::clicked, this, [=] 
        {

                QJsonObject crtAdresElementJson = elementsJsonObj.value(generalCultureListREGName[ui.rmpstab_comboBox_CultureOptn->currentIndex()]).toObject();




            if ( !(lineInputRequired_1 || lineInputRequired_2 || lineInputRequired_3))
            {
                
                QList<QJsonArray> rmElement_JSON_Adres;
                rmElement_JSON_Adres.append( crtAdresElementJson.value(generalRuleElementsList[ui.rmpstab_result_comboBox_1->currentIndex()]).toArray());
                rmElement_JSON_Adres.append( crtAdresElementJson.value(generalRuleElementsList[ui.rmpstab_result_comboBox_2->currentIndex()]).toArray());
                rmElement_JSON_Adres.append( crtAdresElementJson.value(generalRuleElementsList[ui.rmpstab_result_comboBox_3->currentIndex()]).toArray());

                QList<int> rmIndexForElements;
                for (auto Adres : rmElement_JSON_Adres)
                {
                    int i = QRandomGenerator::global()->bounded(0, Adres.size()) - 1;
                    i = i < 0 ? 0 : i;
                    rmIndexForElements.append(i);

                }
                
                ui.rmpstab_result_lineEd_1->setText(rmElement_JSON_Adres[0].at(rmIndexForElements[0]).toObject().value(LE_SpawnMode_1).toString());
                ui.rmpstab_result_lineEd_2->setText(rmElement_JSON_Adres[1].at(rmIndexForElements[1]).toObject().value(LE_SpawnMode_2).toString());
                ui.rmpstab_result_lineEd_3->setText(rmElement_JSON_Adres[2].at(rmIndexForElements[2]).toObject().value(LE_SpawnMode_3).toString());

            }
            else
            {

                if (!lineInputRequired_1)
                {
                    QJsonArray rmElement_JSON_Adres_1 = crtAdresElementJson.value(generalRuleElementsList[ui.rmpstab_result_comboBox_1->currentIndex()]).toArray();
                    int rmIndexForElement_1 = QRandomGenerator::global()->bounded(0, rmElement_JSON_Adres_1.size()) - 1;
                    rmIndexForElement_1 = rmIndexForElement_1 < 0 ? 0 : rmIndexForElement_1;
                    ui.rmpstab_result_lineEd_1->setText(rmElement_JSON_Adres_1[rmIndexForElement_1].toObject().value(LE_SpawnMode_1).toString());

                }
                if (!lineInputRequired_2)
                {
                    QJsonArray rmElement_JSON_Adres_2 = crtAdresElementJson.value(generalRuleElementsList[ui.rmpstab_result_comboBox_2->currentIndex()]).toArray();
                    int rmIndexForElement_2 = QRandomGenerator::global()->bounded(0, rmElement_JSON_Adres_2.size()) - 1;
                    rmIndexForElement_2 = rmIndexForElement_2 < 0 ? 0 : rmIndexForElement_2;
                    ui.rmpstab_result_lineEd_2->setText(rmElement_JSON_Adres_2[rmIndexForElement_2].toObject().value(LE_SpawnMode_2).toString());
                }
                if (!lineInputRequired_3)
                {
                    QJsonArray rmElement_JSON_Adres_3 = crtAdresElementJson.value(generalRuleElementsList[ui.rmpstab_result_comboBox_3->currentIndex()]).toArray();
                    int rmIndexForElement_3 = QRandomGenerator::global()->bounded(0, rmElement_JSON_Adres_3.size()) - 1;
                    rmIndexForElement_3 = rmIndexForElement_3 < 0 ? 0 : rmIndexForElement_3;
                    ui.rmpstab_result_lineEd_3->setText(rmElement_JSON_Adres_3[rmIndexForElement_3].toObject().value(LE_SpawnMode_3).toString());
                }
                

            }




        });
    connect(ui.rmpstab_button_copyOptn, &QPushButton::clicked, this, [=] 
        {
            QClipboard* cb = QApplication::clipboard();
            QString Result;
            Result.append(ui.rmpstab_result_lineEd_1->text());
            Result.append(ui.rmpstab_result_lineEd_2->text());
            Result.append(ui.rmpstab_result_lineEd_3->text());
            cb->setText(Result);

        });







    /*
    ---------------------------------------------------(P3  )-------------------------------------------------------------------
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

                            try
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
                            catch (const std::runtime_error& e)
                            {
                                QMessageBox msgbox;
                                msgbox.setIcon(QMessageBox::Critical);
                                msgbox.setText(e.what());
                                msgbox.exec();
                            }



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
                    msgbox.setIcon(QMessageBox::Critical);
                    msgbox.setText("error: rule stringTable not match");
                    msgbox.exec();
                }
            }
            else
            {
                QMessageBox msgbox;
                msgbox.setIcon(QMessageBox::Critical);
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
                msgbox.setIcon(QMessageBox::Critical);
                msgbox.setText("No Result Existing!");
                msgbox.exec();
            }
        }
    );


}



CultrueThingsNamer::~CultrueThingsNamer()
{

}
