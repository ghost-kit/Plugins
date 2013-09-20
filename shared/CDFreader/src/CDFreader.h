#ifndef CDFREADER_H
#define CDFREADER_H

#include "CDFattribute.h"
#include "CDFvariable.h"
#include "CDFBadDataHandler.h"

#include <QString>
#include <QMap>
#include <QList>
#include <QVariant>



namespace CDFr
{

class CDFvariable;
class CDFattribute;
class CDFbadDataHandler;


class CDFreader
{
public:
    //creator/destructor
    CDFreader();
    ~CDFreader();

    //data related infromation
    /* Variables */
    QString           getVarName(int index);
    QStringList       getVarNames();
    int64_t           getNumberVariables();
    CDFvariable*      getVariable(int index);
    CDFvariable*      getVariable(QString name);

    /* Global Attributes */
    QString           getGlobalAttName(int index);
    QStringList       getGlobalAttNames();
    int64_t           getNumberGlobalAttributes();
    CDFattribute*     getGlobalAttribute(int index);
    CDFattribute*     getGlobalAttribute(QString name);


    //file related information
    QString     getFileName();
    QVariant    getCompressionType();
    QVariant    getChecksum();
    QVariant    getFormat();
    QVariant    getEncoding();
    QVariant    getCdfVersion();
    bool        isRowMajor();

    //handlers
    void        setBadDataHandler(CDFr::CDFbadDataHandler *handler);

protected:

    //File Related information
    QString     FileName;
    QVariant    CompressionType;
    QVariant    Format;
    QVariant    Checksum;
    QVariant    Encoding;
    QVariant    cdfVersion;
    bool        majority;

    //data related information
    QMap<QString, CDFvariable*>     Variables;
    QMap<QString, CDFattribute*>    Attributes;

    //Handlers
    CDFr::CDFbadDataHandler*              BadDataHandler;


private:

};
}


#endif //CDFREADER_H