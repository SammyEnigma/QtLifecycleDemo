#include "SubPageVVm.h"
#include "SubPageVVm_p.h"

#include <qevent.h>
#include <qdebug.h>

#include <qheaderview.h>

#include "../../livedata/AbstractModelHelper.h"

struct ItemData {
    QString name;
    QString phone;
    int age;
    bool male;
};

class ModelHelper : public AbstractModelHelpter<ItemData> {
public:
    using AbstractModelHelpter::AbstractModelHelpter;

protected:
    void data2View(const ItemData& data, int index, QStandardItem* item) override {
        if (index == 0) {
            item->setData(data.name, Qt::DisplayRole);
        } else if (index == 1) {
            item->setData(data.phone, Qt::DisplayRole);
        } else if (index == 2) {
            item->setData(data.age, Qt::DisplayRole);
        } else {
            item->setData(data.male, Qt::DisplayRole);
        }
    }

    void view2Data(ItemData& data, int index, const QStandardItem* item) override {
        if (index == 0) {
            data.name = item->data(Qt::DisplayRole).toString();
        } else if (index == 1) {
            data.phone = item->data(Qt::DisplayRole).toString();
        } else if (index == 2) {
            data.age = item->data(Qt::DisplayRole).toInt();
        } else {
            data.male = item->data(Qt::DisplayRole).toBool();
        }
    }

    QStringList getHeaders() override {
        return QStringList() << u8"姓名" << u8"电话" << u8"年龄" << u8"男";
    }

    void onHeaderCreated(int colSize) override {
        static_cast<QTableView*>(view)->horizontalHeader()->resizeSection(0, 120);
    }
};

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
