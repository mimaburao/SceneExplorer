#include <QWidget>
#include "optiondialog.h"

OptionDialog::OptionDialog(QWidget* parent)
    : QDialog(parent,
              //Qt::WindowFlags())
              ((Qt::WindowTitleHint | Qt::WindowFlags()) & ~Qt::WindowContextHelpButtonHint))
{
    ui.setupUi(this);
    setWindowTitle(tr("option"));
}

void OptionDialog::showEvent(QShowEvent *ev)
{
    ui.spinBoxThumb->setValue(maxff_);
    QDialog::showEvent(ev);
}
void OptionDialog::on_buttonBox_accepted()
{
    maxff_ = ui.spinBoxThumb->value();
}
