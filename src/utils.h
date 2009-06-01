#ifndef UTILS_H
#define UTILS_H

#include <QString>

class Utils
{
public:
    /**
      * Add extension to filename
      */
    static QString addFileExtension(const QString &fileName, const QString &extension)
    {
        QString newFileName = fileName;

        if (newFileName != "") {
            if (newFileName.right(4).toUpper() != QString(".").append(extension).toUpper()) {
                if (newFileName.right(1) != ".") {
                    newFileName.append(".");
                }

                newFileName.append(extension);
            }
        }

        return newFileName;
    }
};

#endif // UTILS_H
