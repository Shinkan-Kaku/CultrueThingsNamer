#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CultrueThingsNamer.h"

class CultrueThingsNamer : public QMainWindow
{
    Q_OBJECT

public:
    CultrueThingsNamer(QWidget *parent = nullptr);
    ~CultrueThingsNamer();

private:
    Ui::CultrueThingsNamerClass ui;
};
