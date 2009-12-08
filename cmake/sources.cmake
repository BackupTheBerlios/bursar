# bursar sources
SET( bursar_SRCS
    src/main.cpp
    src/bursarapp.cpp
    src/mainwindow.cpp

    src/base/burobject.cpp
    src/base/bursql.cpp
    src/base/burdb.cpp
    src/base/burutils.cpp

    src/data/burdoc.cpp
    src/data/accounttreemodel.cpp
    src/data/journaltablemodel.cpp

    src/widgets/burcombobox.cpp

    src/wizards/newdatabasewizard.cpp
    src/wizards/newaccountwizard.cpp

    src/dialogs/transactiondialog.cpp
    src/dialogs/definecountriesdialog.cpp
    src/dialogs/definecurrenciesdialog.cpp
)
