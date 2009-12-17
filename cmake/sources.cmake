# bursar sources
SET( bursar_SRCS
    src/main.cpp

    src/app/burapp.cpp
    src/app/mainwindow.cpp

    src/common/burobject.cpp
    src/common/bursql.cpp
    src/common/burdb.cpp
    src/common/burutils.cpp

    src/data/burdoc.cpp
    src/data/burdbcreationparams.cpp
    src/data/burdbcreator.cpp
    src/data/accounttreemodel.cpp
    src/data/journaltablemodel.cpp

    src/widgets/burcombobox.cpp

    src/wizards/newdocumentwizard.cpp
    src/wizards/newaccountwizard.cpp

    src/dialogs/transactiondialog.cpp
    src/dialogs/definecountriesdialog.cpp
    src/dialogs/definecurrenciesdialog.cpp
)
