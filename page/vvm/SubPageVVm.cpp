#include "SubPageVVm.h"
#include "SubPageVVm_p.h"

#include <qevent.h>
#include <qdebug.h>

SubPageVVm::SubPageVVm(QWidget* parent)
    : LifeCycleWidget(*new SubPageVVmPrivate, parent) {
    Q_D(SubPageVVm);
    d->init();
}

SubPageVVm::~SubPageVVm() {
}

void SubPageVVmPrivate::init() {
    Q_Q(SubPageVVm);
    bindView(q);

    modelHelper = new ModelHelper(getTableView());
    modelHelper->reset();
}

void SubPageVVmPrivate::clickedGotoPage2() {
    Q_Q(SubPageVVm);
    q->navigateTo("subpage2");
    q->finish();
}

void SubPageVVmPrivate::clickedBack() {
    Q_Q(SubPageVVm);
    q->navigateBack();
}

void SubPageVVmPrivate::resetModel() {
    modelHelper->reset();
}

void SubPageVVmPrivate::addData2Model() {
    const char* names[] = { "java", "c++", "c#", "python", "javascript" };
    static int i = 0;
    ItemData data;
    data.name = names[i++];
    data.phone = QString::number(i);
    data.age = i + 5;
    data.male = i % 2;
    modelHelper->append(data);
}

void SubPageVVmPrivate::updateModel() {
    modelHelper->update();
}

void SubPageVVmPrivate::editModel() {
    auto& editor = modelHelper->editRow(1);
    editor().name = editor().name + "_modified";
    editor().age = 666;
    editor.apply();
}

void SubPageVVmPrivate::updateInThread() {
    StrT s;
    s.data = strData2();
    s.a = 1;
    styleData = s;
    strData = s.data;
}
